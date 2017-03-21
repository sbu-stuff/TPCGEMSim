### ATTENTION: To compile and link this program, a version of Geant4.10 has to be installed

- To run the program in batch mode, please type >./exampleGarfield -m ./run.mac.
- In run.mac one can set the material of the absorber that is used, and the type and energy of the particle that are fired with the particle gun.
- The ionization model (PAIPhot or PAI model in Geant4, Heed in Garfield++) and the valid paticle types and energy ranges  can be set in the file physics.mac.
- The program can also be run with visualization, for that type >./exampleGarfield, and then press the "run" button.

### run.mac
- Set absorber material: /exampleGarfield/absorber/setMat
- Execute physic.mac
  ???GarfieldPhysicsList.cc
    ### GarfieldPhysicsList.cc
    - "RegisterPhysics"
    ### GarfieldRunAction.cc
    - "Using Root"
    - Creating histograms: hist1-6
    - Creating ntuple: ...

/control/execute ./physics.mac
  ### physics.mac
  - Set Ionization model: /exampleGarfield/physics/setIonizationModel PAI false
    ### GarfieldMessenger.cc (IMPORTANT file: how GEANT4 commands are interpreted -> look at SetGuidance
    - SetIonizationModel
      ### GarfieldPhysics::SetIonizationModel()
      - name: PAIPhot, PAI or Heed; default is PAIPhot
      - useDefaults=true then add a bunch of particles, otherwise we have to add them manually later

/run/initialize
  ### GarfieldDetectorConstruction.cc
  - fGarfieldMessenger
  - Define Materials
  - Define Volume
    - Geometry
    - Get materials: G4_AIR, NeCF4_95_5, G4_Al, G4_W
    - Visulatization attributes
    - fGarfieldG4FastSimulationModel
      ### GarfieldG4FastSimulationModel.cc
      - InitializePhysics
      	###  GarfieldPhysics::InitializePhysics()
	- Set medium with Magboltz, also load gasfile
	- Creat fSensor, fDrift, fAvalanche, fComponentAnalyticField, fTrackHeed
	- CreateGeomtry() ??? -> another set of parameter???
      - WriteGeometryToGDML
- Something evokes the Isotope command in Messenger here
- "HADRONIC PROCESS SUMMARY"
- "Table of registered couples": list out the use materials
- Run 0 starts
  ### GarfieldRunAction::BeginOfRunAction
  - Open root file: can set different name here!
- Event 0 starts
  ### GarfieldEventAction::BeginOfEventAction
  - Currently set particleNum to # of Ntuples (which is 1), can do this with event->GetEventID()
  - Create new Ntuple with xpos, ypos, zpos
- Sensor, TrackHeed?
- Particle_1 e- 2.02636 56.0615 0.894328
  ### FastSimulationModel:DoIt
  - Kill primary track
  - Switch to Garfield
    ###GarfieldPhysics::DoIt
    - 



### Note
- Just add componentConstant, now having uniform E-field, but no changes seen so far?
-  