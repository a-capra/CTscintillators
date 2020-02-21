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
// $Id: RunAction.cc,v 1.9 2006-06-29 17:48:16 gunter Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "RunAction.hh"

#include "G4Run.hh"

#include "TFile.h"
#include "TNtuple.h"
#include "TString.h"

TFile* rootfile;
TNtuple *nt;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4int rid=aRun->GetRunID();
  G4cout << "### Run " << rid << " start." << G4endl;
  TString filename="../MCfiles/hit";
  if(rid<10) filename+="0";
  filename+=rid;
  //  filename+="_default";
  filename+=".root";
  //rootfile.Open(filename,"RECREATE");
  rootfile=new TFile(filename,"RECREATE");
  
  //PID=0 means primary particle
  //PAD=0 means left pad, PAD=1 mean right pad
  nt=new TNtuple("nt","nt","EVTN:PDG:PID:TID:EDEP:XPOS:YPOS:ZPOS:PAD:KE:GT");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run*)
{
  //nt->Write();
  rootfile->Write();
  rootfile->Close();
  //delete nt;
  delete rootfile;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



