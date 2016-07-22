# Makefile for the ROOT test programs.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
#
# Copyright (c) 2000 Rene Brun and Fons Rademakers
#
# Author: Fons Rademakers, 29/2/2000

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)

CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared

FC            = g77
FCFLAGS       = -fno-second-underscore

CXXFLAGS     += $(ROOTCFLAGS) -I./circe7
LIBS          = $(ROOTLIBS) -lEG -lEGPythia6  -lPythia6 \
		-L/cern/pro/lib -lmathlib -lkernlib -lpacklib -lnsl \
                $(SYSLIBS) -L./circe7 -lCirce7
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)

#------------------------------------------------------------------------------


pythia:         pythia.o
		$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
		@echo "$@ done"

%.o:            %.cpp
		$(CXX) $(CXXFLAGS) -c $^ -o $@
clean:
		@rm -f pythia.o pythia core
###
