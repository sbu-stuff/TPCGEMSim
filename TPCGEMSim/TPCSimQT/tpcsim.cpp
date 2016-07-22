#include "tpcsim.h"
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qgroupbox.h>
#include <qfiledialog.h>
#include <qlineedit.h>
#include <qfile.h>
#include <qlabel.h>
#include <qstring.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include <iostream>
#include <qprocess.h>

#include <stdlib.h>
#include <time.h>
using namespace std;

TPCSim::TPCSim( QWidget* parent, const char* name , WFlags fl ):TPCSimulation(parent, name, fl)
{
  this->setCaption("TPCGEMSimulation v1.10");
  
  connect(PushButtonSimInput,SIGNAL(clicked()),this,SLOT(chooseFileforSim()));
  connect(PushButtonClusterInput,SIGNAL(clicked()),this,SLOT(chooseFileforClusterInfo()));
  connect(PushButtonDriftInput,SIGNAL(clicked()),this,SLOT(chooseFileforDrift()));
  connect(PushButtonPadInput,SIGNAL(clicked()),this,SLOT(chooseFileforPads()));
  connect(PushButtonParamFile,SIGNAL(clicked()),this,SLOT(chooseFileforParam()));
  connect(PushButtonSimulate,SIGNAL(clicked()),this,SLOT(startSimulation()));
  connect(PushButtonDrift,SIGNAL(clicked()),this,SLOT(startDrift()));
  connect(PushButtonMakePads,SIGNAL(clicked()),this,SLOT(startPads()));
  connect(PushButtonElectronicsInput,SIGNAL(clicked()),this,SLOT(chooseFileforElectronics()));
  connect(PushButtonShape,SIGNAL(clicked()),this,SLOT(startElectronics()));
  connect(PushButtonCancel,SIGNAL(clicked()),this,SLOT(cancelprog()));
  
  output = new QTextView( Frame8 );
  output->setGeometry(11,41,320,720);
  proc1 = new QProcess( this ); 
  proc2 = new QProcess( this ); 
  proc3 = new QProcess( this ); 
  proc4 = new QProcess( this ); 
  connect( proc1, SIGNAL(readyReadStdout()),this, SLOT(readFromStdout1()) ); 
  connect( proc2, SIGNAL(readyReadStdout()),this, SLOT(readFromStdout2()) ); 
  connect( proc3, SIGNAL(readyReadStdout()),this, SLOT(readFromStdout3()) ); 
  connect( proc4, SIGNAL(readyReadStdout()),this, SLOT(readFromStdout4()) ); 
  filedialog = new QFileDialog();
  filedialog->setMode(QFileDialog::AnyFile);

}

TPCSim::~TPCSim()
{}


void TPCSim::toggle(int state)
{
 if(state) show();
 else hide();
}


void TPCSim::hideEvent ( QHideEvent * ) 
{
    emit hiding(0);   
}

void TPCSim::chooseFileforSim()
{

  disconnect(filedialog,SIGNAL(fileSelected(const QString &)),0,0);
  connect(filedialog,SIGNAL(fileSelected(const QString &)),LineEditSim, SLOT(setText(const QString &)));
  filedialog->show();
}

void TPCSim::chooseFileforClusterInfo()
{

  disconnect(filedialog,SIGNAL(fileSelected(const QString &)),0,0);
  connect(filedialog,SIGNAL(fileSelected(const QString &)),LineEditClusterInfo, SLOT(setText(const QString &)));
  filedialog->show();
}

void TPCSim::chooseFileforDrift()
{
  disconnect(filedialog,SIGNAL(fileSelected(const QString &)),0,0);
  connect(filedialog,SIGNAL(fileSelected(const QString &)),LineEditDrift, SLOT(setText(const QString &)));
  filedialog->show();
}
void TPCSim::chooseFileforPads()
{
  disconnect(filedialog,SIGNAL(fileSelected(const QString &)),0,0);
  connect(filedialog,SIGNAL(fileSelected(const QString &)),LineEditPads, SLOT(setText(const QString &)));
  filedialog->show();
}

void TPCSim::chooseFileforParam()
{
  disconnect(filedialog,SIGNAL(fileSelected(const QString &)),0,0);
  connect(filedialog,SIGNAL(fileSelected(const QString &)),LineEditParamFile, SLOT(setText(const QString &)));
  filedialog->show();
}

void TPCSim::chooseFileforElectronics()
{
  disconnect(filedialog,SIGNAL(fileSelected(const QString &)),0,0);
  connect(filedialog,SIGNAL(fileSelected(const QString &)),LineEditElectronics, SLOT(setText(const QString &)));
  filedialog->show();
}

void TPCSim::readFromStdout1()
{
    // Read and process the data.
    // Bear in mind that the data might be output in chunks.
    output->append( proc1->readStdout() );
}
void TPCSim::readFromStdout2()
{
    // Read and process the data.
    // Bear in mind that the data might be output in chunks.
    output->append( proc2->readStdout() );
}
void TPCSim::readFromStdout3()
{
    // Read and process the data.
    // Bear in mind that the data might be output in chunks.
    output->append( proc3->readStdout() );
}

