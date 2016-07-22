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


#include "MakePads.h"
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <cstring> //to get strcmp working (KD, Jan08, 2015)
#include "./libgem/libgem.h" //contains information about charge transfer in GEM

#define GEMPITCH 0.14

using namespace std;

MakePads::MakePads(double sigma,int numberofpads,double xoffset, 
		   double yoffset,int columns,double Pady,
		   double Padx,double Drifttime, 
		   double Bfield, double setting[7],
		   char *inputfile, double gain_factor,const char* in_Gas)
{
  //setting of all the needed parameters
  sigma_diff=sigma;
  cout<<"Sigma between GEMs in mm: "<<sigma<<endl;
  npads=numberofpads;
  x0=xoffset;
  y0=yoffset;
  padcolumns=columns;
  B=Bfield;
  pady=Pady;
  padx=Padx;
  drifttime=Drifttime;
  Gas = in_Gas;
  numbersecel=0;
  GEMSetting[0]=setting[0]; // drift field
  GEMSetting[1]=setting[1]; // U_GEM1
  GEMSetting[2]=setting[2]; // E_trans1
  GEMSetting[3]=setting[3]; // U_GEM2
  GEMSetting[4]=setting[4]; // E_trans2
  GEMSetting[5]=setting[5]; // U_GEM3
  GEMSetting[6]=setting[6]; // E_ind
  paramfile=inputfile;
  gainfactor=gain_factor;
  // random number generator from the gsl library
  // the important point is speed 
  r = gsl_rng_alloc(gsl_rng_ran3); 
  
  // reading in the parameters for the charge transfer
  if( ! readpar( paramfile ) ) {
    cerr << "Not all parameters could be read from parameter file " << paramfile << "!" << endl;
    cerr << "Exiting.";
    exit(1);
  }
 else {
   cout << "Parameter file read successfully " << endl;
 }
  //set Parameter for GEM-Setting
  Extr[0]=eextr(GEMSetting[2],GEMSetting[1]);
  Extr[1]=eextr(GEMSetting[4],GEMSetting[3]);
  Extr[2]=eextr(GEMSetting[6],GEMSetting[5]);
  Coll[0]=ecoll(GEMSetting[0],GEMSetting[1]);
  Coll[1]=ecoll(GEMSetting[2],GEMSetting[3]);
  Coll[2]=ecoll(GEMSetting[4],GEMSetting[5]);
  Gain[0]=gain(GEMSetting[1] ,GEMSetting[0], GEMSetting[2] );
  Gain[1]=gain(GEMSetting[3] ,GEMSetting[2], GEMSetting[4] );
  Gain[2]=gain(GEMSetting[5] ,GEMSetting[4], GEMSetting[6] );

  //calculate attachment
  A1 = CalculateAttachment(GEMSetting[2]);
  A2 = CalculateAttachment(GEMSetting[4]);
  A3 = CalculateAttachment(GEMSetting[6]);
}


void MakePads::Amplify(int evtnr,double xe, double ye ,double te, TPCVoxel* voxel, 
			   vector<TPCVoxel> *voxelvector, int particlenr, bool Is_Curler)
{ 
  isCurler=Is_Curler;
  CalculateNrElectrons();
   
  if(numbersecel>0)
    {
      //map position of electron into GEM hole, pitch 140 mum
      //pitch in y=sqrt(3/4)*pitch because of hexagonal structure
      double xe_gem=0.;
      double ye_gem = (int)(ye/(sqrt(3./4.)*GEMPITCH)+(ye<0 ? -0.5:0.5))*sqrt(3./4.)*GEMPITCH;
      int yint=(int)(ye/(sqrt(3./4.)*GEMPITCH)+0.5);
      if(yint%2)
	xe_gem = static_cast<int>(xe/GEMPITCH+(xe<0 ? -0.5:0.5))*GEMPITCH;
      else
	//everysecond row is shifted with half a pitch
	xe_gem = (static_cast<int>(xe/GEMPITCH)+(xe<0 ? -0.5:0.5))*GEMPITCH;
      
      if(fabs(xe-xe_gem)>0.08)
	cout<<"WARNING: x GEM pitch failed, difference: "<<fabs(xe-xe_gem)<<"  "<<xe<<endl;
      if(fabs(ye-ye_gem)>0.08)
	cout<<"WARNING: y GEM pitch failed, difference: "<<fabs(ye-ye_gem)<<"  "<<ye<<endl;
      
      double sigma=sigma_diff; // charge broadening between GEMs
      
      //start values for integration
      double x1=xe_gem-4*sigma;
      double y1=ye_gem-4*sigma;
      //end values for integration
      double x2=xe_gem+4*sigma;
      double y2=ye_gem+4*sigma;
      // start and end in columns and rows
      int column1=(int)((x0+x1)/padx);
      int row1=(int)((y0+y1)/pady);  
      int column2=(int)((x0+x2)/padx);
      int row2=(int)((y0+y2)/pady);
      
      int rownumbers=row2-row1+1;
      int columnnumbers=column2-column1+1;
      
      // time of electron  in ns (no additional smearing in time is done here)
      int time = (int)(te*1000);
      // integration loop
      for(int yint=0;yint<rownumbers;yint++)
	{
	  for(int xint=0;xint<columnnumbers;xint++)
	    {
	      double cstart=(column1+xint)*padx-x0;
	      double cend=(column1+1+xint)*padx-x0;
	      double rend=(row1+1+yint)*pady-y0;
	      double rstart =(row1+yint)*pady-y0;
	      // integration over a 2d gaussian
	      int charge=(int)(numbersecel/4*((erf((cend-xe_gem)/(sqrt(2.)*sigma))-
					       erf((cstart-xe_gem)/(sqrt(2.)*sigma)))*
					      (erf((rend-ye_gem)/(sqrt(2.)*sigma))-
					       erf((rstart-ye_gem)/(sqrt(2.)*sigma)))));
	      
	      long int channr=(row1+yint)*padcolumns+(column1+xint);
	      //check if e- drifted out of read out region
	      if((row1+yint) >=0 && (column1+xint)>=0 && 
		 (column1+xint)<padcolumns && (row1+yint)<(int)(npads/padcolumns) &&
		 charge >0 && channr<npads)
		{
		  voxel->SetVoxel(channr,time,charge,particlenr);
		  voxelvector->push_back(*voxel);
		}
	    }
	}// integration over pads
    }
  
}

