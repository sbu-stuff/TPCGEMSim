// original version by Peter Wieneman

#ifndef HEP_INTERFACE_H
#define HEP_INTERFACE_H
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TParticle.h>
#include <TParticlePDG.h> // for proper declaration of ‘class TParticlePDG’

/** The HepInterface handles reading in the input of primary particles */

class HepInterface{



public:
   
  HepInterface(const char* eventfile, 
	       const char* treename = "tree",
	       const char* clonesarrayname= "MCEvent",
	       const int clonesarraysize = 1000);
  ~HepInterface();

  int GetNEntries(){return nentries;}
  TClonesArray* GetEvent(Int_t eventnr);
  TTree* GetTree(){return tree;}

private:
   /*!tree Root tree with primary particles */
  TTree *tree;
  /*! inputFile File with primary particles */
  TFile *inputFile;
 /*!  mcEvent TClonesarray with the primary particles*/
  TClonesArray *mcEvent;
  /*!  nentries Number of generated events*/
  int nentries;
};

#endif

















