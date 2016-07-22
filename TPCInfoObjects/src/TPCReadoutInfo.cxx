#include "TPCReadoutInfo.h"
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

ClassImp(TPCReadoutInfo)

TPCReadoutInfo::TPCReadoutInfo(Int_t nHardwareChannels, 
			       Int_t nVirtualChannels)
{
    fNHardwareChannels=nHardwareChannels;

    // number of virtual channels can not be smaller than number of
    // hardware channels
    if (nVirtualChannels<nHardwareChannels)
	fNVirtualChannels=nHardwareChannels;
    else
	fNVirtualChannels=nVirtualChannels;
 
    fMapping.Set(fNHardwareChannels);
    fChannelInfos = new TClonesArray("TPCChannelInfo",fNVirtualChannels);

    // generate the channel infos in the clones array
    for (Int_t i=0; i<fNVirtualChannels; i++)
    {
	new((*fChannelInfos)[i]) TPCChannelInfo(i);
    }

    // make trivial mapping
    for (Int_t i=0; i<fNHardwareChannels; i++)
    {
	fMapping[i]=i;
    }

    applyMappingToChannelInfos();
}

TPCReadoutInfo::~TPCReadoutInfo()
{
    delete fChannelInfos;
}

TPCChannelInfo* TPCReadoutInfo::GetChannelInfo(Int_t virtualChanNr)
{
    if (virtualChanNr <0 || virtualChanNr>=fNVirtualChannels)
    {
	cerr << "TPCReadoutInfo::GetChannelInfo :"
	     <<" Invalid virtual channel number" << virtualChanNr << endl;
	return NULL;
    }

    return dynamic_cast<TPCChannelInfo*>
	(fChannelInfos->At(virtualChanNr));
}

TString TPCReadoutInfo::GetDescription()
{
    return fDescription;
}

Int_t TPCReadoutInfo::GetVirtualChannelNumber(Int_t hardwareChanNr)
{
    if ( hardwareChanNr<0 || hardwareChanNr>=fNHardwareChannels)
    {
	cerr << "TPCReadoutInfo::GetChannelInfo :"
	     << " Invalid hardware channel number" 
	     << hardwareChanNr << endl;
	return -1;
    }

    return fMapping[hardwareChanNr];
}

Int_t TPCReadoutInfo::GetNVirtualChannels()
{
    return fNVirtualChannels;
}

Int_t TPCReadoutInfo::GetNHardwareChannels()
{
    return fNHardwareChannels;
}

TArrayI TPCReadoutInfo::GetMapping()
{
    return fMapping;
}

TClonesArray* TPCReadoutInfo::GetChannelInfoArray()
{
    return fChannelInfos;
}

void TPCReadoutInfo::SetMapping(TArrayI mapping)
{
    if (mapping.GetSize() != fNHardwareChannels)
	cerr << "TPCReadoutInfo::SetMapping : "
	     <<"Size of mapping does not match number "
	     <<" of hardware channels, noch applying new mapping." 
	     << endl;

    fMapping=mapping;

    applyMappingToChannelInfos();
}

void TPCReadoutInfo::Print()
{
    cout << fDescription << endl;
    cout << "nHardwareChannels: "<<fNHardwareChannels
	 << " ; nVirtualChannels: "<<fNVirtualChannels<<endl;
}

void TPCReadoutInfo::ReadMappingFromFile(const char *)
{
    cout << "TPCReadoutInfo::ReadMappingFromFile not implemented yet!"
	 <<endl;
}

void TPCReadoutInfo::ReadChannelInfoFromFile(const char *filename)
{
//    cout << "TPCReadoutInfo::ReadChannelInfoFromFile not implemented yet!"
//	 <<endl;

    ifstream channelInfoFile(filename);

    string line;
    
    bool inDeadChannelBlock=false;
    bool inNoisyChannelBlock=false;

    while ( getline(channelInfoFile,line) )// read all lines
    {
	// check if line contains tag "dead channels:"
	if ( line.find( string("dead channels:"),0 ) != string::npos)
	{
	    inDeadChannelBlock=true;
	    inNoisyChannelBlock=false;
	    continue;
	}
	else
	// check if line contains tag "dead channels:"
	if ( line.find( string("noisy channels:"),0 ) != string::npos)
	{
	    inDeadChannelBlock=false;
	    inNoisyChannelBlock=true;
	    continue;
	}
	else
	// try to read integers and set the flags
	if ( inDeadChannelBlock || inNoisyChannelBlock)
	{
	    int channelNr;
	    if ( sscanf(line.c_str(),"%d",&channelNr) == 1)
	    // an integer could be read successfully
	    {
		if (channelNr <0 || channelNr > fNVirtualChannels)
		{
		    cout << "TPCReadoutInfo::ReadChannelInfoFromFile :"
			 << " Invalid channel number " << channelNr 
			 <<endl;
		    continue;
		}
		if (inDeadChannelBlock)
		    GetChannelInfo(channelNr)->SetFlags(channelMode::dead);
		if (inNoisyChannelBlock)
		    GetChannelInfo(channelNr)->SetFlags(channelMode::noisy);
	    }
	}

    } // while getline
}

void TPCReadoutInfo::SetDescription(const TString description)
{
    fDescription=description;
}

void TPCReadoutInfo::applyMappingToChannelInfos()
{
    // first clear the mapping, set all channels invalid
    for (int i=0; i<fNVirtualChannels; i++)
    {
	GetChannelInfo(i)->SetHardwareChannel(-1);
    }

    for (int i=0; i<fNHardwareChannels; i++)
    {
	if (fMapping[i] < 0 || fMapping[i] >fNVirtualChannels)
	{
	    cerr << "TPCReadoutInfo::applyMappingToChannelInfos : "
		 << "Unrecoverable error: Invalid mapping: "
		 << "Virtual channel number "<<fMapping[i]<<endl;
	    exit(-1);
	}
	else
	    GetChannelInfo(fMapping[i])->SetHardwareChannel(i);
    }
}
