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
    pworld(0),
    m_crystalSD(0),
    m_phantomSD(0),
    m_ARFSD(0),
    RODetector(0),
    worldLogical(0),
    RODetectorLog(0),
    pworldPhysicalVolume(0),
    sensitiveLogicalVolume(0)
{ 
  isBuilt = false;
  isInitialized = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GateROGeometry::~GateROGeometry()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GateROGeometry::Initialize(GateBox* mBox)
{
      pworld_x = mBox->GetBoxXLength();
      pworld_y = mBox->GetBoxYLength();
      pworld_z = mBox->GetBoxZLength();
      pworld = mBox;
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
  
  pworldPhysicalVolume = GetWorld();
  worldLogical = pworldPhysicalVolume->GetLogicalVolume();
  
  // World volume of ROGeometry ... SERVE SOLO PER LA ROG

  // Detector ROGeometry 
  G4double halfDetectorSizeX = pworld_x/2;
  G4double halfDetectorSizeY = pworld_y/2;
  G4double halfDetectorSizeZ = pworld_z/2;
  
  G4ThreeVector position = G4ThreeVector(0,0,0);

  RODetector = new G4Box("ParallelWorld", 
			 halfDetectorSizeX, 
			 halfDetectorSizeY, 
			 halfDetectorSizeZ);

  RODetectorLog = new G4LogicalVolume(RODetector,
				      0,
				      "RODetectorLog",
				      0,0,0);
  
  new G4PVPlacement(0,		// rotation with respect to its mother volume
		    position,	// traslation with respect to its mother volume
		    RODetectorLog,	// the assiated logical volume
		    "RODetectorPhys",// physical volume name
		    worldLogical,	// the mother logical volume
		    false,		// for future use,, can be set to false
		    0,		// copy number
		    false);		// false/true = no/yes overlap check triggered
  
  sensitiveLogicalVolume = RODetectorLog;
  
  isBuilt = true;
  GateMessage("Geometry", 5, " GateROGeometry constructor -- end ");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GateROGeometry::ConstructSD()
{
  if(!m_crystalSD) {
    G4String crystalSDname = "/gate/crystal";
    m_crystalSD = new GateCrystalSD(crystalSDname);
    SetSensitiveDetector(sensitiveLogicalVolume,m_crystalSD);
  }

  if(!m_phantomSD) {
    G4String phantomSDname = "/gate/phantom";
    m_phantomSD = new GatePhantomSD(phantomSDname);
    SetSensitiveDetector(sensitiveLogicalVolume,m_phantomSD);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GateROGeometry::UpdateROGeometry()
{
  Construct();
  ConstructSD();
}

//---------------------------------------------------------------------------------
/*PY Descourt 08/09/2008 */
void GateROGeometry::insertARFSD( G4String aName , G4int stage )
{
  GateMessage("Geometry", 5, "GateROGeometry::insertARFSD  entered \n");

  if ( m_ARFSD == 0 )
    {
      m_ARFSD = new GateARFSD("/gate/arf", aName );
      SetSensitiveDetector(sensitiveLogicalVolume,m_ARFSD);
    }
  m_ARFSD->SetStage( stage );
}
/*PY Descourt 08/09/2008 */
