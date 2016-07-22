#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <stdlib.h>
#include <iostream.h>
#include <TParticle.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <string>

//#define MASS 0.10566
#define MASS 0.000511

int main(int argc, char* argv[]){

  cout<<argc<<endl;
  if(argc != 3) 
    {
      cout << "Choose:"<<endl;
           cout<< "Chamber Parameter: Radius [mm], Lenght [mm]"<<endl;
      exit(1);
    }

  double radius=atof(argv[1])-5;
  double length=atof(argv[2]);
  
  const Int_t clonesarraysize = 100000; // size of TClonesArray to store generated particles
  //gsl_rng *r=gsl_rng_alloc(gsl_rng_mt19937);
  char *outfilestring = new char[256]; 
  sprintf(outfilestring,"MuonEvents_differentz_R%.0f_L%.0f.root",
	  (radius+5),length);                                 
  TFile* file = new TFile(outfilestring, "recreate");
  file->SetCompressionLevel(2);
  TTree* tree = new TTree("tree", "Eventtree");
  TClonesArray* mcEvent = new TClonesArray("TParticle", clonesarraysize);
  tree->Branch("MCEvent", &mcEvent);
  TParticle* muon = new TParticle(-11,1,10,10,10,10,0,0,0,0,0,0,0,10);
  // Event loop section
  
  for(int i=0;i<13000;i++)
    {
      double P = 3.0; // momentum = 1Gb
      double pz=0.0001;
      double px=-0.04+drand48()*0.8;
      double py=sqrt(P*P-px*px-pz*pz);
      double energy=sqrt(P*P+MASS*MASS);
      muon->SetMomentum(px,py,pz,energy);
      muon->SetStatusCode(1);
      int numberofmuons=1;
      for(int j=0;j<numberofmuons;j++)
	{
	  // muon->SetProductionVertex(-40.,-118.,length*drand48(),0);
	  
	  if(i<1000)
	    muon->SetProductionVertex(-20+drand48()*40,-radius,231+drand48()*10,0);	  
	  if(i>=1000 && i<2000)
	    muon->SetProductionVertex(-20+drand48()*40,-radius,211+drand48()*10,0);
	  if(i>=2000 && i<3000)
	    muon->SetProductionVertex(-20+drand48()*40,-radius,186+drand48()*10,0);
	  if( i>=3000 && i<4000)
	    muon->SetProductionVertex(-20+drand48()*40,-radius,166+drand48()*10,0);
	  if( i>=4000 && i<5000)
	    muon->SetProductionVertex(-20+drand48()*40,-radius,162+drand48()*10,0);
	  if( i>=5000 && i<6000)
	    muon->SetProductionVertex(-20+drand48()*40,-radius,142+drand48()*10,0);
	  if( i>=6000 && i<7000)
	    muon->SetProductionVertex(-20+drand48()*40,-radius,117+drand48()*10,0);
	  if( i>=7000 && i<8000)
	    muon->SetProductionVertex(-20+drand48()*40,-radius,112+drand48()*10,0);
	  if( i>=8000 && i<9000)
	    muon->SetProductionVertex(-20+drand48()*40,-radius,96+drand48()*10,0);
	  if( i>=10000 && i<11000)
	    muon->SetProductionVertex(-20+drand48()*40,-radius,92+drand48()*10,0);
	  if( i>=11000 && i<12000)
	    muon->SetProductionVertex(-20+drand48()*40,-radius,66+drand48()*10,0);
	  if( i>=12000 && i<13000)
	    muon->SetProductionVertex(-20+drand48()*40,-radius,42+drand48()*10,0);
      
	  
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
