# change install destination as needed
# e. g. to ${HOME}

INSTALLDIR = .
SHELL = /bin/bash

all:
	@(cd TPCInfoObjects/src; make)
	@(cd TPCSimulation/libgem; make)
	@(cd TPCSimulation; make)

gui:
	@(cd TPCSimQT; qmake; make)

doc:
	@(cd TPCSimulation; make doc)

muons:
	@(cd TPCSimulation;make -f Makefile.CreateMuons)

clean:
	@(cd TPCInfoObjects/src; make clean)
	@(cd TPCSimulation/libgem; make clean)
	@(cd TPCSimulation; make clean)
	@(cd TPCSimQT; make clean)
