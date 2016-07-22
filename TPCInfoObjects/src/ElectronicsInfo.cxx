#include "ElectronicsInfo.h"
#include <iostream>
using namespace std;

ClassImp(ElectronicsInfo)

ElectronicsInfo::ElectronicsInfo(Double_t risetime, Double_t timeslice,
				   Int_t adcresolution, Int_t maxcharge,
				   Int_t adcthreshold)
{
  RiseTime=risetime;
  TimeSlice=timeslice;
  ADCResolution=adcresolution;
  MaxCharge=maxcharge;
  ADCThreshhold=adcthreshold;
  
}

ElectronicsInfo::ElectronicsInfo()
{}
ElectronicsInfo::~ElectronicsInfo()
{}


void ElectronicsInfo::PrintAllParameters()
{
  cout<<"The Electronic settings are:"<<endl;
  cout<<"RiseTime: "<<      RiseTime     <<endl;
  cout<<"TimeSlice: "<<   TimeSlice  <<endl;
  cout<<"ADCResolution: "<< ADCResolution<<endl;
  cout<<"MaxCharge: "<<     MaxCharge    <<endl;
  cout<<"ADCThreshhold: "<< ADCThreshhold<<endl; 

}

Double_t ElectronicsInfo::GetRiseTime(){return RiseTime;}
Double_t ElectronicsInfo::GetTimeSlice(){return TimeSlice;}
Int_t ElectronicsInfo::GetADCResolution(){return ADCResolution;}
Int_t ElectronicsInfo::GetMaxCharge(){return MaxCharge;}
Int_t ElectronicsInfo::GetADCThreshhold(){return ADCThreshhold;}

void  ElectronicsInfo::SetRiseTime(Double_t risetime){RiseTime=risetime; }
void  ElectronicsInfo::SetTimeSlice(Double_t timeslice){TimeSlice=timeslice; }
void  ElectronicsInfo::SetADCResolution(Int_t adcresolution){ADCResolution=adcresolution; }
void  ElectronicsInfo::SetMaxCharge(Int_t maxcharge){MaxCharge=maxcharge; }
void  ElectronicsInfo::SetADCThreshhold(Int_t adcthreshold){ADCThreshhold=adcthreshold; }

