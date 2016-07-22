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

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "TPCShaper.h"

using namespace std;


void TPCShaper( int Threshold,int TimeSlices,double Risetime, double TimeJump,
		int ADCbins,int ADCmaxcharge, double GainFactor,double IntCutOff,
		double Frequency, double ADCJitter,TPCSimChannel *channel, Int_t channr, TPCSimChanEvent *outevent)
{

  int THRESHOLD=0;
  double TIMEJUMP=TimeJump;
  int timeslices=TimeSlices;
  double risetime= Risetime;
  double frequency = Frequency;
  int adcbins =  ADCbins;
  int adcmaxcharge = ADCmaxcharge;
  double gainfactor= GainFactor;
  double adcchargefactor = (double)adcbins/(double)adcmaxcharge;
  int IsInPeak=0; // even=is not in peak, odd is in peak
  Int_t sumq=0;
  Int_t maxq=0;
  Int_t edgeq=0; // Not USED???
  Int_t maxtime=0; // Not USED???
  Int_t edgetime=0; // Not USED???
  Int_t peakwidth=0;
  int lastcharge=0;
  int lasttime=0;
  double sumTimeQ=0;
  int hitcount=0;
  int lastparticlenumber=0;
  int particlenumber=0;
  double slicewidth = 1000./frequency;
  unsigned int adcpedestal=Threshold;
  double adcjitter=ADCJitter;
  double cutoff=IntCutOff;
  
  for(int l=0;l<channel->GetNPeaks();l++)
    {
      if(l==0)
	{
	  hitcount=channel->GetPeak(l)->GetMultipleHitStatus();
	  lasttime=(int)(channel->GetPeak(l)->GetAvTime());
	  lastcharge=channel->GetPeak(l)->GetSumQ();
	  lastparticlenumber=channel->GetPeak(l)->GetParticleNr();	  
	}
      int multiplehits=channel->GetPeak(l)->GetMultipleHitStatus();
      particlenumber= channel->GetPeak(l)->GetParticleNr();	       
      int charge=channel->GetPeak(l)->GetSumQ();
      int time=(int)(channel->GetPeak(l)->GetAvTime());
      
      if (charge>THRESHOLD && fabs((double)time-lasttime)<TIMEJUMP)  
	{
	  if (IsInPeak%2==0)    // first bin in peak
	    {
	      sumq=charge;
	      if ( charge>lastcharge)
		maxq=charge;
	      else
		maxq=lastcharge;
	      edgeq=charge;
	      sumTimeQ=(double)charge*(double)time;
	      maxtime=time;
	      edgetime=time;
	      peakwidth=1;
	      IsInPeak++;
	      if(!(lastparticlenumber==particlenumber))
		hitcount+=multiplehits;
	    }
	  else                  // bin is in the peak
	    { 
	      sumq+=charge;
	      sumTimeQ+=(double)charge*(double)time;
	      peakwidth++;
	      if ( charge >maxq)
		{
		  if ( charge>lastcharge)
		    maxq=charge;
		  else
		    maxq=lastcharge;
		  maxtime=time;
		}
	      if(!(lastparticlenumber==particlenumber))
		hitcount+=multiplehits;
	    }
	  lasttime=time;
	  lastcharge=charge;
	  lastparticlenumber=particlenumber;
	}// (charge>THRESHOLD && fabs((double)time-lasttime)<TIMEJUMP)  
      else 
	{
	  if(fabs((double)time-lasttime)<TIMEJUMP) 
	    {
	      peakwidth++;
	      break;
	    } //peak continues but does not contribute, so go to next timeslice
	  else{
	    if (IsInPeak%2!=0)    // peak has ended
	      {
		double Q=(double)sumq/gainfactor;
		double sigma = risetime/3.0;
		float tav = (Double_t)sumTimeQ / (Double_t)(sumq);
		double starttime = tav-risetime;
		double stoptime= tav+cutoff*sigma;
		int timeslice = (int)(starttime/1000.0*frequency);
		//double t1=((double) timeslice)*1000./frequency+adcjitter;
		double t1 = starttime;
		double t2=(timeslice+1)*1000.0/frequency;
		double f=0.;
		bool notyetinpeak=true;
		

		while(f>0 || notyetinpeak)
		  {
		    if(t2<=stoptime)
		      f=Q/2.*(erf((t2-tav)/(sqrt(2.)*sigma))-erf((t1-tav)/(sqrt(2.)*sigma)));
		    else
		      f=Q/2.*(erf((stoptime-tav)/(sqrt(2.)*sigma))-erf((t1-tav)/(sqrt(2.)*sigma)));
		    if(f>0) notyetinpeak=false;    
		    
		    if((unsigned long int)(f*adcchargefactor)>adcpedestal && (int)(t1/1000.0*frequency)<=timeslices)
		      {
			if((long int)(f*adcchargefactor)>=adcbins) 
			  f=adcmaxcharge;
			outevent->AddChanPeak(channr, (unsigned long int)(f*adcchargefactor), 0, 0,
					      (int)(t2/1000.0*frequency -0.5),  //=avtime
					      0, 0, 1,1, 1);
		      }
		    t1=t2;
		    t2+=slicewidth;
		    if(t1>=stoptime)
		      break;
		  }

		
		if(sumTimeQ  / (Double_t)(sumq) <0) cout<<"Warning: AvTime<0"<<endl;
		IsInPeak=0;
		hitcount=multiplehits;
		if(charge>THRESHOLD)
		  {
		    IsInPeak++; // because this timeslice already belongs to next peak
		    sumq=charge;
		    if ( charge>lastcharge)
		      maxq=charge;
		    else
		      maxq=lastcharge;
		    edgeq=charge;
		    sumTimeQ=(double)(charge)*(double)time;
		    maxtime=time;
		    edgetime=time;
		    peakwidth=1;
		    lasttime=time;
		    lastcharge=charge;
		  }
		else peakwidth++;
	      }
	  }
	  lastparticlenumber=particlenumber;
	}

    } //loop over peaks
  
  if (IsInPeak%2==1)                //data ended in a peak 
    {
      if(sumTimeQ  / (Double_t)(sumq) <0) cout<<"Warning: AvTime<0"<<endl;
      IsInPeak++;
      hitcount=0;
      double Q=(double)sumq/gainfactor;
      double sigma = risetime/3.0;
      float tav = (Double_t)sumTimeQ / (Double_t)(sumq);
      double starttime = tav-risetime;
      double stoptime= tav+cutoff*sigma;
      int timeslice = (int)(starttime/1000.0*frequency);
      double t1 = starttime;
      double t2=(timeslice+1)*1000.0/frequency;
      double f=0.;
      bool notyetinpeak=true;
     
      
      while(f>0 || notyetinpeak)
	{
	  if(t2<=stoptime)
	    f=Q/2.*(erf((t2-tav)/(sqrt(2.)*sigma))-erf((t1-tav)/(sqrt(2.)*sigma)));
	  else
	    f=Q/2.*(erf((stoptime-tav)/(sqrt(2.)*sigma))-erf((t1-tav)/(sqrt(2.)*sigma)));

	  if(f>0) notyetinpeak=false;    
	  if((unsigned long int)(f*adcchargefactor)>adcpedestal && (int)(t1/1000.0*frequency)<=timeslices)
	    {
	      if((long int)(f*adcchargefactor)>=adcbins) 
		f=adcmaxcharge;
	      outevent->AddChanPeak(channr, (unsigned long int)(f*adcchargefactor), 0, 0,
				    (int)(t2/1000.0*frequency-0.5),  //=avtime
				    0, 0, 1,1, 1);
	    }
	  t1=t2;
	  t2+=slicewidth;
	  if(t1>=stoptime)
	    break;
	}
    }

  return;
}
