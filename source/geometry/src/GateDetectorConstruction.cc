/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See GATE/LICENSE.txt for further details
  ----------------------*/


#include "GateConfiguration.h"
#include "GateDetectorConstruction.hh"
#include "GateDetectorMessenger.hh"
#include "GateRunManager.hh"
#include "GateVVolume.hh"
#include "GateBox.hh"
#include "GateObjectStore.hh"
#include "GateSystemListManager.hh"
#include "GateMaterialDatabase.hh"
#include "GateCrystalSD.hh"
#include "GatePhantomSD.hh"
#include "GateMessageManager.hh"
#include "GateObjectMoveListMessenger.hh"
#include "GateARFSD.hh"

#include "globals.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Navigator.hh"
#include "G4SDManager.hh"
#include "G4Material.hh"

#ifdef GATE_USE_OPTICAL
#include "GateSurfaceList.hh"
#endif

GateDetectorConstruction* GateDetectorConstruction::pTheGateDetectorConstruction=0;

//---------------------------------------------------------------------------------
GateDetectorConstruction::GateDetectorConstruction()
  :  pworld(0),
     nGeometryStatus(geometry_needs_rebuild),
     flagAutoUpdate(false),
     pdetectorMessenger(0),
     moveFlag(0)
{

  GateMessage("Geometry", 1, "GateDetectorConstruction instantiating...\n");
  GateMessage("Geometry", 5, " GateDetectorConstruction constructor -- begin ");
  GateMessage("Geometry", 5, " nGeometryStatus = " << nGeometryStatus << Gateendl;);

  pTheGateDetectorConstruction = this;

  psystemStore=GateSystemListManager::GetInstance();

  pdetectorMessenger = new GateDetectorMessenger(this);

  G4ThreeVector magFieldValue = G4ThreeVector(0.,0.,0. * tesla);

  G4double pworld_x = 50.*cm;
  G4double pworld_y = 50.*cm;
  G4double pworld_z = 50.*cm;
  
  pworld = new GateROGeometry("world");
  pworld->Initialize(pworld_x, pworld_y, pworld_z, magFieldValue);

  GateMessage("Geometry", 5, "  GateDetectorConstruction constructor -- end ");


  /* instantiate the singleton RTPhantom Manager  - PY Descourt 08/09/2008 */

  m_RTPhantomMgr = GateRTPhantomMgr::GetInstance();
  m_ARFSD = 0;
}
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
GateDetectorConstruction::~GateDetectorConstruction()
{
  delete pdetectorMessenger;
}
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
G4VPhysicalVolume* GateDetectorConstruction::Construct()
{
  GateMessage("Geometry", 3, "Geometry construction starts. " << Gateendl);

  pworld->Construct();
  pworld->ConstructSD();
  SetGeometryStatusFlag(geometry_is_uptodate);

  GateMessage("Geometry", 3, "Geometry has been constructed (status = " << nGeometryStatus << ")." << Gateendl);

  return pworld->GetWorldVolume();
}
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
void GateDetectorConstruction::UpdateGeometry()
{
  GateMessage("Geometry", 3,"UpdateGeometry starts (status = " << nGeometryStatus << "). " << Gateendl);

  if (nGeometryStatus == geometry_is_uptodate){
    GateMessage("Geometry", 3,"Geometry is uptodate." << Gateendl);
    return;
  }

  switch (nGeometryStatus){
  case geometry_needs_update:
    pworld->Construct();
    break;

  case geometry_needs_rebuild:
  default:
    DestroyGeometry();
    Construct();
    break;
  }
  this->RegisterParallelWorld(pworld);
  GateRunManager::GetRunManager()->DefineWorldVolume(pworld->GetWorldVolume());

  nGeometryStatus = geometry_is_uptodate;

  GateMessage("Geometry", 3, "nGeometryStatus = geometry_is_uptodate " << Gateendl);
  GateMessage("Geometry", 3, "UpdateGeometry finished. " << Gateendl);
}
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
void GateDetectorConstruction::DestroyGeometry()
{
  GateMessage("Geometry", 4,"Geometry is going to be destroyed. " << Gateendl);

  pworld->DestroyGeometry();
  nGeometryStatus = geometry_needs_rebuild;

  GateMessage("Geometry", 4,"nGeometryStatus = geometry_needs_rebuild     " << Gateendl);
  GateMessage("Geometry", 4,"Geometry has been destroyed." << Gateendl);
}
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
/*
  void GateDetectorConstruction::GeometryHasChanged(GeometryStatus changeLevel)
  {

  GateMessage("Geometry", 3, "   nGeometryStatus = " << nGeometryStatus << " changeLevel = " << changeLevel << Gateendl;);

  if (flagAutoUpdate == 0)
  GateMessage("Geometry", 3, "   flagAutoUpdate = " << flagAutoUpdate << Gateendl;);

  if ( changeLevel > nGeometryStatus )
  nGeometryStatus = changeLevel;

  if (nGeometryStatus == 0){
  GateMessage("Geometry", 3, "   The geometry is uptodate." << Gateendl;);
  }
  else if (nGeometryStatus == 1){
  GateMessage("Geometry", 3, "   The geometry needs to be uptodated." << Gateendl;);
  }
  else if (nGeometryStatus == 2){
  GateMessage("Geometry", 3, "   The geometry needs to be rebuilt." << Gateendl;);
  }

  if (flagAutoUpdate){
  GateMessage("Geometry", 0,"The geometry is going to be updated." << Gateendl);
  UpdateGeometry();}
  }
*/
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
void GateDetectorConstruction::ClockHasChanged()
{
  GateMessage("Move", 5, "ClockHasChanged = " << GetFlagMove() << Gateendl; );

  if ( GetFlagMove()) {
    GateMessage("Move", 6, "moveFlag = 1" << Gateendl);
    nGeometryStatus = geometry_needs_update;
  }
  else {
    GateMessage("Move", 6, "Geometry is uptodate." << Gateendl);
    nGeometryStatus = geometry_is_uptodate;
  }

  GateMessage("Move", 6, "  Geometry status = " << nGeometryStatus << Gateendl;);

  UpdateGeometry();
  GateMessage("Move", 6, "Clock has changed." << Gateendl);
}
//---------------------------------------------------------------------------------
/*PY Descourt 08/09/2008 */
void GateDetectorConstruction::insertARFSD( G4String aName , G4int stage )
{
  G4cout << " GateDetectorConstruction::insertARFSD  entered " << Gateendl;

  if ( m_ARFSD == 0 )
    {
      m_ARFSD = new GateARFSD("/gate/arf", aName );
      G4SDManager* SDMan = G4SDManager::GetSDMpointer();
      SDMan->AddNewDetector( m_ARFSD );
    }
  m_ARFSD->SetStage( stage );
}
/*PY Descourt 08/09/2008 */
