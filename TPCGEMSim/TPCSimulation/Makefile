#Makefile for TPC Simulation Package
#Author: Astrid Muennich

INSTALLDIR    = .
INCLUDEDIR    = $(INSTALLDIR)/include
INCLUDEDIREXT = $(TPCSIMLIBS)/include
LIBDIR	      = $(INSTALLDIR)/lib
LIBDIREXT     = $(TPCSIMLIBS)/lib
OBJECTDIR     = $(INSTALLDIR)/obj
BINARYDIR     = $(INSTALLDIR)/bin
SOURCEDIR     = $(INSTALLDIR)/src
ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs) -lMinuit -lPhysics -lEG
ROOTGLIBS     = $(shell root-config --glibs)

#CERNLIB      = -L $(HOME)/lib/cern  -lpacklib -lm -lmathlib -lkernlib -lnsl
LIBS          = $(ROOTLIBS)  -L ./bin   -lgslcblas -lgsl -L$(LIBDIREXT) 
CXX           = g++
CXXFLAGS      =  -O3 -Wall $(SHADOWWARNING) -fPIC $(ROOTCFLAGS) -I. -I$(INCLUDEDIR) -I$(INCLUDEDIREXT) -I$(GSL)/include
CXXFLAGSP     = -g3 -pg -Wall $(SHADOWWARNING) -fPIC $(ROOTCFLAGS) -I. -I$(INCLUDEDIR) -I$(GSL)/include
LD            = g++
LDFLAGS       =  -O3 -L$(INSTALLDIR)/lib -L$(GSL)/lib
LDFLAGSP      = -g3 -pg -L$(INSTALLDIR)/lib -L$(GSL)/lib
SOFLAGS       = -shared

all: $(BINARYDIR)/TPCIonisation  $(BINARYDIR)/TPCDrift $(BINARYDIR)/TPCPads $(BINARYDIR)/TPCElectronics

#---------------------------------------------------------
# TPCIonisation

$(BINARYDIR)/TPCIonisation: $(OBJECTDIR)/TPCIonisation.o $(OBJECTDIR)/HepInterface.o $(OBJECTDIR)/MakePrimaryIonisation.o \
	$(LIBDIREXT)/libRunParameterInfo.so $(LIBDIREXT)/libGeometryInfo.so $(LIBDIR)/libTPCSimTrack.so $(LIBDIR)/libTPCElectron.so 
	$(LD) $(LDFLAGS) -o $@  $(OBJECTDIR)/TPCIonisation.o $(OBJECTDIR)/MakePrimaryIonisation.o $(OBJECTDIR)/HepInterface.o \
	$(LIBS) -lRunParameterInfo -lGeometryInfo -lTPCSimTrack -lTPCElectron 

$(OBJECTDIR)/TPCIonisation.o: $(SOURCEDIR)/TPCIonisation.cpp $(INCLUDEDIR)/TPCElectron.h  $(INCLUDEDIREXT)/RunParameterInfo.h \
	$(INCLUDEDIREXT)/GeometryInfo.h $(INCLUDEDIR)/TPCSimTrack.h $(INCLUDEDIR)/HepInterface.h  $(INCLUDEDIR)/MakePrimaryIonisation.h
	$(CXX) -c  $(SOURCEDIR)/TPCIonisation.cpp $(CXXFLAGS)  -o $@

$(OBJECTDIR)/MakePrimaryIonisation.o:  $(SOURCEDIR)/MakePrimaryIonisation.cpp $(INCLUDEDIR)/MakePrimaryIonisation.h 
	$(CXX) -c  $(SOURCEDIR)/MakePrimaryIonisation.cpp $(CXXFLAGS)  -o $@

$(OBJECTDIR)/HepInterface.o:  $(SOURCEDIR)/HepInterface.cpp $(INCLUDEDIR)/HepInterface.h
	$(CXX) -c  $(SOURCEDIR)/HepInterface.cpp $(CXXFLAGS)  -o $@

# TPCSimTrack
$(LIBDIR)/libTPCSimTrack.so: $(OBJECTDIR)/TPCSimTrack.o $(OBJECTDIR)/TPCSimTrackDict.o
	$(CXX) $(SOFLAGS) -o $@ $^

$(OBJECTDIR)/TPCSimTrackDict.o:  $(SOURCEDIR)/TPCSimTrackDict.cpp
	$(CXX) $(CXXFLAGS) -c  $(SOURCEDIR)/TPCSimTrackDict.cpp  -o $@

