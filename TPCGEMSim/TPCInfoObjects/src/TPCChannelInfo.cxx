#include "TPCChannelInfo.h"

#include  <iostream>
using namespace std;

ClassImp(TPCChannelInfo)

TPCChannelInfo::TPCChannelInfo(Int_t channelNr)
    : fChannelNr(channelNr)
{
    fHardwareChannel=-1; // no hardware channel information
    fFlags=0;
    fCalibrationFactors.Set(0);
}

TPCChannelInfo::~TPCChannelInfo()
{}

void TPCChannelInfo::AddFlags(Int_t channelFlags)
{
    fFlags=fFlags | channelFlags;
}

Int_t TPCChannelInfo::GetChannelNumber()
{
    return fChannelNr;
}

Int_t TPCChannelInfo::GetFlags()
{
    return fFlags;
}

Int_t TPCChannelInfo::GetHardwareChannel()
{
    return fHardwareChannel;
}

Double_t TPCChannelInfo::GetCalibrationFactor(Int_t factorNr)
{
    return fCalibrationFactors[factorNr];
}

TArrayD TPCChannelInfo::GetCalibrationFactors()
{
    return fCalibrationFactors;
}

Int_t TPCChannelInfo::GetNCalibrationFactors()
{
    return fCalibrationFactors.GetSize();
}

bool TPCChannelInfo::IsDead()
{
    return IsBad(channelMode::dead);
}

bool TPCChannelInfo::IsNoisy()
{
    return IsBad(channelMode::noisy);
}

bool TPCChannelInfo::IsBad(Int_t flagMask)
{
    return static_cast<bool>(fFlags & flagMask);
}

void TPCChannelInfo::SetCalibrationFactor(Int_t factorNr,
					  Double_t factorValue)
{
    fCalibrationFactors[factorNr]=factorValue;
}

void TPCChannelInfo::SetCalibrationFactors(TArrayD calibrationFactors)
{
    fCalibrationFactors=calibrationFactors;
}

void TPCChannelInfo::SetChannelNumber(Int_t channelNr)
{
    fChannelNr=channelNr;
}

void TPCChannelInfo::SetFlags( Int_t channelFlags)
{
    // no need to check index bound, TArray does this for us
    fFlags=channelFlags;
}

void TPCChannelInfo::SetHardwareChannel(Int_t hardwareChannel)
{
    fHardwareChannel=hardwareChannel;
}

void TPCChannelInfo::SetNCalibrationFactors(Int_t n)
{
    fCalibrationFactors.Set(n);
}

void TPCChannelInfo::Print()
{
    cout << "Channel "<< fChannelNr << " (hardware channel "
	 << fHardwareChannel<< ")"<<endl;
    cout << "Flags : "<<hex<< fFlags << dec<<endl;
    cout << "Calibration factors : ";
    for (int i=0;i < fCalibrationFactors.GetSize() ; i++)
	cout << fCalibrationFactors[i] << "  ";
    cout << endl;
}
