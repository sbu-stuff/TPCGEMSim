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

#ifndef MAKEPRIMARYIONISATION_H
#define MAKEPRIMARYIONISATION_H

#include "TPCSimTrack.h"
#include <TParticle.h>
#include <TParticlePDG.h> // for proper declaration of ‘class TParticlePDG’
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

/** This class generates the primary electrons produced by the primary
    generator particle. */

class MakePrimaryIonisation
{

public:

  /*! \param in_B magnetic field
   * \param in_TPCHalfLength distance from anode to cathode of the TPC
   * \param in_TPCRadius radius of TPC
   * \param inner_radius inner radius of TPC
  */
  MakePrimaryIonisation(float in_B, float in_TPCHalfLength, double in_TPCRadius, double inner_radius );
  MakePrimaryIonisation(); 
  ~MakePrimaryIonisation();
  /*! Creates track for rootParticle in eventnr by positioning created electrons along the track.*/
  void CreateTrack(int eventnr, int particlenr, TPCSimTrack *track, 
		   TParticle *rootParticle, bool isCurler);
  /*! Reads in values from generator particle needed for track, like vertex, energy, momentum etc.*/
  void SetParticleParameters(TParticle *rootParticle);
  /*! Calculates parameters for helix like radius, so tracks can be curled if magnetic field is present. */
  void InitializeTrackPoint();
  /*! Determines number of electrons in a cluster using a parametrisation obtained with HEED. */
  void CalculateNumberOfElectrons();
  /*! Determines number of clusters per cm using a parametrisation obtained with HEED. */
  void CalculateNumberOfClusters();
  /*! Reads in the parametrisation of number of clusters per cm. */
  void ReadClusterInfoFile(char *clusterfile);
  /*! Calculates coordinates of next cluster with magnetic field. */
  void CalculateTrackPointwithBfield();
  /*! Calculates coordinates of next cluster without magnetic field. */
  void CalculateTrackPointwithoutBfield();
  /*! returns the total number of electrons produced on the track wiothin the active TPC volume. */
  int GetTotalNumberOfElectrons(){return InTPC;}
  /*! Calculates distance to next cluster assuming an exponential distribution with a mean of the number of clusters per lenght (cm). */
  void CalculateClusterDistance();
  /*! Calculates energy loss for helix. */
  void CalculateEnergyLoss();
  void SetNextStartPoint();
  /*! Rotation for delta rays. */
  void RotateToTrack(double x,double y,double z);
  /*! Rotation for delta rays. */
  void RotateToDelta(double x, double y, double z);
  /*! Multiple scattering for delta rays. */
  void MultipleScattering(double scatter_phi,double scatter_theta);
  void Clear();

private:
  TPCSimTrack *track;
  TParticle *rootParticle;
  //TPC geometry and fields
  /*! Radius of TPC  in mm*/
  double TPCRadius; 
  /*! Inner radius of TPC  in mm*/
  double inner_radius;
  /*! Magnetic field in Tesla*/
  float B;
  float distance;
  /*! Random generator for landau and gaussian. */
  gsl_rng *r; 
  /*! Fitparameters for calculation of # clusters from Parameterisation from HEED. */
  double a0,a1,a2,a3,a4,a5,a6,a7;
  int numberofelectrons;
  double numberofclusters;
  double clusterdistance;
  double electrons[7632][2];
  int InTPC; // #e- in one event
  // coordinates and variables for track
  /*! Coordinates of first cluster. */
  double xa,ya,za; 
  /*! Vertex of particle. */
  double xv,yv,zv; 
  /*! Coordinates of next cluster. */
  double xend,yend,zend, tend; 
  /*! e- coordinate . */
  double x_e,y_e,z_e,t_e; 
  /*! Length of step to next cluster. */
  double dx,dy,dz,dr; 
  /*! Center of helix . */
  double xm,ym; 
  /*! Radius of helix. */
  double radius;
  /*! Scale factor for radius in case of dE/dx.*/
  double dp;
  /*! Angle corresponding to step on helix. */
  double alpha;
  // particle variables
  /*! Particle impulses. */
  double px,py,pz,pt,p,p_const; 
  double energy;
  double mass;
  double charge;
  int pdg;
  double delta_x,delta_y,delta_z;
};


#endif 
