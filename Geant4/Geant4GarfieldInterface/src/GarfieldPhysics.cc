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
// $Id: GarfieldPhysics.cc 999996 2015-12-11 14:47:43Z dpfeiffe $
//
/// \file GarfieldPhysics.cc
/// \brief Implementation of the GarfieldPhysics class
#include <TFile.h>
#include <TNtuple.h>
#include <TROOT.h>

#include "GarfieldPhysics.hh"
#include "global.h"

#include "TGeoManager.h"
#include "TGeoBBox.h"

#include "GarfieldAnalysis.hh"
/*
namespace Garfield {

  namespace HeedInterface {

    Medium* medium;  }
}
*/

GarfieldPhysics* GarfieldPhysics::fGarfieldPhysics = 0;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GarfieldPhysics* GarfieldPhysics::GetInstance() {
	if (!fGarfieldPhysics) {
		fGarfieldPhysics = new GarfieldPhysics();
	}
	return fGarfieldPhysics;
}

void GarfieldPhysics::Dispose() {
	delete fGarfieldPhysics;
	fGarfieldPhysics = 0;
}

GarfieldPhysics::GarfieldPhysics() {
	fMapParticlesEnergyGeant4 = new MapParticlesEnergy();
	fMapParticlesEnergyGarfield = new MapParticlesEnergy();
	fSecondaryParticles = new std::vector<GarfieldParticle*>();
	fMediumMagboltz = 0;
	fSensor = 0;
	//fAvalanche = 0;
	fDrift = 0;
	componentConstant = 0;
	fComponentAnalyticField = 0;
	fTrackHeed = 0;
	fGeoManager = 0;
	fGeometryRoot = 0;
	fGeometrySimple = 0;
	fTube = 0;
	createSecondariesInGeant4 = false;
	fIonizationModel = "PAIPhot";
}

GarfieldPhysics::~GarfieldPhysics() {
	delete fMapParticlesEnergyGeant4;
	delete fMapParticlesEnergyGarfield;
	DeleteSecondaryParticles();
	delete fSecondaryParticles;
	delete fMediumMagboltz;
	delete fSensor;
	//delete fAvalanche;
	delete fDrift;
	delete componentConstant;
	delete fComponentAnalyticField;
	delete fTrackHeed;
	delete fGeometryRoot;
	delete fGeometrySimple;

	std::cout << "Deconstructor GarfieldPhysics" << std::endl;
}

std::string GarfieldPhysics::GetIonizationModel() {
	return fIonizationModel;
}

void GarfieldPhysics::SetIonizationModel(std::string model, bool useDefaults) {
	if (model != "PAIPhot" && model != "PAI" && model != "Heed") {

		std::cout << "Unknown ionization model " << model << std::endl;
		std::cout << "Using PAIPhot as default model!" << std::endl;
		model = "PAIPhot";
	}
	fIonizationModel = model;

	if (fIonizationModel == "PAIPhot" || fIonizationModel == "PAI") {
		if (useDefaults == true) {
			//Particle types and energies for which the G4FastSimulationModel with Garfield++ is valid
			this->AddParticleName("e-", 1e-6, 1e-3, "garfield");
			this->AddParticleName("gamma", 1e-6, 1e+8, "garfield");

			//Particle types and energies for which the PAI or PAIPhot model is valid
			this->AddParticleName("e-", 0, 1e+8, "geant4");
			this->AddParticleName("e+", 0, 1e+8, "geant4");
			this->AddParticleName("mu-", 0, 1e+8, "geant4");
			this->AddParticleName("mu+", 0, 1e+8, "geant4");
			this->AddParticleName("proton", 0, 1e+8, "geant4");
			this->AddParticleName("pi+", 0, 1e+8, "geant4");
			this->AddParticleName("pi-", 0, 1e+8, "geant4");
			this->AddParticleName("alpha", 0, 1e+8, "geant4");
			this->AddParticleName("He3", 0, 1e+8, "geant4");
			this->AddParticleName("GenericIon", 0, 1e+8, "geant4");
		}

	} else if (fIonizationModel == "Heed") {
		if (useDefaults == true) {
			//Particle types and energies for which the G4FastSimulationModel with Garfield++ is valid
			this->AddParticleName("gamma", 1e-6, 1e+8, "garfield");
			this->AddParticleName("e-", 6e-2, 1e+7, "garfield");
			this->AddParticleName("e+", 6e-2, 1e+7, "garfield");
			this->AddParticleName("mu-", 1e+1, 1e+8, "garfield");
			this->AddParticleName("mu+", 1e+1, 1e+8, "garfield");
			this->AddParticleName("pi-", 2e+1, 1e+8, "garfield");
			this->AddParticleName("pi+", 2e+1, 1e+8, "garfield");
			this->AddParticleName("kaon-", 1e+1, 1e+8, "garfield");
			this->AddParticleName("kaon+", 1e+1, 1e+8, "garfield");
			this->AddParticleName("proton", 9.e+1, 1e+8, "garfield");
			this->AddParticleName("anti_proton", 9.e+1, 1e+8, "garfield");
			this->AddParticleName("deuteron", 2.e+2, 1e+8, "garfield");
			this->AddParticleName("alpha", 4.e+2, 1e+8, "garfield");
		}

	}
}