$(SOURCEDIR)/TPCSimTrackDict.cpp: $(INCLUDEDIR)/TPCSimTrack.h $(INCLUDEDIR)/TPCSimTrackLinkDef.h
	rootcint -f $(SOURCEDIR)/TPCSimTrackDict.cpp -c $(INCLUDEDIR)/TPCSimTrack.h $(INCLUDEDIR)/TPCSimTrackLinkDef.h	

$(OBJECTDIR)/TPCSimTrack.o: $(SOURCEDIR)/TPCSimTrack.cxx $(INCLUDEDIR)/TPCSimTrack.h
	$(CXX) $(CXXFLAGS) -c $(SOURCEDIR)/TPCSimTrack.cxx -o $@

#TPCElectron
$(LIBDIR)/libTPCElectron.so: $(OBJECTDIR)/TPCElectron.o $(OBJECTDIR)/TPCElectronDict.o
	$(CXX) $(SOFLAGS) -o $@ $^

$(OBJECTDIR)/TPCElectronDict.o:  $(SOURCEDIR)/TPCElectronDict.cpp
	$(CXX) $(CXXFLAGS) -c  $(SOURCEDIR)/TPCElectronDict.cpp  $(CXXFLAGS) -o $@

$(SOURCEDIR)/TPCElectronDict.cpp: $(INCLUDEDIR)/TPCElectron.h $(INCLUDEDIR)/TPCElectronLinkDef.h
	rootcint -f  $(SOURCEDIR)/TPCElectronDict.cpp -c $(INCLUDEDIR)/TPCElectron.h $(INCLUDEDIR)/TPCElectronLinkDef.h	

$(OBJECTDIR)/TPCElectron.o: $(SOURCEDIR)/TPCElectron.cxx $(INCLUDEDIR)/TPCElectron.h
	$(CXX) $(CXXFLAGS) -c $(SOURCEDIR)/TPCElectron.cxx -o $@

# TPCSimChannel

$(LIBDIR)/libTPCSimChannel.so: $(OBJECTDIR)/TPCSimChannel.o  $(OBJECTDIR)/TPCSimChannelDict.o
	$(CXX) $(SOFLAGS) -o $@ $^

$(OBJECTDIR)/TPCSimChannelDict.o: $(SOURCEDIR)/TPCSimChannelDict.cxx
	$(CXX) $(CXXFLAGS) -c  $(SOURCEDIR)/TPCSimChannelDict.cxx -o $@

$(SOURCEDIR)/TPCSimChannelDict.cxx: $(INCLUDEDIR)/TPCSimChannel.h $(INCLUDEDIR)/TPCSimChannelLinkDef.h
	rootcint -f $(SOURCEDIR)/TPCSimChannelDict.cxx -c $(INCLUDEDIR)/TPCSimChannel.h $(INCLUDEDIR)/TPCSimChannelLinkDef.h

$(OBJECTDIR)/TPCSimChannel.o: $(SOURCEDIR)/TPCSimChannel.cxx $(INCLUDEDIR)/TPCSimChannel.h
	${CXX} ${CXXFLAGS} -c $(SOURCEDIR)/TPCSimChannel.cxx -o $@


#TPCDrift

$(BINARYDIR)/TPCDrift: $(OBJECTDIR)/TPCDrift.o $(OBJECTDIR)/TrackDrifter.o $(LIBDIREXT)/libRunParameterInfo.so $(LIBDIREXT)/libGeometryInfo.so\
	 $(LIBDIR)/libTPCElectron.so $(LIBDIR)/libTPCSimTrack.so
	$(LD) $(LDFLAGS) -o $@ $(OBJECTDIR)/TPCDrift.o $(OBJECTDIR)/TrackDrifter.o $(LIBS)  -lRunParameterInfo -lGeometryInfo -lTPCSimTrack -lTPCElectron

$(OBJECTDIR)/TPCDrift.o:  $(SOURCEDIR)/TPCDrift.cpp $(INCLUDEDIR)/TrackDrifter.h $(INCLUDEDIR)/TPCElectron.h $(INCLUDEDIR)/TPCSimTrack.h  \
	$(INCLUDEDIREXT)/RunParameterInfo.h $(INCLUDEDIREXT)/GeometryInfo.h
	$(CXX) -c  $(SOURCEDIR)/TPCDrift.cpp $(CXXFLAGS)  -o $@

