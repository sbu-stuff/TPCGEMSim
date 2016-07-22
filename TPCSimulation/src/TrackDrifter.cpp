//*****************************************************
// Part of program to simulate a TPC with GEM readout *
//                                                    *
// Author: Astrid Muennich                            *
//                                                    *
//   Astrid Muennich                                  *
//   RWTH Aachen, III. Phys. Inst. B                  * 
//   Office: 28 A 112, Phone: +49/(0)241/8            *
//   Email: muennich@physik.rwth-aachen.de            * 
//                                                    *
//*****************************************************


#include "TrackDrifter.h"
#include <math.h>
#include <iostream>
#include <string.h>
using namespace std;
#define C 0.299792458 // speed of light / Giga

TrackDrifter::TrackDrifter(const char* in_Gas,double in_B, 
			   double in_Efield, double in_distance, 
			   double radius, double inner_radius )
{
  B = in_B;
  E = in_Efield;
  Gas = in_Gas;
  TPCHalfLength = in_distance;
  numberofelectrons=0;
  x_e=0.,y_e=0.,z_e=0.,t_e=0.; 
  
  distance=0.;
  r=gsl_rng_alloc(gsl_rng_mt19937);
  xdrift=0., ydrift=0.,zdrift=0.,tdrift=0. ;
  TPCRadius=radius;
  TPCInnerRadius=inner_radius;
}



TrackDrifter::~TrackDrifter()
{
}

void TrackDrifter::DriftElectron(TPCSimTrack *drifttrack)
{
  if(z_e<0) distance=-TPCHalfLength; // decide witch readoutplane
  else distance=TPCHalfLength;
  MakeElectronDriftCoordinates();
  //check if e- driftet out ouf TPC volume
  if(xdrift*xdrift+ydrift*ydrift<=TPCRadius*TPCRadius &&
     xdrift*xdrift+ydrift*ydrift>=TPCInnerRadius*TPCInnerRadius) 
    {
      drifttrack->AddTPCElectron(eventnr,particlenr,xdrift,ydrift,zdrift,tdrift); // coordinates in mm
      numberofelectrons++;
    }
}

void TrackDrifter::InitializeNumberElectrons()
{
  numberofelectrons=0;
}

void TrackDrifter::GetTrackParameter(TPCSimTrack *drifttrack)
{
  eventnr=drifttrack->GetEventNumber();
  particlenr=drifttrack->GetParticleNumber();
  isCurler=drifttrack->GetCurlerStatus();
}

void TrackDrifter::SetTrackParameter(TPCSimTrack *drifttrack)
{
  drifttrack->SetTrackParameters(eventnr,particlenr,numberofelectrons,isCurler);

}

void TrackDrifter::GetElectronCoordinates(TPCElectron *electron)
{
  x_e=electron->GetX(); //input in mm 
  y_e=electron->GetY();
  z_e=electron->GetZ();
  t_e=electron->GetTime();
}

void TrackDrifter::MakeElectronDriftCoordinates()
{
  //drift electron
  double driftdistance = distance-z_e;	
  double meandrift = sqrt(fabs(driftdistance/10.))/1000.;
  double gaus_transx=gsl_ran_gaussian(r,difftrans*meandrift);
  double gaus_transy=gsl_ran_gaussian(r,difftrans*meandrift);
  double gaus_long=gsl_ran_gaussian(r,difflong*sqrt(fabs(driftdistance/10.))/1000.); 
  // for diffusion full tpc length, t=0 at fist GEMS, rest of transverse diff is done between GEMS in TPCPads
  tdrift = t_e + (fabs(driftdistance)+gaus_long)/(vdrift); // [mus]
  xdrift = x_e + gaus_transx; // [mm]
  ydrift = y_e + gaus_transy;
  zdrift = z_e + driftdistance;
}


