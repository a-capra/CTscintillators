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
// $Id: CTSciDetectorConstruction.cc,v 1.22 2010-01-22 11:57:03 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#include "DetectorConstruction.hh"
#include "MagneticField.hh"
#include "SciSD.hh"
#include "DetectorMessenger.hh"

#include "G4RunManager.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4SystemOfUnits.hh"

#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include "SwanseaMagField.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"

#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
DetectorConstruction::DetectorConstruction():
  solidWorld(0),         logicWorld(0),         physiWorld(0),
  solidCT(0),            logicCT(0),            physiCT(0),
  solidMagnetOut(0),     logicMagnetOut(0),     physiMagnetOut(0),
  solidMagnetIn(0),      logicMagnetIn(0),      physiMagnetIn(0),
  solidMagnetShield(0),  logicMagnetShield(0),  physiMagnetShield(0),
  solidMagnetWinding(0), logicMagnetWinding(0), physiMagnetWinding(0),
  solidMagnetCover(0),   logicMagnetCover(0),
  solidOVC(0),           logicOVC(0),           physiOVC(0),
  solidInner(0),         logicInner(0),         physiInner(0),
  solidShield(0),        logicShield(0),        physiShield(0),
  solidWall(0),          logicWall(0),          physiWall(0),
  solidTrap(0),          logicTrap(0),          physiTrap(0),
  solidDeg1(0),          logicDeg1(0),          physiDeg1(0),
  solidDeg2(0),          logicDeg2(0),          physiDeg2(0),
  solidSci(0),           logicSci(0),
  NofSci(2)
  //,stepLimit(0)
{
  fWorldLength=5.*m;
  
  MagnetOutID=52.*cm; 
  MagnetOutOD=53.*cm;
  MagnetOutL=75.*cm;
  
  MagnetShieldID=45.5*cm;
  MagnetShieldOD=46.*cm;
  MagnetShieldL=70.*cm;
  
  MagnetWindID=14.5*cm;
  MagnetWindOD=15.*cm;
  
  MagnetBore=140.*mm;
  MagnetCover=1.*cm;

  MagnetInID=MagnetBore; // unused
  MagnetInOD=45.5*cm;
  MagnetInL=69.*cm;
		  
  
  OVCID=78.*mm;
  OVCOD=80.*mm;
  OVCL=150.*cm;
  
  ShieldID=67.*mm;
  ShieldOD=70.*mm;
  ShieldL=70.*cm;
  
  WallID=47.*mm;
  WallOD=50.*mm;
  WallL=67.*cm;
 
  TrapID=36.5*mm;
  TrapOD=40.*mm;
  TrapL=65.*cm;
  
  Deg1L=(0.165+0.05)*mm;
  Deg2L=(0.01+0.03)*mm;
  
  OVCVtOffset=-5.*cm;
  OVCHzOffset=0.*cm;
  
  fSciX=1.*cm;
  fSciY=60.*cm;
  fSciZ=40.*cm;
  //  NofSci=4;
  
  for(G4int i=0;i<NofSci;++i) physiSci[i]=0;
  
  for(G4int i=0;i<2;++i) physiMagnetCover[i]=0;
 
  // //----- 2012 position -----   
  // leftPadPosX=   60.0*cm;
  // leftPadPosY=    0.0;
  // leftPadPosZ=  -15.0*cm;
  // rightPadPosX=-100.0*cm;
  // rightPadPosY=   5.0*cm;
  // rightPadPosZ= -90.0*cm;
  // //-------------------------

  //----- 2016 position -----
  leftPadPosX=   55.0*cm;
  leftPadPosY=    2.0;
  leftPadPosZ=  -(0.5*MagnetOutL+MagnetCover)-32.*cm;
  rightPadPosX= -59.0*cm;
  rightPadPosY=   3.0*cm;
  rightPadPosZ= -(0.5*MagnetOutL+MagnetCover)-30.*cm;

  //-------------------------

  fpMagField = new MagneticField(G4ThreeVector(0.,0.,3.*tesla));

  // global field
  // fpMagField = new MagneticField(G4ThreeVector());
  // fpMagField->SetMagFieldValue(3.*tesla);


  detectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
DetectorConstruction::~DetectorConstruction()
{
  if( fpMagField )
    delete fpMagField;
  if( detectorMessenger )
    delete detectorMessenger;
  //  delete stepLimit;             
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  //--------- Material definition ---------

  G4double density;
  G4int nel;

  G4Element* H  = new G4Element("Hydrogen", "H" ,1., 1.01*g/mole);
  G4Element* He = new G4Element("Helium",   "He",2., 4.*g/mole);
  G4Element* C  = new G4Element("Carbon",   "C" ,6., 12.01*g/mole);
  G4Element* N  = new G4Element("Nitrogen", "N", 7., 14.01*g/mole);
  G4Element* O  = new G4Element("Oxygen"  , "O", 8., 16.00*g/mole);
  G4Element* Si = new G4Element("Silicon",  "Si",14.,28.09*g/mole);
  G4Element* Cr = new G4Element("Chromium", "Cr",24.,52.*g/mole);
  G4Element* Mn = new G4Element("Manganese","Mn",25.,54.94*g/mole);
  G4Element* Fe = new G4Element("Iron",     "Fe",26.,55.85*g/mole);
  G4Element* Ni = new G4Element("Nickel",   "Ni",28.,58.69*g/mole);
   
  G4Material* Air = new G4Material("Air", density= 1.29*mg/cm3, nel=2);
  Air->AddElement(N, 70*perCent);
  Air->AddElement(O, 30*perCent);
  
  G4Material* Vacuum = new G4Material("Vacuum",10.e-10*mg/cm3,2,kStateGas,4.*kelvin,1.e-12*bar);
  Vacuum->AddElement(H,0.7);
  Vacuum->AddElement(He,0.3);


  G4Material* coolant = new G4Material("lHe",2., 4.*g/mole, 0.125*g/cm3, kStateGas, 4.2*kelvin,1.*atmosphere);
 
  
  G4Material* SciMater = new G4Material("Scintillator", density= 1.032*g/cm3, nel=2);
  SciMater->AddElement(C, 9);
  SciMater->AddElement(H, 10);
  
  G4Material* Aluminium = new G4Material("Aluminium",13.,26.98*g/mole,2.70*g/cm3);
  
  G4Material* Copper = new G4Material("Copper",29.,63.55*g/mole,8.96*g/cm3);
  G4Material* CopperW = new G4Material("CopperW",29.,63.55*g/mole,0.6*8.96*g/cm3);
  
  G4Material* StainlessSteel = new G4Material("StainlessSteel",0.5*8.06*g/cm3,6);
  StainlessSteel->AddElement(C,  0.001);
  StainlessSteel->AddElement(Si, 0.007);
  StainlessSteel->AddElement(Cr, 0.18);
  StainlessSteel->AddElement(Mn, 0.01);
  StainlessSteel->AddElement(Fe, 0.712);
  StainlessSteel->AddElement(Ni, 0.09);
  
  G4Material* Beryllium = new G4Material("Beryllium",4,9.01*g/mole,1.85*g/cm3);

  
  //--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------
    
  //--------------------------------------------------------------------
  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;

  //------------------------------ 
  // World
  //------------------------------ 
  solidWorld = new G4Box("solidWorld",0.5*fWorldLength,0.5*fWorldLength,0.5*fWorldLength);
  logicWorld = new G4LogicalVolume( solidWorld, Air, "logicWorld");
  //  Must place the World Physical volume unrotated at (0,0,0).
  // 
  physiWorld = new G4PVPlacement(0,               // no rotation
				 G4ThreeVector(), // at (0,0,0)
				 logicWorld,      // its logical volume
				 "World",         // its name
				 0,               // its mother  volume
				 false,           // no boolean operations
				 0,               // copy number
				 checkOverlaps);  // checking volumes overlaps
  //------------------------------ 
  // Magnet Bore
  //------------------------------
  G4Tubs* Bore = new G4Tubs("MagnetBore",0.,0.5*MagnetBore,0.5*MagnetOutL,0.*deg,360.*deg);



  //------------------------------ 
  // Catching Trap
  //------------------------------			 
  solidCT = new G4Tubs("solidCT",0.,0.5*MagnetOutOD,0.5*OVCL,0.*deg,360.*deg);
  logicCT =  new G4LogicalVolume(solidCT,Air,"logicCT");
  logicCT->SetFieldManager(fpMagField->GetLocalFieldManager(),true); // "local" magnetic field
  physiCT = new G4PVPlacement(0,G4ThreeVector(),
			      logicCT,"CatchingTrap",logicWorld,false,0,checkOverlaps);

  //------------------------------ 
  // Magnet Outer
  //------------------------------
  solidMagnetOut = new G4Tubs("solidMagnetOut",0.5*MagnetOutID,0.5*MagnetOutOD,
			      0.5*MagnetOutL,0.*deg,360.*deg);
  logicMagnetOut = new G4LogicalVolume(solidMagnetOut,Aluminium,"logicMagnetOut");
  physiMagnetOut = new G4PVPlacement(0,G4ThreeVector(),
				     logicMagnetOut,"MagnetOut",logicCT,false,0,checkOverlaps);

  //------------------------------ 
  // Magnet Radiation Shield
  //------------------------------ 
  solidMagnetShield = new G4Tubs("solidShield",0.5*MagnetShieldID,0.5*MagnetShieldOD,0.5*MagnetShieldL,0.*deg,360.*deg);
  logicMagnetShield = new G4LogicalVolume(solidMagnetShield,Aluminium,"logicShield");
  physiMagnetShield = new G4PVPlacement(0,G4ThreeVector(),
					logicMagnetShield,"MagnetShield",
					logicCT,false,0,checkOverlaps);   

  //------------------------------ 
  // Magnet Inner
  //------------------------------
  G4Tubs* Inner = new G4Tubs("Inner",0.,0.5*MagnetInOD,0.5*MagnetInL,0.*deg,360.*deg);
  solidMagnetIn = new G4SubtractionSolid("solidMagnetIn", Inner, Bore, 0, 
					 G4ThreeVector(0.,OVCVtOffset,0.));
  logicMagnetIn = new G4LogicalVolume(solidMagnetIn,coolant,"logicMagnetIn");
  //  logicMagnetIn = new G4LogicalVolume(solidMagnetIn,Vacuum,"logicMagnetIn");
  physiMagnetIn = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),
				    logicMagnetIn,"MagnetIn",logicCT,false,0,checkOverlaps);

  //------------------------------ 
  // Magnet Windings
  //------------------------------
  solidMagnetWinding = new G4Tubs("solidMagnetWinding",0.5*MagnetWindID,0.5*MagnetWindOD,
				  0.5*WallL,0.*deg,360.*deg);
  logicMagnetWinding = new G4LogicalVolume(solidMagnetWinding,CopperW,"logicMagnetWinding");
  physiMagnetWinding = new G4PVPlacement(0,G4ThreeVector(0.,OVCVtOffset,0.),
					 logicMagnetWinding,"MagnetWinding",
  					 logicMagnetIn,false,0,checkOverlaps);


  //------------------------------ 
  // Magnet Side Covers
  //------------------------------
  G4Tubs* Cover = new G4Tubs("Cover",0.,0.49*MagnetOutOD,0.5*MagnetCover,0.*deg,360.*deg);
  solidMagnetCover = new G4SubtractionSolid("solidMagnetCover", Cover, Bore, 0, 
					    G4ThreeVector(0.,OVCVtOffset,0.));
  logicMagnetCover = new G4LogicalVolume(solidMagnetCover,Aluminium,"logicMagnetCovers");
  physiMagnetCover[0] = new G4PVPlacement(0,G4ThreeVector(0.,0.,-0.5*MagnetOutL+0.5*MagnetCover),
					  logicMagnetCover,"MagnetCover01",
  					  logicCT,false,0,checkOverlaps);
  physiMagnetCover[1] = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.5*MagnetOutL-0.5*MagnetCover),
					  logicMagnetCover,"MagnetCover02",
  					  logicCT,false,1,checkOverlaps);


  //------------------------------ 
  // Inner Volume
  //------------------------------
  solidInner = new G4Tubs("solidInner",0.,0.5*OVCOD,0.5*OVCL,0.*deg,360.*deg);
  logicInner = new G4LogicalVolume(solidInner,Vacuum,"logicInner");
  physiInner = new G4PVPlacement(0,                                         // no rotation
				 G4ThreeVector(0.,OVCVtOffset,OVCHzOffset), // at (x,y,z)
				 logicInner,                                // its logical volume				  
				 "VacuumChamber",                           // its name
				 logicCT,                                // its mother  volume
				 false,                                     // no boolean operations
				 0,                                         // copy number
				 checkOverlaps);  
  

  //------------------------------ 
  // OVC
  //------------------------------
  solidOVC = new G4Tubs("solidOVC",0.5*OVCID,0.5*OVCOD,0.5*OVCL,0.*deg,360.*deg); 
  logicOVC = new G4LogicalVolume(solidOVC,StainlessSteel,"logicOVC");
  physiOVC = new G4PVPlacement(0,G4ThreeVector(),logicOVC,"OVC",logicInner,false,0,checkOverlaps);
				 

  //------------------------------ 
  // 40 K Heat Shield
  //------------------------------
  solidShield = new G4Tubs("solidHeatShield",0.5*ShieldID,0.5*ShieldOD,
			   0.5*ShieldL,0.*deg,360.*deg); 
  logicShield = new G4LogicalVolume(solidShield,Copper,"logicHeatShield");
  physiShield = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),
				  logicShield,"HeatShield",logicInner,false,0,checkOverlaps);
  

  //------------------------------ 
  // Trap Vacuum Wall
  //------------------------------
  solidWall = new G4Tubs("solidWall",0.5*WallID,0.5*WallOD,0.5*WallL,0.*deg,360.*deg); 
  logicWall = new G4LogicalVolume(solidWall,Copper,"logicWall");
  physiWall = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),
				logicWall,"TrapWall",logicInner,false,0,checkOverlaps);
  
  
  //------------------------------ 
  // Electrodes
  //------------------------------
  solidTrap = new G4Tubs("solidTrap",0.5*TrapID,0.5*TrapOD,0.5*TrapL,0.*deg,360.*deg); 
  logicTrap = new G4LogicalVolume(solidTrap,Aluminium,"logicTrap");
  physiTrap = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),
				logicTrap,"Electrodes",logicInner,false,0,checkOverlaps);
  
  // Degraders Position
  // G4double Deg2Z=-0.5*TrapL+0.5*Deg2L;
  // G4double Deg1Z=Deg2Z+0.5*Deg1L;
  G4double Deg1Z=-0.5*TrapL-0.5*Deg1L;
  G4double Deg2Z=Deg1Z-0.5*Deg1L-0.5*Deg2L;
  
  //------------------------------ 
  // Degrader 1: Faraday Cup + Vacuum Window
  //------------------------------
  solidDeg1 = new G4Tubs("solidFixDegrader",0.,0.5*TrapID,0.5*Deg1L,0.*deg,360.*deg); 
  logicDeg1 = new G4LogicalVolume(solidDeg1,Beryllium,"logicFixDegrader",0,0,0);
  physiDeg1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,Deg1Z),
				logicDeg1,"FixDegrader",logicInner,false,0,checkOverlaps);
  G4cout<<physiDeg1->GetName()<<" Position (x,y,z): ("
	<<physiDeg1->GetTranslation().x()/cm<<", "
	<<physiDeg1->GetTranslation().y()/cm<<", "
	<<physiDeg1->GetTranslation().z()/cm<<") cm"<<G4endl;

  //------------------------------ 
  // Degrader 2: Radiation shield + Tunable degrader
  //------------------------------
  solidDeg2 = new G4Tubs("solidTuneDegrader",0.,0.5*TrapID,0.5*Deg2L,0.*deg,360.*deg); 
  logicDeg2 = new G4LogicalVolume(solidDeg2,Aluminium,"logicTuneDegrader",0,0,0);
  physiDeg2 = new G4PVPlacement(0,G4ThreeVector(0.,0.,Deg2Z),
				logicDeg2,"TuneDegrader",logicInner,false,0,checkOverlaps);
  G4cout<<physiDeg2->GetName()<<" Position (x,y,z): ("
	<<physiDeg2->GetTranslation().x()/cm<<", "
	<<physiDeg2->GetTranslation().y()/cm<<", "
	<<physiDeg2->GetTranslation().z()/cm<<") cm"<<G4endl;

  //------------------------------------------------ 
  // Sensitive detectors
  //------------------------------------------------ 
  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  G4String SciSDname = "CTSci";
  SciSD* scintillators = new SciSD( SciSDname );
  SDman->AddNewDetector( scintillators );

  //------------------------------ 
  // Scintillators
  //------------------------------
  //  solidSci = new G4Box("Sci",0.5*fSciX,0.5*fSciY,0.5*fSciZ);
  solidSci = new G4Box("solidScintillators",fSciX,0.5*fSciY,0.5*fSciZ);
  logicSci = new G4LogicalVolume(solidSci,SciMater,"logicScintillators");
  logicSci->SetSensitiveDetector( scintillators );
  //  logicSci = new G4LogicalVolume(solidSci,SciMater,"Sci",0,scintillators);
    
  //   physiSci = new G4PVPlacement(0,G4ThreeVector(20.*cm,0.,0.),logicSci,"Sci",logicWorld,false,0);
  //   physiSci = new G4PVPlacement(0,G4ThreeVector(20.*cm+fSciX,0.,0.),logicSci,"Sci",logicWorld,false,1);
  //   physiSci = new G4PVPlacement(0,G4ThreeVector(-20.*cm,0.,0.),logicSci,"Sci",logicWorld,false,2);
  //   physiSci = new G4PVPlacement(0,G4ThreeVector(-20.*cm-fSciX,0.,0.),logicSci,"Sci",logicWorld,false,3);
   
  // LEFT PAD by looking from AD -- Laser Hut Side
  physiSci[0] = new G4PVPlacement(0,G4ThreeVector(leftPadPosX,leftPadPosY,leftPadPosZ),logicSci,
				  "ScintillatorsLeft",logicWorld,false,0,checkOverlaps);
  G4cout<<physiSci[0]->GetName()<<" Position (x,y,z): ("
	<<physiSci[0]->GetTranslation().x()/cm<<", "
	<<physiSci[0]->GetTranslation().y()/cm<<", "
	<<physiSci[0]->GetTranslation().z()/cm<<") cm"<<G4endl;
  // RIGHT PAD -- ASACUSA side
  physiSci[1] = new G4PVPlacement(0,G4ThreeVector(rightPadPosX,rightPadPosY,rightPadPosZ),logicSci,
				  "ScintillatorsRight",logicWorld,false,1,checkOverlaps);
  G4cout<<physiSci[1]->GetName()<<" Position (x,y,z): ("
	<<physiSci[1]->GetTranslation().x()/cm<<", "
	<<physiSci[1]->GetTranslation().y()/cm<<", "
	<<physiSci[1]->GetTranslation().z()/cm<<") cm"<<G4endl;



  //--------- Visualization attributes -------------------------------

  G4VisAttributes* WorldVisAtt= new G4VisAttributes(false);
  logicWorld->SetVisAttributes(WorldVisAtt);

  G4VisAttributes* CTVisAtt= new G4VisAttributes(false);
  logicCT->SetVisAttributes(CTVisAtt);

  // //  G4VisAttributes* SwanVisAtt= new G4VisAttributes(false);
  // G4VisAttributes* SwanVisAtt= new G4VisAttributes(G4Colour::Green());
  // logicSwansea->SetVisAttributes(SwanVisAtt);

  //  G4VisAttributes* MagOutVisAtt= new G4VisAttributes(G4Colour(0.0,0.8,0.2)); // greenish?
  //  G4VisAttributes* MagOutVisAtt= new G4VisAttributes(false);
  G4VisAttributes* MagOutVisAtt=new G4VisAttributes(G4Colour::Green());
  logicMagnetOut->SetVisAttributes(MagOutVisAtt);
  
  G4VisAttributes* MagShlVisAtt= new G4VisAttributes(G4Colour(0.7, 0.4, 0.1)); // brown
  logicMagnetShield->SetVisAttributes(MagShlVisAtt);
  
  G4VisAttributes* MagInVisAtt= new G4VisAttributes(G4Colour::Cyan()); 
  logicMagnetIn ->SetVisAttributes(MagInVisAtt);
  
  G4VisAttributes* MagWindVisAtt= new G4VisAttributes(G4Colour::Yellow()); 
  logicMagnetWinding->SetVisAttributes(MagWindVisAtt);
  
  // G4VisAttributes* MagCovVisAtt= new G4VisAttributes(false); 
  G4VisAttributes* MagCovVisAtt= new G4VisAttributes(G4Colour::Grey());
  logicMagnetCover->SetVisAttributes(MagCovVisAtt);
  
  G4VisAttributes* TrpVisAtt= new G4VisAttributes(G4Colour::Yellow()); 
  logicTrap->SetVisAttributes(TrpVisAtt);
  
  //  G4VisAttributes* InnVisAtt= new G4VisAttributes(G4Colour::Cyan()); 
   G4VisAttributes* InnVisAtt= new G4VisAttributes(false); 
  logicInner->SetVisAttributes(InnVisAtt);
  
  G4VisAttributes* SciVisAtt= new G4VisAttributes(G4Colour::White()); 
  logicSci->SetVisAttributes(SciVisAtt);
  
  G4VisAttributes* OVCVisAtt = new G4VisAttributes(G4Colour::Grey());
  logicOVC->SetVisAttributes(OVCVisAtt);
  
  G4VisAttributes* ShlVisAtt = new G4VisAttributes(G4Colour(0.7, 0.4, 0.1));// brown
  logicShield->SetVisAttributes(ShlVisAtt);
  
  G4VisAttributes* WllVisAtt = new G4VisAttributes(G4Colour::Gray());
  logicWall->SetVisAttributes(WllVisAtt);
  
  G4VisAttributes* Deg1VisAtt = new G4VisAttributes(G4Colour::Magenta());
  //  G4VisAttributes* Deg1VisAtt = new G4VisAttributes(false);
  logicDeg1->SetVisAttributes(Deg1VisAtt);
  
  G4VisAttributes* Deg2VisAtt = new G4VisAttributes(G4Colour::Blue());
  //  G4VisAttributes* Deg2VisAtt = new G4VisAttributes(false);
  logicDeg2->SetVisAttributes(Deg2VisAtt);
  
  // //--------- example of User Limits -------------------------------
  // 
  //   // below is an example of how to set tracking constraints in a given
  //   // logical volume(see also in N02PhysicsList how to setup the processes
  //   // G4StepLimiter or G4UserSpecialCuts).
  //     
  //   // Sets a max Step length in the tracker region, with G4StepLimiter
  //   //
  //   G4double maxStep = 0.5*OVCWidth;
  //   stepLimit = new G4UserLimits(maxStep);
  //   logicTracker->SetUserLimits(stepLimit);
  //   
  //   // Set additional contraints on the track, with G4UserSpecialCuts
  //   //
  //   // G4double maxLength = 2*fTrackerLength, maxTime = 0.1*ns, minEkin = 10*MeV;
  //   // logicTracker->SetUserLimits(new G4UserLimits(maxStep,maxLength,maxTime,
  //   //                                               minEkin));
  
  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetLeftPadPosition(G4double posX,G4double posY,G4double posZ)
{
  physiSci[0]->SetTranslation(G4ThreeVector(posX,posY,posZ));
  //   G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
			     
void DetectorConstruction::SetRightPadPosition(G4double posX,G4double posY,G4double posZ)
{
  physiSci[1]->SetTranslation(G4ThreeVector(posX,posY,posZ));
  //   G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  
// void CTSciDetectorConstruction::SetMagField(G4double fieldValue)
// {
//   fpMagField->SetMagFieldValue(fieldValue);  
// }
// 
// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 
// void CTSciDetectorConstruction::SetMaxStep(G4double maxStep)
// {
//   if ((stepLimit)&&(maxStep>0.)) stepLimit->SetMaxAllowedStep(maxStep);
// }
// 
// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetLeftPadPosX(G4double pos)
{
  physiSci[0]->SetTranslation(G4ThreeVector(pos,leftPadPosY,leftPadPosZ));
  //	G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetLeftPadPosY(G4double pos)
{
  physiSci[0]->SetTranslation(G4ThreeVector(leftPadPosX,pos,leftPadPosZ));
  //	G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetLeftPadPosZ(G4double pos)
{
  physiSci[0]->SetTranslation(G4ThreeVector(leftPadPosX,leftPadPosY,pos));
  //	G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
				
void DetectorConstruction::SetRightPadPosX(G4double pos)
{
  physiSci[1]->SetTranslation(G4ThreeVector(pos,rightPadPosY,rightPadPosZ));
  //	G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetRightPadPosY(G4double pos)
{
	
  physiSci[1]->SetTranslation(G4ThreeVector(rightPadPosX,pos,rightPadPosZ));
  //	G4RunManager::GetRunManager()->GeometryHasBeenModified();
}	
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::SetRightPadPosZ(G4double pos)
{
  physiSci[1]->SetTranslation(G4ThreeVector(rightPadPosX,rightPadPosY,pos));
  //	G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

