#include <TROOT.h>
#include <fstream.h>
#include <iostream.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TParticle.h>
#include "TPCElectron.h"
#include "TPCSimTrack.h"
#include "RunParameterInfo.h"
#include "GeometryInfo.h"
#include <stdio.h> 
#include <iostream.h>
#include <TTree.h>
#include <fstream.h>
#include <string>
#include "TPCEvent.h"


int main(int argc, char* argv[])
{
  if(argc != 2) {
    cout << "Choose: TPCSimulation InputFile"<<endl;
    exit(1);
  }
  const char* infilestring = argv[1]; 
  
  //Input Tree
  TFile *infile=new TFile(infilestring, "READ"); // open File with TPCTracks
  if (infile==NULL)
    { cout << "Error, could not open infile: "<<infilestring<<endl;
    return -1;
    //exit(1);
    }
  else
    cout<<"Opened "<<infilestring<<endl;
  
  // now open the input tree
  TTree *SimTree = (TTree*)infile->Get("Tree");
  TPCSimTrack *in_track=NULL;
  SimTree->SetBranchAddress("Track",&in_track);
  TPCElectron *electron;
  RunParameterInfo *InfoRun = (RunParameterInfo*)infile->Get("RunParameterInfo"); 
  GeometryInfo *InfoGeom = (GeometryInfo*)infile->Get("GeometryInfo"); 
  double Length=InfoGeom->GetTPCLength();
  //double vdrift=InfoRun->GetVDrift();
  
  //double Length=2500.;
  double vdrift=44.7989;
//Output Tree
  char *outfilestring = new char[256]; 
  sprintf(outfilestring,"%s_MartinsFormat.root",infilestring);
  TFile *outfile = new TFile(outfilestring,"RECREATE");
  outfile->SetCompressionLevel(1);
  TTree *outtree = new TTree("Tree","TPCEvent");
  outtree->SetAutoSave(1000000000);  // autosave when 1 Gbyte written
  TPCEvent *tpcevent = new TPCEvent();
  TBranch *tpcbranch = outtree->Branch("TPCEvent", "TPCEvent", &tpcevent);
  tpcbranch->SetAutoDelete(kFALSE);
  
//  write the info files
  InfoGeom->Write();
    InfoRun->Write();
/*
  double particle[4];

   FILE* fin = fopen("primion.dat","r");
   if(! fin) {                             
       printf("Datei konnte nicht geoeffnet werden.\n");
       return 1;                           
   }

// Einlesen der Daten 
   int events = 0;                         
   while(!feof(fin)) {                     
                                           
      fscanf(fin,"%lf %lf %lf %lf" ,
	     &particle[0],
	     &particle[1],
	     &particle[2],
	     &particle[3]);
      if(events%10==0)
      tpcevent->AddPoint(particle[1],particle[2],
			 (Length-particle[3]),0,0,0,0,0,0);
      events++;
   }

   tpcevent->SetTrigger(0);
   outtree->Fill();
   tpcevent->Clear();
   */
   
    //for (int i=0; i<SimTree->GetEntries();i++)
    for (int i=0; i<100;i++)
    {
      SimTree->GetEvent(i);
      int eventnr=in_track->GetEventNumber();
     
      for(int j=0;j<in_track->GetNumberOfElectrons();j++)
	{
	  electron=in_track->GetTPCElectron(j);
	  if(j%100==0)
	  tpcevent->AddPoint(electron->GetX(),electron->GetY(),
			     (Length-electron->GetZ()),0,0,0,0,0,0);
	}
      if(i+1<SimTree->GetEntries())
	{
	  SimTree->GetEvent(i+1);
	  if(eventnr==in_track->GetEventNumber()) 
	    continue;  
	}
      
      tpcevent->SetTrigger(eventnr);
      outtree->Fill();
      //cout<<"after "<<i<<" tracks event "<< eventnr<<" done"<<endl;
      tpcevent->Clear();
            
      //in_track->Clear();
    }
   
  outfile->Write();
  outfile->Close();
  
}
