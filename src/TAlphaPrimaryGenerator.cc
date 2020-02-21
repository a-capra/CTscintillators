// Adapted from:
//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007, 2008 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

/// Implementation of the  class 
/// Geant4 ExampleN06 adapted to Virtual Monte Carlo \n
/// Id: ExN06PrimaryGeneratorAction.cc,v 1.3 2004/04/02 11:54:29 maire Exp \n 
/// GEANT4 tag Name: geant4-07-00-cand-01 
///
/// \date 16/05/2005
/// \author I. Hrivnacova; IPN, Orsay

//#include <utility>

#include <TGenPhaseSpace.h>
#include <TPDGCode.h>
#include <TDatabasePDG.h>
#include <TParticlePDG.h>
#include <TVector3.h>
#include <TMath.h>

#include "DetectorConstruction.hh"
#include "TAlphaPrimaryGenerator.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4ios.hh"
#include "Randomize.hh"

#define MPC 0.139566 // LGCP : This is the mass of a charged pion in GeV/c^2
#define MP0 0.134976 // LGCP : This is the mass of a neutral pion in GeV/c^2

#define NFS 14       // LGCP : This is the number of branches/decay modes of p-pbar annihilation 


// LGCP : Below are the number of particles involved when a certain branch/decay mode is taken
G4int NumPar[NFS] = 
{ 
     2,                                 // p0 p0   
     4,                                 // p0 p0 p0 p0 
     3,                                 // p+ p- p0
     4,                                 // p+ p- p0 p0
     5,                                 // p+ p- p0 p0 p0
     6,                                 // p+ p- p0 p0 p0 p0      
     4,                                 // p+ p- p+ p-
     5,                                 // p0 p+ p- p+ p-
     6,                                 // p0 p0 p+ p- p+ p-
     7,                                 // p0 p0 p0 p+ p- p+ p-
     6,                                 // p+ p- p+ p- p+ p-
     7,                                 // p+ p- p+ p- p+ p- p0
     2,                                 // p+ p-
     3                                  // p0 p0 p0      
};                              


// LGCP : Below are the masses of the particles involved when a certain branch/annihilation mode is taken
G4double ParMas[NFS][7] = 
{ 
     { MP0, MP0,   0,   0,   0,   0,   0},   // p0 p0
     { MP0, MP0, MP0, MP0,   0,   0,   0},   // p0 p0 p0 p0
     { MP0, MPC, MPC,   0,   0,   0,   0},   // p0 p+ p-
     { MP0, MP0, MPC, MPC,   0,   0,   0},   // p0 p0 p+ p-
     { MP0, MP0, MPC, MPC, MP0,   0,   0},   // p0 p0 p0 p+ p-
     { MP0, MP0, MPC, MPC, MP0, MP0,   0},   // p0 p0 p0 p0  p+ p-
     { MPC, MPC, MPC, MPC,   0,   0,   0},   // p+ p- p+ p-
     { MP0, MPC, MPC, MPC, MPC,   0,   0},   // p0 p+ p- p+ p-
     { MP0, MP0, MPC, MPC, MPC, MPC,   0},   // p0 p0 p+ p- p+ p-
     { MP0, MP0, MPC, MPC, MPC, MPC, MP0},   // p0 p0 p0 p+ p- p+ p-
     { MPC, MPC, MPC, MPC, MPC, MPC,   0},   // p+ p- p+ p- p+ p-
     { MPC, MPC, MPC, MPC, MPC, MPC, MP0},   // p+ p- p+ p- p+ p- p0
     { MPC, MPC,   0,   0,   0,   0,   0},   // p+ p-
     { MP0, MP0, MP0,   0,   0,   0,   0}    // p0 p0 p0    
};


// LGCP : Below are the GEANT3 particle id codes for the particles involved when a certain branch/annihilation mode is taken

#define PI0 111     // PDG particle codes
#define PIP 211
#define PIM -211
#define MUP -13
#define MUM 13

