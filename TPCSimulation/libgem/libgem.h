//
// libgem.h: Header file for libgem.o:
// Library with functions for parametrized charge transfer
// (single GEM coefficients + Effective Gain and Ion Feedback
// Author: Sven Lotze 

#ifndef LIBGEM_H
 #define LIBGEM_H


// Chamber Parameters
enum parameters { DRIFT, GEM1, TRANS1, GEM2, TRANS2, GEM3, IND };



//
// Attributes of each single GEM
//


// Calculate Electric field in GEM hole from GEM voltage
double holefield( double gemvoltage, double upperfield, double lowerfield );

// Calculate gain of a GEM
double gain( double gemvoltage, double upperfield, double lowerfield );

// Calculate collection efficiency of a GEM (differentiating ions/e-)
double ecoll( double field, double gemvoltage );

double Icoll( double field, double gemvoltage );

// Calculate extraction efficiency of a GEM (differentiating ions/e-)
double eextr( double field, double gemvoltage );

double Iextr( double field, double gemvoltage );

// Calculate secondary extraction efficiency (for ions) of a GEM
double sextr( double fromfield, double gemvoltage, double tofield );

// Calculate parallel plate multiplication for other fields (2mm)
double pgain( double field );


//
// Attributes of whole multi-GEM-structure
//

// Calculate effective gain
double effgain( double *params );

// Calculate effective ion feedback (see thesis Sobloher p. 80)
double ionf( double *params );


// Read charge transfer parameters from file 
// (instead of hardcoding as in previous versions)

int readpar( char *filename );



#endif
