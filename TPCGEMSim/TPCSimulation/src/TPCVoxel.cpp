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

#include "TPCVoxel.h"

TPCVoxel::TPCVoxel()
{
  Time=0;
  ChannelNumber=0;
  Charge=0;
  particlenumber=0;
}


void TPCVoxel::SetVoxel(long int channr, int time, int charge, short int particlenr)
{
  Time=time;
  ChannelNumber=channr;
  Charge=charge;
  particlenumber=particlenr;
}