void GarfieldPhysics::AddParticleName(const std::string particleName,
		double ekin_min_MeV, double ekin_max_MeV, std::string program) {
	if (ekin_min_MeV >= ekin_max_MeV) {
		std::cout << "Ekin_min=" << ekin_min_MeV
				<< " keV is larger than Ekin_max=" << ekin_max_MeV << " keV"
				<< std::endl;
		return;
	}

	if (program == "garfield") {
		std::cout << "Garfield model (Heed) is applicable for G4Particle "
				<< particleName << " between " << ekin_min_MeV << " MeV and "
				<< ekin_max_MeV << " MeV" << std::endl;

		fMapParticlesEnergyGarfield->insert(
				std::make_pair(particleName,
						std::make_pair(ekin_min_MeV, ekin_max_MeV)));
	} else {
		std::cout << fIonizationModel << " is applicable for G4Particle "
				<< particleName << " between " << ekin_min_MeV << " MeV and "
				<< ekin_max_MeV << " MeV" << std::endl;
		fMapParticlesEnergyGeant4->insert(
				std::make_pair(particleName,
						std::make_pair(ekin_min_MeV, ekin_max_MeV)));
	}

}

bool GarfieldPhysics::FindParticleName(std::string name, std::string program) {
	MapParticlesEnergy::iterator it;
	if (program == "garfield") {
		it = fMapParticlesEnergyGarfield->find(name);
		if (it != fMapParticlesEnergyGarfield->end()) {
			return true;
		}
		return false;
	} else {
		it = fMapParticlesEnergyGeant4->find(name);
		if (it != fMapParticlesEnergyGeant4->end()) {
			return true;
		}
		return false;
	}
}

bool GarfieldPhysics::FindParticleNameEnergy(std::string name, double ekin_MeV,
		std::string program) {
	MapParticlesEnergy::iterator it;
	if (program == "garfield") {
		it = fMapParticlesEnergyGarfield->find(name);
		if (it != fMapParticlesEnergyGarfield->end()) {
			EnergyRange_MeV range = it->second;
			if (range.first <= ekin_MeV && range.second >= ekin_MeV) {
				return true;
			}
		}
		return false;
	} else {
		it = fMapParticlesEnergyGeant4->find(name);
		if (it != fMapParticlesEnergyGeant4->end()) {
			EnergyRange_MeV range = it->second;
			if (range.first <= ekin_MeV && range.second >= ekin_MeV) {
				return true;
			}
		}
		return false;
	}
}

double GarfieldPhysics::GetMinEnergyMeVParticle(std::string name,
		std::string program) {
	MapParticlesEnergy::iterator it;
	if (program == "garfield") {
		it = fMapParticlesEnergyGarfield->find(name);
		if (it != fMapParticlesEnergyGarfield->end()) {
			EnergyRange_MeV range = it->second;
			return range.first;
		}
		return false;
	} else {
		it = fMapParticlesEnergyGeant4->find(name);
		if (it != fMapParticlesEnergyGeant4->end()) {
			EnergyRange_MeV range = it->second;
			return range.first;
		}
	}
	return -1;
}

double GarfieldPhysics::GetMaxEnergyMeVParticle(std::string name,
		std::string program) {
	MapParticlesEnergy::iterator it;
	if (program == "garfield") {
		it = fMapParticlesEnergyGarfield->find(name);
		if (it != fMapParticlesEnergyGarfield->end()) {
			EnergyRange_MeV range = it->second;
			return range.second;

		}
	} else {
		it = fMapParticlesEnergyGeant4->find(name);
		if (it != fMapParticlesEnergyGeant4->end()) {
			EnergyRange_MeV range = it->second;
			return range.second;
		}
	}
	return -1;
}

