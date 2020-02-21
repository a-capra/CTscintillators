// $Id: TAlphaPrimaryGenerator.h 341 2008-05-26 11:04:57Z ivana $

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007, 2008 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

/// \file TAlphaPrimaryGenerator.h
/// \brief Definition of the TAlphaPrimaryGenerator class 
///
/// Geant4 ExampleN06 adapted to Virtual Monte Carlo \n
/// Id: ExN06PrimaryGeneratorAction.hh,v 1.4 2003/01/23 15:34:23 maire Exp \n
/// GEANT4 tag Name: geant4-07-00-cand-01 
///
/// \author I. Hrivnacova; IPN, Orsay

#ifndef TALPHA_PRIMARY_GENERATOR_H
#define TALPHA_PRIMARY_GENERATOR_H

#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "G4VPrimaryGenerator.hh"

#include "globals.hh"

class DetectorConstruction;
class G4Event;

class TAlphaPrimaryGenerator : public G4VPrimaryGenerator
{
  public:
    TAlphaPrimaryGenerator(DetectorConstruction*);
    TAlphaPrimaryGenerator();
    virtual ~TAlphaPrimaryGenerator();

    void GeneratePrimaryVertex(G4Event *evt);
    
  private:
     G4double rad;
     G4double zed;
     G4double vtOff;

};

#endif //TALPHA_PRIMARY_GENERATOR_H

