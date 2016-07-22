#ifndef GEOMETRYINFO_H
#define GEOMETRYINFO_H

#include <TObject.h>

/** Information about detector geometry and readout are stored here.*/
class GeometryInfo : public TObject{

public:
/*! Creates a GeometryInfo object with the following attributes:
 * \param  padwidth  Width of a pad in mm
 * \param  padheight Height of a pad in mm
 * \param  padsinrow Number of pads in a row
 * \param  npads     Total number of pads
 * \param  radius    TPC radius
 * \param  length    Drift length
 * \param  activeareaxoffset X offset of active area relative to coordinate system
 * \param  activeareayoffset Y offset of active area relative to coordinate system
 * \param  cylinderxoffset   X offset of cylinder center relative to coordinate system
 * \param  cylinderyoffset   y offset of cylinder center relative to coordinate system
 * All parameters default to 0. 
 */
  GeometryInfo(Double_t padwidth=0.,Double_t padheight=0.,
	       Int_t padsinrow=0, Int_t npads=0,
	       Double_t radius=0.,Double_t inner_radius=0., Double_t length=0.,
	       Double_t activeareaxoffset=0., Double_t activeareayoffset=0.,
               Double_t cylinderxoffset=0., Double_t cylinderyoffset=0.);
  ~GeometryInfo();

  void PrintAllParameters();
  Double_t GetTPCRadius();
  Double_t GetTPCInnerRadius();
  Double_t GetTPCLength();
  Double_t GetPadWidth();
  Double_t GetPadHeight();
  Int_t    GetPadsInRow();
  Int_t    GetNPads();
  Double_t GetActiveAreaXOffset();
  Double_t GetActiveAreaYOffset();
  Double_t GetCylinderXOffset();
  Double_t GetCylinderYOffset();

/**
 * These functions are for convenience.
 * ActiveAreaX and ActiveAreaY are calculated, no set needed.
 */
  Double_t GetActiveAreaX();
  Double_t GetActiveAreaY();

  void SetTPCRadius(Double_t radius);
  void SetTPCInnerRadius(Double_t radius);
  void SetTPCLength(Double_t length);
  void SetPadWidth(Double_t padwidth);
  void SetPadHeight(Double_t padheight);
  void SetPadsInRow(Int_t padsinrow);
  void SetNPads(Int_t npads);
  void SetActiveAreaXOffset(Double_t activeareaxoffset);
  void SetActiveAreaYOffset(Double_t activeareayoffset);
  void SetCylinderXOffset(Double_t cylinderxoffset);
  void SetCylinderYOffset(Double_t cylinderyoffset);

private:
  Double_t TPCRadius; 
  Double_t TPCInnerRadius;    
  Double_t TPCLength;    
  Double_t PadWidth;     
  Double_t PadHeight;    
  Int_t    PadsInRow;    
  Int_t    NPads;	       
  Double_t ActiveAreaXOffset;  
  Double_t ActiveAreaYOffset;  
  Double_t CylinderXOffset;  
  Double_t CylinderYOffset;  
 
  ClassDef(GeometryInfo,2)
};


#endif
