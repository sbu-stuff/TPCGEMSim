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

#include <TROOT.h>
#include <fstream>
#include <iostream>
#include <TFile.h>
#include <TClonesArray.h>
#include <stdio.h> 
#include <TTree.h>
#include <string>
#include "TPCShaper.h"
#include "RunParameterInfo.h"
#include "GeometryInfo.h"
#include "ElectronicsInfo.h"
#include <TString.h>
#include "TPCSimChannel.h"

using namespace std;
/** Programm to apply electronic effect like shaping and binning of chareg into ADCCounts.
 */

int main(int argc, char* argv[])
{
  if(argc != 9) 
    {
      cout << "Usage:"<<endl;
      cout<< "TPCElectronics \"InputFile with voxl information\" \"readout frequency [MHz]\" "
	  <<"\"rise time [ns]\"  \"adc resolution [bit]\" \"max. adc charge [#e-]\"  "
	  <<"\"ADC threshold (pedestal)\" \"gain factor\" \"integration cut off [sigma of gaussian]\""<< endl;
      exit(1);
    }
  const char* infilestring = argv[1]; 
  double frequency = atof(argv[2]);
  double risetime = atof(argv[3]);
  
  int adcres = atoi(argv[4]);
  int adcmaxcharge = atoi(argv[5]);
  int threshold=atoi(argv[6]);
  double gainfactor = atof(argv[7]);
  double cutoff = atof(argv[8]);
  
  //input tree
  TFile *infile=new TFile(infilestring, "READ"); // open File with TPCTracks
  if (infile==NULL)
    { cout << "Error, could not open infile: "<<infilestring<<endl;
    return -1;
    }
  else
    cout<<"Opened "<<infilestring<<endl;
  
  TTree *chantree = (TTree*)infile->Get("TimeTree");
  TPCSimChanEvent *chanevent = NULL ;
  
  RunParameterInfo *InfoRun = (RunParameterInfo*)infile->Get("RunParameterInfo"); 
  double vdrift = InfoRun->GetVDrift();
  GeometryInfo *InfoGeom = (GeometryInfo*)infile->Get("GeometryInfo"); 
  double tpclength=InfoGeom->GetTPCLength();
  TPCSimChannel *channel=NULL;
  chantree->SetBranchAddress("TimeChanEvent",&chanevent);
  //output tree
  char *outfilestring = new char[256]; 
  string endstring=string(infilestring).substr(strchr(infilestring,'_')+1-infilestring,
					       strlen(infilestring));
  sprintf(outfilestring,"TPCElectronics_%.1f_%s",frequency,endstring.c_str());
  cout<<"Output: "<<outfilestring<<endl;
  TPCSimChanEvent::Class()->IgnoreTObjectStreamer(); //whatever this does...
  TPCSimChannel::Class()->IgnoreTObjectStreamer(); //whatever this does...
  TPCSimPeak::Class()->IgnoreTObjectStreamer(); //whatever this does...
  TFile *outfile = new TFile(outfilestring,"RECREATE");
  outfile->SetCompressionLevel(1);
  TTree *outtree = new TTree("TimeTree","TimeEventTree");
  outtree->SetAutoSave(1000000000);  // autosave when 1 Gbyte written

  TPCSimChanEvent *outevent = new TPCSimChanEvent();
  TBranch *outbranch = outtree->Branch("TimeChanEvent","TPCSimChanEvent", &outevent,32000,0);
  outbranch->SetAutoDelete(kFALSE);
  InfoRun->Write();
  InfoGeom->Write();
  ElectronicsInfo *InfoElectronics = new ElectronicsInfo(risetime,1.0/frequency , 
							 adcres, adcmaxcharge, 
							 threshold);
  InfoElectronics->Write();

  int timeslices=(int)(ceil)(tpclength/vdrift*frequency);
  
  
  int timejump=(int)(3.*InfoRun->GetDiffLong()*sqrt(tpclength)/vdrift*sqrt(10.));
  int adcbins = 1;
  for(int i=0;i<adcres;i++) adcbins=adcbins*2;
  int trigger=0;
  
  for (int i=0;i<chantree->GetEntries();i++)
    {
      chantree->GetEvent(i);
      //adcjitter could be used if clock and trigger are not synchronised
      double adcjitter=0.;
      if(i%100==0)cout<<"Event "<<i<<" with "<<chanevent->GetNChan()<<"  channels"<<endl;
      for(int j=0;j<(chanevent->GetNChan());j++)
	{
	  channel=chanevent->GetChannel(j);
	  int channr=channel->GetChanNr();
	  TPCShaper(threshold,timeslices, risetime, timejump ,adcbins,adcmaxcharge,gainfactor,
		    cutoff,frequency,adcjitter,channel, channr, outevent);
	  channel->Delete();
	}//loop over channels
      
      if(outevent->GetNChan())
	{
	  outevent->SetRuntime(i); 
	  outevent->SetTrigger(chanevent->GetTrigger()); 
	  outtree->Fill();
	  trigger++;
	}
      outevent->Delete();    
  }
  outfile->Write();
  outfile->Close();
  cout<<"TPCElectronics DONE !"<<endl;
}



