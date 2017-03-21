# To Do
- [ ] GarfieldPhysics.cc : set xc,yc,zc (initial position of cluster) to be variables, will be input from Monte Carlo. Undertand these, xc, yc, zc
- [ ] GarfieldRunAction.cc : Stop changing files. Open only one.
- [x] GarfieldEventAction.cc : Use global variable that increments for Event_ instead of ID.
- [ ] Document the logical flow of the code
- [ ] Fix material for Geant4, need gas for Geant4
- [ ] Get the actual gas file for Garfield??
- [ ] need to use ComponentAnalyticField->ElectricField() to set inhomogeneous E-field (400 V/cm)
- [ ] fix geometry for garfield (full size: halflength=100cm), use what Matt had. 
# Done

# Goal
- [ ] we want GEANT4 to take on ionization, then pass the output to HEED(Garfield) for drifting
- [ ] Get rid of wire (HEED)
- [ ] Give electron start and end positions
