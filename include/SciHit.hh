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
// $Id: SciHit.hh,v 1.8 2006-06-29 17:47:53 gunter Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef SciHit_h
#define SciHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SciHit : public G4VHit
{
  public:

      SciHit();
     ~SciHit();
      SciHit(const SciHit&);
      const SciHit& operator=(const SciHit&);
      G4int operator==(const SciHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();

  public:
  
      void SetPrim     (G4int prim)       { parentID = prim; };
      void SetTrackID  (G4int track)      { trackID = track; };
      void SetTrackPDG (G4int pdgc)       { trackPDG=pdgc;};
      void SetPadNb    (G4int chamb)      { PadNb = chamb; };  
      void SetEdep     (G4double de)      { edep = de; };
      void SetPos      (G4ThreeVector xyz){ pos = xyz; };
      void SetKinEnergy(G4double K)       { kinEnergy = K; };
      void SetGtime    (G4double t)       { gtime = t; };
      
      G4int GetPrim()        { return parentID; };
      G4int GetTrackID()     { return trackID; };
      G4int GetTrackPDG()    { return trackPDG;}
      G4int GetPadNb()       { return PadNb; };
      G4double GetEdep()     { return edep; };      
      G4ThreeVector GetPos() { return pos; };
      G4double GetKinEnergy(){ return kinEnergy; };
      G4double GetGtime()    { return gtime; };
      
  private:
  
      G4int         parentID;
      G4int         trackID;
      G4int	    trackPDG;
      G4int         PadNb;
      G4double      edep;
      G4ThreeVector pos;
      G4double      kinEnergy;
      G4double      gtime;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<SciHit> SciHitsCollection;

extern G4Allocator<SciHit> SciHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* SciHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) SciHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void SciHit::operator delete(void *aHit)
{
  SciHitAllocator.FreeSingle((SciHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
