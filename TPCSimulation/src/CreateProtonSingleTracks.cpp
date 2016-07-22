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

#define MASS 0.938272
using namespace std;

int main(int argc, char* argv[]){

  if(argc != 4) 
    {
      cout << "Choose:"<<endl;
      cout<< "Number of Muonevents to be craeted" << endl;
      cout<< "Chamber Parameter: Radius [mm], Lenght [mm]"<<endl;
      exit(1);
    }

  int events=atoi(argv[1]);
  double radius=atof(argv[2])-1;
  double length=atof(argv[3]);
  
  const Int_t clonesarraysize = 100000; // size of TClonesArray to store generated particles
  gsl_rng *r=gsl_rng_alloc(gsl_rng_mt19937);
  char *outfilestring = new char[256]; 
  sprintf(outfilestring,"ProtonEvents_N%i_R%.0f_L%.0f.root",events,
	  (radius+1),length);                                 
  TFile* file = new TFile(outfilestring, "recreate");
  file->SetCompressionLevel(2);
  TTree* tree = new TTree("tree", "Eventtree");
  TClonesArray* mcEvent = new TClonesArray("TParticle", clonesarraysize);
  tree->Branch("MCEvent", &mcEvent);
  TParticle* muon = new TParticle(2212,1,10,10,10,10,0,0,0,0,0,0,0,10);
  // Event loop section

  for(int i=0;i<events;i++)
    {
      int numberofmuons=1;
      for(int j=0;j<numberofmuons;j++)
      {
	  //dice starting point
	  double vx = -0.1+0.2*drand48();
	  double vy = -sqrt(radius*radius-vx*vx);
	  double vz = 10.+0.1*drand48();
	  //dice energy
	  double energy=1.5;
	  double P = sqrt(energy*energy-MASS*MASS);
	  //split momentum in components
	  double pz=0;
	  //if(drand48()>0.5)
	  //pz=drand48()*P/10;
	  //else 
	  //pz=-drand48()*P/10;
	  double px=0;
	  //if(drand48()>0.5)
	  //px=sqrt(P*P-pz*pz)*0.2*drand48();
	  // else
	  //px=-sqrt(P*P-pz*pz)*0.4*drand48();
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
