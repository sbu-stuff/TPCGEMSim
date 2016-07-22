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

/*! Programm to create a primary electrons along the particle track. */

#include "MakePrimaryIonisation.h"
#include <math.h>
#include <iostream>
using namespace std;
#define C 0.299792458 // speed of light / Giga

MakePrimaryIonisation::MakePrimaryIonisation(float in_B, float in_TPCHalfLength, double in_TPCRadius,double InnerRadius)
{
  B = in_B;
  TPCRadius = in_TPCRadius;
  inner_radius=InnerRadius;
  distance= in_TPCHalfLength;
  //set and initialize other private members
  r = gsl_rng_alloc(gsl_rng_mt19937);

  //parameters for HEED Parametrisation
  // for number of clusters per mm
  a0= 41.1221      ;
  a1= -30.6686     ;
  a2= 22.839       ;
  a3= -7.92683     ;
  a4= 1.57031      ;
  a5= -0.182929    ;
  a6= 0.0116357    ;
  a7= -0.000310538 ;

  clusterdistance=0.;
  numberofelectrons=0;
  numberofclusters=0.;
  InTPC=0;
  xa=0.,ya=0.,za=0.;
  xv=0.,yv=0.,zv=0.;
  xend=0.,yend=0., zend=0., tend=0.;
  dx=0., dy=0., dz=0.,dr=0.; 
  xm=0., ym=0.; 
  radius=0.; 
  dp=1.; 
  alpha=0; 
  px=0., py=0., pz=0.,pt=0.,p=0., p_const=0.;
  energy=0.;
  mass=0.;
  charge=0.;
  pdg=0;
  delta_x=0.,delta_y=0.,delta_z=0.;
}



MakePrimaryIonisation::~MakePrimaryIonisation()
{
}

void MakePrimaryIonisation::CreateTrack(int eventnr, int particlenr,  TPCSimTrack *track, 
			       TParticle *rootParticle, bool isCurler)
{
  SetParticleParameters(rootParticle);
  InitializeTrackPoint();
  InTPC=0;
  int e_curlercounter=0;
  CalculateNumberOfClusters();
  // as long as cluster in TPC and particle not stopped (p>0) continue track
  while((xend+xv)*(xend+xv)+(yend+yv)*(yend+yv)<=TPCRadius*TPCRadius && 
	fabs(zend+zv)<fabs(distance) && p>0.0)
    {
      if(energy>mass)
	{   
	  CalculateClusterDistance();
	  double delta_cut=0;
	  if(B==0)
	    {
	      CalculateTrackPointwithoutBfield();
	      delta_cut=60; // equals range of 100 mum
	    }
	  if(B!=0) 
	    {
	      CalculateTrackPointwithBfield();
	      delta_cut=(30.0*B+0.017)/0.026;
	      //delta_cut=1200 equals 100 mum at B=1T
	    }
	  // Warning if huge rather big steps occur, might result in empty pads
	  if(dr>10 && dp>1) cout<<"Warning: high dE/dx "<<endl; 
	  CalculateNumberOfElectrons();

	  //delta electron that moves away from track
	  if(numberofelectrons > delta_cut) 
	    {
	      double delta_range=0;
	      double delta_energy=(0.026*numberofelectrons-0.017)*pow(10.,-6.);//in GeV
	      //angle to track in most cases 90 degrees
	      double delta_angle_track=acos(sqrt(delta_energy/energy));// cos of angle
	      double delta_angle_plane=2*M_PI*drand48();
	      
	      if(B==0)
		delta_range=8.23935e-05*pow(numberofelectrons,1.7293); //mm, is a constant number
	      if(B!=0)
		delta_range=(delta_energy/(0.3*B))*1000; //in mm, is a constant number prop to #electrons
	      
	      double step=delta_range/(double)numberofelectrons;
	     
	      double xe=xend+xv;
	      double ye=yend+yv;
	      double ze=zend+zv;
	     	     
	      //direction if track would be in 0,1,0
	      double deltax=sin(delta_angle_track)*cos(delta_angle_plane);
	      double deltaz=cos(delta_angle_track);
	      double deltay=sin(delta_angle_track)*sin(delta_angle_plane);
	      //transform to track coordinates   
	      RotateToTrack(deltax,deltay,deltaz);
	      	      
	      for(int enumber=0;enumber<numberofelectrons;enumber++)
		{
		  
		  //Multiple Scattering
		  if(!(enumber%30) && !(enumber==0))
		    {
		      double scatter_phi=2*M_PI*drand48();
		      double scatter_theta=1./6*M_PI*drand48();
		      // new direction
		      MultipleScattering(scatter_phi,scatter_theta);
		    }
		  if(sqrt((xe+delta_x*step)*(xe+delta_x*step)+(ye+delta_y*step)*(ye+delta_y*step))>=inner_radius)  
		    {
		      if(isCurler)
			{
			  if(e_curlercounter%10==0) //take only every 10th electron for curlers
			    {
			      track->AddTPCElectron(eventnr,particlenr,xe+delta_x*step,ye+delta_y*step,ze+delta_z*step,tend);
			      InTPC++;  // counter for # e-
			    }
			  e_curlercounter++;
			}
		      else
			{
			  track->AddTPCElectron(eventnr,particlenr,xe+delta_x*step,ye+delta_y*step,ze+delta_z*step,tend);
			  InTPC++;
			}
		    }
		  
		  xe+=delta_x*step;
		  ye+=delta_y*step;
		  ze+=delta_z*step;
		}
	    }
	  else
	    {
	      for(int enumber=0;enumber<numberofelectrons;enumber++)
		{
		  if(sqrt((xend+xv)*(xend+xv)+(yend+yv)*(yend+yv))>=inner_radius)
		    {
		      if(isCurler)
			{
			  if(e_curlercounter%10==0)//take only every 10th electron for curlers
			    {
			      track->AddTPCElectron(eventnr,particlenr,xend+xv,yend+yv,zend+zv,tend);
			      InTPC++;  // counter for # e-
			    }
			  e_curlercounter++;
			}
		      else
			{
			  track->AddTPCElectron(eventnr,particlenr,xend+xv,yend+yv,zend+zv,tend);
			  InTPC++;
			}
		    }
		}
	    }
	  CalculateEnergyLoss();
	  SetNextStartPoint();
	  CalculateNumberOfClusters();
	}
      else
	{//cout<<"Energy lower than mass -> Particle stopped in TPC"<<endl;
        break;}
    } //loop over clusters
  track->SetTrackParameters(eventnr,particlenr,InTPC,isCurler);
}

