//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: GarfieldRunAction.cc 999999 2015-12-11 14:47:43Z dpfeiffe $
//
/// \file GarfieldRunAction.cc
/// \brief Implementation of the GarfieldRunAction class

#include <TFile.h>
#include <TNtuple.h>
#include <TROOT.h>
#include <TH1F.h>
#include <TH3F.h>

#include "GarfieldRunAction.hh"
#include "GarfieldAnalysis.hh"
#include "global.h"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GarfieldRunAction::GarfieldRunAction() :
		G4UserRunAction() {
	// set printing event number per each event
	G4RunManager::GetRunManager()->SetPrintProgress(1);

	// Create analysis manager
	// The choice of analysis technology is done via selectin of a namespace
	// in Garfieldnalysis.hh
	TFile *f =  new TFile("Garfield.root","UPDATE");
	//G4cout << "Using " << analysisManager->GetType() << G4endl;

	// Book histograms, ntuple
	//

	// Creating histograms
	
	
	TH1F* h1 = new TH1F("hist1", "Edep in absorber", 100, 0., 800 * MeV);
	TH1F* h2 = new TH1F("hist2", "trackL in absorber", 100, 0., 1 * m);
	TH1F* h3 = new TH1F("hist3", "Edep in gas", 1000, 0., 100 * keV);

	TH1F* h4 = new TH1F("hist4", "Avalanche size in gas", 10000,0, 10000);
	TH1F* h5 = new TH1F("hist5", "gain", 1000, 0., 100);
	TH3F* h6 = new TH3F("hist6", "Track position",200, -10*cm, 10*cm, 29, -1.45*cm, 1.45*cm, 29,-1.45*cm, 1.45*cm);
	
	// Creating ntuple
	//
	TNtuple *ntuple = new TNtuple("Garfield","Edep and TrackL","Egas:AvalancheSize:Gain:xe:ye:ze");
	f->Write();
	f->Close();
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GarfieldRunAction::~GarfieldRunAction() {
	delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GarfieldRunAction::BeginOfRunAction(const G4Run* run) {	
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GarfieldRunAction::EndOfRunAction(const G4Run* /*run*/) {
	// print histogram statistics
	//

        TFile *f =  new TFile("Garfield.root","UPDATE");
	/*if ((TH1F*)f->Get("hist1")) {
		G4cout << G4endl << " ----> print histograms statistic ";
		if (isMaster) {
			G4cout << "for the entire run " << G4endl << G4endl;
		} else {
			G4cout << "for the local thread " << G4endl << G4endl;
		}

		G4cout << " EAbs : mean = "
		       << G4BestUnit(((TH1F*) f->Get("hist1"))->mean(), "Energy")
		       << " rms = "
		       << G4BestUnit(((TH1F*)f->Get("his1"))->rms(), "Energy")
		       << G4endl;

		G4cout << " LAbs : mean = "
		       << G4BestUnit(((TH1F*)f->Get("hist2"))->mean(), "Length")
		       << " rms = "
		       << G4BestUnit(((TH1F*)f->GetH1("hist2"))->rms(), "Length")
		       << G4endl;

		G4cout << " EGas : mean = "
		       << G4BestUnit(((TH1F*)f->Get("hist3"))->mean(), "Energy")
		       << " rms = "
		       << G4BestUnit(((TH1F*)f->Get("hist3"))->rms(), "Energy")
		       << G4endl;

		G4cout << " Avalanche size : mean = "
		       << ((TH1F*)f->Get("hist4"))->mean()
		       << " rms = "
		       << ((TH1F*)f->Get("hist4"))->rms()
		       << G4endl;

		G4cout << " Gain : mean = "
		       << ((TH1F*)f->Get("hist5"))->mean()
		       << " rms = "
		       << ((TH1F*)f->Get("hist5"))->rms()
		       << G4endl;
	}*/

	// save histograms & ntuple
	//
	f->Write();
	f->Close();
	particleNum++;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
