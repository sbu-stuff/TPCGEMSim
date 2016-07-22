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

#include "TPCElectron.h"
ClassImp(TPCElectron)

TPCElectron::TPCElectron(int EventNr,int ParticleNr,
			   float X,float Y,float Z,float Time)
{ 
  EventNumber=EventNr;
  ParticleNumber=ParticleNr;
  x=X;
  y=Y;
  z=Z;
  t=Time;
}

TPCElectron::TPCElectron()
{
  EventNumber=0;
  ParticleNumber=0;
  x=0;
  y=0;
  z=0;
  t=0;
}

TPCElectron::~TPCElectron()
{}

void TPCElectron::SetElectron(int EventNr,int ParticleNr,
			   float X,float Y,float Z,float Time)
{
  EventNumber=EventNr;
  ParticleNumber=ParticleNr;
  x=X;
  y=Y;
  z=Z;
  t=Time;
}

void TPCElectron::ClearElectron()
{
  EventNumber=0;
  ParticleNumber=0;
  x=0;
  y=0;
  z=0;
  t=0;
}
