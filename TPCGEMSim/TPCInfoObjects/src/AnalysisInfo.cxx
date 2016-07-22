#include "AnalysisInfo.h"
#include <iostream>
using namespace std;

ClassImp(AnalysisInfo)

AnalysisInfo::AnalysisInfo()
{
   MinClusterSize=0;
   MaxTimeSpread= 0;
   ChargeThresholdSim=0;
   TimeJumpSim=0;
   PedestalFile="none";
   DeltaX=0;
   DeltaY=0;
   DeltaZ=0;
   MinTrackPoints=0;

   TimeMarkerCut=448;// the last 64 samples are for time marker
   OffTriggerCut=448;// no extra off trigger cut

   BadPointsMask=0xFFFF; // cut on all flags

   PadResponseMethod=0;
   Sigma_0=0.;
   D_trans=0.;
   Z_0=0.;
}

AnalysisInfo::~AnalysisInfo(){}

void AnalysisInfo::PrintAllParameters()
{
  cout<<"The Analysis Settings are:"<<endl;
  cout<<"Minimal Cluster Size: "<<MinClusterSize<<endl;
  cout<<"Maximal Time Spread: "<<MaxTimeSpread<<endl;
  cout<<"Charge Threshold in Simulation: "<<ChargeThresholdSim<<endl;
  cout<<"Time Jump in Simulation: "<<TimeJumpSim<<endl;
  cout<<"Pedestal File from Measurement: "<<PedestalFile<<endl<< endl;
  
  cout<<"DeltaX: "<<DeltaX<<" ; DeltaY: "<<DeltaY<<" ; DeltaZ: "<<DeltaZ<<endl;
  cout<<"MinTrackPoints: "<<MinTrackPoints<<endl<< endl;

  cout<<"TimeMarkerCut: "<<TimeMarkerCut<<" time samples"<<endl;
  cout<<"OffTriggerCut: "<<OffTriggerCut<<" time samples"<<endl;

  cout<<"BadPointsMask: "<<hex<<BadPointsMask<<dec<<endl<<endl;

  cout<<"Sigma_0: "<<Sigma_0<<endl;
  cout<<"D_trans: "<<D_trans<<endl;
  cout<<"Z_0: "<<Z_0<<endl;
}

Int_t   AnalysisInfo::GetMinClusterSize()    {return  MinClusterSize;}
Float_t AnalysisInfo::GetMaxTimeSpread()     {return  MaxTimeSpread;}
Int_t   AnalysisInfo::GetChargeThresholdSim(){return ChargeThresholdSim;}
Int_t   AnalysisInfo::GetTimeJumpSim()       {return TimeJumpSim;}
TString AnalysisInfo::GetPedestalFile()      {return PedestalFile;}
Float_t AnalysisInfo::GetDeltaX()            {return DeltaX;}
Float_t AnalysisInfo::GetDeltaY()            {return DeltaY;}
Float_t AnalysisInfo::GetDeltaZ()            {return DeltaZ;}
Int_t   AnalysisInfo::GetMinTrackPoints()    {return MinTrackPoints;}

Int_t   AnalysisInfo::GetTimeMarkerCut()     {return TimeMarkerCut;}
Int_t   AnalysisInfo::GetOffTriggerCut()     {return OffTriggerCut;}

Int_t   AnalysisInfo::GetBadPointsMask()     {return BadPointsMask;}

Int_t   AnalysisInfo::GetPadResponseMethod() const
{return PadResponseMethod;}

Float_t AnalysisInfo::GetSigma_0() const
{ return Sigma_0; }

Float_t AnalysisInfo::GetD_trans() const
{ return D_trans; }

Float_t AnalysisInfo::GetZ_0() const
{ return Z_0; }

void AnalysisInfo::SetMinClusterSize(Int_t minclustersize)
{MinClusterSize=minclustersize;}
void AnalysisInfo::SetMaxTimeSpread(Float_t maxtimespread)
{MaxTimeSpread= maxtimespread;}
void AnalysisInfo::SetChargeThresholdSim(Int_t chargethresholdsim)
{ChargeThresholdSim=chargethresholdsim;}
void AnalysisInfo::SetTimeJumpSim( Int_t timejumpsim)
{TimeJumpSim=timejumpsim;}
void AnalysisInfo::SetPedestalFile(const char* pedestalfile)
{
    if (pedestalfile)
	PedestalFile=pedestalfile;
    else
	PedestalFile="none";
}
void AnalysisInfo::SetDeltaX(Float_t deltax)
{DeltaX=deltax;}
void AnalysisInfo::SetDeltaY(Float_t deltay)
{DeltaY=deltay;}
void AnalysisInfo::SetDeltaZ(Float_t deltaz)
{DeltaZ=deltaz;}
void AnalysisInfo::SetMinTrackPoints(Int_t mintrackpoints)
{MinTrackPoints=mintrackpoints;}

void AnalysisInfo::SetTimeMarkerCut(Int_t timemarkercut)
{TimeMarkerCut=timemarkercut;}
void AnalysisInfo::SetOffTriggerCut(Int_t offtriggercut)
{OffTriggerCut=offtriggercut;}

void AnalysisInfo::SetBadPointsMask(Int_t badpointsmask)
{BadPointsMask=badpointsmask;}

void AnalysisInfo::SetSigma_0(Float_t sigma_0)
{ Sigma_0=sigma_0; }

void AnalysisInfo::SetD_trans(Float_t d_trans)
{ D_trans=d_trans; }

void AnalysisInfo::SetZ_0(Float_t z_0)
{ Z_0=z_0; }


void AnalysisInfo::SetPadResponseMethod(Int_t PRMethod)
{ PadResponseMethod=PRMethod; }

