//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: DetectorMessenger.cc,v 1.12 2008-09-22 16:41:20 maire Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction* det):Detector(det)
{ 
  SciDir = new G4UIdirectory("/scintillator/");
  SciDir->SetGuidance("Scintillator Pads Position");
  
  leftDir = new G4UIdirectory("/scintillator/left/");
  leftDir->SetGuidance("Left Pad Position");
  
  rightDir = new G4UIdirectory("/scintillator/right/");
  rightDir->SetGuidance("Right Pad Position");
  
  //   FieldCmd = new G4UIcmdWithADoubleAndUnit("/N02/det/setField",this);  
  //   FieldCmd->SetGuidance("Define magnetic field.");
  //   FieldCmd->SetGuidance("Magnetic field will be in X direction.");
  //   FieldCmd->SetParameterName("Bx",false);
  //   FieldCmd->SetUnitCategory("Magnetic flux density");
  //   FieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  //         
  //   StepMaxCmd = new G4UIcmdWithADoubleAndUnit("/N02/det/stepMax",this);  
  //   StepMaxCmd->SetGuidance("Define a step max");
  //   StepMaxCmd->SetParameterName("stepMax",false);
  //   StepMaxCmd->SetUnitCategory("Length");
  //   StepMaxCmd->AvailableForStates(G4State_Idle);    

  LposX = new G4UIcmdWithADoubleAndUnit("/scintillator/left/setPosX",this);
  LposX ->SetGuidance("Move Pad in the X direction");
  LposX ->SetParameterName("LposX",false);				     
  LposX ->SetUnitCategory("Length");			     
  LposX ->AvailableForStates(G4State_PreInit,G4State_Idle);		     
   
  LposY = new G4UIcmdWithADoubleAndUnit("/scintillator/left/setPosY",this);
  LposY ->SetGuidance("Move Pad in the Y direction");
  LposY ->SetParameterName("LposY",false);				     
  LposY ->SetUnitCategory("Length");			     
  LposY ->AvailableForStates(G4State_PreInit,G4State_Idle);
		     
  LposZ = new G4UIcmdWithADoubleAndUnit("/scintillator/left/setPosZ",this);
  LposZ ->SetGuidance("Move Pad in the Y direction");
  LposZ ->SetParameterName("LposZ",false);				     
  LposZ ->SetUnitCategory("Length");			     
  LposZ ->AvailableForStates(G4State_PreInit,G4State_Idle);
     
  RposX = new G4UIcmdWithADoubleAndUnit("/scintillator/right/setPosX",this);
  RposX ->SetGuidance("Move Pad in the X direction");
  RposX ->SetParameterName("RposX",false);				     
  RposX ->SetUnitCategory("Length");			     
  RposX ->AvailableForStates(G4State_PreInit,G4State_Idle);
     
  RposY = new G4UIcmdWithADoubleAndUnit("/scintillator/right/setPosY",this);
  RposY ->SetGuidance("Move Pad in the Y direction");
  RposY ->SetParameterName("RposX",false);				     
  RposY ->SetUnitCategory("Length");			     
  RposY ->AvailableForStates(G4State_PreInit,G4State_Idle);
     
  RposZ = new G4UIcmdWithADoubleAndUnit("/scintillator/right/setPosZ",this);
  RposZ ->SetGuidance("Move Pad in the Z direction");
  RposZ ->SetParameterName("RposX",false);				     
  RposZ ->SetUnitCategory("Length");			     
  RposZ ->AvailableForStates(G4State_PreInit,G4State_Idle);

  leftPosCmd = new G4UIcmdWith3VectorAndUnit("/scintillator/left/setPos",this);
  leftPosCmd->SetGuidance("Translation Vector");
  leftPosCmd->SetParameterName("LposX","LposY","LposZ",false);			     
  leftPosCmd->SetUnitCategory("Length");				
  leftPosCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rightPosCmd = new G4UIcmdWith3VectorAndUnit("/scintillator/right/setPos",this);
  rightPosCmd->SetGuidance("Translation Vector");
  rightPosCmd->SetParameterName("RposX","RposY","RposZ",false);			     
  rightPosCmd->SetUnitCategory("Length");				
  rightPosCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  //  delete FieldCmd;
  //  delete StepMaxCmd;  
  delete SciDir;
  delete leftDir;
  delete rightDir;
  
  delete LposX;
  delete LposY;       
  delete LposZ;       
  delete RposX;       
  delete RposY;       
  delete RposZ;		  
  delete leftPosCmd;
  delete rightPosCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  //  if( command == FieldCmd ) Detector->SetMagField(FieldCmd->GetNewDoubleValue(newValue));
  //  if( command == StepMaxCmd ) Detector->SetMaxStep(StepMaxCmd->GetNewDoubleValue(newValue));

  if( command == LposX ) Detector->SetLeftPadPosX(LposX->GetNewDoubleValue(newValue));
  if( command == LposY ) Detector->SetLeftPadPosY(LposY->GetNewDoubleValue(newValue));
  if( command == LposZ ) Detector->SetLeftPadPosZ(LposZ->GetNewDoubleValue(newValue));
  if( command == RposX ) Detector->SetRightPadPosX(RposX->GetNewDoubleValue(newValue));
  if( command == RposY ) Detector->SetRightPadPosY(RposY->GetNewDoubleValue(newValue));
  if( command == RposZ ) Detector->SetRightPadPosZ(RposZ->GetNewDoubleValue(newValue));

  if( command == leftPosCmd )
    { 
      G4ThreeVector newPos = leftPosCmd->GetNew3VectorValue(newValue);
      Detector->SetLeftPadPosition(newPos.x(),newPos.y(),newPos.z());
    }
      
  if( command == rightPosCmd )
    { 
      G4ThreeVector newPos = rightPosCmd->GetNew3VectorValue(newValue);
      Detector->SetRightPadPosition(newPos.x(),newPos.y(),newPos.z());
    }
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
