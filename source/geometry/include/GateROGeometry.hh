/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See GATE/LICENSE.txt for further details
  ----------------------*/
//
// $Id: GateROGeometry.hh 68698 2013-04-05 08:41:22Z gcosmo $
//
/// \file geometry/include/GateROGeometry.hh
/// \brief Definition of the GateROGeometry class
//

#ifndef GateROGeometry_h
#define GateROGeometry_h 1

#include "G4VUserParallelWorld.hh"

#include "GateConfiguration.h"
#include "GateMaterialDatabase.hh"
#include "GateCrystalSD.hh"
#include "GatePhantomSD.hh"

#include "globals.hh"

class G4UniformMagField;
class GateObjectStore;
class GateVVolume;
class GateBox;

#define theMaterialDatabase GateROGeometry::GetGateROGeometry()->mMaterialDatabase

class GateROGeometry : public G4VUserParallelWorld
{
public:
  GateROGeometry(G4String);
  virtual ~GateROGeometry();
  
  enum GeometryStatus {
    geometry_is_uptodate = 0,
    geometry_needs_update = 1,
    geometry_needs_rebuild = 2
  };

  virtual void Construct();
  virtual void ConstructSD();
  void Initialize(G4double, G4double, G4double, G4ThreeVector);
  inline G4VPhysicalVolume* GetWorldVolume() {return pworldPhysicalVolume;}
  //inline G4VPhysicalVolume* GetWorldVolume() {return this->GetWorld();}
  inline GateObjectStore* GetObjectStore()  { return pcreatorStore; }
  inline virtual void SetGeometryStatusFlag(GeometryStatus val)  { nGeometryStatus = val; }
  inline virtual G4bool GetGeometryStatusFlag()  { return nGeometryStatus; }
  static GateROGeometry* GetGateROGeometry()
  {
    return pTheGateROGeometry;
  };
  virtual void SetMagField (G4ThreeVector);
  virtual void BuildMagField ();
    /// The Material database
  GateMaterialDatabase mMaterialDatabase;
  // Material DB
  /// Mandatory : Adds a Material Database to use (filename, callback for Messenger)
  void AddFileToMaterialDatabase(const G4String& f);

  inline GateCrystalSD* GetCrystalSD()
  { return m_crystalSD; }

  inline GatePhantomSD*   GetPhantomSD()
  { return m_phantomSD; }
  
#ifdef GATE_USE_OPTICAL
  virtual void BuildSurfaces();
#endif
  
  void SetMaterialIoniPotential(G4String n,G4double v){theListOfIonisationPotential[n]=v;}
  G4double GetMaterialIoniPotential(G4String n){ return theListOfIonisationPotential[n];}
  
  virtual void DestroyGeometry();
  
private:
  GateBox* pworld;
  GeometryStatus nGeometryStatus;
  GateCrystalSD*   m_crystalSD;
  GatePhantomSD*   m_phantomSD;
  GateObjectStore* pcreatorStore;
  //GateDetectorConstruction * pdet;
  G4double pworld_x;
  G4double pworld_y;
  G4double pworld_z;
  G4bool isBuilt;
  G4bool isInitialized;
  
    //! Magnetic field
  G4UniformMagField* m_magField;
  G4ThreeVector      m_magFieldValue;
  
  static GateROGeometry* pTheGateROGeometry;
  G4VPhysicalVolume*  pworldPhysicalVolume;
  G4LogicalVolume* sensitiveLogicalVolume;
  
protected:
  std::map<G4String,G4double> theListOfIonisationPotential;
};

#endif
