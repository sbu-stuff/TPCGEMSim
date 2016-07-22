
{
  double R=GeometryInfo->GetTPCRadius();
  double d=GeometryInfo->GetTPCLength();
  double padx=GeometryInfo->GetPadWidth();
  double pady=GeometryInfo->GetPadHeight();
  double active_x=GeometryInfo->GetActiveAreaXOffset();
  double active_y=GeometryInfo->GetActiveAreaYOffset();
  double vdrift=RunParameterInfo->GetVDrift();
  int npads=GeometryInfo->GetNPads();
  int padsinrow = GeometryInfo->GetPadsInRow();
  int padrows=(double)npads/(double)padsinrow;
  int padcolumns=padsinrow;
  
  gStyle->SetPalette(1,0);
  TPCSimChannel *channel=NULL;
  TPCSimChanEvent *event=NULL;
  TPCSimPeak *peak=NULL;
 
  TH2F* histrc = new TH2F("rowchannel","histrc",padcolumns,0,padcolumns,padrows,0,padrows);
  TH2F* hist = new TH2F("xy","padplane",(int)2*R/padx,-R,R,(int)2*R/pady,-R,R);
 
  TTree *ct=TimeTree;
  
  ct->SetBranchAddress("TimeChanEvent",&event);
  
  //for(int i=0;i<ct->GetEntries();i++)
  {
    int i=0;
    ct->GetEvent(i);
    
    for(int j=0;j<(event->GetNChan());j++)
      {
	channel=event->GetChannel(j);
	long int channr=channel->GetChanNr();
	
	int r = channr/padcolumns;
	int c = channr%padcolumns;
	double x=(c-padsinrow/2)*padx;
	double y=(r-padrows/2)*pady;
	
	int row = (int)((R+y)/pady);
	int column= (int)((R+x)/padx);
	int sum=0;
	for(int k=0;k<channel->GetNPeaks();k++)
	  {
	    peak=channel->GetPeak(k);
	    
	    int sumone=peak->GetSumQ();
	    float time=peak->GetAvTime();
	    sum+=peak->GetSumQ();
	  }
	histrc->SetBinContent(c,r,sum);
	hist->Fill(x,y,sum);
		
       }
   }
 /*  
 TCanvas pads("Padsxy","histosxy",500,700);
 
 pads.Divide(1,2);
 pads.cd(2);
 histrt->SetXTitle("z [mus]");
 histrt->SetYTitle("y [mm]");
 histrt->Draw("zcol");

 pads.cd(1);
  */
 hist->SetXTitle("x [mm]");
 hist->SetYTitle("y [mm]");
 hist->Draw("zcol");
 //   channelQ->Draw();
 //histrc->SetXTitle("column");
 //histrc->SetYTitle("row");
 //histrc->Draw("zcol");
 
}

