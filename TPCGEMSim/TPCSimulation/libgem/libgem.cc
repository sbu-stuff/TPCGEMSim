// 
// Library with functions for parametrized charge transfer
// (single GEM coefficients + Effective Gain and Ion Feedback
// 

#include "libgem.h"

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
using namespace std;

double PAR_a=0, PAR_b=0, PAR_T=0, PAR_alpha=0, PAR_beta=0, PAR_r_eext=0, PAR_s_eext=0, PAR_e_eext=0, PAR_z_eext=0, PAR_b_eext=0, PAR_y_eext=0, PAR_r_ecoll=0, PAR_s_ecoll=0, PAR_f_ecoll=0, PAR_w_ecoll=0, PAR_r_Iext=0, PAR_s_Iext=0, PAR_y_Iext=0, PAR_r_Isext=0, PAR_s_Isext=0, PAR_a1_Isext=0, PAR_a2_Isext=0, PAR_a3_Isext=0, PAR_r_Icoll=0, PAR_s_Icoll=0, PAR_a_Icoll=0;

//
// Attributes of each single GEM
//


// Calculate Electric field in GEM hole from GEM voltage
double holefield( double gemvoltage, double upperfield, double lowerfield )
{
    return  ( PAR_a * gemvoltage + PAR_b * ( upperfield + lowerfield ) );
}

// Calculate gain of a GEM
double gain( double gemvoltage, double upperfield, double lowerfield )
{
    return PAR_beta * exp( PAR_alpha * holefield( gemvoltage, upperfield, lowerfield ) );
}

// Calculate collection efficiency of a GEM (differentiating ions/e-)
double ecoll( double field, double gemvoltage )
{
    if  ( ( field / holefield( gemvoltage, 0, 0 ) ) <= pow( PAR_r_ecoll, (1/PAR_s_ecoll) ) ) // Durchgriff vernachlässigen
        return ( 1 );
    else
        return ( PAR_r_ecoll * pow( ( field / holefield( gemvoltage, 0, 0 ) ), ( - PAR_s_ecoll ) ) );
}

double Icoll( double field, double gemvoltage )
{
    double x;

    x = ( field / holefield( gemvoltage, 0, 0 ) );

    if  ( x <= pow( PAR_r_Icoll, (1/PAR_s_Icoll) ) ) // Durchgriff vernachlässigen
//      return 1 * ( 1 - ( exp ( - PAR_a_Icoll * x ) ) );
        return 1;
    else
        return ( PAR_r_Icoll * pow( x, ( - PAR_s_Icoll ) ) ); // Korrekturfunktion (s. then-Zweig) vernachlaessigt
}

// Calculate extraction efficiency of a GEM (differentiating ions/e-)
double eextr( double field, double gemvoltage )
{
    // Calculate pseudo collection efficiency with paramteters
    // s, r as fitted to extraction

    double ecoll;
    if  ( ( field / holefield( gemvoltage, 0, 0 ) - PAR_y_eext ) <= pow( PAR_r_eext, (1/PAR_s_eext) ) ) // Durchgriff vernachlässigen
        ecoll = 1;
    else
        ecoll = ( PAR_r_eext * pow( ( field / holefield( gemvoltage, 0, 0 ) - PAR_y_eext ), ( - PAR_s_eext ) ) );
    return PAR_b_eext + ( ecoll / PAR_T ) * ( ( field / holefield( gemvoltage, 0, 0 ) ) - PAR_y_eext );
}

double Iextr_electrostatic( double field, double gemvoltage )
{
    // Calculate pseudo collection efficiency with paramteters
    // s, r as fitted to extraction
    double Icoll;
    if  ( ( field / holefield( gemvoltage, 0, 0 ) ) <= pow( PAR_r_Iext, (1/PAR_s_Iext) ) ) // Durchgriff vernachlässigen
        Icoll = 1;
    else
        Icoll = ( PAR_r_Iext * pow( ( field / holefield( gemvoltage, 0, 0 ) ), ( - PAR_s_Iext ) ) );
    return Icoll * ( field / ( holefield( gemvoltage, 0, 0 ) * PAR_T ) );
}

double Iextr( double field, double gemvoltage )
{
    return PAR_y_Iext + Iextr_electrostatic( field, gemvoltage );
}


