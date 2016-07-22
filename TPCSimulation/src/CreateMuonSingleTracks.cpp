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
  TParticle* muon = new TParticle(13,1,0,0,0,0,0,0,0,0,0,0,0,0);
  TParticle* antimuon = new TParticle(-13,1,0,0,0,0,0,0,0,0,0,0,0,0);
  // Event loop section
  
  double array[175716];
  FILE* fin = fopen("/home/home2/institut_3b/muennich/TPCSimulation/TPCSimulation/inputs/muonenergy.dat","r");
  if(! fin) {  
    printf("Datei konnte nicht geoeffnet werden.\n");
    return 1;
  }
  int evts=0;
  while(!feof(fin)) {                    
    fscanf(fin,"%lf", &array[evts] );
    evts++;                            /* zaehle eingelesene Ereignisse */
    if(evts > 175716) {             /* ueberpruefe Feldgroesse */
         printf("Ereigniszahl ueberschreitet Feldgroesse %i\n", 175716);
         break;                            /* Verlasse while-Schleife */
    }
  }
  evts--;                               /* korrigiere Ereigniszahl */
  printf("%i Ereignisse eingelesen. \n", evts);
  fclose(fin);
  for(int i=0;i<events;i++)
    {
      int numberofmuons=1;
      for(int j=0;j<numberofmuons;j++)
	{
	  //dice starting point
	  double vx = 0.;
	  double vy = 0.;
	  double vz = 1.;
	  //dice energy
	  int rand = (int)175713*drand48();
	  double energy=500.;//array[rand];
	  
	  //double P = sqrt(energy*energy-MASS_M*MASS_M);
	  double P=energy;
	  double px=-P/(sqrt(2.0)*tan(86.0*M_PI/180.))+(-0.5+1.*drand48());
	  
	  double py=sqrt(P*P-px*px);
	  
	  double pz=py/tan(45.0*M_PI/180.);	 
	 
	  //double energy=sqrt(P*P+MASS*MASS);
	  //set TParticle values
	  muon->SetMomentum(px,py,pz,energy);
	  muon->SetProductionVertex(vx,vy,vz,0);
	  muon->SetStatusCode(1);
	  antimuon->SetMomentum(px,py,pz,energy);
	  antimuon->SetProductionVertex(vx,vy,vz,0);
	  antimuon->SetStatusCode(1);
	  TClonesArray &particle = *mcEvent;
	  double rnd = drand48();
	  // if(rnd<0.5)
	    new(particle[j]) TParticle(*muon);
	    // else
	    //  new(particle[j]) TParticle(*antimuon);
	  
      }
      tree->Fill();
      mcEvent->Clear();
    }

  tree->Write();
  file->Close();

}
