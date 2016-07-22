//
// pythia.cpp
//
// $Id$
// $Name$
//
// History:
// 2002-03-26, P. Wienemann, first version
//modified by A.Muennich
//

#ifndef __CINT__
#include "TCirce.h"
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <stdlib.h>
#include <TPythia6.h>
#include <iostream.h>
#include <TParticle.h>
#include "TRandom.h"
#include "TDatabasePDG.h"
#include <cstdlib>
#endif

void loadLibraries() 
{
#ifdef __CINT__
  // Load the Event Generator abstraction library, Pythia 6
  // library, and the Pythia 6 interface library. 
  gSystem->Load("libEG");
  gSystem->Load("libPythia6");
  gSystem->Load("libEGPythia6");
  gSystem->Load("libCirce7");
  gSystem->Load("libCirce.a")
#endif
}

// This is the main part
// 
#ifdef __CINT__
void pythia_gg() 
#else
  int main(Int_t argc, Char_t** argv)
#endif
{
  // Load needed libraries 
  loadLibraries();
  
  TROOT root("pythia", "PYTHIA event generator interface");
  
  if (argc != 3) {
    cerr<<argv[0]<<": wrong number of parameters"<<endl;
    cerr<<endl;
    cerr<<"usage: "<<argv[0]<<" <sqrts [GeV]> <nevents>"<<endl;
    cerr<<endl;
    exit(EXIT_FAILURE);
    }

    Float_t sqrts    = atof(argv[1]);  // center of mass energy in GeV
    Int_t   nevents  = atoi(argv[2]);  // number of events to be generated

    const Int_t clonesarraysize = 1000; // size of TClonesArray to store
                                        // generated particles


    // Settings section
    // ================

    TPythia6* eg = new TPythia6();
    // Create an instance of the Circe code
    TCirce* circe = new TCirce;

    // set flags
    eg->SetMSTP(11,1);   // electron contains photon flux
    eg->SetMSTP(171,1);  // allow variable energies in PYTHIA when CIRCE is used.
    eg->SetPARP(2,1.0);  // minimum CMS energy
    eg->SetCKIN(3,0.2);  // lower cut off on p_T 

    // Select full user control
    eg->SetMSEL(0);
    
    eg->SetMSUB(58,1);
    
    // in case of many warnings of maximum violations...
    eg->SetMSTP(121,1);
    eg->SetPARP(121,1000.0);
    // set (and use) random gen. seed to fixed value for reproducible results
    eg->SetMRPY(1,12345678);
    eg->SetMRPY(2,0);
    
    // ... and initialise it to run gamma gamma with variable energy
    for(int ip=1; ip<=2; ip++) {
      for(int im=1; im<=5; im++) {
	eg->SetP(ip,im,0.0);
      }
    }
    
 
  eg->SetP(1,3,0.5*sqrts);
  eg->SetP(2,3,-0.5*sqrts);
  eg->SetP(1,4,0.5*sqrts);
  eg->SetP(2,4,0.5*sqrts);
  // Initialize Pythia for an e+ e- collider
  eg->Initialize("4mom", "gamma", "gamma", sqrts);
  
  // initialize Circe
  circe->Initialize(sqrts, "TESLA");
  
    // List table of resonance decay channels
  //    eg->Pystat(2);

    TFile* file = new TFile("TeslaEvents.root", "recreate");
    file->SetCompressionLevel(2);

    TTree* tree = new TTree("tree", "Event tree");

    TClonesArray* mcEvent = new TClonesArray("TParticle", clonesarraysize);

    tree->Branch("MCEvent", &mcEvent);


    // Event loop section
    // ==================
    for (Int_t evt=0; evt<nevents; evt++) {

      //      do {
	// Simulate beam strahlung
	double x1, x2, p1, p2;
	circe->GenerateEvent(x1,x2,"GG");
	//        cout << " x1= " << x1 << " x2 = " << x2 << endl;
	p1 =  0.5*x1*sqrts;
	p2 = -0.5*x2*sqrts;
	
	// Define colliding particles
	for(int ip=1; ip<=2; ip++) {
	  for(int im=1; im<=5; im++) {
	    eg->SetP(ip,im,0.0);
	  }
	}
	eg->SetP(1,3,p1);
	eg->SetP(2,3,p2);
	eg->SetP(1,4,TMath::Abs(p1));
	eg->SetP(2,4,TMath::Abs(p2));
	
        eg->GenerateEvent();
	//      } while (eg->GetMSTI(61)==1);
	
      // Look at first event
	//	if (!evt)
	    eg->Pylist(1);

	if (eg->GetN() > clonesarraysize)
	    cout<<"INFO: Event "<<evt<<" contained more than "
		<<clonesarraysize<<" events"<<endl;

	// Fill TClonesArray with all (not only final state) particles
	eg->ImportParticles(mcEvent, "All");

	tree->Fill();
    }

    // Output section
    // ==============

    // Print cross section table
    eg->Pystat(1);

    // Write histograms to file
    file->cd();
    tree->Write();
    file->Close();

    return 0;
}