// Calculate secondary extraction efficiency (for ions) of a GEM
double sextr( double fromfield, double gemvoltage, double tofield )
{
    // Smoothing function
    double smooth = 1 - PAR_a1_Isext * exp( - PAR_a3_Isext * fabs( ( tofield - fromfield ) / holefield( gemvoltage, 0, 0 ) ) );
    //double smooth = 1 - PAR_a1_Isext * exp( - PAR_a3_Isext * fabs( tofield / holefield( gemvoltage, 0, 0 ) - PAR_a2_Isext ) );
    // Durchgriff vernachlässigt:
    if ( tofield <= fromfield )
        return smooth * ( Iextr_electrostatic( tofield, gemvoltage ) / Iextr_electrostatic( fromfield, gemvoltage ) );
    else
        return 1 * smooth;
}


// Calculate parallel plate multiplication for other fields (2mm)
double pgain( double field )
{
   if ( field < PAR_z_eext )
      return 1;
   else
      return exp( PAR_e_eext * ( field - PAR_z_eext ) );
}




//
// Attributes of whole multi-GEM-structure
//

// Calculate effective gain
double effgain( double *params )
{
    // parallel_gain_drift * coll_gem1 * gain_gem1 * extr_gem1 *...*extr_gem3 * parallel_gain_induction

//    cout << "GEM2: ecoll " << ecoll( params[TRANS1], params[GEM2] ) << " gain " <<  gain( params[GEM2], params[TRANS1], params[TRANS2] ) << " eextr " <<  eextr( params[TRANS2], params[GEM2] )  // GEM2
//         << " following pgain " << pgain( params[TRANS2] ) << endl;
    
//    cout << "GEM3: ecoll " << ecoll( params[TRANS2], params[GEM3] ) << " gain " <<  gain( params[GEM3], params[TRANS2], params[IND] ) << " eextr " <<  eextr( params[IND], params[GEM3] )  // GEM3
//         << " following pgain " << pgain( params[IND] ) << endl;


    return ecoll( params[DRIFT], params[GEM1] ) * gain( params[GEM1], params[DRIFT], params[TRANS1] ) * eextr( params[TRANS1], params[GEM1] )   // GEM1
         * pgain( params[TRANS1] )
         * ecoll( params[TRANS1], params[GEM2] ) * gain( params[GEM2], params[TRANS1], params[TRANS2] ) * eextr( params[TRANS2], params[GEM2] )   // GEM2
         * pgain( params[TRANS2] )
         * ecoll( params[TRANS2], params[GEM3] ) * gain( params[GEM3], params[TRANS2], params[IND] ) * eextr( params[IND], params[GEM3] )  // GEM3
         * pgain( params[IND] );
}