$(OBJECTDIR)/TrackDrifter.o:  $(SOURCEDIR)/TrackDrifter.cpp $(INCLUDEDIR)/TrackDrifter.h $(INCLUDEDIR)/TPCSimTrack.h
	$(CXX) -c  $(SOURCEDIR)/TrackDrifter.cpp $(CXXFLAGS)  -o $@


# TPCPads
$(BINARYDIR)/TPCPads: $(OBJECTDIR)/TPCPads.o $(OBJECTDIR)/TrackDrifter.o $(OBJECTDIR)/TPCVoxel.o  $(INSTALLDIR)/libgem/libgem.o\
	 $(OBJECTDIR)/MakePads.o $(LIBDIREXT)/libRunParameterInfo.so $(LIBDIREXT)/libGeometryInfo.so $(LIBDIR)/libTPCElectron.so \
	$(LIBDIR)/libTPCSimTrack.so $(LIBDIR)/libTPCSimChannel.so 
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTDIR)/TPCPads.o $(OBJECTDIR)/TrackDrifter.o $(OBJECTDIR)/TPCVoxel.o $(INSTALLDIR)/libgem/libgem.o\
	 $(OBJECTDIR)/MakePads.o $(LIBS) -lRunParameterInfo -lGeometryInfo -lTPCElectron  -lTPCSimTrack -lTPCSimChannel 

$(OBJECTDIR)/TPCPads.o:  $(SOURCEDIR)/TPCPads.cpp $(INCLUDEDIR)/TrackDrifter.h $(INCLUDEDIR)/TPCElectron.h $(INCLUDEDIR)/TPCSimTrack.h \
	$(INCLUDEDIREXT)/RunParameterInfo.h $(INCLUDEDIREXT)/GeometryInfo.h $(INCLUDEDIR)/TPCVoxel.h  $(INCLUDEDIR)/MakePads.h $(INCLUDEDIR)/TPCSimChannel.h 
	$(CXX) -c  $(SOURCEDIR)/TPCPads.cpp $(CXXFLAGS)  -o $@

$(OBJECTDIR)/MakePads.o:  $(SOURCEDIR)/MakePads.cpp $(INCLUDEDIR)/MakePads.h $(INCLUDEDIR)/TPCVoxel.h 
	$(CXX) -c  $(SOURCEDIR)/MakePads.cpp $(CXXFLAGS)  -o $@


$(OBJECTDIR)/TPCVoxel.o:  $(SOURCEDIR)/TPCVoxel.cpp $(INCLUDEDIR)/TPCVoxel.h
	$(CXX) -c  $(SOURCEDIR)/TPCVoxel.cpp $(CXXFLAGS)  -o $@

$(INSTALLDIR)/libgem/libgem.o: $(INSTALLDIR)/libgem/libgem.cc $(INSTALLDIR)/libgem/libgem.h
	g++ -c $(INSTALLDIR)/libgem/libgem.cc -o $(INSTALLDIR)/libgem/libgem.o


#TPCElectronics
$(BINARYDIR)/TPCElectronics: $(OBJECTDIR)/TPCElectronics.o  $(OBJECTDIR)/TPCShaper.o $(LIBDIREXT)/libRunParameterInfo.so \
	$(LIBDIREXT)/libGeometryInfo.so $(LIBDIR)/libTPCSimChannel.so 
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTDIR)/TPCElectronics.o $(OBJECTDIR)/TPCShaper.o $(LIBS) -lRunParameterInfo \
	-lGeometryInfo -lTPCSimChannel -lElectronicsInfo

$(OBJECTDIR)/TPCElectronics.o: $(SOURCEDIR)/TPCElectronics.cpp $(INCLUDEDIR)/TPCShaper.h 
	$(CXX) -c  $(SOURCEDIR)/TPCElectronics.cpp $(CXXFLAGS)  -o $@

$(OBJECTDIR)/TPCShaper.o: $(SOURCEDIR)/TPCShaper.cpp $(INCLUDEDIR)/TPCShaper.h $(LIBDIR)/libTPCSimChannel.so 
	$(CXX) -c  $(SOURCEDIR)/TPCShaper.cpp	$(CXXFLAGS)  -o $@ -lTPCSimChannel 

doc: Doxyfile
	doxygen Doxyfile


clean:
	rm -f $(OBJECTDIR)/*.o	
	rm -f $(SOURCEDIR)/*Dict.cxx
	rm -f $(SOURCEDIR)/*Dict.cpp
	rm -f $(SOURCEDIR)/*Dict.h
	rm -f core


