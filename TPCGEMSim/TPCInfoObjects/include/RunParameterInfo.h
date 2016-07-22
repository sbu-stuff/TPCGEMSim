#ifndef RUNPARAMETERINFO_H
#define RUNPARAMETERINFO_H

#include <TObject.h>
#include <TString.h>

/** This class stores parameters of the run or the measurement, like GEM setting, 
    Gas and its prperties.
 */
  
class RunParameterInfo : public TObject{

public:
    RunParameterInfo( const char* gas=NULL, Int_t nGems=3, Double_t eDrift=0.,
		      Double_t uGem1 =0. ,Double_t eTrans1=0., 
		      Double_t uGem2 =0. ,Double_t eTrans2=0., 
		      Double_t uGem3 =0. ,Double_t eInd   =0.,
		      Double_t B =-1);
    ~RunParameterInfo();

  void PrintAllParameters();
  TString GetInputfile();
  TString GetGas();
  TString GetParamFile();
  Int_t    GetNGems();
  Double_t GetBField();
  Double_t GetEDrift();
  Double_t GetETrans1();
  Double_t GetETrans2();
  Double_t GetEInd();
  Double_t GetUGem1();
  Double_t GetUGem2();
  Double_t GetUGem3();
  Double_t GetGainFactor();
  Double_t GetVDrift();
  Double_t GetDiffLong();
  Double_t GetDiffTrans();
  Double_t GetUFieldcage();
  Double_t GetUShielding();
  Double_t GetPressure();
  Double_t GetTemperature();
  
  void SetInputfile(const char* inputfile);	    
  void SetGas(const char* gas);	    
  void SetParamFile(const char* paramfile);	    
  void SetBField(Double_t B);	    
  void SetEDrift(Double_t eDrift);	    
  void SetETrans1(Double_t eTrans1);	    
  void SetETrans2(Double_t eTrans2);	    
  void SetEInd(Double_t eInd);	    
  void SetUGem1(Double_t uGem1);	    
  void SetUGem2(Double_t uGem2);	    
  void SetUGem3(Double_t uGem3);
  void SetGainFactor(Double_t gainfactor);
  void SetVDrift(Double_t vDrift);	    
  void SetDiffLong(Double_t diffLong);	    
  void SetDiffTrans(Double_t diffTrans);	    
  void SetUFieldcage(Double_t uFieldcage);
  void SetUShielding(Double_t uShielding);
  void SetPressure(Double_t pressure);
  void SetTemperature(Double_t temperature);
  void SetNGems(Int_t nGems);

private:
  TString Inputfile;
  TString Gas;
  TString ParamFile;
  Int_t    NGems;
  Double_t EDrift, ETrans1, ETrans2, EInd;
  Double_t UGem1,UGem2, UGem3;
  Double_t GainFactor;
  Double_t BField;
  Double_t VDrift, DiffLong,DiffTrans;
  Double_t UFieldcage;
  Double_t UShielding;
  Double_t Pressure;
  Double_t Temperature;

  ClassDef(RunParameterInfo,3)
};


#endif
