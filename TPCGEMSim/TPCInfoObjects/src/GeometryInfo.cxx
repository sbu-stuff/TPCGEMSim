#include "GeometryInfo.h"
#include <iostream>
using namespace std;

ClassImp(GeometryInfo)

GeometryInfo::GeometryInfo(Double_t padwidth,Double_t padheight,
			   Int_t padsinrow, Int_t npads,
			   Double_t radius,Double_t inner_radius,Double_t length,
			   Double_t activeareaxoffset,
			   Double_t activeareayoffset,
			   Double_t cylinderxoffset,
			   Double_t cylinderyoffset)
{
  TPCRadius=radius; 
  TPCInnerRadius=inner_radius;
  TPCLength=length;    
  PadWidth=padwidth;     
  PadHeight=padheight;    
  PadsInRow=padsinrow;    
  NPads=npads;	       
  ActiveAreaXOffset=activeareaxoffset;  
  ActiveAreaYOffset=activeareayoffset;  
  CylinderXOffset=cylinderxoffset;  
  CylinderYOffset=cylinderyoffset;  
}

GeometryInfo::~GeometryInfo()
{}

void GeometryInfo::PrintAllParameters()
{
  cout<<"The Geometry Settings are:"<<endl;
  cout<<"TPC Radius: "<<TPCRadius<<endl;
  cout<<"TPC Inner Radius: "<<TPCInnerRadius<<endl;
  cout<<"TPC Length: "<<TPCLength<<endl;
  cout<<"Pad Width: "<<PadWidth<<endl;
  cout<<"Pad Height: "<<PadHeight<<endl;
  cout<<"Pads in one Row: "<< PadsInRow<<endl;
  cout<<"Number of Pads: "<<NPads<<endl;
  cout<<"Active Area X Offset: "<<ActiveAreaXOffset<<endl;
  cout<<"Active Area Y Offset: "<<ActiveAreaYOffset<<endl;
  cout<<"Cylinder X Offset: "<<CylinderXOffset<<endl;
  cout<<"Cylinder Y Offset: "<<CylinderYOffset<<endl;
}

Double_t GeometryInfo::GetTPCRadius(){return TPCRadius;}
Double_t GeometryInfo::GetTPCInnerRadius(){return TPCInnerRadius;}
Double_t GeometryInfo::GetTPCLength(){return TPCLength;}
Double_t GeometryInfo::GetPadWidth(){return PadWidth;}
Double_t GeometryInfo::GetPadHeight(){return PadHeight;}
Int_t GeometryInfo::GetPadsInRow(){return PadsInRow;}
Int_t GeometryInfo::GetNPads(){return NPads;}
Double_t GeometryInfo::GetActiveAreaXOffset(){return ActiveAreaXOffset;}
Double_t GeometryInfo::GetActiveAreaYOffset(){return ActiveAreaYOffset;}
Double_t GeometryInfo::GetCylinderXOffset(){return CylinderXOffset;}
Double_t GeometryInfo::GetCylinderYOffset(){return CylinderYOffset;}

Double_t GeometryInfo::GetActiveAreaX()
{
    return PadsInRow*PadWidth;
}

Double_t GeometryInfo::GetActiveAreaY()
{
    return NPads/PadsInRow * PadHeight;
}

void GeometryInfo::SetTPCRadius(Double_t radius){TPCRadius=radius; }
void GeometryInfo::SetTPCInnerRadius(Double_t inner_radius){TPCInnerRadius=inner_radius; }
void GeometryInfo::SetTPCLength(Double_t length){TPCLength=length;}
void GeometryInfo::SetPadWidth(Double_t padwidth){PadWidth=padwidth; }
void GeometryInfo::SetPadHeight(Double_t padheight){PadHeight=padheight;}
void GeometryInfo::SetPadsInRow(Int_t padsinrow){PadsInRow=padsinrow;}
void GeometryInfo::SetNPads(Int_t npads){NPads=npads;}
void GeometryInfo::SetActiveAreaXOffset(Double_t activeareaxoffset)
     {ActiveAreaXOffset=activeareaxoffset;}
void GeometryInfo::SetActiveAreaYOffset(Double_t activeareayoffset)
     {ActiveAreaYOffset=activeareayoffset;}
void GeometryInfo::SetCylinderXOffset(Double_t cylinderxoffset)
     {CylinderXOffset=cylinderxoffset;}
void GeometryInfo::SetCylinderYOffset(Double_t cylinderyoffset)
     {CylinderYOffset=cylinderyoffset;}
