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
// $Id: MagneticField.hh,v 1.8 2007-08-22 13:11:51 gcosmo Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//
//    A class for control of the Magnetic Field of the detector.
//  The field is assumed to be uniform.
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef MagneticField_H
#define MagneticField_H

#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"

class G4FieldManager;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


class MagneticField//: public G4UniformMagField
{
public:  
  MagneticField(G4ThreeVector);  //  The value of the field
  ~MagneticField() {}  
      
  //Set the field 
  void SetMagFieldValue(G4double fieldValue);
  void SetMagFieldValue(G4ThreeVector fieldVector);
      
  G4ThreeVector GetConstantFieldValue();
  G4FieldManager*  GetLocalFieldManager() { return fLocalFieldManager;}

protected:

  // Find the global Field Manager
  G4FieldManager* GetGlobalFieldManager();   // static 
      
  G4FieldManager*         fFieldManager;
  G4FieldManager*         fLocalFieldManager;
      
  G4MagneticField*        fMagneticField; 
  G4MagneticField*        fLocalMagneticField;
      
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