void TrackDrifter::InitializeDriftValues()
{
  cout<<"Drifting for "<<Gas<<" gas with E="<<E<<" V/cm, "<<endl;
   
  if(strcmp(Gas,"TDR")==0)
    {
      difflong=CalculateGasParameter( -110369.279057625,
				      220779.365529786 ,
				      -187931.357154949,
				      90465.0565843025 ,
				      -27363.2494470196,
				      5451.70005605478 ,
				      -727.005814951371,
				      64.2889479781    ,
				      -3.61907342719664,
				      0.117440351004847,
				      -0.00167233389877851);
      cout<<"dl="<<difflong<<"  [mum/sqrt(cm)]"<<endl;
      //only for E<10000 v/cm
      vdrift=10*CalculateGasParameter(-2087.14481157477,
				    4988.19775908129  ,
				    -5213.28050066342 ,
				    3134.02364965672  ,
				    -1199.06293662325 ,
				    304.93453476299   ,
				    -52.2070052208005 ,
				    5.94607746435271  ,
				    -0.431707055905293,
				    0.0180715488714349,
				   -0.000331805483109844);
      cout<<"v_d="<<vdrift<<" [mm/mus]"<<endl;
    }

  if(strcmp(Gas,"P10")==0)
    {
      difflong=CalculateGasParameter( 56323.2298716282   ,
				      -104137.055803	 ,
				      84443.4053447754	 ,
				      -38744.2017170156	 ,
				      11144.8199782006	 ,
				      -2108.00545694589	 ,
				      266.523751314122	 ,
				      -22.3152100099685	 ,
				      1.18752302003322	 ,
				      -0.0363634262572915,
				      0.000487691075825722);
      cout<<"dl="<<difflong<<"  [mum/sqrt(cm)]"<<endl;
      //only for E<10000 v/cm
      vdrift=10*CalculateGasParameter( 1862.50727805909    ,
				    -4100.98694313903	,
				    3932.6230354755	,
				    -2160.5991694089	,
				    752.872704920645	,
				    -173.939322553779	,
				    27.0266629604996	,
				    -2.79534719623288	,
				    0.18467738994886	,
				    -0.00705629626191505,
				    0.00011870800945113);
      cout<<"v_d="<<vdrift<<" [mm/mus]"<<endl;
    }
  
  if(strcmp(Gas,"P5")==0)
    {
      difflong=CalculateGasParameter( 66540.3253522381  ,
				      -125892.973218309	,
				      105109.552186917	,
				      -49900.9805699735	,
				      14901.2375078537	,
				      -2932.47405365043	,
				      386.37974056973	,
				      -33.7549355914578	,
				      1.87617799102579	,
				      -0.060056848900623,
				      0.000842629436663657);
				     
      cout<<"dl="<<difflong<<"  [mum/sqrt(cm)]"<<endl;
      //only for E<10000 v/cm
      vdrift=10*CalculateGasParameter(434.076969292862    ,
				   -1074.66184491203   ,
				   1149.72785706044    ,
				   -698.444581229727   ,
				   266.473335099845    ,
				   -66.6913114740444   ,
				   11.1071873889043    ,
				   -1.21924046183097   ,
				   0.0847232468170763  ,
				   -0.00337737394355272,
				   5.88460170933486e-05);
      cout<<"v_d="<<vdrift<<" [mm/mus]"<<endl;
    }
  CalculateTransverseDiffusion();
  cout<<"d_t="<<difftrans<<"  [mum/sqrt(cm)]"<<endl;
}

