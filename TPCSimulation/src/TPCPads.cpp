//*****************************************************
// Part of program to simulate a TPC with GEM readout *
//                                                    *
// Author: Astrid Muennich                            *
//                                                    *
//   Astrid Muennich                                  *
//   RWTH Aachen, III. Phys. Inst. B                  * 
//   Office: 28 A 112, Phone: +49/(0)241/8            *
//   Email: muennich@physik.rwth-aachen.de            * 
//                                                    *
//*****************************************************



#include <TROOT.h>
#include <fstream>
#include <iostream>
#include <TFile.h>
#include <TClonesArray.h>
#include "TPCElectron.h"
#include "TPCSimTrack.h"
#include <stdio.h> 
#include <TTree.h>
#include <string>
#include "TPCSimChannel.h"
#include "TrackDrifter.h"
#include "TPCVoxel.h"
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "MakePads.h"
#include <math.h>
#include "RunParameterInfo.h"
#include "GeometryInfo.h"
#include <TString.h>

using namespace std;

/** Structure defines sorting criteria for sorting the vector containing the voxels. */
struct SAscendingSort
{

     bool operator()(TPCVoxel rpStart, TPCVoxel rpEnd)
     {
       return (rpStart.GetVoxelChanNr() < rpEnd.GetVoxelChanNr()) ||
	 ((rpStart.GetVoxelChanNr() <= rpEnd.GetVoxelChanNr())  && 
	  (rpStart.GetVoxelTime() < rpEnd.GetVoxelTime()));
     }
};


