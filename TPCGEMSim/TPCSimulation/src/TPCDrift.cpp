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

/*! Programm to drift electrons in specified gas over certain
   distance.
*/

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
#include "TrackDrifter.h"
#include "RunParameterInfo.h"
#include "GeometryInfo.h"
#include <TString.h>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc != 4) {
    cout << "Usage:"<<endl;
    cout<< "TPCDrift \"TPCIonisation file\" \"Gas (TDR,P5,P10)\" \"electric Field [V/cm]\" " << endl;
    exit(1);
  }
  const char* infilestring = argv[1]; 
  const char* gas = argv[2];
  if(strcmp(gas,"TDR")!=0 && strcmp(gas,"P5")!=0 && strcmp(gas,"P10")!=0 )
    {
      cout<<"Gas choices are TDR, P5, P10!"<<endl;
      exit(1);
    }
  double Efield = atof(argv[3]);
  int returnE = sscanf( argv[3],"%lf",&Efield);
  if(returnE==0 || Efield <0)
    {
      cout<<"Drift field must be a positive number!"<<endl;
       exit(1);
    }
  //Input Tree
  TFile *infile=new TFile(infilestring, "READ"); // open File with TPCSimTracks
  if (infile==NULL)
    { cout << "Error, could not open file: "<<infilestring<<endl;
    return -1;
    }
  else
    cout<<"Opened "<<infilestring<<endl;
  // now open the input tree
  TTree *SimTree = (TTree*)infile->Get("Tree");
  TPCSimTrack *in_track=NULL;
  SimTree->SetBranchAddress("Track",&in_track);
  TPCElectron *electron;
  
  RunParameterInfo *RunInfo = (RunParameterInfo*)infile->Get("RunParameterInfo"); 
  GeometryInfo *GeomInfo = (GeometryInfo*)infile->Get("GeometryInfo"); 
  double Bfield=RunInfo->GetBField();
  if(Bfield > 5)
    cout<<"Correct transverse diffusion only garanteed up to B=5T!"<<endl;
  double Radius=GeomInfo->GetTPCRadius();
  double inner_radius=GeomInfo->GetTPCInnerRadius();
  double Length=GeomInfo->GetTPCLength();
  double driftdistance=Length;
   
  //Output Tree
  char *outfilestring = new char[256]; 
  sprintf(outfilestring,"TPCDrift_B%.1f_R%.0f_L%.0f_E%.0f_%s.root",Bfield,
	  Radius,Length,Efield,gas);
  TFile *outfile = new TFile(outfilestring,"RECREATE");
  outfile->SetCompressionLevel(1);
  TTree *outtree = new TTree("Tree","DriftTree");
  outtree->SetAutoSave(1000000000);  // autosave when 1 Gbyte written
  TPCSimTrack *drifttrack = new TPCSimTrack();
  TBranch *driftbranch = outtree->Branch("DriftTrack", "TPCSimTrack", &drifttrack);
  driftbranch->SetAutoDelete(kFALSE);
  
  TrackDrifter *makedrift = new TrackDrifter(gas, Bfield,Efield,driftdistance,Radius,inner_radius);
  makedrift->InitializeDriftValues();

  RunInfo->SetInputfile(infilestring);
  RunInfo->SetGas(gas);
  RunInfo->SetEDrift(Efield);
  RunInfo->SetVDrift(makedrift->GetDriftVelocity());
  RunInfo->SetDiffLong(makedrift->GetDiffLong());
  RunInfo->SetDiffTrans(makedrift->GetDiffTrans());
  RunInfo->SetPressure(1013.25);
  RunInfo->SetTemperature(295);
  RunInfo->Write();
  GeomInfo->Write();
  int entries=SimTree->GetEntries();
 //loop over tracks
  for (int i=0; i<entries;i++)
    {
      SimTree->GetEvent(i);
      makedrift->GetTrackParameter(in_track);
      makedrift->InitializeNumberElectrons();
      if(i%100==0)
	cout<<in_track->GetNumberOfElectrons()<<" electrons on track: "<<i<<endl;
      //electron loop
      for(int j=0;j<in_track->GetNumberOfElectrons();j++)
	{
	  electron=in_track->GetTPCElectron(j);
	  makedrift->GetElectronCoordinates(electron);
	  makedrift->DriftElectron(drifttrack);
	}//e-
      makedrift->SetTrackParameter(drifttrack);
      if(drifttrack->GetNumberOfElectrons())
	outtree->Fill();
      in_track->Clear();
      drifttrack->Clear();
    }//tracks
  
  outfile = outtree->GetCurrentFile();
  outfile->Write();
  outfile->Close();

  cout<<"DRIFTING FINISHED"<<endl;
}//main