void TrackDrifter::CalculateTransverseDiffusion()
{
  double a=0.0, b=0.0, c=0.0, d=0.0, e=0.0, f=0.0, g=0.0,h=0.0;
  if(strcmp(Gas,"TDR")==0)
    {
      //determine fitparameter dependent on B
      a=CalculateDiffTransBParam( -106.046108535431,
				  -7925.61400273791,
				  6686.92350165348 ,
				  -1736.42761722403,
				  146.611430723786);
      b=CalculateDiffTransBParam( 1970.33307314786,
				  8539.99540224613,
				  -8165.5604789030,
				  2185.06605798116,
				  -186.64910130239);
      c=CalculateDiffTransBParam( -1310.89853174629,
				  -3859.80438359763,
				  4067.95823611071,
				  -1112.18595370353,
				  95.7332916666454);
      d=CalculateDiffTransBParam( 359.575535714393,
				  906.582285713412,
				  -1055.48393749909,
				  294.561624999709,
				  -25.5341874999711);
      e=CalculateDiffTransBParam( -47.8321031745661,
				  -121.309271693408,
				  156.069644444719,
				  -44.4134370371213,
				  3.87508333334145);
      f=CalculateDiffTransBParam( 3.08740047617949,
				  9.46675825402465,
				  -13.3412950000488,
				  3.86233555556974,
				  -0.338861666667986);
      g=CalculateDiffTransBParam( -0.0802989230166763,
				  -0.406835040606432,
				  0.616783563887318,
				  -0.181050885184737,
				  0.0159530999999581);
      h=CalculateDiffTransBParam( 0.000202925869483748,
				  0.00751979708915846,
				  -0.0119714449267601,
				  0.00355000019899887,
				  -0.000313752165998087);
    }
  if(strcmp(Gas,"P5")==0)
    {
      a=CalculateDiffTransBParam( 1717.55091269849 ,
				  -11862.4161798943,
				  7645.31818055561 ,
				  -1711.3409351852 ,
				  131.273458333334);
      b=CalculateDiffTransBParam( -1187.37916666688,
				  15041.8556111118 ,
				  -10250.1270416673,
				  2349.85980555573 ,
				  -183.043375000017);
      c=CalculateDiffTransBParam( 749.58074206344,
				  -8386.30572089888,
				  5915.78454861053,
				  -1385.18655092575,
				  109.588270833316);
      d=CalculateDiffTransBParam( -277.356452380926,
				  2393.05499206331,
				  -1741.8060416665,
				  415.234138888839,
				  -33.2723749999953);
      e=CalculateDiffTransBParam( 58.7842686507959,
				  -378.769551719536,
				  284.079220138844,
				  -68.8185782407264,
				  5.57579791666526);
      f=CalculateDiffTransBParam( -6.89263670634272,
				  33.816481256577,
				  -26.0894200694113,
				  6.41412967591606,
				  -0.524940624999067);
      g=CalculateDiffTransBParam( 0.411706769841139,
				  -1.59868090608373,
				  1.26615805555469,
				  -0.315568351851591,
				  0.0260675833333084);
      h=CalculateDiffTransBParam( -0.00974956896824944,
				  0.031175398716901,
				  -0.0252933602777505,
				  0.00638410037036229,
				  -0.00053190499999924);
    }
  if(strcmp(Gas,"P10")==0)
    {
      a=CalculateDiffTransBParam( 5275.68159650525 ,
				  -16880.2740313074,
				  12867.7142585106 ,
				  -3363.51052406353,
				  292.460617554278);
      b=CalculateDiffTransBParam(-5706.28654761803,
				 20937.2623412812 ,
				 -16759.4706250131,
				 4464.23652778203 ,
				 -392.358958333753);
      c=CalculateDiffTransBParam(3047.80333333317,
				 -11063.7030555512,
				 9116.48541666194,
				 -2460.36027777624,
				 217.967916666513);
      d=CalculateDiffTransBParam(-899.991821429039,
				 3046.22859523997,
				 -2579.98914583488,
				 705.574708333773,
				 -63.0282291667072);
      e=CalculateDiffTransBParam(154.97143253985,
				 -473.445552646092,
				 412.008873611581,
				 -114.223045370503,
				 10.2919291666788);
      f=CalculateDiffTransBParam(-15.3491762500078,
				 41.9985363334113,
				 -37.5006902292425,
				 10.53647404169,
				 -0.957505645835577);
      g=CalculateDiffTransBParam(0.805057706349255,
				 -1.98744670661367,
				 1.81693607777767,
				 -0.516984125925895,
				 0.0473617166666638);
      h=CalculateDiffTransBParam(-0.0172623238095152,
				 0.0389708056348575,
				 -0.0363897941666099,
				 0.0104751738888722,
				 -0.000966802499998446);
    }
  //now d_t dependend on E
  difftrans=CalculateGasParameter(a,b,c,d,e,f,g,h,0,0,0);
  
}


double TrackDrifter::CalculateGasParameter(double a, double b ,double c, double d,
					    double e, double f, double g, double h,
					    double i, double j,double k)
{
  double logE=log(E);
  return a+b*logE+c*pow(logE,2)+d*pow(logE,3)
    +e*pow(logE,4)+f*pow(logE,5)+g*pow(logE,6)
    +h*pow(logE,7)+i*pow(logE,8)+j*pow(logE,9)
    +k*pow(logE,10);
}

double TrackDrifter::CalculateDiffTransBParam(double a, double b, double c, 
					      double d,double e)
{
  return a+b*B+c*B*B+d*B*B*B+e*B*B*B*B;
}


void TrackDrifter::Clear()
{
  
}

