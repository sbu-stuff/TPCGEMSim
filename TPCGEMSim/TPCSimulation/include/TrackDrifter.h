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


#ifndef TRACHDRIFTER_H
#define TRACKDRIFTER_H

#include "TPCSimTrack.h"
#include <TParticle.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

/** This class drifts an electron according to the characteristics of the choosen gas.*/

class TrackDrifter
{

public:
  /*! \param in_Gas Choosen gas (P5, P10, TDR).
   * \param in_B Magnetic field in Tesla.
   * \param in_Efield Drift field in V/cm.
   * \param in_distance Drift distance in mm.
   * \param radius Radius of TPC in mm. 
   * \param inner_radius Inner Radius of TPC in mm. 
   */
  TrackDrifter(const char* in_Gas,double in_B, double in_Efield, double in_distance, double radius,double inner_radius );
  TrackDrifter(); 
  ~TrackDrifter();
  void DriftElectron(TPCSimTrack *drifttrack);
  void InitializeDriftValues();
  void InitializeNumberElectrons();
  void CalculateTransverseDiffusion();
  void GetTrackParameter(TPCSimTrack *drifttrack);
  void SetTrackParameter(TPCSimTrack *drifttrack);
  void MakeElectronDriftCoordinates();
  void GetElectronCoordinates(TPCElectron *electron);
  double GetDrift_x(){return xdrift;}
  double GetDrift_y(){return ydrift;}
  double GetDrift_z(){return zdrift;}
  double GetDriftVelocity(){return vdrift;}
  double GetDiffLong(){return difflong;}
  double GetDiffTrans(){return difftrans;}
  /*! Parameter for this function are from parametrisation of gas properties obtained with magboltz. */
  double CalculateGasParameter(double a, double b ,double c, double d,
			      double e, double f, double g, double h,
			      double i, double j,double k);
  /*! Parameter for this function are from parametrisation of gas properties obtained with magboltz. */
  double CalculateDiffTransBParam(double a, double b, double c,double d, double e);
  void Clear();

private:
  TPCSimTrack *drifttrack;
  TPCElectron *electron;
  double E;
  double B;
  const char* Gas;
  /*! Random generator for landau and gaussian. */
  gsl_rng *r;
  // coordinates and variables for track
  /*! Coordinates of the electron. */
  double x_e,y_e,z_e,t_e; // e- coordinates
  // particle variables
  int eventnr;
  int particlenr;
  int numberofelectrons;
  bool isCurler;
  //needed for drifting
  double TPCHalfLength;
  double distance;
/*! Coordinates of the drifted electron. */
  float xdrift,ydrift,zdrift,tdrift; // coordinates of drifted e-
  double vdrift;  // mm/mus  
  double difflong; // mum/sqrt(cm)
  double difftrans;
  double TPCRadius;
  double TPCInnerRadius;
};


#endif 
