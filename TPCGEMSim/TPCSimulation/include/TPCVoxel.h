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


#ifndef TPC_VOXEL_H
#define TPC_VOXEL_H

/** A TPCVoxel containes the charge (in number of electrons) in one timeslice
 * of a certain channel.*/ 
class TPCVoxel{

public:
  TPCVoxel();
  ~TPCVoxel(){};

  void SetVoxel(long int channr, int time, int charge, short int particlenr);
  // int GetVoxelEventNumber(){return EventNumber;}
  // int GetVoxelColumn(){return Column;}
  // int GetVoxelRow(){return Row;}
  int GetVoxelTime(){return Time;}
  long int GetVoxelChanNr(){return ChannelNumber;}
  int GetVoxelCharge(){return Charge;}
  short int GetParticleNr(){return particlenumber;}
 
private:
  // int EventNumber;
  //int Column;
  // int Row;
  int Time;
  long int ChannelNumber;
  int Charge;
  short int particlenumber;
  
};

#endif
