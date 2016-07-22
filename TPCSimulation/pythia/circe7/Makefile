
ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)

USRLIBS       = -lg2c -lstdc++

CC            = g++
CCFLAGS       = -g -Wall -ansi -Df2cFortran -fPIC $(ROOTCFLAGS)
LD            = g++ 
LDFLAGS       = -g
SOFLAGS       = -g -shared


all: libCirce7.so 

libCirce7.so: TCirce.o TCirceDict.o circe_interface.o circe7.o
	$(LD) TCirce.o TCirceDict.o circe_interface.o circe7.o $(ROOTLIBS) $(USRLIBS) $(SOFLAGS) -o libCirce7.so

TCirce.o: TCirce.cxx TCirce.h
	${CC} ${CCFLAGS} -c TCirce.cxx

TCirceDict.o: TCirceDict.cxx
	$(CC) $(CCFLAGS) -c TCirceDict.cxx

TCirceDict.cxx: TCirce.h
	rootcint -f TCirceDict.cxx -c TCirce.h

circe_interface.o: circe_interface.f
	g77 -c circe_interface.f

circe7.o: circe7.f
	g77 -c circe7.f

clean:
	/bin/rm -f libCirce7.so
	/bin/rm -f TCirce.o TCirceDict.o
	/bin/rm -f TCirceDict.cxx TCirceDict.h
	/bin/rm -f circe_interface.o circe7.o
	/bin/rm -f core
