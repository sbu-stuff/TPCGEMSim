# To Do
- [ ] AvalanchMicroscopic.cc: "No medium at initial position" in TransportElectron - something to do with sensor -> happen in avalanche, can remove
- [ ] Input from Monte Carlo, not xc,yc,zc but x_cm,y_cm,z_cm
- [ ] GarfieldRunAction.cc : Stop changing files. Open only one: try using TFile to open root file instead of analysisManager, can use "UPDATE" (look into Matt's test.C)
- [ ] Document the logical flow of the code
- [ ] Fix material for Geant4 (and for Garfield via fMediumMagboltz), need gas for Geant4: change fractionmass, ask Klaus about density (90,10)
- [ ] Get the actual gas file for Garfield??
- [ ] need to use ComponentAnalyticField->ElectricField() to set inhomogeneous E-field (400 V/cm)
- [ ] 400V/cm is too small to produce secondary electrons. How to deal with delta electron properly? Look into TPCGEMSimulation by Muennich to see the treatment for delta electrons.
- [ ] Make a run with all the fixes
- [ ] Try to get the energy/direction of delta electrons (if statement to identify electrons that are too off-track) 
# Done
- [x] GarfieldPhysics.cc : set xc,yc,zc (initial position of cluster) to be variables, understand them
- [x] GarfieldEventAction.cc : Use global variable that increments for Event_ instead of ID.
- [x] fix geometry for garfield (full size: halflength=100cm), use what Matt had. 
- [x] GEANT4 takes on ionization (set IonizationModel to PAI or PAIPhot in physics.mac) and pass the output to HEED(Garfield) for drifting (already in code)
- [x] change ComponentAnalyticField entirely to ComponentConstants???
- [x] Get rid of wire (HEED)
# Goal
- [ ] Give electron start and end positions
