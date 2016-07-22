/**
 * The TPCReadoutInfo contains information about the readout structure
 * like number of virutal channels, hardware channels, mapping,
 * an array of TPCChannelInfos etc.
 * The mapping is initialised with the trivial (1:1) mapping
 *
 */

#ifndef TPC_READOUT_INFO_H
#define TPC_READOUT_INFO_H

#include <TClonesArray.h>
#include <TArrayI.h>
#include <TString.h>

#include "TPCChannelInfo.h"

class TPCReadoutInfo : public TObject
{
 public:
    TPCReadoutInfo(Int_t nHardwareChannels = 0, 
		   Int_t nVirtualChannels  = 0);
    virtual ~TPCReadoutInfo();
    
    /// get the info object to one (virtual) channel
    TPCChannelInfo *GetChannelInfo(Int_t virtualChanNr);

    /// get the decription string
    TString GetDescription();

    /// get mapping information for one channel
    Int_t GetVirtualChannelNumber(Int_t hardwareChanNr);

    /// get number of hardware / virtual channels
    Int_t GetNVirtualChannels();
    Int_t GetNHardwareChannels();

    /// get complete mapping information
    /// (an array with the size nHardwareChannels and
    ///  the virtual channel number at position i of the hardware channel)
    TArrayI GetMapping();

    /// get array with all channel infos
    TClonesArray *GetChannelInfoArray();

    /// set mapping by giving the array
    void SetMapping(TArrayI mapping);

    /// allows to set a description string for the readout
    void SetDescription(const TString description);

    virtual void Print();

    /// read the mapping from a file
    void ReadMappingFromFile(const char *filename = "mapping.txt");

    /** Read the channel information from a file.
     *
     *  File Syntax:
     *  There might be a header with additional information.
     *  The relevant information starts with a line containing
     *  "dead channels:" (without quotation marks).
     *  All following lines contain one integer with the
     *  (virtual) channel number.
     *  The second block starts with the tag "noisy channels:"
     *
     *  Example:
     *
     *  This is header in formation which is ignored!
     *
     *  dead channels:                                <br>
     *  0                                             <br>
     *  1                                             <br>
     *  62                                            <br>
     *  63                                            <br>
     *
     *  noisy channels:                               <br>
     *  17                                            <br>
     *  23
     */
    // Note: The <br> at the end of the line are format instructions for
    // doxygen, but as only the beginning of a line is scanned they would
    // not have any effect.
    
    void ReadChannelInfoFromFile(const char *filename);



 private:
    TArrayI fMapping;

    Int_t fNHardwareChannels;
    Int_t fNVirtualChannels;

    TClonesArray *fChannelInfos;

    TString fDescription;

    /// after the mapping has changed the channel infos have to be updated
    void applyMappingToChannelInfos();

    ClassDef(TPCReadoutInfo,2)
};

#endif // TPC_READOUT_INFO_H