// Calculate effective ion feedback (see thesis Sobloher p. 80)
double ionf( double *params )
{
    // Fraction produced in induction field:
    double value = 
                ecoll( params[DRIFT], params[GEM1] ) * gain( params[GEM1], params[DRIFT], params[TRANS1] ) * eextr( params[TRANS1], params[GEM1])       // e- through GEM1
              * pgain( params[TRANS1] )
              * ecoll( params[TRANS1], params[GEM2] ) * gain( params[GEM2], params[TRANS1], params[TRANS2] ) * eextr( params[TRANS2], params[GEM2] )       // e- through GEM2
              * pgain( params[TRANS2] )
              * ecoll( params[TRANS2] , params[GEM3] ) * gain( params[GEM3], params[TRANS2], params[IND] )  * eextr( params[IND], params[GEM3] )           // e- through GEM3
              * ( pgain( params[IND] ) - 1 )                                                                                                               // I+ produced
              * Icoll( params[IND], params[GEM3] ) * sextr( params[IND], params[GEM3], params[TRANS2] )                                                    // I+ through GEM3
              * Icoll( params[TRANS2], params[GEM2] ) * sextr( params[TRANS2], params[GEM2], params[TRANS1] )                                              // I+ through GEM2
              * Icoll( params[TRANS1], params[GEM1] ) * sextr( params[TRANS1], params[GEM1], params[DRIFT] );                                              // I+ through GEM1

    // Fraction produced in GEM3:
    value  += 
                ecoll( params[DRIFT], params[GEM1] ) * gain( params[GEM1], params[DRIFT], params[TRANS1] ) * eextr( params[TRANS1], params[GEM1])            // e- through GEM1
              * pgain( params[TRANS1] )
              * ecoll( params[TRANS1], params[GEM2] ) * gain( params[GEM2], params[TRANS1], params[TRANS2] ) * eextr( params[TRANS2], params[GEM2] )       // e- through GEM2
              * pgain( params[TRANS2] )
              * ecoll( params[TRANS2] , params[GEM3] )                                                                                                     // e- into GEM3
              * ( gain( params[GEM3], params[TRANS2], params[IND] ) - 1 ) * Iextr( params[TRANS2], params[GEM3] )                                          // I+ from GEM3
              * Icoll( params[TRANS2], params[GEM2] ) * sextr( params[TRANS2], params[GEM2], params[TRANS1] )                                              // I+ through GEM2
              * Icoll( params[TRANS1], params[GEM1] ) * sextr( params[TRANS1], params[GEM1], params[DRIFT] );                                              // I+ through GEM1

    // Fraction produced in transfer field 2:
    value +=  
                ecoll( params[DRIFT], params[GEM1] ) * gain( params[GEM1], params[DRIFT], params[TRANS1] ) * eextr( params[TRANS1], params[GEM1])             // e- through GEM1
              * pgain( params[TRANS1] )
              * ecoll( params[TRANS1], params[GEM2] ) * gain( params[GEM2], params[TRANS1], params[TRANS2] ) * eextr( params[TRANS2], params[GEM2] )       // e- through GEM2
              * ( pgain( params[TRANS2] ) - 1 )                                                                                                            // I+ produced
              * Icoll( params[TRANS2], params[GEM2] ) * sextr( params[TRANS2], params[GEM2], params[TRANS1] )                                              // I+ through GEM2
              * Icoll( params[TRANS1], params[GEM1] ) * sextr( params[TRANS1], params[GEM1], params[DRIFT] );                                              // I+ through GEM1

    // Fraction produced in GEM2:
    value += 
             ecoll( params[DRIFT], params[GEM1] ) * gain( params[GEM1], params[DRIFT], params[TRANS1] ) * eextr( params[TRANS1], params[GEM1])              // e- through GEM1
           * pgain( params[TRANS1] )
           * ecoll( params[TRANS1], params[GEM2] )                                                                                                          // e- into GEM2
           * ( gain( params[GEM2], params[TRANS1], params[TRANS2] ) -1 ) * Iextr( params[TRANS1], params[GEM2] )                                            // I+ from GEM2
           * Icoll( params[TRANS1], params[GEM1] ) * sextr( params[TRANS1], params[GEM1], params[DRIFT] );                                                   // I+ through GEM1

    // Fraction produced in transfer field 1:
    value += 
             ecoll( params[DRIFT], params[GEM1] ) * gain( params[GEM1], params[DRIFT], params[TRANS1] ) * eextr( params[TRANS1], params[GEM1])              // e- through GEM1
           * ( pgain( params[TRANS1] ) - 1 )                                                                                                                // I+ produced
           * Icoll( params[TRANS1], params[GEM1] ) * sextr( params[TRANS1], params[GEM1], params[DRIFT] );                                                  // I+ through GEM1

    // Fraction produced in GEM1:
    value += 
             ecoll( params[DRIFT], params[GEM1] )                                                                                                            // e- into GEM1
           * ( gain( params[GEM1], params[DRIFT], params[TRANS1] ) - 1 ) * Iextr( params[DRIFT], params[GEM1] );                                             // I+ in GEM1

    // Fraction produced in drift field is not counted, because we consider only the readout;
    // also for TPC settings there will never be parallel plate gain in the drift field.

    // Division by effective Gain
    value /= effgain( params );

    return value;
}



// Read charge transfer parameters from file 
// (instead of hardcoding as in previous versions)

