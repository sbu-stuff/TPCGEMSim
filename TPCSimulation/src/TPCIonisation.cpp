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

/*! Programm to simulate electron production and create a track.*/

#include <TROOT.h>
#include <fstream>
#include <iostream>
#include <string>
#include <TH1F.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <stdio.h> 
#include "HepInterface.h"
#include "TPCElectron.h"
#include "TPCSimTrack.h"
#include "MakePrimaryIonisation.h"
#include "RunParameterInfo.h"
#include "GeometryInfo.h"

using namespace std;

int main(int argc, char* argv[])
{
  //bool to mark low momentum particles as curler 
  bool fullCurler=false;
  switch (argc)
    {
    case 7: break;
    case 8: if ( !strcmp( argv[7], "--full_curler") )
	{
	  fullCurler=true;
	  break;
	}
    default:
      cout<<"Usage: \n"<<"TPCIonisation \"PYTHIA_inputfile\" \"TPC length [mm]\" "<<
	"\"TPC radius [mm]\" \"TPC inner radius [mm]\" \"magnetic field [T]\" \"clusterinfofile\" \"--full_curler\" "
	  <<endl;
      return(1);
    }
  //read in user input
  char *clusterfile=argv[6];
  char *infilestring = argv[1];
  double TPCHalfLength=0.;
  int returnL = sscanf( argv[2],"%lf",&TPCHalfLength);
  if(returnL==0 || TPCHalfLength <0)
    {
      cout<<"Length of TPC must be a positiv number!"<<endl;
      exit(1);
    }
  double TPCRadius = 0.;
  int returnR = sscanf( argv[3],"%lf",&TPCRadius);
  if(returnR==0 || TPCRadius <0)
    {
      cout<<"Radius of TPC must be a positiv number!"<<endl;
      exit(1);
    }
  double inner_radius = 0.;
  int returnRI = sscanf( argv[4],"%lf",&inner_radius);
  if(returnRI==0 || inner_radius <0)
    {
      cout<<"Inner Radius of TPC must be a positiv number!"<<endl;
      exit(1);
    }
  
  double B = 0.;
  int returnB = sscanf( argv[5],"%lf",&B);
  if(returnB==0 || B <0)
    {
      cout<<"Magnetic field must be a positiv number!"<<endl;
      exit(1);
    }
    
  //Output Tree
  char *outfilestring = new char[256];
  sprintf(outfilestring,"TPCIonisation_B%.1f_R%.0f_L%.0f.root",B,TPCRadius,TPCHalfLength);
  TFile *outfile = new TFile(outfilestring,"RECREATE");
  outfile->SetCompressionLevel(1);
  TTree *outtree = new TTree("Tree","Sim Tree");
  outtree->SetAutoSave(1000000000);  // autosave when 1 Gbyte written
  TPCSimTrack *track = new TPCSimTrack();
  TBranch *branch = outtree->Branch("Track", "TPCSimTrack", &track);
  branch->SetAutoDelete(kFALSE);
  
  RunParameterInfo *InfoRun = new RunParameterInfo();
  InfoRun->SetInputfile(infilestring);
  InfoRun->SetBField(B);
  GeometryInfo *InfoGeometry = new GeometryInfo();
  InfoGeometry->SetTPCRadius(TPCRadius);
  InfoGeometry->SetTPCInnerRadius(inner_radius);
  InfoGeometry->SetTPCLength(TPCHalfLength);
  InfoRun->Write();
  InfoGeometry->Write();
  
  //Input Tree  
  const char* filename = infilestring;
  TClonesArray *rootEvent;
  TParticle *rootParticle;
  // read in particles with interface
  HepInterface* Hep = new HepInterface(filename);
  MakePrimaryIonisation *primionisation = new MakePrimaryIonisation(B,TPCHalfLength,TPCRadius,inner_radius);
  //read in file with information about #e- in cluster
  primionisation->ReadClusterInfoFile(clusterfile);
  
  // the event loop
  for (int i=0; i<Hep->GetTree()->GetEntries();i++)
    {
      int totalnumberofelectrons=0;
      rootEvent = Hep->GetEvent(i);
      
      //particle loop
      for(int j=0;j<rootEvent->GetEntries();j++)
	{
	  //Marking low pt and low pz particles as curler
	  bool isCurler=false;
	  rootParticle = (TParticle*)rootEvent->At(j);
	  if(!fullCurler)
	    {
	      if(sqrt(rootParticle->Px()*rootParticle->Px()+rootParticle->Py()*rootParticle->Py())<1 && 
		 atan(sqrt(rootParticle->Px()*rootParticle->Px()+rootParticle->Py()*rootParticle->Py())/(fabs(rootParticle->Pz())))*180/M_PI > 88 )
		isCurler=true;
	    }
	  
	  if ((rootParticle->GetStatusCode()==1) && //only stable particles
	      ((rootParticle->GetPDG()->Charge())!=0))
	    {
	      primionisation->CreateTrack(i,j,track,rootParticle,isCurler);
	      if(track->GetNumberOfElectrons())
		outtree->Fill();
	      track->Clear();
	    }//if particle ok
	  totalnumberofelectrons+=primionisation->GetTotalNumberOfElectrons();
	}//particle loop
      
      if(i%100==0)
	{
	  cout<<"Event "<<i<<" with "<<rootEvent->GetEntries()<<" particle(s) and "      
	      <<totalnumberofelectrons<<" electrons"<<endl;
	}
      
    }//event loop
  outfile = outtree->GetCurrentFile();
  outfile->Write();
  outfile->Close();
  cout<<"TPCIONISATION FINISHED"<<endl;
}// main
