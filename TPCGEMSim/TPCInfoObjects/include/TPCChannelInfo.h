#ifndef TPC_CHANNEL_INFO_H
#define TPC_CHANNEL_INFO_H

#include <TObject.h>
#include <TArrayD.h>

/// The struct with the constants of the channel status
/// (just to have names and make the code more readable)
struct channelMode
{
    static const int dead  = 1     ,
	             noisy = 1 << 1;
};

/**
 * The TPCChannelInfo contains information about one virtual channels,
 * whether a channel is dead or noisy. (It's the virtual channel because
 * a pad which is not connected is a dead channel, but it has no
 * hardware channel).
 */

class TPCChannelInfo : public TObject
{
 public:
    TPCChannelInfo(Int_t channelNr = 0);
    virtual ~TPCChannelInfo();

    /// add the flags (bits) for the existing channel
    void AddFlags(Int_t channelFlags);

    /// get the channel number
    Int_t GetChannelNumber();

    /// get the flags for one channel
    Int_t GetFlags();

    /// get the harware channel number
    Int_t GetHardwareChannel();

    /// retrieve one specific calibration factor
    Double_t GetCalibrationFactor(Int_t factorNr);

    /// get all calibration factors
    TArrayD GetCalibrationFactors();

    /// set the number of calibration constants
    Int_t GetNCalibrationFactors();

    bool IsDead(); ///< check if dead flag is set
    bool IsNoisy();///< check if noisy flag is set

    /// check if any flag (accroding to mask) is set
    bool IsBad(Int_t flagMask=0xFFFF);

    /// set one specific calibration factor
    void SetCalibrationFactor(Int_t factorNr, Double_t factorValue);

    /// set all the calibration constants using a TArrayD
    void SetCalibrationFactors(TArrayD calibrationFactors);

    /// set the channel Number
    void SetChannelNumber(Int_t channelNr);

    /// replace the flags for the channel
    void SetFlags(Int_t channelFlags);

    /// set the hardware channel
    void SetHardwareChannel(Int_t hardwareChannel);

    /// set the number of calibration constants
    void SetNCalibrationFactors(Int_t n);

    /// print flags to cout
    virtual void Print();

 private:
    /// The channel number (it's always a good idea to know who you are)
    Int_t fChannelNr;
    Int_t fHardwareChannel;

    /// the local variable containing the flags
    Int_t fFlags;

    /// Array containing calibration constants
    TArrayD fCalibrationFactors;
    

    ClassDef(TPCChannelInfo,1)
};

#endif // TPC_CHANNEL_INFO_H
