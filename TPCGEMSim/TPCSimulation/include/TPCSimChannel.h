#ifndef TPCSim_Channel
#define TPCSim_Channel

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TPCSimChannel                                                  //
//                                                                      //
// Description of Peaks, Channels                     //
// and ChanEvents                                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TObject.h"
#include "TClonesArray.h"


// a TPCSimPeak is the information about a peak fond in a channel
// the channel is not stored in the peak!
// the peaks according to a channel are stored in a TPCSimChannel

/** A TPCSimPeak contains time information of charge deposition on one channel. */
class TPCSimPeak : public TObject {

private:
  Int_t      fSumQ;           ///< Sum of charge in peak (ADC Counts)
  Int_t      fEdgeQ;          ///< First ADC value above threshold
  Int_t      fMaxQ;           ///<Maximum ADC value in peak
  Float_t    fAvTime;           ///<Average time of peak
  Int_t	     fEdgeTime;	      ///<time of first bin above threshold
  Int_t      fMaxTime;         ///<time of MaxQ
  Int_t      fPeakWidth;      ///<width of peak (in Bins)
  Int_t      fNumberOfParticles;///< number of Particles that contributet to peak
  Int_t      fParticleNr;       ///< Particlenumber of genereator particle
  
public:
   TPCSimPeak() { }
  /*! Creates a TPCSimPeak with the following attributes:
   * \param  sumq  Sum of charge in peak (ADC Counts)
   * \param  edgeq First ADC value above threshold
   * \param  maxq Maximum ADC value in peak
   * \param  avtime Average time of peak
   * \param  edgetime Time of first bin above threshold
   * \param  maxtime Time of MaxQ
   * \param  peakwidth Width of peak (in Bins)
   * \param  partnr Particle number
   * \param multiplehit Indicates if peak was created by more than one particle
   */
  TPCSimPeak(Int_t sumq, Int_t edgeq, Int_t maxq, Float_t avtime,
	  Int_t edgetime,Int_t maxtime, Int_t peakwidth,
	  Int_t partnr =0, Int_t multiplehit =0);
  
  virtual ~TPCSimPeak() { }
  /*! Returns charge of Peak */
  Int_t       GetSumQ() const { return fSumQ; }
  /* ! Returns first ADC value above threshold */
   Int_t       GetEdgeQ() const { return fEdgeQ; }
  /* ! Returns maximum ADC value in peak*/
   Int_t       GetMaxQ() const { return fMaxQ; }
  /* ! Returns average time of peak*/
  Float_t       GetAvTime() const { return fAvTime; }
  /* ! Returns time of first bin above threshold*/
  Int_t	 GetEdgeTime() const { return fEdgeTime; }
  /* ! Returns time of MaxQ*/
  Int_t       GetMaxTime() const { return fMaxTime; }
  /* ! Returns width of peak*/
   Int_t       GetPeakWidth() const { return fPeakWidth; }
  /*! Returns particle number.*/
  Int_t GetParticleNr(){return fParticleNr;}
  /*! If peak was caused by more than one generator particle this function tells you how many. */
  Int_t GetMultipleHitStatus(){return  fNumberOfParticles;}
  ClassDef(TPCSimPeak,2)  //A peak
};


// TPCSimChannel
// containing the TPCSimPeaks

/** This class containes a TClonesArray of TPCSimPeaks.*/
class TPCSimChannel : public TObject {

private:
    Int_t         fNPeaks;    ///< Number of peaks in this channel
    Int_t         fChanNr;    ///< Number of this Channel
    TClonesArray *fPeaks;     ///< Array of peaks in this channel
  
public:
  
  TPCSimChannel() { fPeaks = NULL; }
  TPCSimChannel(Int_t);
  virtual ~TPCSimChannel();
  void          Clear();
  void          Delete();
  
  void          AddPeak(Int_t,Int_t,Int_t,Float_t,Int_t,Int_t,Int_t,
			Int_t =0,Int_t =0);
  
  
  Int_t         GetChanNr() const { return fChanNr; }
  Int_t	        GetNPeaks() const { return fNPeaks; }
  
  TClonesArray *GetPeakArray() const { return fPeaks; }
  TPCSimPeak      *GetPeak(Int_t) const;
  Int_t         GetPeakAtTime(Float_t, Float_t) const;
  
  ClassDef(TPCSimChannel,2)  //Channel
};



// TPCSimChanEvent
// containing one event in channel format

/** This class containes a TClonesArray of TPCSimChannels. */
class TPCSimChanEvent : public TObject {

private:
    Int_t         fTrigger;       ///< Trigger number
    Int_t         fRuntime;       ///< Runtime since DAQ start
    Int_t         fNChan;         ///< Number of aktive channels
    TClonesArray *fChans;         ///< Array of channels in this event
  
public:
  
  TPCSimChanEvent() ;
  virtual ~TPCSimChanEvent();
  void          Clear();
  void          Delete();
  
  void          SetTrigger(Int_t n) { fTrigger = n; }
  void          SetRuntime(Int_t n) { fRuntime = n; }
  void          AddChanPeak(Int_t,Int_t,Int_t,Int_t,Float_t,Int_t,Int_t,Int_t,
			    Int_t =0, Int_t =0);
  // ChanNr, SumQ, EdgeQ, MaxQ, AvTime, EdgeTime, Maxtime, PeakWidth,ParticleNumber,MultipleHits
  
  
  Int_t        GetTrigger() const { return fTrigger; }
  Int_t	       GetRuntime() const { return fRuntime; }
  Int_t        GetNChan() const {return fNChan; }
  Int_t        GetMaxPeaks(); ///< Returns maximum number of peaks per channel
  
  TClonesArray *GetChannelArray() const { return fChans; }
  TPCSimChannel     *GetChannel(Int_t) const;
  
  ClassDef(TPCSimChanEvent,2)  //Channel
};


#endif
