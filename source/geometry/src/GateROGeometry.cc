/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See GATE/LICENSE.txt for further details
  ----------------------*/
//
// $Id: $
//
/// \file geometry/src/GateROGeometry.cc
/// \brief Implementation of the GateROGeometry class
//
#include "GateConfiguration.h"
#include "GateROGeometry.hh"
#include "GateMessageManager.hh"
#include "GateException.hh"
#include "GateBox.hh"
#include "GateObjectStore.hh"
#include "GateSystemListManager.hh"
#include "GateMaterialDatabase.hh"
#include "GateCrystalSD.hh"
#include "GatePhantomSD.hh"
#include "GateDetectorMessenger.hh"
#include "GateRunManager.hh"
#include "GateVVolume.hh"
#include "GateMessageManager.hh"
#include "GateObjectMoveListMessenger.hh"
#include "GateARFSD.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4SDManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Navigator.hh"
#include "G4UnitsTable.hh"

#ifdef GATE_USE_OPTICAL
#include "GateSurfaceList.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GateROGeometry::GateROGeometry(G4String parallelWorldName)
  : G4VUserParallelWorld(parallelWorldName), 
    pworld(0) 
    //pworldPhysicalVolume(0),
    //sensitiveLogicalVolume(0)
{ 
  isBuilt = false;
  isInitialized = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GateROGeometry::~GateROGeometry()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GateROGeometry::Initialize(GateBox* mBox, G4VPhysicalVolume* mPhysicalVolume)
{
      pworld_x = mBox->GetBoxXLength();
      pworld_y = mBox->GetBoxYLength();
      pworld_z = mBox->GetBoxZLength();
      pworld = mBox;
      pworldPhysicalVolume = mPhysicalVolume;
      isInitialized = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GateROGeometry::Construct()
{
  GateMessage("Geometry", 1, "GateROGeometry instantiating...\n");
  GateMessage("Geometry", 5, " GateROGeometry constructor -- begin ");
  
  if (!isInitialized)
    {
      GateError("GateROGeometry::Construct() error\n" <<
		"Parameters of the RO geometry are not initialized");
      return;
    }
  
  G4TransportationManager::GetTransportationManager()->RegisterWorld(pworldPhysicalVolume);
  sensitiveLogicalVolume = pworldPhysicalVolume->GetLogicalVolume();
  
  isBuilt = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GateROGeometry::ConstructSD()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GateROGeometry::UpdateROGeometry()
{
  Construct();
  ConstructSD();
}
