#include <TROOT.h>
#include <fstream>
#include <iostream>
#include <TFile.h>
#include <TClonesArray.h>
#include <stdio.h> 
#include <TTree.h>
#include <string>
#include "TPCChannel.h"
#include <TString.h>
#include <TH1F.h>
using namespace std;
int main(int argc, char* argv[])
{
  if(argc != 2) 
    {
      cout << "Choose:"<<endl;
      cout<< "InputFile with Peaks" << endl;
      exit(1);
    }
  const char* infilestring = argv[1]; 
  
  //input tree
  TFile *infile=new TFile(infilestring, "READ"); // open File with TPCTracks
  if (infile==NULL)
    { cout << "Error, could not open infile: "<<infilestring<<endl;
    return -1;
    }
  else
    cout<<"Opened "<<infilestring<<endl;
  
  TTree *chantree = (TTree*)infile->Get("ChanTree");
  TPCChanEvent *chanevent = NULL ;
  TPCChannel *channel=NULL;
  chantree->SetBranchAddress("TPCChanEvent",&chanevent);
   char *outfilestring = new char[256];
  //output tree
  TPCPeak *peak=NULL;
  sprintf(outfilestring,"%s_MaxQ255.root",infilestring);
  TPCChanEvent::Class()->IgnoreTObjectStreamer(); //whatever this does...
  TPCChannel::Class()->IgnoreTObjectStreamer(); //whatever this does...
  TPCPeak::Class()->IgnoreTObjectStreamer(); //whatever this does...
  TFile *outfile = new TFile(outfilestring,"RECREATE");
  outfile->SetCompressionLevel(1);
  TTree *outtree = new TTree("ChanTree","ChanEventTree");
  outtree->SetAutoSave(1000000000);  // autosave when 1 Gbyte written

  TPCChanEvent *outevent = new TPCChanEvent();
  TBranch *outbranch = outtree->Branch("TPCChanEvent", "TPCChanEvent", &outevent,32000,0);
  outbranch->SetAutoDelete(kFALSE);
  // TH1F *hist=new TH1F("histo","maxq",256,0,256);
  for (int i=0;i<chantree->GetEntries();i++)
  {
      chantree->GetEvent(i);
      if(i%100==0)cout<<"Event "<<i<<" with "<<chanevent->GetNChan()<<"  channels"<<endl;
      for(int j=0;j<(chanevent->GetNChan());j++)
	{
	  channel=chanevent->GetChannel(j);
	  int channr=channel->GetChanNr();
	  for (int p=0;p<channel->GetNPeaks();p++)
	    {
	      peak=channel->GetPeak(p);
	      int maxq=peak->GetMaxQ();
	      int newmaxq=0;
	      if(maxq>50000)
		newmaxq=255;
	      else
		newmaxq=(int)(maxq*255/50000);
	      //	newmaxq=200;
	      //   hist->Fill(newmaxq);
	      if( newmaxq==0 )
		newmaxq=1;
	      outevent->AddChanPeak(channr, peak->GetSumQ(),peak->GetEdgeQ() , newmaxq,
				    peak->GetAvTime(),  //=avtime
				    peak->GetEdgeTime(),peak->GetMaxTime(),peak->GetPeakWidth(),
				    peak->GetParticleNr(),peak->GetMultipleHitStatus());
	    }
	  channel->Delete();
	}//loop over channels
      
      outevent->SetTrigger(i);
      outtree->Fill();
      outevent->Delete();    
  }
  outfile->Write();
  outfile->Close();
}



