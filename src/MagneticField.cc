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
// $Id: MagneticField.cc,v 1.9 2007-08-22 13:11:51 gcosmo Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//  
//   User Field class implementation.
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "MagneticField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MagneticField::MagneticField(G4ThreeVector fieldVector):fFieldManager(0),fMagneticField(0)
{
  fLocalMagneticField = new G4UniformMagField( fieldVector );
  fLocalFieldManager = new G4FieldManager( fLocalMagneticField );
  fLocalFieldManager->CreateChordFinder( fLocalMagneticField );
  //  fLocalFieldManager->GetChordFinder()->SetDeltaChord( 1.*cm );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Set the value of the Global Field to fieldValue along Z
//
void MagneticField::SetMagFieldValue(G4double fieldValue)
{
  SetMagFieldValue(G4ThreeVector(0.,0.,fieldValue));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Set the value of the Global Field
//
void MagneticField::SetMagFieldValue(G4ThreeVector fieldVector)
{
  if(fMagneticField) delete fMagneticField;

  if(fieldVector != G4ThreeVector(0.,0.,0.))
  { 
    fMagneticField = new G4UniformMagField(fieldVector);
    fFieldManager = GetGlobalFieldManager();
    fFieldManager->SetDetectorField( fMagneticField );
    fFieldManager->CreateChordFinder( fMagneticField );
  }
  else 
  {
    // If the new field's value is Zero, then 
    //  setting the pointer to zero ensures 
    //  that it is not used for propagation.
    fMagneticField = 0; 
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4FieldManager*  MagneticField::GetGlobalFieldManager()
{
  return G4TransportationManager::GetTransportationManager()->GetFieldManager();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
