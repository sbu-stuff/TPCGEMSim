#include <iostream>
#include <math.h>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>

#include <TCanvas.h>
#include <TFile.h>
#include <TNtuple.h>
#include <TROOT.h>
#include <TApplication.h>
#include <TH1F.h>
#include <TH3F.h>

#include "MediumMagboltz.hh"
#include "SolidTube.hh"
#include "GeometrySimple.hh"
#include "ComponentConstant.hh"
#include "ComponentAnalyticField.hh"
#include "ComponentBase.hh"
#include "Sensor.hh"
#include "TrackHeed.hh"
#include "Plotting.hh"
#include "Random.hh"
#include "ViewDrift.hh"
#include "AvalancheMicroscopic.hh"
#include "ViewCell.hh"

using namespace Garfield;

Float_t x,y,z;

//TNtuple *mapped = (TNtuple*) mmap(NULL, sizeof *ntuple, PROT_READ | PROT_WRITE, 
//		      MAP_SHARED | MAP_ANONYMOUS, -1, 0);

/*TH1F* hElectrons = new TH1F("hElectrons", "Number of electrons", 100, 300, 11000);
TH1F* hEdep = new TH1F("hEdep", "Energy Loss", 100, 0., 500.);
TH1F* xPos = new TH1F("xPos", "x Position over time", 100, 0., 10);
TH1F* yPos = new TH1F("yPos", "y Position over time", 100, 0., 10);
TH1F* zPos = new TH1F("zPos", "z Position over time", 100, 0., 10);

TH3F* clusterLocation = new TH3F("clusterLocation", "Location of Clusters",100,  0., 10, 100, 0., 20, 100, 0., 20);*/

typedef struct Node 
{
  TrackHeed* track;
  int nEvents;
  int id;
  double momentum;
  char* particle;
  double dx0;
  double dy0;
  double dz0;
}Node;

void EventHandler(void* p) 
{
  TFile *f =  new TFile("basic.root","UPDATE");
  TNtuple *ntuple = (TNtuple*) f->Get("ntuple");

  Node *obj = (Node*) p;

  obj->track->SetParticle(obj->particle);
  obj->track->SetMomentum(obj->momentum);

  std::cout<< "\nRUNNING\n";
  for (int i = 0; i <obj->nEvents; i++) 
    {
      if (i == 1) obj->track->DisableDebugging();
      if (i % 1000 == 0) std::cout << i << "/" << obj->nEvents << "\n";
      double x0 = 0., y0 = 0., z0 = 0., t0 = 0.;
      
      obj->track->NewTrack(x0, y0, z0, t0, obj->dx0, obj->dy0, obj->dz0);
      
      double xc = 0., yc = 0., zc = 0., tc = 0.;
      
      int nc = 0.;
      
      double ec = 0.;
      
      double extra = 0.;
      
      //double esum = 0.;
      
      //int nsum = 0;
      
      while (obj->track->GetCluster(xc, yc, zc, tc, nc, ec, extra)) 
	{
	  //esum += ec;
	  //nsum += nc;
	  ntuple->Fill(xc,yc,zc, tc, nc, ec, obj->id, obj->dx0, obj->dy0, obj->dz0);
	  //xPos->Fill(tc, xc);
	  //yPos->Fill(tc, yc);
	  //zPos->Fill(tc, zc);
	  //clusterLocation->Fill(xc, atan2(yc,xc), zc);
	}
      //hElectrons->Fill(nsum);
      //hEdep->Fill(esum * 1.e-3);
    }
    f->Write();
    f->Close();
}


