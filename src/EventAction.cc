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
// $Id: EventAction.cc,v 1.11 2006-06-29 17:48:05 gunter Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#include "EventAction.hh"

#include "G4Event.hh"
#include "G4ios.hh"
#include "G4ThreeVector.hh"

#include "SciHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"

#include "TNtuple.h"

extern TNtuple *nt;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
EventAction::EventAction()
{
  SciCollID = -1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void EventAction::BeginOfEventAction(const G4Event*)
{
  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  if(SciCollID < 0 ) SciCollID = SDman->GetCollectionID("SciCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void EventAction::EndOfEventAction(const G4Event* evt)
{
  G4int event_id = evt->GetEventID();
  
  if (event_id%1000 == 0) 
 	 G4cout << ">>> Event " << evt->GetEventID() << G4endl;
  
  if(SciCollID < 0) return;

  G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
  
  SciHitsCollection* SHC = 0;
  
  if(HCE) SHC = (SciHitsCollection*)(HCE->GetHC(SciCollID));

  if(SHC)
  {
    int n_hit = SHC->entries();
    
    G4int pdg;
    G4int pID;
    G4int tID;
    G4double dE;
    G4ThreeVector P;
    G4int pad;
    G4double ke;
    G4double t;
    
    for(int i=0;i<n_hit;i++)
    { 
      dE   = (*SHC)[i] -> GetEdep();
      pID  = (*SHC)[i] -> GetPrim();
      tID  = (*SHC)[i] -> GetTrackID();
      pdg  = (*SHC)[i] -> GetTrackPDG();
      P    = (*SHC)[i] -> GetPos();
      pad  = (*SHC)[i] -> GetPadNb();
      ke   = (*SHC)[i] -> GetKinEnergy();
      t    = (*SHC)[i] -> GetGtime();

      // Fill the Ntuple
      nt -> Fill( event_id, pdg, pID ,tID, dE, P.getX(),P.getY(),P.getZ(),pad,ke,t);
    }
    
   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