G4int ParNum[NFS][7] = 
{    
     {   PI0,   PI0,   0,     0,     0,     0,     0},   // p0 p0        
     {   PI0,   PI0,   PI0,   PI0,   0,     0,     0},   // p0 p0 p0 p0                
     {   PI0,   PIP,   PIM,   0,     0,     0,     0},   // p0 p+ p-
     {   PI0,   PI0,   PIP,   PIM,   0,     0,     0},   // p0 p0 p+ p-
     {   PI0,   PI0,   PIP,   PIM,   PI0,   0,     0},   // p0 p0 p0 p+ p-   
     {   PI0,   PI0,   PIP,   PIM,   PI0,   PI0,   0},   // p0 p0 p0 p0 p+ p-            
     {   PIP,   PIM,   PIP,   PIM,   0,     0,     0},   // p+ p- p+ p-
     {   PI0,   PIP,   PIM,   PIP,   PIM,   0,     0},   // p0 p+ p- p+ p-
     {   PI0,   PI0,   PIP,   PIM,   PIP,   PIM,   0},   // p0 p0 p+ p- p+ p-
     {   PI0,   PI0,   PIP,   PIM,   PIP,   PIM,   PI0}, // p0 p0 p0 p+ p- p+ p-
     {   PIP,   PIM,   PIP,   PIM,   PIP,   PIM,   0},   // p+ p- p+ p- p+ p-
     {   PIP,   PIM,   PIP,   PIM,   PIP,   PIM,   PI0}, // p+ p- p+ p- p+ p- p0
     {   PIP,   PIM,   0,     0,     0,     0,     0},   // p+ p-
     {   PI0,   PI0,   PI0,   0,     0,     0,     0}    // p0 p0 p0 
};

// LGCP : This MaxWeight function still puzzles me.
// LGCP : This is supposed to be, according to Pablo Genova, a correction to the phase space...
G4double MaxWeigth[NFS] = 
{
     1.000000, // p0 p0  
     0.118145, // p0 p0 p0 p0  
     0.411809, // p0 p+ p-  
     0.118144, // p0 p0 p+ p-
     0.027187, // p0 p0 p0 p+ p-
     0.005407, // p0 p0 p0 p0 p+ p-
     0.118187, // p+ p- p+ p-  
     0.027182, // p0 p+ p- p+ p-  
     0.005405, // p0 p0 p+ p- p+ p-
     0.000963, // p0 p0 p0 p+ p- p+ p- 
     0.005405, // p+ p- p+ p- p+ p-  
     0.000967, // p+ p- p+ p- p+ p- p0  
     1.000000, // p+ p-  
     0.411814  // p0 p0 p0 
};

// LGCP : These are the branching ratios for the different p-pbar annihilation modes
G4double BraRat[NFS] = 
{  
     .00028,   // p0 p0  
     .03000,   // p0 p0 p0 p0               
     .06900,   // p0 p+ p-  
     .09300,   // p0 p0 p+ p-
     .23300,   // p0 p0 p0 p+ p-
     .02800,   // p0 p0 p0 p0 p+ p- 
     .06900,   // p+ p- p+ p-  
     .19600,   // p0 p+ p- p+ p-  
     .16600,   // p0 p0 p+ p- p+ p-  
     .04200,   // p0 p0 p0 p+ p- p+ p-  
     .02100,   // p+ p- p+ p- p+ p-  
     .01900,   // p+ p- p+ p- p+ p- p0  
     .00320,   // p+ p-
     .00760    // p0 p0 p0   
}; 

G4double BraRatCum[NFS];


//ClassImp(TAlphaPrimaryGenerator)
//_____________________________________________________________________________
TAlphaPrimaryGenerator::TAlphaPrimaryGenerator()
{ 
 	rad = 2.5*cm;
 	zed = 10.*cm;
	vtOff = 0.;
}

//_____________________________________________________________________________
TAlphaPrimaryGenerator::TAlphaPrimaryGenerator(DetectorConstruction* det)
{
	rad = det->GetTrapRadius();
        zed = det->GetDegPosition();
	vtOff = det->GetTrapVtOffset();
}