void MakePrimaryIonisation::SetParticleParameters(TParticle *rootParticle)
{
  energy=rootParticle->Energy();
  mass=rootParticle->GetCalcMass();
  pdg=rootParticle->GetPdgCode();
  charge=(rootParticle->GetPDG()->Charge())/3.; // charge comes in e/3 from TParticle
  xv=rootParticle->Vx(); // Vx() is in mm
  yv=rootParticle->Vy(); 
  zv=rootParticle->Vz();  

  px=rootParticle->Px();
  py=rootParticle->Py();
  pz=rootParticle->Pz();
  pt=sqrt(px*px+py*py);
  p=rootParticle->P();
  p_const=p;
}

void MakePrimaryIonisation::InitializeTrackPoint()
{
  xa=0.; ya=0.; za=0.;
  xend=0.;yend=0.;zend=0.;
}

void MakePrimaryIonisation::CalculateTrackPointwithBfield()
{
  // rotation angle
  double factor = charge*B*C;
  alpha=factor/p*clusterdistance/1000.; //[1/mm]
  // center of circle
  xm=1000*py*dp/factor; //[mm]
  ym=-1000*px*dp/factor;
  //coordinates on helix
  xend=cos(alpha)*(xa-xm)*dp+sin(alpha)*(ya-ym)*dp+xm;
  yend=-sin(alpha)*(xa-xm)*dp+cos(alpha)*(ya-ym)*dp+ym;
  zend=za+pz/p*clusterdistance;
  
}

void MakePrimaryIonisation::CalculateTrackPointwithoutBfield()
{
  //coordinates on straight line along p
  dr=clusterdistance;
  dx=px/p_const;
  dy=py/p_const;
  dz=pz/p_const;
  xend=xa+dr*dx;
  yend=ya+dr*dy;
  zend=za+dr*dz;
}

