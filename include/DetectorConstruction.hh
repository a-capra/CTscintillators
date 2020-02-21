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
// $Id: CTSciDetectorConstruction.hh,v 1.10 2008-09-22 16:41:20 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef CTSciDetectorConstruction_h
#define CTSciDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "MagneticField.hh"

class G4Box;
class G4Tubs;
class G4SubtractionSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class DetectorMessenger;
class G4Material;
class G4UserLimits;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  ~DetectorConstruction();
  
  G4VPhysicalVolume* Construct();
     
  G4double GetDegPosition()  const {return -0.5*TrapL+Deg2L+0.5*Deg1L;};
  G4double GetTrapRadius()   const {return 0.5*TrapID;};
  G4double GetTrapVtOffset() const {return OVCVtOffset;};
     
  void SetLeftPadPosX(G4double pos) ;
  void SetLeftPadPosY(G4double pos) ;
  void SetLeftPadPosZ(G4double pos) ;
  void SetRightPadPosX(G4double pos);
  void SetRightPadPosY(G4double pos);
  void SetRightPadPosZ(G4double pos);   
     
  void SetLeftPadPosition(G4double posX,G4double posY,G4double posZ) ;
  void SetRightPadPosition(G4double posX,G4double posY,G4double posZ); 	      
      
  //      void SetMagField(G4double);
  //      void SetMaxStep (G4double);

  G4double GetSwanseaOD() const {return MagnetOutOD;}
  G4double GetSwanseaL()  const {return MagnetOutL;}
     
private:

  G4Box*             solidWorld;    
  G4LogicalVolume*   logicWorld;  
  G4VPhysicalVolume* physiWorld;

  G4Tubs*            solidCT;
  G4LogicalVolume*   logicCT;
  G4VPhysicalVolume* physiCT;
     
  G4Tubs*            solidMagnetOut;
  G4LogicalVolume*   logicMagnetOut;
  G4VPhysicalVolume* physiMagnetOut;
     
  G4SubtractionSolid* solidMagnetIn;
  G4LogicalVolume*    logicMagnetIn;
  G4VPhysicalVolume*  physiMagnetIn;
     
  G4Tubs*             solidMagnetShield;
  G4LogicalVolume*    logicMagnetShield;
  G4VPhysicalVolume*  physiMagnetShield;
     
  G4Tubs* 	     solidMagnetWinding;
  G4LogicalVolume*   logicMagnetWinding;
  G4VPhysicalVolume* physiMagnetWinding;
     
  G4SubtractionSolid* solidMagnetCover;
  G4LogicalVolume*    logicMagnetCover;
  G4VPhysicalVolume*  physiMagnetCover[2];
     
  G4Tubs*            solidOVC;  
  G4LogicalVolume*   logicOVC;  
  G4VPhysicalVolume* physiOVC;
     
  G4Tubs*            solidInner;
  G4LogicalVolume*   logicInner;
  G4VPhysicalVolume* physiInner;
     
  G4Tubs*            solidShield;  
  G4LogicalVolume*   logicShield;  
  G4VPhysicalVolume* physiShield;
     
  G4Tubs*            solidWall;  
  G4LogicalVolume*   logicWall;  
  G4VPhysicalVolume* physiWall;
     
  G4Tubs*            solidTrap;  
  G4LogicalVolume*   logicTrap;  
  G4VPhysicalVolume* physiTrap;
     
  G4Tubs*            solidDeg1;  
  G4LogicalVolume*   logicDeg1;  
  G4VPhysicalVolume* physiDeg1;
  G4Tubs*            solidDeg2;  
  G4LogicalVolume*   logicDeg2;  
  G4VPhysicalVolume* physiDeg2;
     
  G4Box*             solidSci;
  G4LogicalVolume*   logicSci;
  G4VPhysicalVolume* physiSci[2];         

  MagneticField* fpMagField;
     
  DetectorMessenger* detectorMessenger;
        
  G4double fWorldLength;  
     
  G4double MagnetOutID;	   
  G4double MagnetOutOD;
  G4double MagnetOutL;

  G4double MagnetShieldID;
  G4double MagnetShieldOD;
  G4double MagnetShieldL;

  G4double MagnetWindID;
  G4double MagnetWindOD;
		     
  G4double MagnetInID;
  G4double MagnetInOD;
  G4double MagnetInL;
	        	      
  G4double MagnetBore;
  G4double MagnetCover;
            
  G4double OVCID;   
  G4double OVCOD;
  G4double OVCL;
     
  G4double ShieldID;
  G4double ShieldOD;
  G4double ShieldL;

  G4double WallID;
  G4double WallOD;
  G4double WallL;     
     
  G4double TrapID;   
  G4double TrapOD;
  G4double TrapL;     
     
  G4double Deg1L;
  G4double Deg2L;
     
  G4double fSciX;
  G4double fSciY;
  G4double fSciZ;
  G4int    NofSci;
     
  G4double OVCVtOffset;
  G4double OVCHzOffset;
     
  G4double leftPadPosX;
  G4double leftPadPosY;
  G4double leftPadPosZ;
  G4double rightPadPosX;
  G4double rightPadPosY;
  G4double rightPadPosZ;
     
  //  G4UserLimits* stepLimit; 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
