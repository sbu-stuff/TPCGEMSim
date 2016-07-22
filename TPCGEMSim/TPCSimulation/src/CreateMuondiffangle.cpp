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

#define MASS 0.10566
using namespace std;

int main(int argc, char* argv[]){

  cout<<argc<<endl;
  if(argc != 4) 
    {
      cout << "Choose:"<<endl;
           cout<< "Number of Event,Chamber Parameter: Radius, Lenght"<<endl;
      exit(1);
    }
  int events=atoi(argv[1]);
  double radius=atof(argv[2])-1;
  double length=atof(argv[3]);
  
  const Int_t clonesarraysize = 100000; // size of TClonesArray to store generated particles
  //gsl_rng *r=gsl_rng_alloc(gsl_rng_mt19937);
  char *outfilestring = new char[256]; 
  sprintf(outfilestring,"MuonEvents_diffangle_R%.0f_L%.0f.root",
	  (radius+1),length);                                 
  TFile* file = new TFile(outfilestring, "recreate");
  file->SetCompressionLevel(2);
  TTree* tree = new TTree("tree", "Eventtree");
  TClonesArray* mcEvent = new TClonesArray("TParticle", clonesarraysize);
  tree->Branch("MCEvent", &mcEvent);
  TParticle* muon = new TParticle(13,1,10,10,10,10,0,0,0,0,0,0,0,10);
  // Event loop section
  
  for(int i=0;i<events;i++)
    {
      double P = 0.5; // momentum = 1Gb
      double pz=0;
      double energy=sqrt(P*P+MASS*MASS);
      
      muon->SetStatusCode(1);
      int numberofmuons=1;
      for(int j=0;j<numberofmuons;j++)
	{
	  double vx = -0.1+0.2*drand48();
	  double vy = -sqrt(radius*radius-vx*vx);
	  double vz = 150.+0.1*drand48();
	  muon->SetProductionVertex(vx,vy,vz,0);
	  
	  double px=0.;
	  double py=sqrt(P*P-px*px);
	  muon->SetMomentum(px,py,pz,energy);
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
