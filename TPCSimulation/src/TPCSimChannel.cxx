#include <iostream>
using namespace std;

#include "TPCSimChannel.h"


ClassImp(TPCSimChanEvent)
ClassImp(TPCSimChannel)
ClassImp(TPCSimPeak)


//______________________________________________________________________________
TPCSimChanEvent::TPCSimChanEvent() : TObject()
{
   // Create an TPCSimChanEvent object.

   fChans = new TClonesArray("TPCSimChannel", 100);
   fNChan = 0;
   fTrigger = -1;
   fRuntime = -1;
   
}

//______________________________________________________________________________
TPCSimChanEvent::~TPCSimChanEvent()
{

    if (fChans)
	fChans->Delete();   // here we need delete, since TPCSimChannels allocate memory for the Peaks
    if (fChans)
	delete fChans;
}

//______________________________________________________________________________
void TPCSimChanEvent::Clear()  // This does NOT free the memory allocated from the Channels
{                                      // I don't know if it's needed, just to be complete
   fNChan = 0;               // better use Delete()
   fTrigger = -1;
   fRuntime = -1;
   fChans->Clear();
}

//______________________________________________________________________________
void TPCSimChanEvent::Delete()    // frees the  memory for the Peaks, too
{
   fNChan = 0;
   fTrigger = -1;
   fRuntime = -1;
   fChans->Delete();    // here we need delete, since TPCSimChannels allocate memory for the Peaks
//   cout << "TPCSimChanEvent::Delete : fChans : " << fChans <<endl;
}

//______________________________________________________________________________
void TPCSimChanEvent::AddChanPeak(Int_t channr,Int_t sumq,Int_t edgeq,Int_t maxq,
			       Float_t avtime,Int_t edgetime,Int_t maxtime,
			       Int_t peakwidth, Int_t partnr, 
			       Int_t multiplehit)
{
   if (fNChan) // only do this test if at least one channel in array
   {
       if (  ( (TPCSimChannel*)fChans->At(fNChan-1) )->GetChanNr()  < channr )
             // new channelnumber is bigger, we need a new channel
       {
             TClonesArray &chans = *fChans;
            new(chans[fNChan++]) TPCSimChannel(channr);
       }
   }
   else // if there is no channel yet, we have to create one
   {
          TClonesArray &chans = *fChans;
          new(chans[fNChan++]) TPCSimChannel(channr);
   }

   if (  ( (TPCSimChannel*)fChans->At(fNChan-1) )->GetChanNr()  == channr )
       // now this should alway be true, if not, something's wrong
   {    // we can now add the new peak to the last channel in array
       ( (TPCSimChannel*)fChans->At(fNChan-1) )->AddPeak(sumq, edgeq, maxq, avtime,
						      edgetime, maxtime, peakwidth,
						      partnr,multiplehit);
   }
   else cout << "TPCSimEvent::AddChanPeak: Error, wrong order of channels!!" <<endl;


}

//______________________________________________________________________________
Int_t TPCSimChanEvent::GetMaxPeaks()
// calculates maximum number of peaks of all channels
{
   Int_t maxchan = 0;

     for (int i= 0; i < fNChan; i++)
       {
          if (  ( (TPCSimChannel*)fChans->At(i) ) ->GetNPeaks()  > maxchan ) // if channel(i) has more channels
             maxchan =  ( (TPCSimChannel*)fChans->At(i) ) ->GetNPeaks();   // save this number as new maximum
       }
   return maxchan;
}

//______________________________________________________________________________
TPCSimChannel* TPCSimChanEvent::GetChannel(Int_t ichannel) const
{
   if ( ichannel > -1 && ichannel < fNChan )
     return (TPCSimChannel*)fChans->At(ichannel);
   else
     return NULL;
}

//______________________________________________________________________________
TPCSimChannel::TPCSimChannel(Int_t channr) : TObject()
{
   // Create an TPCSimChannel object.

   fPeaks = new TClonesArray("TPCSimPeak", 30);
   fNPeaks = 0;
   fChanNr = channr;

}

//______________________________________________________________________________
TPCSimChannel::~TPCSimChannel()
{
   if (fPeaks)
   {
      fPeaks->Clear();   // here Clear() is sufficient, because TPCSimPeaks don't allocate memory
      if (fPeaks)
	  delete fPeaks; // here we can't do this thing one memory for all instances, because several
                              // instances are used paralelly
   }
}

//______________________________________________________________________________
void TPCSimChannel::Clear()
{
   fNPeaks = 0;
   fPeaks->Clear();
}

//______________________________________________________________________________
void TPCSimChannel::Delete()
{
   fNPeaks = 0;
   fPeaks->Delete();
}


//______________________________________________________________________________
void TPCSimChannel::AddPeak(Int_t sumq,Int_t edgeq,Int_t maxq,
			 Float_t avtime,Int_t edgetime,Int_t maxtime,Int_t peakwidth,
			 Int_t partnr, Int_t multiplehit)
{
             TClonesArray &peaks = *fPeaks;
            new(peaks[fNPeaks++]) TPCSimPeak(sumq, edgeq, maxq, avtime, edgetime, 
					  maxtime, peakwidth,partnr, multiplehit);
}


//______________________________________________________________________________
TPCSimPeak* TPCSimChannel::GetPeak(Int_t ipeak) const
{
   if ( ipeak > -1 && ipeak < fNPeaks )
     return (TPCSimPeak*)fPeaks->At(ipeak);
   else
     return NULL;
}

//______________________________________________________________________________
Int_t TPCSimChannel::GetPeakAtTime(Float_t time_at, Float_t maxpeakwidth) const
{
    TPCSimPeak *peak;

    for (Int_t i=0 ; i< fNPeaks ; i++){
        peak = (TPCSimPeak*)fPeaks->At(i);
        if ( ( peak->GetAvTime() > (time_at - maxpeakwidth) ) &&
                                  //If time between Peaks is more than Peakwidth
             ( peak->GetAvTime() < (time_at + maxpeakwidth) ) )   // Peaks do not overlap -> no Cluster

	    return i;
    }

    return -1;
}

//______________________________________________________________________________
TPCSimPeak::TPCSimPeak(Int_t sumq,Int_t edgeq,Int_t maxq, Float_t avtime, Int_t edgetime,
		 Int_t maxtime ,Int_t peakwidth, Int_t partnr,  Int_t multiplehit)
              : TObject()
{
   fSumQ=sumq;
   fEdgeQ=edgeq;
   fMaxQ=maxq;
   fAvTime=avtime;
   fEdgeTime=edgetime;
   fMaxTime=maxtime;
   fPeakWidth=peakwidth;
   fParticleNr=partnr;
   fNumberOfParticles=multiplehit;
}
