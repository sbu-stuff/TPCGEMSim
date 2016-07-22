
ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)

USRLIBS       = -lnsl -lcrypt -ldl -lstdc++

INCLUDEDIR    = ../include
LIBDIR        = ../lib
BINDIR        = ../bin

CC            = g++
CCFLAGS       = -g -Wall -ansi -Df2cFortran -fPIC $(ROOTCFLAGS) -I$(INCLUDEDIR)
LD            = g++
LDFLAGS       = -g -L$(LIBDIR)
SOFLAGS       = -g -shared

all:  $(LIBDIR)/libAnalysisInfo.so $(LIBDIR)/libGeometryInfo.so\
      $(LIBDIR)/libRunParameterInfo.so $(LIBDIR)/libElectronicsInfo.so\
      $(LIBDIR)/libTPCChannelInfo.so $(LIBDIR)/libTPCReadoutInfo.so 

#---------------------------------------------------------------------------------

# AnalysisInfo

$(LIBDIR)/libAnalysisInfo.so: AnalysisInfo.o  AnalysisInfoDict.o
	$(LD) -o $@ $(SOFLAGS) AnalysisInfo.o  AnalysisInfoDict.o

AnalysisInfoDict.o: AnalysisInfoDict.cxx
	$(CC) $(CCFLAGS) -c AnalysisInfoDict.cxx

AnalysisInfoDict.cxx: $(INCLUDEDIR)/AnalysisInfo.h
	rootcint -f AnalysisInfoDict.cxx -c -I$(INCLUDEDIR)\
	         AnalysisInfo.h AnalysisInfoLinkDef.h

AnalysisInfo.o: AnalysisInfo.cxx  $(INCLUDEDIR)/AnalysisInfo.h
	${CC} ${CCFLAGS} -c AnalysisInfo.cxx

#---------------------------------------------------------------------------------
# GeometryInfo

$(LIBDIR)/libGeometryInfo.so: GeometryInfo.o  GeometryInfoDict.o
	$(LD) -o $@ $(SOFLAGS) GeometryInfo.o  GeometryInfoDict.o

GeometryInfoDict.o: GeometryInfoDict.cxx
	$(CC) $(CCFLAGS) -c GeometryInfoDict.cxx

GeometryInfoDict.cxx: $(INCLUDEDIR)/GeometryInfo.h
	rootcint -f GeometryInfoDict.cxx -c -I$(INCLUDEDIR)\
	         GeometryInfo.h GeometryInfoLinkDef.h

GeometryInfo.o: GeometryInfo.cxx $(INCLUDEDIR)/GeometryInfo.h
	${CC} ${CCFLAGS} -c GeometryInfo.cxx

#---------------------------------------------------------------------------------
# RunParameterInfo

$(LIBDIR)/libRunParameterInfo.so: RunParameterInfo.o  RunParameterInfoDict.o
	$(LD) -o $@ $(SOFLAGS) RunParameterInfo.o  RunParameterInfoDict.o

RunParameterInfoDict.o: RunParameterInfoDict.cxx
	$(CC) $(CCFLAGS) -c RunParameterInfoDict.cxx

RunParameterInfoDict.cxx: $(INCLUDEDIR)/RunParameterInfo.h
	rootcint -f RunParameterInfoDict.cxx -c -I$(INCLUDEDIR)\
	         RunParameterInfo.h RunParameterInfoLinkDef.h

RunParameterInfo.o: RunParameterInfo.cxx $(INCLUDEDIR)/RunParameterInfo.h
	${CC} ${CCFLAGS} -c RunParameterInfo.cxx

#---------------------------------------------------------------------------------
# ElectronicsInfo

$(LIBDIR)/libElectronicsInfo.so: ElectronicsInfo.o  ElectronicsInfoDict.o
	$(LD) -o $@ $(SOFLAGS) ElectronicsInfo.o  ElectronicsInfoDict.o

ElectronicsInfoDict.o: ElectronicsInfoDict.cxx
	$(CC) $(CCFLAGS) -c ElectronicsInfoDict.cxx

ElectronicsInfoDict.cxx: $(INCLUDEDIR)/ElectronicsInfo.h
	rootcint -f ElectronicsInfoDict.cxx -c -I$(INCLUDEDIR)\
	         ElectronicsInfo.h ElectronicsInfoLinkDef.h

ElectronicsInfo.o: ElectronicsInfo.cxx $(INCLUDEDIR)/ElectronicsInfo.h
	${CC} ${CCFLAGS} -c ElectronicsInfo.cxx

#---------------------------------------------------------------------------------
# TPCChannelInfo

$(LIBDIR)/libTPCChannelInfo.so: TPCChannelInfo.o  TPCChannelInfoDict.o
	$(LD) -o $@ $(SOFLAGS) TPCChannelInfo.o  TPCChannelInfoDict.o

TPCChannelInfoDict.o: TPCChannelInfoDict.cxx
	$(CC) $(CCFLAGS) -c TPCChannelInfoDict.cxx

TPCChannelInfoDict.cxx: $(INCLUDEDIR)/TPCChannelInfo.h
	rootcint -f TPCChannelInfoDict.cxx -c -I$(INCLUDEDIR)\
	         TPCChannelInfo.h TPCChannelInfoLinkDef.h

TPCChannelInfo.o: TPCChannelInfo.cxx $(INCLUDEDIR)/TPCChannelInfo.h
	${CC} ${CCFLAGS} -c TPCChannelInfo.cxx

#---------------------------------------------------------------------------------
# TPCReadoutInfo

$(LIBDIR)/libTPCReadoutInfo.so: TPCReadoutInfo.o  TPCReadoutInfoDict.o
	$(LD) -o $@ $(SOFLAGS) TPCReadoutInfo.o  TPCReadoutInfoDict.o

TPCReadoutInfoDict.o: TPCReadoutInfoDict.cxx
	$(CC) $(CCFLAGS) -c TPCReadoutInfoDict.cxx

TPCReadoutInfoDict.cxx: $(INCLUDEDIR)/TPCReadoutInfo.h
	rootcint -f TPCReadoutInfoDict.cxx -c -I$(INCLUDEDIR)\
	         TPCReadoutInfo.h TPCReadoutInfoLinkDef.h

TPCReadoutInfo.o: TPCReadoutInfo.cxx $(INCLUDEDIR)/TPCReadoutInfo.h
	${CC} ${CCFLAGS} -c TPCReadoutInfo.cxx


clean:
	rm -f *.o
	rm -f *Dict.cxx
	rm -f *Dict.h
	rm -f core
	rm -f *~
