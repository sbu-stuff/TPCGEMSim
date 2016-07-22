/****************************************************************************
** Form interface generated from reading ui file 'form1.ui'
**
** Created: Thu Sep 21 10:57:17 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.1.2   edited Dec 19 11:45 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef TPCSIMULATION_H
#define TPCSIMULATION_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLineEdit;
class QFrame;
class QLabel;
class QPushButton;

class TPCSimulation : public QWidget
{
    Q_OBJECT

public:
    TPCSimulation( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~TPCSimulation();

    QLineEdit* LineEditSim_2;
    QLineEdit* LineEditSim_3;
    QFrame* Frame3;
    QLineEdit* LineEditBfield;
    QLabel* TextLabel1;
    QLabel* TextLabel4;
    QLineEdit* LineEditSim;
    QPushButton* PushButtonSimInput;
    QLabel* TextLabel7;
    QLabel* TextLabel12;
    QPushButton* PushButtonSimulate;
    QLabel* TextLabel12_4;
    QLineEdit* LineEditClusterInfo;
    QPushButton* PushButtonClusterInput;
    QLineEdit* LineEditLength;
    QLabel* TextLabel11;
    QLabel* TextLabel2;
    QLabel* TextLabel2_2;
    QLabel* TextLabel5;
    QLabel* TextLabel5_7;
    QLabel* TextLabel6;
    QLineEdit* LineEditOuterRadius;
    QLineEdit* LineEditInnerRadius;
    QFrame* Frame4;
    QPushButton* PushButtonDriftInput;
    QLabel* TextLabel9;
    QLineEdit* LineEditGas;
    QLabel* TextLabel1_3;
    QPushButton* PushButtonDrift;
    QLabel* TextLabel10;
    QLabel* TextLabel13;
    QLabel* TextLabel12_2;
    QLabel* TextLabel8;
    QLineEdit* LineEditDrift;
    QLineEdit* LineEditEfield;
    QFrame* Frame7;
    QLineEdit* LineEditPads;
    QLabel* TextLabel7_2;
    QLabel* TextLabel12_3;
    QPushButton* PushButtonPadInput;
    QPushButton* PushButtonMakePads;
    QLabel* TextLabel3_3;
    QLabel* TextLabel3_3_2;
    QLineEdit* LineEditPadx;
    QLabel* TextLabel4_2;
    QLineEdit* LineEditPady;
    QLabel* TextLabel4_2_2;
    QLabel* TextLabel3_3_3_2;
    QLineEdit* LineEditPadsInRow;
    QLineEdit* LineEditNPads;
    QLabel* TextLabel3_3_3_3;
    QLineEdit* LineEditOffsetX;
    QLabel* TextLabel4_2_2_2;
    QLabel* TextLabel4_2_2_2_2;
    QLabel* TextLabel3_3_3;
    QLineEdit* LineEditOffsetY;
    QLabel* TextLabel5_2;
    QLabel* TextLabel6_3_2;
    QLabel* TextLabel6_3_3;
    QLabel* TextLabel6_3_4;
    QLabel* TextLabel6_3_5;
    QLabel* TextLabel6_3_6;
    QLabel* TextLabel6_3_7;
    QLineEdit* LineEditUGEM1;
    QLineEdit* LineEditEtrans1;
    QLineEdit* LineEditUGEM2;
    QLineEdit* LineEditEtrans2;
    QLineEdit* LineEditUGEM3;
    QLineEdit* LineEditEind;
    QLabel* TextLabel6_3_8;
    QLabel* TextLabel7_3_2;
    QLabel* TextLabel6_3_8_2;
    QLabel* TextLabel7_3_3;
    QLabel* TextLabel6_3_8_3;
    QLabel* TextLabel7_3_4;
    QLabel* TextLabel2_3;
    QLineEdit* LineEditParamFile;
    QPushButton* PushButtonParamFile;
    QLabel* TextLabel3_3_3_4;
    QLineEdit* LineEditGainFactor;
    QFrame* Frame8;
    QLabel* TextLabel1_4;
    QPushButton* PushButtonCancel;
    QFrame* frame7;
    QLabel* TextLabel8_2;
    QPushButton* PushButtonElectronicsInput;
    QLabel* TextLabel12_3_2;
    QLineEdit* LineEditElectronics;
    QPushButton* PushButtonShape;
    QLabel* TextLabel12_3_2_2;
    QLineEdit* LineEditFrequency;
    QLabel* TextLabel5_3;
    QLineEdit* LineEditRiseTime;
    QLabel* TextLabel12_3_2_3;
    QLabel* TextLabel5_4;
    QLabel* TextLabel12_3_2_3_2;
    QLineEdit* LineEditADCRes;
    QLabel* TextLabel5_5;
    QLineEdit* LineEditADCMaxQ;
    QLabel* TextLabel12_3_2_3_2_2_2;
    QLabel* TextLabel5_6;
    QLabel* TextLabel12_3_2_3_2_2;
    QLineEdit* LineEditThreshold;
    QLabel* TextLabel5_5_2;
    QLabel* TextLabel5_5_2_2;
    QLineEdit* LineEditCutOff;
    QLineEdit* LineEditgainF;
    QLabel* TextLabel1299;
    QLabel* TextLabel1299_2;

protected:

protected slots:
    virtual void languageChange();

};

#endif // TPCSIMULATION_H