void MakePrimaryIonisation::CalculateNumberOfClusters()
{
  //from parametrisation one knows function (polynom) and constants
  double x=sqrt((energy*energy)/(mass*mass)-1);
  double logx = log(x);
  double log10000 = log(10000.0);
  if(x<10000)
    numberofclusters = a0+a1*logx+a2*logx*logx+a3*pow(logx,3)
			+a4*pow(logx,4)+a5*pow(logx,5)
			+a6*pow(logx,6)+a7*pow(logx,7);
  else
    numberofclusters = a0+a1*log10000+a2*log10000*log10000+a3*pow(log10000,3)
			+a4*pow(log10000,4)+a5*pow(log10000,5)
			+a6*pow(log10000,6)+a7*pow(log10000,7);
  // number of cluster per cm constant after p/m>10.000
}

void MakePrimaryIonisation::CalculateClusterDistance()
{
  clusterdistance =10.*(gsl_ran_exponential(r,1./numberofclusters)); 
  //*10 because distance needed in mm
}

void MakePrimaryIonisation::CalculateNumberOfElectrons()
{
  //pick a random value between 0 and 1 and check file if random number is bigger than
  //integrated probability
  double r=0.998177337261218*drand48(); 
  //cryptic factor because of cut off on distribution at n=7632 comming from HEED
  int i=0;
  while(r>electrons[i][1] && i<7632)
    i++;
  numberofelectrons=(int)electrons[i][0];
  
}

void  MakePrimaryIonisation::ReadClusterInfoFile(char *clusterfile)
{
  int lines=7632;
  FILE* fin = fopen(clusterfile,"r");
  if(! fin) {                             
       printf("File with cluster information could not be opened.\n");
       exit(1);                           
   }
  /* read in events */
  int events = 0;                            
  while(!feof(fin)) {                     
    fscanf(fin,"%lf %lf" ,
	   &electrons[events][0],
	   &electrons[events][1]);
    events++;                           
    
    if(events >lines) {            
      printf("More events than array range (%i) allows.\n", lines);
      break;                            
    }
  }
  printf("%i Events read. \n", events);
  fclose(fin);                     
}

void MakePrimaryIonisation::CalculateEnergyLoss()
{
  // assume an energy loss of 26 eV for each produced electron
  energy=energy-numberofelectrons*0.000000026; 
  dp=(p-numberofelectrons*0.000000026)/p;
  if(energy-mass<=0)
    cout<<"Particle stopped in TPC"<<endl;
  else
    p=sqrt(energy*energy-mass*mass);
}

void MakePrimaryIonisation::SetNextStartPoint()
{
  xa=xend;
  ya=yend;
  za=zend;
}


void  MakePrimaryIonisation::RotateToTrack(double x, double y, double z)
{
  double phi;
  if(px>=0)
    phi=atan(py/px);
  else
    phi=atan(py/px)+M_PI;
  if(px==0 && py<0)
    phi=-phi;
  double theta=acos(pz);
  delta_x=cos(phi)*cos(theta)*x-sin(phi)*y+cos(phi)*sin(theta)*z;
  delta_y=sin(phi)*cos(theta)*x+cos(phi)*y+sin(phi)*sin(theta)*z;
  delta_z=-sin(theta)*x+cos(theta)*z;
}

void  MakePrimaryIonisation::RotateToDelta(double x, double y, double z)
{
  double phi;
  if(delta_x>0)
    phi=atan(delta_y/delta_x);
  else
    phi=atan(delta_y/delta_x)+M_PI;
  if(delta_x==0 && delta_y<0)
    phi=-phi;
  double theta=acos(delta_z);
  delta_x=cos(phi)*cos(theta)*x-sin(phi)*y+cos(phi)*sin(theta)*z;
  delta_y=sin(phi)*cos(theta)*x+cos(phi)*y+sin(phi)*sin(theta)*z;
  delta_z=-sin(theta)*x+cos(theta)*z;
}

void  MakePrimaryIonisation::MultipleScattering(double phi, double theta)
{
  double x_s=sin(theta)*cos(phi);
  double z_s=cos(theta);
  double y_s=sin(theta)*sin(phi);
  RotateToDelta(x_s,y_s,z_s);
}

void MakePrimaryIonisation::Clear()
{
  
}
