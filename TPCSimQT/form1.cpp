/****************************************************************************
** Form implementation generated from reading ui file 'form1.ui'
**
** Created: Thu Sep 21 10:57:22 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.1.2   edited Dec 19 11:45 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "form1.h"

#include <qvariant.h>
#include <qlineedit.h>
#include <qframe.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "form1.ui.h"

/* 
 *  Constructs a TPCSimulation as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
TPCSimulation::TPCSimulation( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "TPCSimulation" );

    LineEditSim_2 = new QLineEdit( this, "LineEditSim_2" );
    LineEditSim_2->setGeometry( QRect( 120, 60, 150, 23 ) );
    LineEditSim_2->setFrameShape( QLineEdit::LineEditPanel );
    LineEditSim_2->setFrameShadow( QLineEdit::Sunken );

    LineEditSim_3 = new QLineEdit( this, "LineEditSim_3" );
    LineEditSim_3->setGeometry( QRect( 120, 60, 150, 22 ) );
    LineEditSim_3->setFrameShape( QLineEdit::LineEditPanel );
    LineEditSim_3->setFrameShadow( QLineEdit::Sunken );

    Frame3 = new QFrame( this, "Frame3" );
    Frame3->setGeometry( QRect( 10, 10, 320, 350 ) );
    Frame3->setFrameShape( QFrame::StyledPanel );
    Frame3->setFrameShadow( QFrame::Raised );

    LineEditBfield = new QLineEdit( Frame3, "LineEditBfield" );
    LineEditBfield->setGeometry( QRect( 150, 100, 50, 22 ) );

    TextLabel1 = new QLabel( Frame3, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 30, 100, 110, 20 ) );

    TextLabel4 = new QLabel( Frame3, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 220, 100, 65, 20 ) );

    LineEditSim = new QLineEdit( Frame3, "LineEditSim" );
    LineEditSim->setGeometry( QRect( 110, 50, 150, 22 ) );
    LineEditSim->setFrameShape( QLineEdit::LineEditPanel );
    LineEditSim->setFrameShadow( QLineEdit::Sunken );

    PushButtonSimInput = new QPushButton( Frame3, "PushButtonSimInput" );
    PushButtonSimInput->setGeometry( QRect( 270, 50, 30, 20 ) );

    TextLabel7 = new QLabel( Frame3, "TextLabel7" );
    TextLabel7->setGeometry( QRect( 10, 10, 290, 21 ) );
    QFont TextLabel7_font(  TextLabel7->font() );
    TextLabel7_font.setPointSize( 13 );
    TextLabel7->setFont( TextLabel7_font ); 

    TextLabel12 = new QLabel( Frame3, "TextLabel12" );
    TextLabel12->setGeometry( QRect( 30, 50, 72, 20 ) );

    PushButtonSimulate = new QPushButton( Frame3, "PushButtonSimulate" );
    PushButtonSimulate->setGeometry( QRect( 110, 310, 80, 22 ) );

    TextLabel12_4 = new QLabel( Frame3, "TextLabel12_4" );
    TextLabel12_4->setGeometry( QRect( 10, 260, 89, 50 ) );

    LineEditClusterInfo = new QLineEdit( Frame3, "LineEditClusterInfo" );
    LineEditClusterInfo->setGeometry( QRect( 110, 270, 150, 22 ) );
    LineEditClusterInfo->setFrameShape( QLineEdit::LineEditPanel );
    LineEditClusterInfo->setFrameShadow( QLineEdit::Sunken );

    PushButtonClusterInput = new QPushButton( Frame3, "PushButtonClusterInput" );
    PushButtonClusterInput->setGeometry( QRect( 270, 270, 30, 20 ) );

    LineEditLength = new QLineEdit( Frame3, "LineEditLength" );
    LineEditLength->setGeometry( QRect( 150, 220, 50, 22 ) );

    TextLabel11 = new QLabel( Frame3, "TextLabel11" );
    TextLabel11->setGeometry( QRect( 30, 220, 105, 16 ) );

    TextLabel2 = new QLabel( Frame3, "TextLabel2" );
    TextLabel2->setGeometry( QRect( 30, 140, 110, 20 ) );

    TextLabel2_2 = new QLabel( Frame3, "TextLabel2_2" );
    TextLabel2_2->setGeometry( QRect( 30, 180, 102, 20 ) );

    TextLabel5 = new QLabel( Frame3, "TextLabel5" );
    TextLabel5->setGeometry( QRect( 220, 140, 65, 20 ) );

    TextLabel5_7 = new QLabel( Frame3, "TextLabel5_7" );
    TextLabel5_7->setGeometry( QRect( 220, 180, 65, 20 ) );

    TextLabel6 = new QLabel( Frame3, "TextLabel6" );
    TextLabel6->setGeometry( QRect( 220, 220, 65, 20 ) );

    LineEditOuterRadius = new QLineEdit( Frame3, "LineEditOuterRadius" );
    LineEditOuterRadius->setGeometry( QRect( 150, 180, 50, 22 ) );

    LineEditInnerRadius = new QLineEdit( Frame3, "LineEditInnerRadius" );
    LineEditInnerRadius->setGeometry( QRect( 150, 140, 50, 22 ) );

    Frame4 = new QFrame( this, "Frame4" );
    Frame4->setGeometry( QRect( 10, 371, 320, 260 ) );
    Frame4->setFrameShape( QFrame::StyledPanel );
    Frame4->setFrameShadow( QFrame::Raised );

    PushButtonDriftInput = new QPushButton( Frame4, "PushButtonDriftInput" );
    PushButtonDriftInput->setGeometry( QRect( 280, 70, 30, 20 ) );

    TextLabel9 = new QLabel( Frame4, "TextLabel9" );
    TextLabel9->setGeometry( QRect( 30, 120, 26, 14 ) );

    LineEditGas = new QLineEdit( Frame4, "LineEditGas" );
    LineEditGas->setGeometry( QRect( 150, 110, 70, 22 ) );

    TextLabel1_3 = new QLabel( Frame4, "TextLabel1_3" );
    TextLabel1_3->setGeometry( QRect( 230, 110, 89, 20 ) );
    QFont TextLabel1_3_font(  TextLabel1_3->font() );
    TextLabel1_3_font.setPointSize( 9 );
    TextLabel1_3->setFont( TextLabel1_3_font ); 

    PushButtonDrift = new QPushButton( Frame4, "PushButtonDrift" );
    PushButtonDrift->setGeometry( QRect( 110, 210, 84, 22 ) );

    TextLabel10 = new QLabel( Frame4, "TextLabel10" );
    TextLabel10->setGeometry( QRect( 30, 160, 90, 16 ) );

    TextLabel13 = new QLabel( Frame4, "TextLabel13" );
    TextLabel13->setGeometry( QRect( 240, 160, 72, 20 ) );

    TextLabel12_2 = new QLabel( Frame4, "TextLabel12_2" );
    TextLabel12_2->setGeometry( QRect( 30, 70, 72, 20 ) );

    TextLabel8 = new QLabel( Frame4, "TextLabel8" );
    TextLabel8->setGeometry( QRect( 10, 20, 130, 21 ) );
    QFont TextLabel8_font(  TextLabel8->font() );
    TextLabel8_font.setPointSize( 13 );
    TextLabel8->setFont( TextLabel8_font ); 

    LineEditDrift = new QLineEdit( Frame4, "LineEditDrift" );
    LineEditDrift->setGeometry( QRect( 110, 70, 160, 22 ) );
    LineEditDrift->setFrameShape( QLineEdit::LineEditPanel );
    LineEditDrift->setFrameShadow( QLineEdit::Sunken );

    LineEditEfield = new QLineEdit( Frame4, "LineEditEfield" );
    LineEditEfield->setGeometry( QRect( 150, 160, 70, 22 ) );

    Frame7 = new QFrame( this, "Frame7" );
    Frame7->setGeometry( QRect( 340, 10, 320, 620 ) );
    Frame7->setFrameShape( QFrame::StyledPanel );
    Frame7->setFrameShadow( QFrame::Raised );

    LineEditPads = new QLineEdit( Frame7, "LineEditPads" );
    LineEditPads->setGeometry( QRect( 100, 40, 160, 22 ) );
    LineEditPads->setFrameShape( QLineEdit::LineEditPanel );
    LineEditPads->setFrameShadow( QLineEdit::Sunken );

    TextLabel7_2 = new QLabel( Frame7, "TextLabel7_2" );
    TextLabel7_2->setGeometry( QRect( 10, 9, 306, 21 ) );
    QFont TextLabel7_2_font(  TextLabel7_2->font() );
    TextLabel7_2_font.setPointSize( 13 );
    TextLabel7_2->setFont( TextLabel7_2_font ); 

    TextLabel12_3 = new QLabel( Frame7, "TextLabel12_3" );
    TextLabel12_3->setGeometry( QRect( 20, 40, 72, 20 ) );

    PushButtonPadInput = new QPushButton( Frame7, "PushButtonPadInput" );
    PushButtonPadInput->setGeometry( QRect( 280, 40, 30, 20 ) );

    PushButtonMakePads = new QPushButton( Frame7, "PushButtonMakePads" );
    PushButtonMakePads->setGeometry( QRect( 120, 570, 84, 22 ) );

    TextLabel3_3 = new QLabel( Frame7, "TextLabel3_3" );
    TextLabel3_3->setGeometry( QRect( 20, 80, 65, 20 ) );

    TextLabel3_3_2 = new QLabel( Frame7, "TextLabel3_3_2" );
    TextLabel3_3_2->setGeometry( QRect( 160, 80, 71, 20 ) );

    LineEditPadx = new QLineEdit( Frame7, "LineEditPadx" );
    LineEditPadx->setGeometry( QRect( 40, 100, 50, 22 ) );

    TextLabel4_2 = new QLabel( Frame7, "TextLabel4_2" );
    TextLabel4_2->setGeometry( QRect( 100, 100, 30, 20 ) );

    LineEditPady = new QLineEdit( Frame7, "LineEditPady" );
    LineEditPady->setGeometry( QRect( 180, 100, 50, 22 ) );

    TextLabel4_2_2 = new QLabel( Frame7, "TextLabel4_2_2" );
    TextLabel4_2_2->setGeometry( QRect( 250, 100, 30, 20 ) );

    TextLabel3_3_3_2 = new QLabel( Frame7, "TextLabel3_3_3_2" );
    TextLabel3_3_3_2->setGeometry( QRect( 160, 130, 100, 20 ) );

    LineEditPadsInRow = new QLineEdit( Frame7, "LineEditPadsInRow" );
    LineEditPadsInRow->setGeometry( QRect( 180, 150, 50, 22 ) );

    LineEditNPads = new QLineEdit( Frame7, "LineEditNPads" );
    LineEditNPads->setGeometry( QRect( 40, 150, 50, 22 ) );

    TextLabel3_3_3_3 = new QLabel( Frame7, "TextLabel3_3_3_3" );
    TextLabel3_3_3_3->setGeometry( QRect( 20, 180, 230, 20 ) );

    LineEditOffsetX = new QLineEdit( Frame7, "LineEditOffsetX" );
    LineEditOffsetX->setGeometry( QRect( 40, 210, 50, 23 ) );

    TextLabel4_2_2_2 = new QLabel( Frame7, "TextLabel4_2_2_2" );
    TextLabel4_2_2_2->setGeometry( QRect( 100, 210, 45, 20 ) );

    TextLabel4_2_2_2_2 = new QLabel( Frame7, "TextLabel4_2_2_2_2" );
    TextLabel4_2_2_2_2->setGeometry( QRect( 240, 210, 45, 20 ) );

    TextLabel3_3_3 = new QLabel( Frame7, "TextLabel3_3_3" );
    TextLabel3_3_3->setGeometry( QRect( 20, 130, 100, 20 ) );

    LineEditOffsetY = new QLineEdit( Frame7, "LineEditOffsetY" );
    LineEditOffsetY->setGeometry( QRect( 180, 210, 50, 23 ) );

    TextLabel5_2 = new QLabel( Frame7, "TextLabel5_2" );
    TextLabel5_2->setGeometry( QRect( 20, 250, 130, 24 ) );
    QFont TextLabel5_2_font(  TextLabel5_2->font() );
    TextLabel5_2_font.setPointSize( 12 );
    TextLabel5_2_font.setItalic( TRUE );
    TextLabel5_2->setFont( TextLabel5_2_font ); 

    TextLabel6_3_2 = new QLabel( Frame7, "TextLabel6_3_2" );
    TextLabel6_3_2->setGeometry( QRect( 30, 290, 65, 20 ) );

    TextLabel6_3_3 = new QLabel( Frame7, "TextLabel6_3_3" );
    TextLabel6_3_3->setGeometry( QRect( 30, 320, 92, 20 ) );

    TextLabel6_3_4 = new QLabel( Frame7, "TextLabel6_3_4" );
    TextLabel6_3_4->setGeometry( QRect( 30, 350, 65, 20 ) );

    TextLabel6_3_5 = new QLabel( Frame7, "TextLabel6_3_5" );
    TextLabel6_3_5->setGeometry( QRect( 30, 380, 92, 20 ) );

    TextLabel6_3_6 = new QLabel( Frame7, "TextLabel6_3_6" );
    TextLabel6_3_6->setGeometry( QRect( 30, 410, 65, 20 ) );

    TextLabel6_3_7 = new QLabel( Frame7, "TextLabel6_3_7" );
    TextLabel6_3_7->setGeometry( QRect( 30, 440, 100, 20 ) );

    LineEditUGEM1 = new QLineEdit( Frame7, "LineEditUGEM1" );
    LineEditUGEM1->setGeometry( QRect( 170, 290, 50, 22 ) );

    LineEditEtrans1 = new QLineEdit( Frame7, "LineEditEtrans1" );
    LineEditEtrans1->setGeometry( QRect( 170, 320, 50, 22 ) );

    LineEditUGEM2 = new QLineEdit( Frame7, "LineEditUGEM2" );
    LineEditUGEM2->setGeometry( QRect( 170, 350, 50, 22 ) );

    LineEditEtrans2 = new QLineEdit( Frame7, "LineEditEtrans2" );
    LineEditEtrans2->setGeometry( QRect( 170, 380, 50, 22 ) );

    LineEditUGEM3 = new QLineEdit( Frame7, "LineEditUGEM3" );
    LineEditUGEM3->setGeometry( QRect( 170, 410, 50, 22 ) );

    LineEditEind = new QLineEdit( Frame7, "LineEditEind" );
    LineEditEind->setGeometry( QRect( 170, 440, 50, 22 ) );

    TextLabel6_3_8 = new QLabel( Frame7, "TextLabel6_3_8" );
    TextLabel6_3_8->setGeometry( QRect( 240, 290, 30, 20 ) );

    TextLabel7_3_2 = new QLabel( Frame7, "TextLabel7_3_2" );
    TextLabel7_3_2->setGeometry( QRect( 240, 320, 40, 20 ) );

    TextLabel6_3_8_2 = new QLabel( Frame7, "TextLabel6_3_8_2" );
    TextLabel6_3_8_2->setGeometry( QRect( 240, 350, 30, 20 ) );

    TextLabel7_3_3 = new QLabel( Frame7, "TextLabel7_3_3" );
    TextLabel7_3_3->setGeometry( QRect( 240, 380, 40, 20 ) );

    TextLabel6_3_8_3 = new QLabel( Frame7, "TextLabel6_3_8_3" );
    TextLabel6_3_8_3->setGeometry( QRect( 240, 410, 30, 20 ) );

    TextLabel7_3_4 = new QLabel( Frame7, "TextLabel7_3_4" );
    TextLabel7_3_4->setGeometry( QRect( 240, 440, 40, 20 ) );

    TextLabel2_3 = new QLabel( Frame7, "TextLabel2_3" );
    TextLabel2_3->setGeometry( QRect( 20, 490, 100, 20 ) );

    LineEditParamFile = new QLineEdit( Frame7, "LineEditParamFile" );
    LineEditParamFile->setGeometry( QRect( 120, 490, 130, 22 ) );

    PushButtonParamFile = new QPushButton( Frame7, "PushButtonParamFile" );
    PushButtonParamFile->setGeometry( QRect( 260, 490, 30, 20 ) );

    TextLabel3_3_3_4 = new QLabel( Frame7, "TextLabel3_3_3_4" );
    TextLabel3_3_3_4->setGeometry( QRect( 20, 530, 100, 20 ) );

    LineEditGainFactor = new QLineEdit( Frame7, "LineEditGainFactor" );
    LineEditGainFactor->setGeometry( QRect( 120, 530, 50, 23 ) );

    Frame8 = new QFrame( this, "Frame8" );
    Frame8->setGeometry( QRect( 671, 10, 340, 830 ) );
    Frame8->setFrameShape( QFrame::StyledPanel );
    Frame8->setFrameShadow( QFrame::Raised );

    TextLabel1_4 = new QLabel( Frame8, "TextLabel1_4" );
    TextLabel1_4->setGeometry( QRect( 90, 10, 150, 24 ) );
    QFont TextLabel1_4_font(  TextLabel1_4->font() );
    TextLabel1_4_font.setPointSize( 14 );
    TextLabel1_4->setFont( TextLabel1_4_font ); 

    PushButtonCancel = new QPushButton( Frame8, "PushButtonCancel" );
    PushButtonCancel->setGeometry( QRect( 120, 770, 110, 20 ) );

    frame7 = new QFrame( this, "frame7" );
    frame7->setGeometry( QRect( 10, 640, 651, 200 ) );
    frame7->setFrameShape( QFrame::StyledPanel );
    frame7->setFrameShadow( QFrame::Raised );

    TextLabel8_2 = new QLabel( frame7, "TextLabel8_2" );
    TextLabel8_2->setGeometry( QRect( 20, 10, 150, 21 ) );
    QFont TextLabel8_2_font(  TextLabel8_2->font() );
    TextLabel8_2_font.setPointSize( 13 );
    TextLabel8_2->setFont( TextLabel8_2_font ); 

    PushButtonElectronicsInput = new QPushButton( frame7, "PushButtonElectronicsInput" );
    PushButtonElectronicsInput->setGeometry( QRect( 380, 40, 30, 20 ) );

    TextLabel12_3_2 = new QLabel( frame7, "TextLabel12_3_2" );
    TextLabel12_3_2->setGeometry( QRect( 20, 40, 72, 20 ) );

    LineEditElectronics = new QLineEdit( frame7, "LineEditElectronics" );
    LineEditElectronics->setGeometry( QRect( 100, 40, 260, 23 ) );
    LineEditElectronics->setFrameShape( QLineEdit::LineEditPanel );
    LineEditElectronics->setFrameShadow( QLineEdit::Sunken );

    PushButtonShape = new QPushButton( frame7, "PushButtonShape" );
    PushButtonShape->setGeometry( QRect( 490, 40, 84, 22 ) );

    TextLabel12_3_2_2 = new QLabel( frame7, "TextLabel12_3_2_2" );
    TextLabel12_3_2_2->setGeometry( QRect( 20, 80, 117, 20 ) );

    LineEditFrequency = new QLineEdit( frame7, "LineEditFrequency" );
    LineEditFrequency->setGeometry( QRect( 150, 80, 70, 22 ) );

    TextLabel5_3 = new QLabel( frame7, "TextLabel5_3" );
    TextLabel5_3->setGeometry( QRect( 230, 80, 65, 20 ) );

    LineEditRiseTime = new QLineEdit( frame7, "LineEditRiseTime" );
    LineEditRiseTime->setGeometry( QRect( 150, 110, 70, 22 ) );

    TextLabel12_3_2_3 = new QLabel( frame7, "TextLabel12_3_2_3" );
    TextLabel12_3_2_3->setGeometry( QRect( 20, 110, 72, 20 ) );

    TextLabel5_4 = new QLabel( frame7, "TextLabel5_4" );
    TextLabel5_4->setGeometry( QRect( 230, 110, 30, 20 ) );

    TextLabel12_3_2_3_2 = new QLabel( frame7, "TextLabel12_3_2_3_2" );
    TextLabel12_3_2_3_2->setGeometry( QRect( 20, 140, 120, 20 ) );

    LineEditADCRes = new QLineEdit( frame7, "LineEditADCRes" );
    LineEditADCRes->setGeometry( QRect( 150, 140, 70, 23 ) );

    TextLabel5_5 = new QLabel( frame7, "TextLabel5_5" );
    TextLabel5_5->setGeometry( QRect( 230, 140, 30, 20 ) );

    LineEditADCMaxQ = new QLineEdit( frame7, "LineEditADCMaxQ" );
    LineEditADCMaxQ->setGeometry( QRect( 470, 80, 70, 23 ) );

    TextLabel12_3_2_3_2_2_2 = new QLabel( frame7, "TextLabel12_3_2_3_2_2_2" );
    TextLabel12_3_2_3_2_2_2->setGeometry( QRect( 320, 110, 140, 20 ) );

    TextLabel5_6 = new QLabel( frame7, "TextLabel5_6" );
    TextLabel5_6->setGeometry( QRect( 560, 80, 40, 20 ) );

    TextLabel12_3_2_3_2_2 = new QLabel( frame7, "TextLabel12_3_2_3_2_2" );
    TextLabel12_3_2_3_2_2->setGeometry( QRect( 320, 80, 140, 20 ) );

    LineEditThreshold = new QLineEdit( frame7, "LineEditThreshold" );
    LineEditThreshold->setGeometry( QRect( 470, 110, 70, 23 ) );

    TextLabel5_5_2 = new QLabel( frame7, "TextLabel5_5_2" );
    TextLabel5_5_2->setGeometry( QRect( 560, 110, 67, 20 ) );

    TextLabel5_5_2_2 = new QLabel( frame7, "TextLabel5_5_2_2" );
    TextLabel5_5_2_2->setGeometry( QRect( 560, 160, 68, 33 ) );

    LineEditCutOff = new QLineEdit( frame7, "LineEditCutOff" );
    LineEditCutOff->setGeometry( QRect( 470, 170, 70, 23 ) );

    LineEditgainF = new QLineEdit( frame7, "LineEditgainF" );
    LineEditgainF->setGeometry( QRect( 470, 140, 70, 23 ) );

    TextLabel1299 = new QLabel( frame7, "TextLabel1299" );
    TextLabel1299->setGeometry( QRect( 320, 170, 140, 20 ) );

    TextLabel1299_2 = new QLabel( frame7, "TextLabel1299_2" );
    TextLabel1299_2->setGeometry( QRect( 320, 140, 140, 20 ) );
    languageChange();
    resize( QSize(1020, 849).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
TPCSimulation::~TPCSimulation()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void TPCSimulation::languageChange()
{
    setCaption( tr( "Form1" ) );
    TextLabel1->setText( tr( "Magnetic Field B" ) );
    TextLabel4->setText( tr( "[T]" ) );
    PushButtonSimInput->setText( tr( "..." ) );
    TextLabel7->setText( tr( "1. Primary Ionisation" ) );
    TextLabel12->setText( tr( "Input File" ) );
    PushButtonSimulate->setText( tr( "Simulate" ) );
    TextLabel12_4->setText( tr( "#e- pro Cluster \n"
"    Info File" ) );
    PushButtonClusterInput->setText( tr( "..." ) );
    TextLabel11->setText( tr( "TPC Drift Length " ) );
    TextLabel2->setText( tr( "TPC inner radius" ) );
    TextLabel2_2->setText( tr( "TPC outer radius" ) );
    TextLabel5->setText( tr( "[mm]" ) );
    TextLabel5_7->setText( tr( "[mm]" ) );
    TextLabel6->setText( tr( "[mm]" ) );
    PushButtonDriftInput->setText( tr( "..." ) );
    TextLabel9->setText( tr( "Gas" ) );
    TextLabel1_3->setText( tr( "(TDR, P5, P10)" ) );
    PushButtonDrift->setText( tr( "Drift" ) );
    TextLabel10->setText( tr( "Electric Field E" ) );
    TextLabel13->setText( tr( "[V/cm]" ) );
    TextLabel12_2->setText( tr( "Input File" ) );
    TextLabel8->setText( tr( "2. Drift Tracks" ) );
    TextLabel7_2->setText( tr( "3. Amplification and Creation of Voxel" ) );
    TextLabel12_3->setText( tr( "Inputfile" ) );
    PushButtonPadInput->setText( tr( "..." ) );
    PushButtonMakePads->setText( tr( "Make Pads" ) );
    TextLabel3_3->setText( tr( "Pad Width " ) );
    TextLabel3_3_2->setText( tr( "Pad Height " ) );
    TextLabel4_2->setText( tr( "[mm]" ) );
    TextLabel4_2_2->setText( tr( "[mm]" ) );
    TextLabel3_3_3_2->setText( tr( "Pads in Row" ) );
    TextLabel3_3_3_3->setText( tr( "Offset of Padplane to Center of TPC" ) );
    TextLabel4_2_2_2->setText( tr( "x [mm]" ) );
    TextLabel4_2_2_2_2->setText( tr( "y [mm]" ) );
    TextLabel3_3_3->setText( tr( "Number of Pads" ) );
    TextLabel5_2->setText( tr( "GEM Settings" ) );
    TextLabel6_3_2->setText( tr( "U GEM 1" ) );
    TextLabel6_3_3->setText( tr( "Transfer Field 1" ) );
    TextLabel6_3_4->setText( tr( "U GEM 2" ) );
    TextLabel6_3_5->setText( tr( "Transfer Field 2" ) );
    TextLabel6_3_6->setText( tr( "U GEM 3" ) );
    TextLabel6_3_7->setText( tr( "Induction Field" ) );
    TextLabel6_3_8->setText( tr( "[V]" ) );
    TextLabel7_3_2->setText( tr( "[V/cm]" ) );
    TextLabel6_3_8_2->setText( tr( "[V]" ) );
    TextLabel7_3_3->setText( tr( "[V/cm]" ) );
    TextLabel6_3_8_3->setText( tr( "[V]" ) );
    TextLabel7_3_4->setText( tr( "[V/cm]" ) );
    TextLabel2_3->setText( tr( "Parameter File" ) );
    PushButtonParamFile->setText( tr( "..." ) );
    TextLabel3_3_3_4->setText( tr( "Gain Factor" ) );
    TextLabel1_4->setText( tr( "Program Output" ) );
    PushButtonCancel->setText( tr( "Cancel Program" ) );
    TextLabel8_2->setText( tr( "4. TPCElectronics" ) );
    PushButtonElectronicsInput->setText( tr( "..." ) );
    TextLabel12_3_2->setText( tr( "Inputfile" ) );
    PushButtonShape->setText( tr( "Do Shaping" ) );
    TextLabel12_3_2_2->setText( tr( "Readout Frequency" ) );
    TextLabel5_3->setText( tr( "[MHz]" ) );
    TextLabel12_3_2_3->setText( tr( "Rise Time" ) );
    TextLabel5_4->setText( tr( "[ns]" ) );
    TextLabel12_3_2_3_2->setText( tr( "ADC Resolution" ) );
    TextLabel5_5->setText( tr( "[bit]" ) );
    TextLabel12_3_2_3_2_2_2->setText( tr( "Threshold for ADC bin" ) );
    TextLabel5_6->setText( tr( "[#e-]" ) );
    TextLabel12_3_2_3_2_2->setText( tr( "max. Charge for ADC" ) );
    TextLabel5_5_2->setText( tr( "[ADC bins]" ) );
    TextLabel5_5_2_2->setText( tr( "[multiple of \n"
"sigma]" ) );
    TextLabel1299->setText( tr( "Integration cutoff" ) );
    TextLabel1299_2->setText( tr( "Charge loss factor" ) );
}

