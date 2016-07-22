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

#ifndef MAKEPADS_H
#define MAKEPADS_H
#include "TPCVoxel.h"
#include <vector>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>


/** This Class takes one primary electron and uses a triple GEM structure for
    for amplification. Broadening of the charge cloud due to diffussion between the 
    GEMs is included as well as Charge Transfer Parameters in dependence on the GEM settings.
   */

class MakePads
{


public:
  /*! \param sigma Transverse Diffusion between GEMs
   * \param numberofpads Number of Pads on Readout
   * \param xoffset Offset of padplane to center of TPC in x
   * \param yoffset Offset of padplane to center of TPC in y
   * \param columns Number of columns of pads on Readout
   * \param Pady height of readout pad
   * \param Padx width of readout pad
   * \param Drifttime Time needed to drift through chamber (needed for determination of timeslice)
   * \param Bfield Magnetic field inside TPC
   * \param setting Parameters of the GEM Struture: Drift Field, GEM Voltages, Transfer Fields and Induction field
   * \param inputfile File containing the parameter for Collection, Gain, Extraction etc.
  */ 
  MakePads(double sigma,int numberofpads,double xoffset, double yoffset ,int columns,
	   double Pady,double Padx,double Drifttime,double Bfield,
	   double setting[7],char *inputfile, double gain_factor,const char* in_Gas);
  
  ~MakePads();
  
  /*! \param sigma Diffusion betweenm GEMs calculated from gas parameters 
   * \param evtnr Number of current event
   * \param xe,ye,te Coordinates of the primary electron
   * \param voxel TPCVoxel to be filled by this function
   * \param voxelvector Vector to store voxel temporarily
   * \param particlenr number of the generator particle that created the electron
   */
  /*! Amplify() does the transfer of the e- throug hthe GEM structure amd the integration on the pads.
   */
  void Amplify(int evtnr,double xe, double ye ,double te, TPCVoxel* voxel, 
	       std::vector<TPCVoxel> *voxelvector, int particlenr, bool isCurler);
  /*! Function to claculate number of electrons after passing through the GEM structure.
   * This function makes use of the parametrisation of the charge transfer through the GEMs.
   */
  void CalculateNrElectrons();
  /*! Gives the Extraction out of GEM i=GEMNr for enumber of electrons indside GEM hole.
   */
  int GEM_Extraction(int GEMNr, int enumber);
/*! Gives the Collection into GEM i=GEMNr for enumber of electrons in front of GEM hole.
   */
  int GEM_Collection(int GEMNr, int enumber);
  /*! Gives the gain in GEM i=GEMNr using an exponential distribution for the gain in one GEM. */
  double GEM_Gain(int GEMNr, int enumber);
  /*!Claculates the attachment between GEM */
  double CalculateAttachment(double E);
  double AttachmentParam(double E,double a0,double a1,double a2,double a3,
			 double a4,double a5);
private:
  /*! Magnetic field inside TPC */
  double B;
  /*! Offset of active area to coordinate system */
  double x0;
  double y0;
  /*! height of readout pad */
  double pady;
  /*! width of readout pad */
  double padx;
  /*! number of columns of pads */
  int padcolumns;
  int npads;
  /*! Time needed to drift through chamber (needed for determination of timeslice) */
  double drifttime;
  const char* Gas;
  /*! number of electrons prduced by GEM structure from one primary electron */
  int numbersecel;
  /*!  Parameters of the GEM Struture: Drift Field, GEM Voltages, Transfer Fields and Induction field */
  double GEMSetting[7];
  /*! File containing the parameter for Collection, Gain, Extraction etc. */
  char *paramfile;
  /*! random number generator from the gsl library */
  gsl_rng *r;
  /*! Extraction for each GEM */
  double Extr[3];
  /*! Collection for each GEM */  
  double Coll[3];
  /*! Gain for each GEM */ 
  double Gain[3];
  /*!Diffusion between GEMS*/
  double sigma_diff;
  /*!Factor to correct gain for temperature and pressure to fit chargespectrum in measurement*/
  double gainfactor;
  /*! Attachment coefficients*/
  double A1,A2,A3;
  /*! Charge comes from Curler */
  bool isCurler;
  
};

#endif
