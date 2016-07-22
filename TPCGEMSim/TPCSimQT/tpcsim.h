#ifndef TPCSIM_H
#define TPCSIM_H


#include "form1.h"
#include <qfiledialog.h>
#include <qfile.h>
#include <qprocess.h>
#include <qtextview.h>

class TPCSim : public TPCSimulation
{
  Q_OBJECT
    
public:
  TPCSim( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
  ~TPCSim();
  
protected:
  QFileDialog *filedialog;
  QProcess *proc1;
  QProcess *proc2;
  QProcess *proc3;
  QProcess *proc4;
  QTextView *output;
  
  virtual void hideEvent (QHideEvent * );
   
  public slots: 
  void   readFromStdout1();
  void   readFromStdout2();
  void   readFromStdout3();
  void   readFromStdout4();
  void   toggle(int state);
  void   chooseFileforSim();
  void   chooseFileforClusterInfo();
  void   chooseFileforDrift();
  void   chooseFileforPads();
  void   chooseFileforParam();
  void   chooseFileforElectronics();
  void   startSimulation();
  void   startDrift();
  void   startPads();
  void   startElectronics();
  void   cancelprog();
  
  signals:
  void hiding(bool);
  
};

#endif
