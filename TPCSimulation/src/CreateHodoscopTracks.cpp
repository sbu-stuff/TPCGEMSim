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
#include <TiH.h>
#include <calibrationOperations.h>
#include <TPCEvent.h>
#include <TTrackMaker.h>
#include <hodoscopeCorrelation.h>
#include <GeometryInfo.h>
#include <TPCCorrelation.h>

using namespace std;

//#define MASS 0.10566
#define MASS 0.000511

int main(int argc, char* argv[]){
  
  if(argc != 7) {
    cout << "Choose inputfiles: calibration hodoscopecorrelation tpccorrelation hodoscopedata tpctracks energy" << endl;
    exit(1);
  }
  const char *calibration=argv[1];
  const char *hodcorrelation=argv[2];
  const char *tpccorrelation=argv[3];
  const char *hodoscopdata =argv[4];
  const char *tpctracks = argv[5];
  
  double energy = atof(argv[6]);

  TFile *cal=new TFile(calibration, "READ");
  TFile *hodcorr=new TFile(hodcorrelation, "READ");
  TFile *tpccorr=new TFile(tpccorrelation, "READ");
  TFile *hoddata=new TFile(hodoscopdata , "READ");
  TFile *tpctrack=new TFile(tpctracks, "READ");

  
  GeometryInfo *geoInfo = (GeometryInfo*)tpctrack->Get("GeometryInfo");
  TiH *myTiH=(TiH*)cal->Get("TiH");
  TPCCorrelation TPCCorr;
  hodoscopeCorrelation HodCorr;
  TTrackMaker *trackmaker=NULL;
  TTree *TPCCorrTree = (TTree*)tpccorr->Get("CorrTree"); 
  TPCCorrTree->SetBranchAddress("TPCCorrelation",&TPCCorr);
  TTree *HodCorrTree = (TTree*)hodcorr->Get("HodCorrTree");
  HodCorrTree->SetBranchAddress("hodoscopeCorrelation",&HodCorr);
  TTree *HodTrackTree = (TTree*)hoddata->Get("tree_tracks");
  HodTrackTree->SetBranchAddress("Tracks",&trackmaker);
  
  
  const Int_t clonesarraysize = 100000; // size of TClonesArray to store generated particles
  // gsl_rng *r=gsl_rng_alloc(gsl_rng_mt19937);
  TFile* file = new TFile("HodoskopSpuren.root", "recreate");
  file->SetCompressionLevel(2);
  TTree* tree = new TTree("tree", "Eventtree");
  TClonesArray* mcEvent = new TClonesArray("TParticle", clonesarraysize);
  tree->Branch("MCEvent", &mcEvent);
  TParticle* muon = new TParticle(-11,1,10,10,10,10,0,0,0,0,0,0,0,10);
  // Event loop section
  
  int inevents=175800;
  double array[inevents];
  if(energy==0)
    {
      FILE* fin = fopen("/home/home2/institut_3b/muennich/TPCSimulation/TPCSimulation/inputs/muonenergy.dat","r");
      if(! fin) {  
	printf("Datei konnte nicht geoeffnet werden.\n");
	return 1;
      }
      int evts=0;
      while(!feof(fin)) {                    
	fscanf(fin,"%lf", &array[evts] );
	evts++;                            /* zaehle eingelesene Ereignisse */
	if(evts > inevents) {             /* ueberpruefe Feldgroesse */
	  printf("Ereigniszahl ueberschreitet Feldgroesse %i\n", inevents);
	  break;                            /* Verlasse while-Schleife */
	}
      }
      evts--;                               /* korrigiere Ereigniszahl */
      printf("%i Ereignisse eingelesen. \n", evts);
      fclose(fin);
    }
 

  //calculate z_0 offset of TPC (from GEM to anode)
  double z0_hod=myTiH->GEM1Position-60.*myTiH->chamberPosition; //60 mm mechanical offset
  double z0=(z0_hod-myTiH->zOffset)/(cos((myTiH->deltaPhiZY)/1000.0)*cos((myTiH->deltaPhiXZ)/1000.0));
  //cout<<z0_hod<<"  "<<z0<<"  "<<(cos((myTiH->deltaPhiZY)/1000.0)*cos((myTiH->deltaPhiXZ)/1000.0))<<endl;
  
  for(int trigger=0;trigger<(myTiH->badTriggers).GetSize();trigger++)
    {
     
      if ((myTiH->badTriggers)[trigger]) //check if both hodoscope and tpc saw same event
	{
	  tree->Fill(); // write empty event to outtree
	  continue;        // continue with next track
 	}
      TPCCorrTree->GetEntry(trigger);
      int tpctracknr=TPCCorr.trackNr;
     
      if((myTiH->badTracks)[tpctracknr] & tih::cuts::sigmaZ ) //checking if track in tpc is ok
	{
	  tree->Fill(); // write empty event to outtree
	  continue;
	}
      HodCorrTree->GetEntry(trigger);
      int hodtracknr=HodCorr.TTrackMakerNr;
      HodTrackTree->GetEntry(hodtracknr);
      
      double a=trackmaker->GetParameterTau();
      double b=trackmaker->GetParameterLambda();
      double c=trackmaker->GetParameterNu();
      double d=trackmaker->GetParameterMu();
            
      TPCPoint p1(b,0,d,0,0,0,0); // basepoint
      TPCPoint p2(a+b,1,c+d,0,0,0,0); // basepoint + direction
      
      // redo translation
      p1=tih::translatePoint(&p1, -(myTiH->xOffset), tih::X);
      p1=tih::translatePoint(&p1, -(myTiH->yOffset), tih::Y);
      p1=tih::translatePoint(&p1, -(myTiH->zOffset), tih::Z);
      p2=tih::translatePoint(&p2, -(myTiH->xOffset), tih::X);
      p2=tih::translatePoint(&p2, -(myTiH->yOffset), tih::Y);
      p2=tih::translatePoint(&p2, -(myTiH->zOffset), tih::Z);
     
      // redo rotations
      p1=tih::rotatePoint(&p1, -(myTiH->deltaPhiXZ)/1000.0, tih::Y);
      p1=tih::rotatePoint(&p1, -(myTiH->deltaPhiZY)/1000.0, tih::X);
      p1=tih::rotatePoint(&p1, -(myTiH->deltaPhiXY)/1000.0, tih::Z);
      p2=tih::rotatePoint(&p2, -(myTiH->deltaPhiXZ)/1000.0, tih::Y);
      p2=tih::rotatePoint(&p2, -(myTiH->deltaPhiZY)/1000.0, tih::X);
      p2=tih::rotatePoint(&p2, -(myTiH->deltaPhiXY)/1000.0, tih::Z);
     
      //move points into coordinate system with center in middle of TPC
      p1=tih::translatePoint(&p1, -(geoInfo->GetCylinderXOffset()), tih::X);
      p1=tih::translatePoint(&p1, -(geoInfo->GetCylinderYOffset()), tih::Y);
      p2=tih::translatePoint(&p2, -(geoInfo->GetCylinderXOffset()), tih::X);
      p2=tih::translatePoint(&p2, -(geoInfo->GetCylinderYOffset()), tih::Y);

      
      //calculate entry point in TPC
      double radius=geoInfo->GetTPCRadius()-1;
      double atpc=p2.GetX()-p1.GetX();
      double btpc=p1.GetX()- atpc*p1.GetY();
      double ytpc=-(atpc*btpc)/(atpc*atpc+1)-1/(atpc*atpc+1)*sqrt(radius*radius*(atpc*atpc+1)-btpc*btpc);
      double xtpc=atpc*ytpc+btpc;
      double ztpc=(p2.GetZ()-p1.GetZ())*(ytpc-p1.GetY())+(p1.GetZ()-z0);
     
      int numberofmuons=1;
      for(int j=0;j<numberofmuons;j++)
	{
	  //starting point
	  double vx = xtpc;
	  double vy = ytpc;
	  double vz = geoInfo->GetTPCLength()-ztpc; 
	  // length of tpc because z axis of tpc system opposite to t axis of points
	  
	  //dice energy
	  int rand = (int)(175713.*drand48());
	  if(energy==0)
	    energy=array[rand];
	  double P = sqrt(energy*energy-MASS*MASS);
	  double pyt=1.;
	  double pxt=atpc; //x2-x1
	  double pzt=-(p2.GetZ()-p1.GetZ()); // -c because z axis in different direction
	  double pt=sqrt(pyt*pyt+pxt*pxt+pzt*pzt);
	  double py=pyt/pt*P;
	  double px=pxt/pt*P;
	  double pz=pzt/pt*P;
	  
	  muon->SetMomentum(px,py,pz,energy);
	  muon->SetProductionVertex(vx,vy,vz,0);
	 
	  muon->SetStatusCode(1);
	  TClonesArray &particle = *mcEvent;
	  new(particle[j]) TParticle(*muon);
	}
      tree->Fill();
      mcEvent->Clear();
    }
  
  tree->Write();
  file->Close();
  
}