void GarfieldPhysics::InitializePhysics() {

	fMediumMagboltz = new Garfield::MediumMagboltz();

	// fMediumMagboltz->SetComposition("ar", 70., "co2", 30.);
	fMediumMagboltz->SetComposition("ne", 95., "cf4", 5.);
	fMediumMagboltz->SetTemperature(293.15);
	fMediumMagboltz->SetPressure(760.);
	fMediumMagboltz->EnableDebugging();
	fMediumMagboltz->Initialise(true);
	fMediumMagboltz->DisableDebugging();
// Set the Penning transfer efficiency.
	const double rPenning = 0.57;
	const double lambdaPenning = 0.;
	fMediumMagboltz->EnablePenningTransfer(rPenning, lambdaPenning, "ne");
	fMediumMagboltz->LoadGasFile("ne_95_cf4_5_1000mbar.gas");

	fSensor = new Garfield::Sensor();
	fDrift = new Garfield::AvalancheMC();
	//fAvalanche = new Garfield::AvalancheMicroscopic();
	fComponentAnalyticField = new Garfield::ComponentAnalyticField();

	CreateGeometry();

	fDrift->SetSensor(fSensor);
	//fAvalanche->SetSensor(fSensor);

	fTrackHeed = new Garfield::TrackHeed();
	fTrackHeed->EnableDebugging();
	fTrackHeed->SetSensor(fSensor);

	fTrackHeed->EnableDeltaElectronTransport();
}

void GarfieldPhysics::CreateGeometry() {
// Wire radius [cm]
  //const double rWire = 25.e-4;
// Radii of the tube [cm]
	const double rOuterTube = 80;
	const double rInnerTube = 20;
//	const double rTube = 1.451;
// Half-length of the tube [cm]
	const double lTube = 100.;
//	const double lTube = 10.;

	fGeometrySimple = new Garfield::GeometrySimple();
// Make a tube (centered at the origin, inner radius: 0, outer radius: rTube).
	fTube = new Garfield::SolidTube(0., 0., 0., rInnerTube, rOuterTube, lTube);
// Add the solid to the geometry, together with the medium inside.
	fGeometrySimple->AddSolid(fTube, fMediumMagboltz);

	componentConstant = new Garfield::ComponentConstant();
       	//componentConstant->SetElectricField(0, 0, 400);
       	componentConstant->SetElectricField(0, 400, 400);
       	componentConstant->SetMagneticField(0, 0, 1.5);

	componentConstant->SetGeometry(fGeometrySimple);

	fSensor->AddComponent(componentConstant);
	//fComponentAnalyticField->ElectricField

// Voltages
	//const double vWire = 1000.;
	//const double vWire = 1000.;
	//const double vTube = 0.;
// Add the wire in the center.
	//fComponentAnalyticField->AddWire(0., 0., 2 * rWire, vWire, "w");
// Add the tube.
	//fComponentAnalyticField->AddTube(rTube, vTube, 0, "t");
	//fComponentAnalyticField->AddTube(rInnerTube, 0, 0, "t");

	/*
      	fComponentAnalyticField->SetGeometry(fGeometrySimple);
	fComponentAnalyticField->AddWire(0., 0., 2 * rInnerTube, 0, "w");
	fComponentAnalyticField->AddTube(rOuterTube, 0, 0, "t");
	fSensor->AddComponent(fComponentAnalyticField);
	*/

}

