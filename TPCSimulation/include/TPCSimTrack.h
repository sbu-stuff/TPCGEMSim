//*****************************************************
// Part of program to simulate a TPC with GEM readout *
//                                                    *
// Author: Astrid Muennich                            *
//                                                    *
//   Astrid Muennich                                  *
//   RWTH Aachen, III. Phys. Inst. B                  * 
//   Office: 28 A 112, Phone: +49/(0)241/8            *
//   Email: muennich@physik.rwth-aachen.de            * 
//                                                    *
//*****************************************************


#ifndef TPC_SIMTRACK_H
#define TPC_SIMTRACK_H

#include "TPCElectron.h"
#include <TROOT.h>
#include <TClonesArray.h>
#include <TObject.h>

/** TPCSimTrack stores a TClonesarray of TPCElectrons*/

class TPCSimTrack : public TObject{
  
public:
   
  TPCSimTrack();
  ~TPCSimTrack();
  TPCElectron* GetTPCElectron(int e_number);
  
  int GetParticleNumber(){return ParticleNumber;}
  int GetEventNumber(){return EventNumber;}
  int GetNumberOfElectrons(){return ProducedElectrons;}
  bool GetCurlerStatus(){return isCurler;}

  TClonesArray* GetTPCElectrons(){return felectrons;}
  void AddTPCElectron(int,int,float,float,float,float);
  void Clear();
  void SetTrackParameters(int EventNr, int ParticleNr, int NumberofElectrons, bool Is_Curler);

  
private:
  /*! ParticleNumber Keeps track of particle which caused the track.*/
  int ParticleNumber;
 /*!  EventNumber Holds the number of the event the track was created in.*/
  int EventNumber;
 /*!   ProducedElectrons Gives the number of electrons created along the track.*/
  int ProducedElectrons;
  /*! Remember if this was curler. */
  bool isCurler;
  /*!   felectrons TClonesarray of TPCElectrons. */
  TClonesArray *felectrons;

  ClassDef(TPCSimTrack,2)
};


#endif
