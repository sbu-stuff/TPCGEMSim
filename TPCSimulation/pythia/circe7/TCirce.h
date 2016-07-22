#ifndef TCirce_h
#define TCirce_h

#include <TObject.h>

class TCirce : public TObject {

 public:
    
    TCirce();
    virtual ~TCirce();

    void Initialize(double roots, char *accname);
    void GenerateEvent(double& x1, double& x2, char *proname);

    ClassDef(TCirce,1)
};

#endif
