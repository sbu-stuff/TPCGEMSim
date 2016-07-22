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

#define MASS_M 0.10566 //muon 13
#define MASS_Pi 0.13957 //pion -211
#define MASS_K 0.493677 //kaon- -321
#define MASS_P 0.938272 //proton 2212
#define MASS_E 0.000511 //electron 11
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
  sprintf(outfilestring,"MuonEvents_N%i_R%.0f_L%.0f.root",events,
	  (radius+1),length);                                 
  TFile* file = new TFile(outfilestring, "recreate");
  file->SetCompressionLevel(2);
  TTree* tree = new TTree("tree", "Eventtree");
  TClonesArray* mcEvent = new TClonesArray("TParticle", clonesarraysize);
  tree->Branch("MCEvent", &mcEvent);
  TParticle* muon = new TParticle(11,1,10,10,10,10,0,0,0,0,0,0,0,10);
  // Event loop section
  
  for(int i=0;i<events;i++)
    {
      
      //int numberofmuons=(int)(1+randgaus*drand48());
      int numberofmuons=1;
      
      for(int j=0;j<numberofmuons;j++)
      {
	//starting point is interaction point
	double vx = 0;
	double vy = 0;
	double vz = 0;
	//dice energy
	double energy= MASS_E*exp(log(250./MASS_E)*drand48());
	double P = sqrt(energy*energy-MASS_E*MASS_E);
	//split momentum in components
	double pz=0.05;
	double px=0.005;//sin(0.75)*P+drand48()*(1-sin(0.75))*P;
	double py=sqrt(P*P-px*px-pz*pz);

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