void TPCSim::readFromStdout4()
{
    // Read and process the data.
    // Bear in mind that the data might be output in chunks.
    output->append( proc4->readStdout() );
}

void TPCSim::startSimulation()
{
  QString B=LineEditBfield->text();
  QString L=LineEditLength->text();
  QString RI=LineEditInnerRadius->text();
  QString RO=LineEditOuterRadius->text();
  QString siminput=LineEditSim->text();
  QString clusterinfo=LineEditClusterInfo->text();
  proc1->clearArguments();
  proc1->addArgument( "TPCIonisation" );
  proc1->addArgument( siminput );
  proc1->addArgument( L );
  proc1->addArgument( RO);
  proc1->addArgument( RI);
  proc1->addArgument( B );
  proc1->addArgument( clusterinfo );

  if ( !proc1->start() )
    {
      // error handling
      cout<<"ERROR:programm could not be started!"<<endl;
      exit( -1 );
    }
  // proc1->start();
  output->append( proc1->readStdout() );
  
}

void TPCSim::startDrift()
{
  QString gas=LineEditGas->text();
  QString driftinput=LineEditDrift->text();
  QString E=LineEditEfield->text();
  proc2->clearArguments();
  proc2->addArgument( "TPCDrift" );
  proc2->addArgument( driftinput );
  proc2->addArgument( gas );
  proc2->addArgument( E );
  if ( !proc2->start() )
    {
      // error handling
      cout<<"ERROR:programm could not be started!"<<endl;
      exit( -1 );
    }
  //proc2->start();
  output->append( proc2->readStdout() );
}

void TPCSim::startPads()
{
  QString padinput=LineEditPads->text();
  //QString f=LineEditFrequency->text();
  QString padx=LineEditPadx->text();
  QString pady=LineEditPady->text();
  QString npads=LineEditNPads->text();
  QString padsinrow=LineEditPadsInRow->text();
  QString offsetx=LineEditOffsetX->text();
  QString offsety=LineEditOffsetY->text();
  QString gainfactor=LineEditGainFactor->text();
  QString U1=LineEditUGEM1->text();
  QString Et1=LineEditEtrans1->text();
  QString U2=LineEditUGEM2->text();
  QString Et2=LineEditEtrans2->text();
  QString U3=LineEditUGEM3->text();
  QString Ei=LineEditEind->text();
  QString paramfile=LineEditParamFile->text();
  proc3->clearArguments();
  proc3->addArgument( "TPCPads" );
  proc3->addArgument( padinput );
  //proc3->addArgument( f );
  proc3->addArgument( padx );
  proc3->addArgument( pady );
  proc3->addArgument( npads );
  proc3->addArgument( padsinrow );
  proc3->addArgument( offsetx );
  proc3->addArgument( offsety );
  // proc3->addArgument( voxelcut );
  proc3->addArgument( U1 );
  proc3->addArgument( Et1 );
  proc3->addArgument( U2 );
  proc3->addArgument( Et2 );
  proc3->addArgument( U3 );
  proc3->addArgument( Ei );
  proc3->addArgument( paramfile );
  proc3->addArgument( gainfactor );
  
  
  if ( !proc3->start() )
    {
      // error handling
      cout<<"ERROR:programm could not be started!"<<endl;
      exit( -1 );
    }
  //proc3->start();
  output->append( proc3->readStdout() );
}

void TPCSim::startElectronics()
{
  QString frequency=LineEditFrequency->text();
  QString electronicsinput=LineEditElectronics->text();
  QString risetime=LineEditRiseTime->text();
  QString adcres=LineEditADCRes->text();
  QString maxcharge=LineEditADCMaxQ->text();
  QString threshold=LineEditThreshold->text();
  QString gainF=LineEditgainF->text();
  QString cutoff=LineEditCutOff->text();
  proc4->clearArguments();
  proc4->addArgument( "TPCElectronics" );
  proc4->addArgument( electronicsinput );
  proc4->addArgument( frequency );
  proc4->addArgument( risetime );
  proc4->addArgument( adcres );
  proc4->addArgument( maxcharge );
  proc4->addArgument( threshold ); 
  proc4->addArgument( gainF ); 
  proc4->addArgument( cutoff ); 
  if ( !proc4->start() )
    {
      // error handling
      cout<<"ERROR:programm could not be started!"<<endl;
      exit( -1 );
    }
  //proc4->start();
  output->append( proc4->readStdout() );
}

void TPCSim::cancelprog()
{
  if(proc1->isRunning())
    {
      proc1->kill();
    }
  if(proc2->isRunning())
    {
      proc2->kill();
    }
  if(proc3->isRunning())
    {
      proc3->kill();
    }
  if(proc4->isRunning())
    {
      proc4->kill();
    }
}
