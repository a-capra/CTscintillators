#include "SwanseaMagField.hh"
#include "G4RunManager.hh"

#include "DetectorConstruction.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

SwanseaMagField::SwanseaMagField():G4MagneticField()
{
  fDetector = (DetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();
}

SwanseaMagField::SwanseaMagField(DetectorConstruction* det):G4MagneticField()
{
  fDetector = det;
}


void SwanseaMagField::GetFieldValue(const G4double* point, G4double* field) const
{
  field[0] = field[1] = field[2] = field[3] = field[4] = field[5] = 0.0;

  // protect against Geant4 bug that calls us with point[] NaN.
  if(point[0] != point[0]) return;

  //point[0,1,2] = (x,y,z)
  //field[0,1,2] = (Bx,By,Bz)

  if( sqrt(point[0]*point[0]+point[1]*point[1]) < fDetector->GetSwanseaOD() 
      && abs(point[2]) < fDetector->GetSwanseaL() )
    {
      field[2] = 3.*tesla;
    }
}
