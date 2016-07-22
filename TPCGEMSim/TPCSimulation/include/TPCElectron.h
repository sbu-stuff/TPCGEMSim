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


/** \mainpage <a href="http://www.physik.rwth-aachen.de/group/IIIphys/TESLA/en/simulation/doc/html/index.html">TPCGEMSimulation</a> (v1.10) 
 *This simulation package is dedicated to detailed studies of a Time 
 *Projection Chamber (TPC) with a Gas Electron Multiplier (GEM) readout.
 * \section Overview
 *It consists of for Modules <br>
 *1. Primary ionisation <br>
 *2. Drifting the electrons including diffusion <br>
 *3. Amplification in a triple GEM structure <br>
 *4. Shaping and binning of charge in ADC counts <br>
 * \section Usage
 * The <a href="./annotated.html">Class List</a> gives an overview of available classes
 * and their functionality.
 * For a detailed description refer to the 
 *<a href="http://www.physik.rwth-aachen.de/group/IIIphys/TESLA/en/simulation/UserManual/UserManual_v1.10.html">user manual</a>.
 */


#ifndef TPC_ELECTRON_H
#define TPC_ELECTRON_H

#include <TObject.h>

/** The TPCElectrons stores the information of the primary or the drifted electron
*/

class TPCElectron : public TObject{

public:
  /*!  \param EventNr Number of the event
   * \param ParticleNr Counts the particles in one event
   * \param X x-coordinate of electron
   * \param Y y-coordinate of electron
   * \param Z z-coordinate of electron  
   * \param Time time-coordinate of electron 
   */
  TPCElectron(int EventNr, int ParticleNr,
	       float X,float Y,float Z,float Time);
  TPCElectron();
  ~TPCElectron();
  
  int GetParticleNumber(){return ParticleNumber;}
  int GetEventNumber(){return EventNumber;}
  float GetX(){return x;}
  float GetY(){return y;}
  float GetZ(){return z;}
  float GetTime(){return t;}
  void SetElectron(int EventNr, int ParticleNr,
	       float X,float Y,float Z,float Time);
  void ClearElectron();
  
private:
  /*! ParticleNumber Counts the particles in one event*/
  int ParticleNumber;
  /*!  EventNumber Number of the event*/
  int EventNumber;
  /*!  x x-coordinate of electron*/
  float x;
  /*!  y y-coordinate of electron*/
  float y;
  /*!  z z-coordinate of electron   (z=postion of readout for drifted electrons)*/
  float z;
  /*!  t time-coordinate of electron (t=0 for primary electrons)*/
  float t;

  ClassDef(TPCElectron,1)
};



#endif
