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

#ifndef TPC_Shaper
#define TPC_Shaper

/** Procedure finds electron signals comtributing to same peak, does the shaping
    and binning of time and charge in ADC bins. */

#include "TPCSimChannel.h"

void TPCShaper(int Threshold,int TimeSlice,double Risetime,double ShapingTime,
	       int ADCbins,int ADCmaxcharge, double GainFactor, double IntCuttOff,
	       double Freuqency,double ADCJitter,
	       TPCSimChannel *channel, Int_t channr, TPCSimChanEvent *outevent);

#endif
