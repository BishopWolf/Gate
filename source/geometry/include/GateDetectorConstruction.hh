/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See GATE/LICENSE.txt for further details
  ----------------------*/


#ifndef GateDetectorConstruction_H
#define GateDetectorConstruction_H 1

#include "GateConfiguration.h"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "GateMaterialDatabase.hh"
#include "GateCrystalSD.hh"
#include "GatePhantomSD.hh"
#include "GateObjectMoveListMessenger.hh"
#include "GatePhysicsList.hh"
#include "GateROGeometry.hh"

class GateObjectStore;
class GateDetectorMessenger;
class GateSystemListManager;
class G4VPhysicalVolume;

#define theROGeometry GateDetectorConstruction::GetGateDetectorConstruction()->GetGateROGeometry()
#define theMaterialDatabase theROGeometry->mMaterialDatabase

class GateDetectorConstruction : public G4VUserDetectorConstruction
{

public:

  GateDetectorConstruction();
  virtual ~GateDetectorConstruction();

  virtual G4VPhysicalVolume* Construct();
  virtual void UpdateGeometry();

  static GateDetectorConstruction* GetGateDetectorConstruction()
  {
    return pTheGateDetectorConstruction;
  };

  inline G4VPhysicalVolume*   GetWorldVolume()
  { return pworld->GetWorldVolume(); }

  inline GateObjectStore* GetObjectStore()
  { return pworld->GetObjectStore(); }
  
  inline GateROGeometry* GetGateROGeometry()
  { return pworld; }
  
  inline void SetMagField (G4ThreeVector theVector){pworld->SetMagField(theVector);}

  enum GeometryStatus {
    geometry_is_uptodate = 0,
    geometry_needs_update = 1,
    geometry_needs_rebuild = 2
  };

  //  virtual void GeometryHasChanged(GeometryStatus changeLevel);
  virtual void ClockHasChanged();

  inline virtual void SetAutoUpdateFlag(G4bool val)
  { flagAutoUpdate = val; }

  inline virtual G4bool GetAutoUpdateFlag()
  { return flagAutoUpdate; }

  inline virtual void SetGeometryStatusFlag(GeometryStatus val)
  { nGeometryStatus = val; }

  inline virtual G4bool GetGeometryStatusFlag()
  { return nGeometryStatus; }

  virtual inline void SetFlagMove(G4bool val)  { moveFlag = val; };

  virtual inline G4bool GetFlagMove() const { return moveFlag; };
  
  //private:

  virtual void DestroyGeometry();

private :

  GateROGeometry* pworld;

  GeometryStatus nGeometryStatus;
  G4bool flagAutoUpdate;

  GateSystemListManager*  psystemStore;

  // Pour utiliser le DetectorMessenger
  GateDetectorMessenger* pdetectorMessenger;  //pointer to the Messenger

  static GateDetectorConstruction* pTheGateDetectorConstruction;
  
protected :
  //!< List of movements
  G4bool moveFlag;

};

#endif