/** Programm to sort drifted electrons into voxel
    and amplify them with GEM structure
*/
int main(int argc, char* argv[]){
 
  if(argc != 16) 
    {
      cout << "Usage:"<<endl;
      cout<< "TPCPads \"TPCDrift file\" \"pad width[mm]\" "
	  << "\"pad height[mm]\" \"number of pads\" \"pads in row\" \"padshift in x\""
	  <<" \"padshift in y\" \"GEM Setting (6 parameters)\" \"charge transfer file\" \"gain factor\" "<<endl;
      exit(1);
    }
  const char* infilestring = argv[1]; 
  
  double padwidth = 0.;
  double padheight = 0.;
  int returnpadx = sscanf( argv[2],"%lf",&padwidth);
  int returnpady = sscanf( argv[3],"%lf",&padheight);
  if ( returnpadx==0 || returnpady==0 || padwidth<0 || padheight<0)
    {
      cout<<"Pad width and pad height must be a positiv number!"<<endl;
       exit(1);
    }
  int npads = 0;
  int padsinrow = 0;
  int returnpads =  sscanf( argv[4],"%i",&npads);
  int returnpadrows =  sscanf( argv[5],"%i",&padsinrow);
  if ( returnpads==0 || returnpadrows==0 || npads<0 || padsinrow<0)
    {
      cout<<"Number of pads and pads in row must be a positiv integer!"<<endl;
       exit(1);
    }
  double padshift_x=0.;
  double padshift_y=0.;
  int returnshiftx = sscanf( argv[6],"%lf",&padshift_x);
  int returnshifty = sscanf( argv[7],"%lf",&padshift_y);
  if ( returnshiftx==0 || returnshifty==0 )
    {
      cout<<"Shift in x and y must be a number!"<<endl;
       exit(1);
    }
  double setting[7];
  //Gem setting:
  setting[1]=atof(argv[8]);
  setting[2]=atof(argv[9]);
  setting[3]=atof(argv[10]);
  setting[4]=atof(argv[11]);
  setting[5]=atof(argv[12]);
  setting[6]=atof(argv[13]);
  int return1 = sscanf( argv[8],"%lf",&setting[1]);
  int return2 = sscanf( argv[9],"%lf",&setting[2]);
  int return3 = sscanf( argv[10],"%lf",&setting[3]);
  int return4 = sscanf( argv[11],"%lf",&setting[4]);
  int return5 = sscanf( argv[12],"%lf",&setting[5]);
  int return6 = sscanf( argv[13],"%lf",&setting[6]);
  if(return1==0 || return2==0 || return3==0 || return4==0 || return5==0 || return6==0
     || setting[1]<0 || setting[2]<0 || setting[3]<0 || setting[4]<0 || setting[5]<0 
     || setting[6]<0)
    {
      cout<<"All Fields and voltages must be positiv numbers!"<<endl;
       exit(1);
    }
  char *paramfile=argv[14]; // file with charge transfer coefficients
  double gain_factor=atof(argv[15]);

  TFile *infile=new TFile(infilestring, "READ"); // open File with TPCSimTracks
  if (infile==NULL)
    { cout << "Error, could not open infile: "<<infilestring<<endl;
    return -1;
    }
  else
    cout<<"Opened "<<infilestring<<endl;
  
  // now open the input tree
  TTree *DriftTree = (TTree*)infile->Get("Tree");
  TPCSimTrack *in_track=NULL;
  DriftTree->SetBranchAddress("DriftTrack",&in_track);
  TPCElectron *electron=NULL;
  RunParameterInfo *InfoRun = (RunParameterInfo*)infile->Get("RunParameterInfo;1"); 
  GeometryInfo *InfoGeom = (GeometryInfo*)infile->Get("GeometryInfo;1"); 
  double TPCRadius=InfoGeom->GetTPCRadius();
  double TPCInnerRadius=InfoGeom->GetTPCInnerRadius();
  const char* gas=InfoRun->GetGas();
  double Efield=InfoRun->GetEDrift();
  double Bfield=InfoRun->GetBField();
  double Length=InfoGeom->GetTPCLength();
  double driftdistance=Length;  
  setting[0]=Efield; //make sure Driftfield is same as in drift simulation
  
  //Output Tree
  char *outfilestring = new char[256]; 
  const char* middleend=(strchr(infilestring,'B')-1);
  string middle =string(middleend).substr(0,strlen(middleend)-5);
  sprintf(outfilestring,"TPCPads%s_px%.1f_py%.1f.root",middle.c_str(),padwidth,padheight);
  
  TPCSimChanEvent::Class()->IgnoreTObjectStreamer(); //whatever this does...
  TPCSimChannel::Class()->IgnoreTObjectStreamer(); //whatever this does...
  TPCSimPeak::Class()->IgnoreTObjectStreamer(); //whatever this does...
  TFile *outfile = new TFile(outfilestring,"RECREATE");
  outfile->SetCompressionLevel(1);
  TTree *outtree = new TTree("TimeTree","TimeEventTree");
  outtree->SetAutoSave(1000000000);  // autosave when 1 Gbyte written
  TPCSimChanEvent *chanevent = new TPCSimChanEvent();
  TBranch *chaneventbranch = outtree->Branch("TimeChanEvent","TPCSimChanEvent",&chanevent,  32000 ,0);
  chaneventbranch->SetAutoDelete(kFALSE);
 
    
  TrackDrifter *makedrift = new TrackDrifter(gas, Bfield,Efield,driftdistance,TPCRadius,TPCInnerRadius);
  makedrift->InitializeDriftValues();
  double vdrift=makedrift->GetDriftVelocity();

  //diffusion between GEMS
  TrackDrifter *etrans1 = new TrackDrifter(gas, Bfield,setting[2],driftdistance,TPCRadius,TPCInnerRadius);
  TrackDrifter *etrans2 = new TrackDrifter(gas, Bfield,setting[4],driftdistance,TPCRadius,TPCInnerRadius);
  TrackDrifter *eind = new TrackDrifter(gas, Bfield,setting[6],driftdistance,TPCRadius,TPCInnerRadius);
  etrans1->CalculateTransverseDiffusion();
  double difftrans1=etrans1->GetDiffTrans();
  etrans2->CalculateTransverseDiffusion();
  double difftrans2= etrans2->GetDiffTrans();
  eind->CalculateTransverseDiffusion();
  double diffind =eind->GetDiffTrans();
  //this is for a GEM setup with 2 mm between the GEMs
  double sigma = 1./1000*sqrt((0.2*difftrans1*difftrans1+0.2*difftrans2*difftrans2+
			       0.2*diffind*diffind)); // in mm
 
  int columns = padsinrow;
  int rows = (npads/padsinrow);
  //offsets accounts for possible shift of pad plane realtive to chamber center
  double activeareaoffsetx = 0.5*padwidth*columns-padshift_x; 
  // attention: y and x axis are in different direction between chamber and simulation
  // because of not centered pad plane in chamber
  double activeareaoffsety = 0.5*padheight*rows+padshift_y; 
  cout <<npads<<" Pads in "<<rows<<" rows and "<<columns<<" columns."<<endl;
  cout<<"Offset of Active Area in x: "<<-activeareaoffsetx<<" in y: "<<-activeareaoffsety<<endl;

  InfoRun->SetInputfile(infilestring);  
  InfoRun->SetParamFile(paramfile);
  InfoRun->SetETrans1(setting[2]);
  InfoRun->SetETrans2(setting[4]);
  InfoRun->SetEInd(setting[6]);
  InfoRun->SetUGem1(setting[1]);
  InfoRun->SetUGem2(setting[3]);
  InfoRun->SetUGem3(setting[5]);
  InfoRun->SetGainFactor(gain_factor);
  
  InfoGeom->SetPadWidth(padwidth);
  InfoGeom->SetPadHeight(padheight);
  InfoGeom->SetPadsInRow(padsinrow);
  InfoGeom->SetNPads(npads);
  InfoGeom->SetActiveAreaXOffset(-activeareaoffsetx);
  InfoGeom->SetActiveAreaYOffset(-activeareaoffsety);
  InfoGeom->SetCylinderXOffset(0);
  InfoGeom->SetCylinderYOffset(0);

  InfoRun->Write();
  InfoGeom->Write();

  
  double drifttime=driftdistance/vdrift;
  
  MakePads *amplification = new MakePads(sigma,npads,activeareaoffsetx,activeareaoffsety,columns,
					 padheight,padwidth,drifttime,
					 Bfield,setting,paramfile,gain_factor,gas);
  TPCVoxel *voxel = new TPCVoxel();
  vector<TPCVoxel> voxelvector;  
  
  int hitbymoreparticles=1;
  int nelectrons=0;
  
  for (int i=0;i<DriftTree->GetEntries();i++)
    { 
      DriftTree->GetEvent(i);     
      int event = in_track->GetEventNumber();     
      int particlenumber =  in_track->GetParticleNumber();   
      bool isCurler = in_track->GetCurlerStatus();
 
      for(int j=0;j<in_track->GetNumberOfElectrons();j++)
	{
	  electron=in_track->GetTPCElectron(j);
	  if(electron->GetZ()>=0)  //only one readout plane
	    {
	      double x=electron->GetX(); 
	      double y=electron->GetY();
	      double t=electron->GetTime();
	      // check if electron is on padplane
	      if(x>=-activeareaoffsetx && x<=activeareaoffsetx+padwidth*columns && 
		 y>=-activeareaoffsety && y<=activeareaoffsety+padheight*rows)
		{
		  
		  
		  amplification->Amplify(event,x,y,t,voxel,&voxelvector,particlenumber,isCurler);
		  nelectrons++;
		  
		}
	    }
	}

      if(i+1<DriftTree->GetEntries())
	{
	  DriftTree->GetEvent(i+1);
	  if(event==in_track->GetEventNumber()) 
	    continue;  //fill voxelvector as long as event not ended
	}
      
      // sort voxel_vector to be able to add up the same voxels
      // not very elegant, better would be a list or a tree
       stable_sort(voxelvector.begin(), voxelvector.end(), SAscendingSort());
 
      int sumq =0;
      int lasttime=0;
      int lastchannel=0;
      int lastparticlenumber=0;
      //loop over vector and add up charge of identical voxels
      for (int k=0;k<(int)voxelvector.size();k++)
	{
	  int time = voxelvector[k].GetVoxelTime();
	  long int channr=voxelvector[k].GetVoxelChanNr();
	  int charge=voxelvector[k].GetVoxelCharge();
	  int particlenumber=voxelvector[k].GetParticleNr();
	  
	  if(k==0)
	    {
	      sumq=charge;
	      lasttime=time;
	      lastchannel=channr;
	      lastparticlenumber=particlenumber;
	    }
	  else
	    {
	      if(channr==lastchannel && time==lasttime)
		 {
		   sumq+=charge;
		   if(!(particlenumber==lastparticlenumber))
		     hitbymoreparticles++;
		 }
	      else
		{
		  if(sumq > 0)
		    {
		      chanevent->AddChanPeak(lastchannel,sumq,0,0,
					     lasttime,0,0,0,lastparticlenumber,
					     hitbymoreparticles);
		    }
		  sumq=charge;
		  hitbymoreparticles=1;
		}
	      if(sumq<0)cout<<"WARNING sumq<0"<<endl;
	      lasttime=time;
	      lastchannel=channr;
	      lastparticlenumber=particlenumber;
	    }
	}
       
      if(event%100==0) 
	cout<<"Event "<<event<<" done with "<<nelectrons<<" electrons."<<endl;      
      chanevent->SetTrigger(event);
      if(chanevent->GetNChan())
	  outtree->Fill();
      nelectrons=0;
      // cleaning up memory
      chanevent->Delete();
      delete chanevent;
      chanevent = new TPCSimChanEvent();
      voxelvector.clear();
      
      
    }
  outfile = outtree->GetCurrentFile();
  cout<<"Entries in tree: "<<outtree->GetEntries()<<endl;
  outfile->Write();
  outfile->Close();
  cout<<"MAKING PADS FINISHED"<<endl;
}

