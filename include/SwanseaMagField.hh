#ifndef __SWANSEAMAGFIELD__
#define __SWANSEAMAGFIELD__

#include "G4MagneticField.hh"
#include "G4TransportationManager.hh"

class DetectorConstruction;
class SwanseaMagField : public G4MagneticField
{
public:
  SwanseaMagField();
  SwanseaMagField(DetectorConstruction*);
  virtual ~SwanseaMagField() {};

  virtual void  GetFieldValue(const G4double Point[4],
			      G4double *Bfield ) const;
  
  virtual G4bool DoesFieldChangeEnergy() const { return false; }

private:
  DetectorConstruction* fDetector;
};
#endif 