void GarfieldPhysics::DoIt(std::string particleName, double ekin_MeV,
		double time, double x_cm, double y_cm, double z_cm, double dx,
		double dy, double dz) {

	TFile *f =  new TFile("Garfield.root","UPDATE");
	
	fEnergyDeposit = 0;
	DeleteSecondaryParticles();
	
	std::string particleId =  "Particle_" + particleName + "_" +  std::to_string(particleNum);
	std::string eventId = "Event_" + std::to_string(particleNum);
	G4cout<<particleId<<"\n";
	TNtuple *ntuple;
	if ((ntuple = (TNtuple*) f->Get(particleId.c_str())) == NULL)
	  {
	    G4cout << "New TNtuple";
	    ntuple = new TNtuple(particleId.c_str(), eventId.c_str(), "xpos:ypos:zpos:nc");
	  }

	//G4cout << particleId << " " << particleName << " " << time << " " << x_cm << " " <<  dx << G4endl;
// Wire radius [cm]
	//const double rWire = 25.e-4;
// Outer radius of the tube [cm]
	const double rOuterTube = 80;
	const double rInnerTube = 20;
//	const double rTube = 1.451;
// Half-length of the tube [cm]
	const double lTube = 100.;
//	const double lTube = 10.;

	double eKin_eV = ekin_MeV * 1e+6;

	double xc = 21., yc = 21., zc = 0., tc = 0.;
	//	double xc = 0., yc = 0., zc = 0., tc = 0.;
// Number of electrons produced in a collision
	int nc = 0;
// Energy loss in a collision
	double ec = 0.;
// Dummy variable (not used at present)
	double extra = 0.;
	fEnergyDeposit = 0;
	if (fIonizationModel != "Heed" || particleName == "gamma") {
		if (particleName == "gamma") {
			fTrackHeed->TransportPhoton(x_cm, y_cm, z_cm, time, eKin_eV, dx, dy,
					dz, nc);
		} else {
			fTrackHeed->TransportDeltaElectron(x_cm, y_cm, z_cm, time, eKin_eV,
					dx, dy, dz, nc);
			fEnergyDeposit = eKin_eV;
		}
		G4cout << "Collisional output " << nc << G4endl; 
		Garfield::Medium* medium = NULL;
		/*
		for (int x=-80;x<81;x+=5){
		  for (int y=-80;y<81;y+=5){
		    for (int z=-100;z<101;z+=5){
		      if (fSensor->GetMedium(x, y, z, medium)) {
			std::cerr << "    Medium at "<< x << " " <<y << " " <<z<< "\n";		
		      }
		    }
		  }
		}
		*/ 
		for (int cl = 0; cl < nc; cl++) {
			double xe, ye, ze, te;
			double ee, dxe, dye, dze;
			fTrackHeed->GetElectron(cl, xe, ye, ze, te, ee, dxe, dye, dze);
			if (ze < lTube && ze > -lTube && sqrt(xe * xe + ye * ye) < rOuterTube && sqrt(xe * xe + ye * ye) > rInnerTube) {
				nsum++;
				if (particleName == "gamma") {
					fEnergyDeposit += fTrackHeed->GetW();
				}
				//G4cout << "cl,xe,ye,ze,te,ee,dxe" << " " << cl <<" " << xe <<" " << ye <<" " << ze <<" " << te <<" " << ee <<" " << dxe << G4endl;
				ntuple->Fill(xe,ye,ze,nc);
				if (createSecondariesInGeant4) {
					double newTime = te;
					if (newTime < time) {
						newTime += time;
					}
					fSecondaryParticles->push_back(
							new GarfieldParticle("e-",ee, newTime, xe, ye, ze, dxe,
									dye, dze));
				}

				fDrift->DriftElectron(xe, ye, ze, te);

				double xe1, ye1, ze1, te1;
				double xe2, ye2, ze2, te2;

				int status;
				fDrift->GetElectronEndpoint(0, xe1, ye1, ze1, te1, xe2, ye2,
						ze2, te2, status);

				if (0 < xe2 && xe2 < rInnerTube) {
					xe2 += 2 * rInnerTube;
				}
				if (0 > xe2 && xe2 > -rInnerTube) {
					xe2 += -2 * rInnerTube;
				}
				if (0 < ye2 && ye2 < rInnerTube) {
					ye2 += 2 * rInnerTube;
				}
				if (0 > ye2 && ye2 > -rInnerTube) {
					ye2 += -2 * rInnerTube;
				}
				/*
				if (0 < xe2 && xe2 < rWire) {
					xe2 += 2 * rWire;
				}
				if (0 > xe2 && xe2 > -rWire) {
					xe2 += -2 * rWire;
				}
				if (0 < ye2 && ye2 < rWire) {
					ye2 += 2 * rWire;
				}
				if (0 > ye2 && ye2 > -rWire) {
					ye2 += -2 * rWire;
				}
				*/
				double e2 = 0.1;
				/*
				Garfield::Medium* medium = NULL;
				if (fSensor->GetMedium(xe1, ye1, ze1, medium)) {
				  std::cerr << "    Medium at "<< xe1 << " " <<ye1 << " " <<ze1<< "\n";		}
				
				if (!fSensor->GetMedium(xe2, ye2, ze2, medium)) {
				  std::cerr << "    No medium at "<< xe2 << " " <<ye2 << " " <<ze2<< "\n";		}
				
				if (fSensor->GetMedium(xe2+1., ye2-1., (ze2-1.), medium)) {
				  std::cerr << "    Medium at varied "<< xe2+1. << " " <<ye2 -1.<< " " <<(ze2-1.)<< "\n";		}
				else {std::cerr << "    No medium at varied "<< xe2+1. << " " <<ye2 -1.<< " " <<(ze2-1.)<< "\n";}
				
				fAvalanche->AvalancheElectron(xe2, ye2, ze2, te2, e2, 0, 0, 0);

				int ne = 0, ni = 0;
				fAvalanche->GetAvalancheSize(ne, ni);
				fAvalancheSize += ne;
				*/
			}
		}
	} else {
		fTrackHeed->SetParticle(particleName);
		fTrackHeed->SetKineticEnergy(eKin_eV);
		fTrackHeed->NewTrack(x_cm, y_cm, z_cm, time, dx, dy, dz);

		while (fTrackHeed->GetCluster(xc, yc, zc, tc, nc, ec, extra)) {
			if (zc < lTube && zc > -lTube && sqrt(xc * xc + yc * yc) < rOuterTube && sqrt(xc * xc + yc * yc) > rInnerTube) {
				nsum += nc;
				fEnergyDeposit += ec;
				for (int cl = 0; cl < nc; cl++) {
					double xe, ye, ze, te;
					double ee, dxe, dye, dze;
					fTrackHeed->GetElectron(cl, xe, ye, ze, te, ee, dxe, dye,
							dze);
					if (ze < lTube && ze > -lTube
							&& sqrt(xe * xe + ye * ye) < rOuterTube && sqrt(xe * xe + ye * ye) > rInnerTube) {
					  G4cout << ">>>>>>>>H3 2nd input "<< ze << " " << xe << " " << ye << G4endl;
						if (createSecondariesInGeant4) {
							double newTime = te;
							if (newTime < time) {
								newTime += time;
							}
							fSecondaryParticles->push_back(
									new GarfieldParticle("e-", ee, newTime, xe, ye,
											ze, dxe, dye, dze));
						}

						fDrift->DriftElectron(xe, ye, ze, te);

						double xe1, ye1, ze1, te1;
						double xe2, ye2, ze2, te2;

						int status;
						fDrift->GetElectronEndpoint(0, xe1, ye1, ze1, te1, xe2,
								ye2, ze2, te2, status);
						/*
						if (0 < xe2 && xe2 < rWire) {
							xe2 += 2 * rWire;
						}
						if (0 > xe2 && xe2 > -rWire) {
							xe2 += -2 * rWire;
						}
						if (0 < ye2 && ye2 < rWire) {
							ye2 += 2 * rWire;
						}
						if (0 > ye2 && ye2 > -rWire) {
							ye2 += -2 * rWire;
						}
						*/
						if (0 < xe2 && xe2 < rInnerTube) {
						  xe2 += 2 * rInnerTube;
						}
						if (0 > xe2 && xe2 > -rInnerTube) {
						  xe2 += -2 * rInnerTube;
						}
						if (0 < ye2 && ye2 < rInnerTube) {
						  ye2 += 2 * rInnerTube;
						}
						if (0 > ye2 && ye2 > -rInnerTube) {
						  ye2 += -2 * rInnerTube;
						}

						double e2 = 0.1;
						/*fAvalanche->AvalancheElectron(xe2, ye2, ze2, te2, e2, 0,
								0, 0);

						int ne = 0, ni = 0;
						fAvalanche->GetAvalancheSize(ne, ni);
						fAvalancheSize += ne;
						*/
					}
				}

			}
		}
	}
	//fGain = fAvalancheSize / nsum;

       	//ntuple->Write();
	f->Write("", TObject::kOverwrite);
	f->Close();
}

std::vector<GarfieldParticle*>* GarfieldPhysics::GetSecondaryParticles() {
	return fSecondaryParticles;
}

void GarfieldPhysics::DeleteSecondaryParticles() {
	if (!fSecondaryParticles->empty()) {
		fSecondaryParticles->erase(fSecondaryParticles->begin(),
				fSecondaryParticles->end());
	}
}


