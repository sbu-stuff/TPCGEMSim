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

#include "TPCSimTrack.h"
#include "TPCElectron.h"


ClassImp(TPCSimTrack)
  
  
TPCSimTrack::TPCSimTrack()
{
  felectrons = new TClonesArray("TPCElectron",100000);
  ProducedElectrons = 0;
}

TPCSimTrack::~TPCSimTrack()
{
  // delete felectrons;
  felectrons->Clear();
}

void TPCSimTrack::Clear()
{
  ProducedElectrons = 0;
  felectrons->Clear();
}

void TPCSimTrack::AddTPCElectron(int EventNr, int ParticleNr, 
				  float X,float Y, float Z,float Time)
{
  TClonesArray &electrons = *felectrons;
  new(electrons[ProducedElectrons++]) TPCElectron( EventNr,ParticleNr, X, Y, Z, Time);
}

void TPCSimTrack::SetTrackParameters(int EventNr, int ParticleNr, int NumberofElectrons, bool Is_Curler) 
{
  ParticleNumber=ParticleNr;
  EventNumber=EventNr;
  ProducedElectrons=NumberofElectrons;
  isCurler=Is_Curler;
}

TPCElectron* TPCSimTrack::GetTPCElectron(int e_number)
{
  if ( e_number > -1 && e_number < ProducedElectrons )
    return (TPCElectron*)felectrons->At(e_number);
  else
    return NULL;
}
