//read TParticle from RootTree

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <stdlib.h>
#include <TPythia6.h>
#include <iostream>
#include <TParticle.h>
#include "TRandom.h"
#include "TDatabasePDG.h"
#include "HepInterface.h"
#include <TClonesArray.h>
using namespace std;

HepInterface::HepInterface(const char* eventfile, 
			  const char* treename,
			  const char* clonesarrayname,
			  const int clonesarraysize)
{
  inputFile = new TFile(eventfile, "read");
  if (!inputFile->IsOpen())
    cout << "Could not open file with primary particle information!"<<endl;
  
  tree = (TTree*)inputFile->Get(treename);
  mcEvent = new TClonesArray("TParticle", clonesarraysize);
  tree->SetBranchAddress(clonesarrayname, &mcEvent);
  nentries = (int)tree->GetEntries();
  
  cout<<"Opened file "<<eventfile<<" with "<<nentries<<" entries"<<endl;
}

HepInterface::~HepInterface()
{
  delete inputFile;
  delete mcEvent;
  delete tree;
}

TClonesArray* HepInterface::GetEvent(Int_t eventnr)
{
  tree->GetEntry(eventnr);
  return mcEvent;
}



