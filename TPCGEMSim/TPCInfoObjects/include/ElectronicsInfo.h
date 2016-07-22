#ifndef ELECTRONICSINFO_H
#define ELECTRONICSINFO_H

#include <TObject.h>

/** This class stores parameters of the electronics, like rise time 
    and ADC resolution.
 */

class ElectronicsInfo : public TObject{

public:
/*! Creates a ElectronicsInfo object with the following attributes:
 * \param RiseTime risetime of the shaper in ns
 * \param TimeSlice width on timeslice in mus
* \param ADCResolution resolution of the adc in bits
* \param MaxCharge number of electrons when ADC goes into overrange
* \param Threshold minimum number of ADC bins to be reached
*/

  ElectronicsInfo(Double_t risetime, Double_t timeslice,
				   Int_t adcresolution, Int_t maxcharge,
				 Int_t adcthreshold);
  ElectronicsInfo();
  ~ElectronicsInfo();

  void PrintAllParameters(); 
  Double_t GetRiseTime();
  Double_t GetTimeSlice();
  Int_t GetADCResolution();
  Int_t GetMaxCharge();
  Int_t GetADCThreshhold();

  void SetRiseTime(Double_t risetime);
  void SetTimeSlice(Double_t timeslice);
  void SetADCResolution(Int_t adcresolution);
  void SetMaxCharge(Int_t maxcharge);
  void SetADCThreshhold(Int_t adcthreshold);

private:
  Double_t RiseTime;
  Double_t TimeSlice;
  Int_t ADCResolution;
  Int_t MaxCharge;
  Int_t ADCThreshhold;


  ClassDef(ElectronicsInfo,2)
};


#endif