int readpar( char *filename )
{
   char descriptor[20];
   double value;

   // checksum gets one bit set for every read charge transfer parameter
   // so we can check if all are specified
   int checksum=0;

   ifstream par_file;
   par_file.open( filename );

   if( ! par_file.is_open() )
      return 0;

   while( ! par_file.eof() )
      {
         par_file >> descriptor;
         par_file >> value;

         if( strcmp( descriptor, "PAR_a" ) == 0 ){
            PAR_a = value;
            checksum = checksum | 0x1;
         }

         else if( strcmp( descriptor, "PAR_b" ) == 0 ){
            PAR_b = value;
            checksum = checksum | 0x2;
         }

         else if( strcmp( descriptor, "PAR_T" ) == 0 ){
            PAR_T = value;
            checksum = checksum | 0x4;
         }

         else if( strcmp( descriptor, "PAR_alpha" ) == 0 ){
            PAR_alpha = value;
            checksum = checksum | 0x8;
         }

         else if( strcmp( descriptor, "PAR_beta" ) == 0 ){
            PAR_beta = value;
            checksum = checksum | 0x10;
         }

         else if( strcmp( descriptor, "PAR_r_eext" ) == 0 ){
            PAR_r_eext = value;
            checksum = checksum | 0x20;
         }

         else if( strcmp( descriptor, "PAR_s_eext" ) == 0 ){
            PAR_s_eext = value;
            checksum = checksum | 0x40;
         }

         else if( strcmp( descriptor, "PAR_e_eext" ) == 0 ){
            PAR_e_eext = value;
            checksum = checksum | 0x80;
         }

         else if( strcmp( descriptor, "PAR_z_eext" ) == 0 ){
            PAR_z_eext = value;
            checksum = checksum | 0x100;
         }

         else if( strcmp( descriptor, "PAR_b_eext" ) == 0 ){
            PAR_b_eext = value;
            checksum = checksum | 0x200;
         }

         else if( strcmp( descriptor, "PAR_y_eext" ) == 0 ){
            PAR_y_eext = value;
            checksum = checksum | 0x400;
         }

         else if( strcmp( descriptor, "PAR_r_ecoll" ) == 0 ){
            PAR_r_ecoll = value;
            checksum = checksum | 0x800;
         }

         else if( strcmp( descriptor, "PAR_s_ecoll" ) == 0 ){
            PAR_s_ecoll = value;
            checksum = checksum | 0x1000;
         }

         else if( strcmp( descriptor, "PAR_f_ecoll" ) == 0 ){
            PAR_f_ecoll = value;
            checksum = checksum | 0x2000;
         }

         else if( strcmp( descriptor, "PAR_w_ecoll" ) == 0 ){
            PAR_w_ecoll = value;
            checksum = checksum | 0x4000;
         }

         else if( strcmp( descriptor, "PAR_r_Iext" ) == 0 ){
            PAR_r_Iext = value;
            checksum = checksum | 0x8000;
         }

         else if( strcmp( descriptor, "PAR_s_Iext" ) == 0 ){
            PAR_s_Iext = value;
            checksum = checksum | 0x10000;
         }

         else if( strcmp( descriptor, "PAR_y_Iext" ) == 0 ){
            PAR_y_Iext = value;
            checksum = checksum | 0x20000;
         }

         else if( strcmp( descriptor, "PAR_r_Isext" ) == 0 ){
            PAR_r_Isext = value;
            checksum = checksum | 0x40000;
         }

         else if( strcmp( descriptor, "PAR_s_Isext" ) == 0 ){
            PAR_s_Isext = value;
            checksum = checksum | 0x80000;
         }

         else if( strcmp( descriptor, "PAR_a1_Isext" ) == 0 ){
            PAR_a1_Isext = value;
            checksum = checksum | 0x100000;
         }

         else if( strcmp( descriptor, "PAR_a2_Isext" ) == 0 ){
            PAR_a2_Isext = value;
            checksum = checksum | 0x200000;
         }

         else if( strcmp( descriptor, "PAR_a3_Isext" ) == 0 ){
            PAR_a3_Isext = value;
            checksum = checksum | 0x400000;
         }

         else if( strcmp( descriptor, "PAR_r_Icoll" ) == 0 ){
            PAR_r_Icoll = value;
            checksum = checksum | 0x800000;
         }

         else if( strcmp( descriptor, "PAR_s_Icoll" ) == 0 ){
            PAR_s_Icoll = value;
            checksum = checksum | 0x1000000;
         }

         else if( strcmp( descriptor, "PAR_a_Icoll" ) == 0 ){
            PAR_a_Icoll = value;
            checksum = checksum | 0x2000000;
         }
      }
   par_file.close();

   return( checksum == ( 0x4000000 - 1 ) ); // TRUE if all parameters have been read
}
