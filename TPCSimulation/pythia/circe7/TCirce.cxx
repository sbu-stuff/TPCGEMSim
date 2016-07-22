
#include "TCirce.h"

ClassImp(TCirce)

extern "C" void icirce_(double*,char*,int);
extern "C" void gcirce_(double*,double*,char*);

TCirce::TCirce() 
{}

TCirce::~TCirce() 
{}

void TCirce::Initialize(double ecm, char *accname)
{
    int acclen = strlen(accname);
    icirce_(&ecm,accname,acclen);
}

void TCirce::GenerateEvent(double& x1, double& x2, char *proname)
{
    gcirce_(&x1,&x2,proname);
}
