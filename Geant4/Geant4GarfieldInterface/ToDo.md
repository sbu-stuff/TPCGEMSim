# To Do
- [ ] GarfieldPhysics.cc : set xc,yc,zc (initial position of cluster) to be variables, will be input from Monte Carlo. Undertand these, xc, yc, zc
- [ ] GarfieldRunAction.cc : Stop changing files. Open only one.
- [x] GarfieldEventAction.cc : Use global variable that increments for Event_ instead of ID.
- [ ] Document the logical flow of the code

# Done
- Instead of using global variable that increments Event_ name has been changed to Particle_id#. Can be changed to 'Event' if desired in GarfieldEventAction by replacing 'Particle_' with 'Event_'.

# Goal
- [ ] we want GEANT4 to take on ionization, then pass the output to HEED(Garfield) for drifting
- [ ] Get rid of wire (HEED)
- [ ] Give electron start and end positions