//_____________________________________________________________________________
TAlphaPrimaryGenerator::~TAlphaPrimaryGenerator() 
{ }

//____________________________________________________
void TAlphaPrimaryGenerator::GeneratePrimaryVertex(G4Event *evt)
{    

  // Position
      G4double vx  = 0.; 
      G4double vy  = 0.; 
      G4double vz  = 0.;
      
//--------------------------------------------------------------
//     Degrader generation (uniform on a disc)
//--------------------------------------------------------------  
      G4double csi = G4UniformRand();
      G4double phi = 2.0*M_PI*G4UniformRand();
      G4double r   = rad;
      vx  = r*sqrt(csi)*cos(phi);
      vy  = r*sqrt(csi)*sin(phi)+vtOff;
      vz  = zed;
//--------------------------------------------------------------
  
//--------------------------------------------------------------
//    Electrode generation
//--------------------------------------------------------------      
//       G4double phi = G4UniformRand() * 2*3.14159265;
//       G4double Cph = TMath::Cos(phi);
//       G4double Sph = TMath::Sin(phi);
//       
//       G4double radii = 2.2275;
//       vx= radii*Cph;
//       vy= radii*Sph;
//       vz= gRandom->Gaus(0,2.5);
//--------------------------------------------------------------
      
      G4double nor=0;
      for (G4int k=0;k<NFS;k++) nor+=BraRat[k];
      for (G4int k=0;k<NFS;k++) BraRat[k] /= nor;
      
      BraRatCum[0] = BraRat[0];
      for (G4int k=1;k<NFS;k++) BraRatCum[k] = BraRat[k] + BraRatCum[k-1];
      
      G4double fs = G4UniformRand();
      G4int fFs = 0;
      while (fs>BraRatCum[fFs]) fFs++;
      
      TLorentzVector P(0.,0.,0., 2.*938.279E-3);
      TGenPhaseSpace ps;     
      ps.SetDecay(P,NumPar[fFs],ParMas[fFs]);
      
      G4double wt=0;
      while (1) // make unweighted events
	{
	  wt = ps.Generate(); // generate a phasespace configuration
	  G4double wt_r = MaxWeigth[fFs]*G4UniformRand(); // random number between
	                                                  // [0,MaxWeight]
	  //printf("wt: %lf wt_r: %lf\n",wt,wt_r);
	  if(wt > wt_r) break;
	}
	  
      for (G4int n=0; n<NumPar[fFs]; ++n) 
      {
            // Lorentz Vector corresponding to the Nth decay
            TVector3 *p = new TVector3(ps.GetDecay(n)->Vect()); // Momentum in GeV/c
            G4double E = ps.GetDecay(n)->E(); // Energy in GeV
          
            // Particle type
            G4int pdg  = ParNum[fFs][n];
	  
	    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
            G4ParticleDefinition* particle = particleTable->FindParticle(pdg);
	    
	    G4PrimaryVertex *vt   = new G4PrimaryVertex(vx, vy, vz, 0.);
	    // Geant4 uses MeV/c and MeV
	    G4PrimaryParticle *pp = new G4PrimaryParticle(particle, p->X()*1000., p->Y()*1000., p->Z()*1000.,E*1000.);
	    
	    //vt->SetWeight(wt);
	    vt->SetPrimary(pp);
	    evt->AddPrimaryVertex(vt);
	    
//  	    G4double pMod=TMath::Sqrt(p->X()*p->X()+p->Y()*p->Y()+p->Z()*p->Z());
// 	    G4cout<<"Particle: "<<pdg<<"\t Energy = "<<E<<" GeV"<<G4endl;
// 	    G4cout<<"	      \t 3-Momentum = "<<pMod<<" GeV/c\t Mass = "<< TMath::Sqrt(E*E-pMod*pMod)<<" GeV/c^2"<<G4endl;
        }

}
