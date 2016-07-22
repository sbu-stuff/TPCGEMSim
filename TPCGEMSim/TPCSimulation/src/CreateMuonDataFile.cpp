#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <stdlib.h>
#include <iostream>
#include <TParticle.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <string>
#include "TClonesArray.h" // else error: forward declaration of ‘class TClonesArray’

#define MASS 0.10566
using namespace std;

int main(int argc, char* argv[]){

  if(argc != 5) 
    {
      cout << "Usage:"<<endl;
      cout<< "CreateMuonDataFile \"Number of Muonevents to be craeted\" \"tpc radius\" \"tpc length\" \"muonenergy.dat\" " << endl;
      exit(1);
    }

  int events=atoi(argv[1]);
  double radius=atof(argv[2])-1;
  double length=atof(argv[3]);
  const char *muonenergy=argv[4];
  const Int_t clonesarraysize = 100000; // size of TClonesArray to store generated particles
  gsl_rng *r=gsl_rng_alloc(gsl_rng_mt19937);
  char *outfilestring = new char[256]; 
  sprintf(outfilestring,"MuonEvents_N%i_R%.0f_L%.0f.root",events,
	  (radius+1),length);                                 
  TFile* file = new TFile(outfilestring, "recreate");
  file->SetCompressionLevel(2);
  TTree* tree = new TTree("tree", "Eventtree");
  TClonesArray* mcEvent = new TClonesArray("TParticle", clonesarraysize);
  tree->Branch("MCEvent", &mcEvent);
  TParticle* muon = new TParticle(13,1,10,10,10,10,0,0,0,0,0,0,0,10);
  // Event loop section
  
  double array[175715];
  FILE* fin = fopen(muonenergy,"r");
  if(! fin) {  
    printf("File with muon energies could not be opened.\n");
    return 1;
  }
  int evts=0;
  while(!feof(fin)) {                    
    fscanf(fin,"%lf", &array[evts] );
    evts++;                            
    if(evts > 175715) {             
         printf("Number of energies in file bigger than array! %i\n", 175715);
         break;                            
    }
  }
  
  fclose(fin);
  for(int i=0;i<events;i++)
    {
      //dice number of Muons in event
      double randgaus = gsl_ran_exponential(r,1.);
      //int numberofmuons=(int)(1+randgaus*drand48());
      int numberofmuons=1;
      if(numberofmuons<0 || numberofmuons==0) numberofmuons=1;
      if(i%100==0) 
	cout<<"Event: "<<i<<" with "<<numberofmuons<<" muons"<<endl;
      for(int j=0;j<numberofmuons;j++)
	{
	  //dice starting point
	  // double vx = -radius/2+radius*drand48();
	  double vx = -10+20*drand48();
	  double vy = -sqrt(radius*radius-vx*vx);
	  double vz = length*drand48();
	  //dice energy
	  int rand = (int)175713*drand48();
	  double energy=array[rand];
	  double P = sqrt(energy*energy-MASS*MASS);
	  //split momentum in components
	  double pz=0;
	  if(drand48()>0.5)
	    pz=drand48()*P/10;
	  else 
	    pz=-drand48()*P/10;
	  double px=0;
	  // if(drand48()>0.5)
	  if(vx<0)
	    px=sqrt(P*P-pz*pz)*0.4*drand48();
	  else
	    px=-sqrt(P*P-pz*pz)*0.4*drand48();
	  double py=sqrt(P*P-px*px-pz*pz);
	  //double energy=sqrt(P*P+MASS*MASS);
	  //set TParticle values
	  muon->SetMomentum(px,py,pz,energy);
	  muon->SetProductionVertex(vx,vy,vz,0);
	  muon->SetStatusCode(1);
	  TClonesArray &particle = *mcEvent;
	  new(particle[j]) TParticle(*muon);
	  //new(mcEvent[j]) muon;
	  //mcEvent[j]=muon;
      }
      tree->Fill();
      mcEvent->Clear();
    }

  tree->Write();
  file->Close();

}
