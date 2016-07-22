#ifndef ANALYSISINFO_H
#define ANALYSISINFO_H

#include <TObject.h>
#include <TString.h>

/** This class is used to store cuts during reconstruction and is not part of the simulation.*/
class AnalysisInfo : public TObject
{

 public:
    AnalysisInfo();
    ~AnalysisInfo();

    void    PrintAllParameters();

    Int_t   GetMinClusterSize();
    Float_t GetMaxTimeSpread();
    Int_t   GetChargeThresholdSim();
    Int_t   GetTimeJumpSim();
    TString GetPedestalFile();
    Float_t GetDeltaX();
    Float_t GetDeltaY();
    Float_t GetDeltaZ();
    Int_t   GetMinTrackPoints();

    Int_t   GetTimeMarkerCut();
    Int_t   GetOffTriggerCut();

    Int_t   GetBadPointsMask();

    Int_t   GetPadResponseMethod() const;
    Float_t GetSigma_0() const;
    Float_t GetD_trans() const;
    Float_t GetZ_0() const;

    void SetMinClusterSize(Int_t minclustersize);
    void SetMaxTimeSpread(Float_t maxtimespread);
    void SetChargeThresholdSim(Int_t chargethresholdsim);
    void SetTimeJumpSim( Int_t timejumpsim);
    void SetPedestalFile(const char* pedestalfile);
    void SetDeltaX(Float_t deltax);
    void SetDeltaY(Float_t deltay);
    void SetDeltaZ(Float_t deltaz);
    void SetMinTrackPoints(Int_t mintrackpoints);

    void SetTimeMarkerCut(Int_t timemarkercut);
    void SetOffTriggerCut(Int_t offtriggercut);

    void SetBadPointsMask(Int_t badpointsmask);

/** 
 * Set the pad response method used.                  <br>
 * 0 = no pad response (center of gravity)            <br>
 * 1 = gaus fit with fixed width from simulation   
 *      ( TPCCluster r109 )
 */
    void SetPadResponseMethod(Int_t PRMethod);

/**    
 * Set the width caused by diffusion etc. in the GEM stack.
 * Used in pad resonse. Units are mm.
 */
    void SetSigma_0(Float_t sigma_0);

/**
 * Set the transverse diffusion coefficient (in mm^2/sqrt(musec) ).
 * Used in pad resonse. <br> <br>
 * 
 * Attention: Be aware that the width after drifting t museconds is <br>
 *                                                                  <strong>
 * sigma = sqrt( 2 * D * t)                                         <br>
 *                                                                  </strong>
 * So D is calculated from D' (from Magboltz in mum/sqrt(cm)) <br>
 *                                                            <strong>
 * D = v_drift / 2 * D'^2
 *                                                                  </strong>
 */
    void SetD_trans(Float_t d_trans);

/**
 * Set the time offset, i. e. the time when drift distance is 0.
 * Used in pad resonse. Units are musec.
 */
    void SetZ_0(Float_t z_0);
    

 private:
    Int_t MinClusterSize;    ///< Minimum number of pads in cluster (MakePoints)
    Float_t MaxTimeSpread;   ///< Cut to seperate clusters in time (MakePoints)
    Int_t ChargeThresholdSim;///< Threshold in the simulation (CreatePeaks)
    Int_t TimeJumpSim;       ///< Cut for empty voxels in a peak (CreatePeaks)
    TString PedestalFile;    ///< Pedestals and thresholds in measurement (Peakfind)
    Float_t DeltaX,DeltaY, DeltaZ; ///< Cuts for maximum distance from predicted track (MakeTrack)
    Int_t MinTrackPoints;    ///< Minimum number of points in a track (MakeTrack)

    Int_t TimeMarkerCut;     ///< Pulses after this time sample are treated as time marker
    Int_t OffTriggerCut;     ///< Pulses starting after this time sample are treated as off trigger (cut away)

    Int_t BadPointsMask;     /**< Flags used during track reconstruction
			      *   See pointQuality struct in TPCEvent.h
			      */

   /// constants used for pad response correction
    Int_t PadResponseMethod; ///< Pad response method
    Float_t Sigma_0; ///< Width caused by diffusion in GEM stack
    Float_t D_trans; ///< Transverse diffusion coefficient
    Float_t Z_0; ///< Time offset, time when drift distance is 0
    

    ClassDef(AnalysisInfo,5)
};


#endif
