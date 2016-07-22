#include "RunParameterInfo.h"
#include <iostream>
using namespace std;

ClassImp(RunParameterInfo)

RunParameterInfo::RunParameterInfo( const char* gas, Int_t nGems,
				    Double_t eDrift,
				    Double_t uGem1, Double_t eTrans1, 
				    Double_t uGem2, Double_t eTrans2, 
				    Double_t uGem3, Double_t eInd,
				    Double_t B)
{
    if(gas)
	Gas=gas;
    else
	Gas="none";
    NGems=nGems;
    EDrift=eDrift;
    UGem1=uGem1;
    ETrans1=eTrans1;
    UGem2=uGem2;
    ETrans2=eTrans2;
    UGem3=uGem3;
    EInd=eInd;
    BField=B;

// These variables can not be set in the constructor
// They are defaulted to 0

// simulation:
    VDrift         = 0;
    DiffLong       = 0;
    DiffTrans      = 0;
    GainFactor     = 0;

    ParamFile      = "none";
    Inputfile      = "none";

// measurement
    UFieldcage     = 0;
    UShielding     = 0;
    Pressure       = 0;
    Temperature    = -273.15; //degree Centigrade
} 

RunParameterInfo::~RunParameterInfo()
{}

void RunParameterInfo::PrintAllParameters()
{
  cout<<"The Run Parameter are:"<<endl;
  cout<<"Gas    : "<<Gas<<endl;
  cout<<"NGems  : "<<NGems<< endl;
  cout<<"EDrift : "<<EDrift<<endl;
  cout<<"UGem1  : "<<UGem1 <<endl;
  cout<<"ETrans1: "<<ETrans1<<endl;
  cout<<"UGem2  : "<<UGem2 <<endl;
  cout<<"ETrans2: "<<ETrans2<<endl;
  cout<<"UGem3  : "<<UGem3 <<endl;
  cout<<"EInd   : "<<EInd<<endl;
  cout<<"BField : "<<BField<<endl<<endl;

  cout<<"Drift velocity          : "<<VDrift<<endl;
  cout<<"Longitudinal diffusion  : "<<DiffLong<<endl;
  cout<<"Transverse diffusion    : "<<DiffTrans<<endl;
  cout<<"Inputfile               : "<<Inputfile<<endl;  
  cout<<"File with GEM parameters: "<<ParamFile<<endl;
  cout<<"Gain factor: "<<GainFactor<<endl;

  cout<<"Voltage of fieldcage: "<<UFieldcage<<endl;
  cout<<"Voltage of shielding: "<<UShielding<<endl;
  cout<<"Pressure            : "<<Pressure<<endl;
  cout<<"Temperature         : "<<Temperature<<endl;
}

TString  RunParameterInfo::GetInputfile()     {return Inputfile;}
TString  RunParameterInfo::GetGas()           {return Gas;}
TString  RunParameterInfo::GetParamFile()     {return ParamFile;}
Double_t RunParameterInfo::GetBField()        {return BField;}
Double_t RunParameterInfo::GetEDrift()        {return EDrift;}
Double_t RunParameterInfo::GetETrans1()       {return ETrans1;}
Double_t RunParameterInfo::GetETrans2()       {return ETrans2;}
Double_t RunParameterInfo::GetEInd()          {return EInd;}
Double_t RunParameterInfo::GetUGem1()         {return UGem1;}
Double_t RunParameterInfo::GetUGem2()         {return UGem2;}
Double_t RunParameterInfo::GetUGem3()         {return UGem3;}
Double_t RunParameterInfo::GetGainFactor()    {return GainFactor;}
Double_t RunParameterInfo::GetVDrift()        {return VDrift;}
Double_t RunParameterInfo::GetDiffLong()      {return DiffLong;}
Double_t RunParameterInfo::GetDiffTrans()     {return DiffTrans;}
Double_t RunParameterInfo::GetUFieldcage()    {return UFieldcage;}
Double_t RunParameterInfo::GetUShielding()    {return UShielding;}
Double_t RunParameterInfo::GetPressure()      {return Pressure;}
Double_t RunParameterInfo::GetTemperature()   {return Temperature;}
Int_t    RunParameterInfo::GetNGems()         {return NGems;}


void RunParameterInfo::SetInputfile(const char* inputfile)
{
    if (inputfile)
	Inputfile=inputfile;
    else
	Inputfile="none";
}	    
void RunParameterInfo::SetGas(const char* gas)
{
    if (gas)
	Gas=gas;
    else
	Gas="none";
}	    
void RunParameterInfo::SetParamFile(const char* paramfile)
{
    if (paramfile)
	ParamFile=paramfile;
    else
	ParamFile="none";
}	    
void RunParameterInfo::SetBField(Double_t B){ BField=B;}	    
void RunParameterInfo::SetEDrift(Double_t eDrift){ EDrift=eDrift;}	    
void RunParameterInfo::SetETrans1(Double_t eTrans1){ ETrans1=eTrans1;}	    
void RunParameterInfo::SetETrans2(Double_t eTrans2){ETrans2=eTrans2;}	    
void RunParameterInfo::SetEInd(Double_t eInd){EInd=eInd;}	    
void RunParameterInfo::SetUGem1(Double_t uGem1){UGem1=uGem1;}	    
void RunParameterInfo::SetUGem2(Double_t uGem2){ UGem2=uGem2;}	    
void RunParameterInfo::SetUGem3(Double_t uGem3){UGem3=uGem3;}	   
void RunParameterInfo::SetGainFactor(Double_t gainfactor){GainFactor=gainfactor;}
void RunParameterInfo::SetVDrift(Double_t vDrift){VDrift=vDrift;}	    
void RunParameterInfo::SetDiffLong(Double_t diffLong){DiffLong=diffLong;}	    
void RunParameterInfo::SetDiffTrans(Double_t diffTrans){DiffTrans=diffTrans;}    
void RunParameterInfo::SetUFieldcage(Double_t uFieldcage){UFieldcage=uFieldcage;}
void RunParameterInfo::SetUShielding(Double_t uShielding){UShielding=uShielding;}
void RunParameterInfo::SetPressure(Double_t pressure){Pressure=pressure;}
void RunParameterInfo::SetTemperature(Double_t temperature){Temperature=temperature;}
void RunParameterInfo::SetNGems(Int_t nGems){NGems=nGems;}
