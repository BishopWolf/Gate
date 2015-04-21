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
#include "GateRTPhantomMgr.hh"
#include "GateROGeometry.hh"

class G4UniformMagField;
class GateObjectStore;
class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class GateDetectorMessenger;
class GateVVolume;
class GateBox;
class GateSystemListManager;
class GateARFSD;

class GateDetectorConstruction : public G4VUserDetectorConstruction
{

public:

  GateDetectorConstruction();
  virtual ~GateDetectorConstruction();

  virtual G4VPhysicalVolume* Construct();
  virtual void UpdateGeometry();

  /* PY Descourt 08/09/2009 */
  GateARFSD* GetARFSD(){ return m_ARFSD;};
  void insertARFSD( G4String , G4int );
  /* PY Descourt 08/09/2009 */

  // Material DB
  /// Mandatory : Adds a Material Database to use (filename, callback for Messenger)
  inline void AddFileToMaterialDatabase(const G4String& f) 
  { pworld->AddFileToMaterialDatabase(f); }

  static GateDetectorConstruction* GetGateDetectorConstruction()
  {
    return pTheGateDetectorConstruction;
  };

  inline G4VPhysicalVolume*   GetWorldVolume()
  { return pworld->GetWorldVolume(); }

  inline GateObjectStore* GetObjectStore()
  { return pworld->GetObjectStore(); }
  
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

  /// The Material database
  GateMaterialDatabase mMaterialDatabase;

  inline GateCrystalSD* GetCrystalSD()
  { return m_crystalSD; }


  inline GatePhantomSD*   GetPhantomSD()
  { return m_phantomSD; }

  //private:

  virtual void DestroyGeometry();

  //void SetIonisationPotential(G4String n, G4double v){mMaterialDatabase.SetMaterialIoniPotential(n,v);}
  void SetMaterialIoniPotential(G4String n,G4double v){pworld->SetMaterialIoniPotential(n,v);}
  G4double GetMaterialIoniPotential(G4String n){ return pworld->GetMaterialIoniPotential(n);}


private :

  GateROGeometry* pworld;

  GeometryStatus nGeometryStatus;
  G4bool flagAutoUpdate;

  GateCrystalSD*   m_crystalSD;
  GatePhantomSD*   m_phantomSD;

  GateSystemListManager*  psystemStore;

  // Pour utiliser le DetectorMessenger
  GateDetectorMessenger* pdetectorMessenger;  //pointer to the Messenger

  static GateDetectorConstruction* pTheGateDetectorConstruction;
  
protected :
  //!< List of movements
  G4bool moveFlag;

private:

  GateARFSD* m_ARFSD; // PY Descourt 8/09/2009
  GateRTPhantomMgr* m_RTPhantomMgr; // PY Descourt 08/09/2009
};

#endif