int MakePads::GEM_Collection(int GEMNr, int enumber)
{
  //Collection using random generator to account for binomial statistics
  return gsl_ran_binomial(r,Coll[GEMNr-1],enumber);
}

double MakePads::GEM_Gain(int GEMNr, int enumber)
{
  //Gain
  double gainmean=Gain[GEMNr-1]/gainfactor; //factor for gain correction to fit data
  // exponential distribution for gain distribution of single electron
  double electrons=0.;
  if(enumber<200)
    {
      for(int i=0;i<enumber;i++)
	electrons+=gsl_ran_exponential(r,gainmean);
    }
  else //because than statistics is enough to form gaussian anyway
    electrons=(gsl_ran_gaussian(r,sqrt((double)enumber))+enumber)*gainmean;
    
  if(electrons>=0)
    return electrons;
  else
    return 0;
}

int MakePads::GEM_Extraction(int GEMNr, int enumber)
{
  //Extraction
  return gsl_ran_binomial(r,Extr[GEMNr-1],enumber);
}

void  MakePads::CalculateNrElectrons()
{

  //GEM1
  int C1=0;
  if(isCurler)
       C1=GEM_Collection(1,10);
  else
    C1=GEM_Collection(1,1);
  double G1=GEM_Gain(1,C1);
  int E1=GEM_Extraction(1,(int)(G1));
  int NE1 = (int)(A1*E1);
  
  //GEM2
  int C2=GEM_Collection(2,NE1);
  double G2=GEM_Gain(2,C2);
  int E2=GEM_Extraction(2,(int)(G2));
  int NE2 = (int)(A2*E2);

  //GEM3
  int C3=GEM_Collection(3,NE2);
  double G3=GEM_Gain(3,C3);
  int E3=GEM_Extraction(3,(int)(G3));
  int NE3 = (int)(A3*E3);

  numbersecel=NE3;
}


double  MakePads::CalculateAttachment(double E)
{
  double attachment=0.;
  if(E>1000 && E<10000)
    {
      if(strcmp(Gas,"TDR")==0)
	{
	  attachment=AttachmentParam(E,0.55746495832639, -0.000976295444932751,
				     5.3027197364505e-07, -9.07408257219121e-11,
				     6.69870876291181e-15, -1.86507294442893e-19);
	}
      if(strcmp(Gas,"P5")==0)
	{
	  attachment=AttachmentParam(E,0.629533727124781,-0.00108472142344718,
				     5.84515020493324e-07,-1.1692383060812e-10,
				     1.04404353256126e-14,-3.4883967794339e-19);

	}
      if(strcmp(Gas,"P10")==0)
	{
	  attachment=AttachmentParam(E,0.38315599849704, -0.000496101873773124,
				     1.59951805618856e-07,-8.32609010589732e-12,
				     -8.47193583341197e-16,6.53327997981156e-20);

	}
    }
  //0.2 because 2mm between GEMs
  return exp(-0.2*attachment);
}

double  MakePads::AttachmentParam(double E,double a0,double a1,double a2,double a3,
				  double a4,double a5)
{
  return a0+a1*E+a2*pow(E,2)+a3*pow(E,3)+a4*pow(E,4)+a5*pow(E,5);
}