void forkSim(int processes, TrackHeed* track) 
{
  pid_t process;
  const int nEvents = 1;
  const int nParticles = 5;
  char particles[][5] = {"e-", "pi", "p", "mu", "e+"};
  int particleId[5] = {11, 211, 2212, 13, -11};
  const int nMomentums = 6;
  double momentums[6] = {100.e9, 50.e9, 10.e9, 5.e9, 1.e9, .5e9};
  const int nDirections = 4;

  
  Node* obj = (Node*) malloc(sizeof(*obj));
  obj->track = track;
  //obj->ntuple = ntuple;
  //obj->f = f;
  int p = 0, m = 0, d = 0; 
  for  (int i = 0; i < processes; i++) 
    {
      if ((process = fork()) != 0) 
	{
	  d++;
	  if (d % nDirections == 0) 
	    {
	      m++;
	    }
	  if (m == nMomentums) 
	    {
	      p++;
	      m = 0;
	    }
	  if (p == nParticles)
	    {
	      p = 0;
	    } 
	  int status;
	  //waitpid(process,&status,WNOHANG);
	  wait(NULL);
	}
      else 
	{
	  double dx0 = ((double)rand()/(double) 1), dy0 = ((double)rand()/(double) 1), dz0 = ((double)rand()/(double) 1);
	  obj->dx0 = dx0;
	  obj->dy0 = dy0;
	  obj->dz0 = dz0;
	  obj->particle = particles[p];
	  obj->momentum = momentums[m];
	  obj->nEvents = nEvents;
	  obj->id = particleId[p];

	  std::cout<< "d: " << d << " p:" << p << " m:" << m << "\n";
	  std::cout<< "Child: " << i << " particle: " << particles[p] 
		   << " momentum: " << momentums[m];

	  EventHandler(obj);
	  std::cout<<"DONE\n";

	  //wait(NULL);
	  //exit(EXIT_SUCCESS);
	  exit(0);
	}
    }
  //munmap(mapped, sizeof *mapped);
  exit(1);

}

int main(int argc, char * argv[])
{
  TFile *f = new TFile("basic.root","RECREATE");
  TNtuple *ntuple = new TNtuple("ntuple","data for the ntuple","x:y:z:t:ec:nc:particle:dx:dy:dz");
  f->Write();
  f->Close();

  TH1::StatOverflows(kTRUE);
  
  randomEngine.Seed(123456);
  TApplication app("app", &argc, argv);
  plottingEngine.SetDefaultStyle();
  srand(time(0));

  MediumMagboltz* gas = new MediumMagboltz();
  gas->SetComposition("ne", 95., "cf4", 5.);
  gas->SetTemperature(295);
  gas->SetPressure(750.062);
  gas->EnableDebugging();
  gas->Initialise();
  gas->DisableDebugging();

  
  const double l = 100;
  SolidTube* tube = new SolidTube(0., 0., 0., 0., 78., l);
  SolidTube* filler = new SolidTube(0., 0., 0., 0., 20., l);
  GeometrySimple* geo = new GeometrySimple();
  geo->AddSolid(filler, NULL);
  geo->AddSolid(tube, gas);

  ComponentConstant* comp = new ComponentConstant();
  comp->SetGeometry(geo);
  comp->SetElectricField(0., 0., 400.);
  comp->SetMagneticField(0., 0., 1.5);
  
  Sensor* sensor = new Sensor();
  sensor->AddComponent(comp);
  TrackHeed *track = new TrackHeed();
  track->SetSensor(sensor);
  track->SetParticle("e-");
  track->SetMomentum(100.e9);

  forkSim(120, track);

  /* TCanvas* c1 = new TCanvas();
  hElectrons->GetXaxis()->SetTitle("number of electrons");
  hElectrons->Draw();

  TCanvas* c2 = new TCanvas();
  hEdep->GetXaxis()->SetTitle("energy loss [keV]");
  hEdep->Draw();

  TCanvas* c3 = new TCanvas();
  xPos->GetXaxis()->SetTitle("Time");
  xPos->GetYaxis()->SetTitle("X");
  xPos->Draw();

  TCanvas* c4 = new TCanvas();
  yPos->GetXaxis()->SetTitle("Time");
  yPos->GetYaxis()->SetTitle("Y");
  yPos->Draw();

  TCanvas* c5 = new TCanvas();
  zPos->GetXaxis()->SetTitle("Time");
  zPos->GetYaxis()->SetTitle("Z");
  zPos->Draw();

  TCanvas* c6 = new TCanvas();
  clusterLocation->Draw();*/ 
  
  /*delete c1;
  delete c2;
  delete c3;
  delete c4;
  delete c5;
  delete c6;*/
  
  app.Run(kTRUE);
  exit(EXIT_SUCCESS);
}
