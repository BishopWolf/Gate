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

GateROGeometry* GateROGeometry::pTheGateROGeometry=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GateROGeometry::GateROGeometry(G4String parallelWorldName)
  : G4VUserParallelWorld(parallelWorldName), 
    pworld(0), nGeometryStatus(geometry_needs_rebuild), 
    m_crystalSD(0), m_phantomSD(0),
    pcreatorStore(0), m_magField(0), m_magFieldValue(0),
    sensitiveLogicalVolume(0)
{ 
  pTheGateROGeometry = this;
  
  isBuilt = false;
  isInitialized = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GateROGeometry::~GateROGeometry()
{
  if (pworld) {
    DestroyGeometry();
    delete pworld;
    pworld = 0;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GateROGeometry::Initialize(G4double sizeX, G4double sizeY, G4double sizeZ, G4ThreeVector magFieldValue)
{
  pworld_x = sizeX;
  pworld_y = sizeY;
  pworld_z = sizeZ;
  m_magFieldValue = magFieldValue;
  isInitialized = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GateROGeometry::Construct()
{
  GateMessage("Geometry", 1, "GateROGeometry instantiating..." << Gateendl);
  GateMessage("Geometry", 5, " GateROGeometry constructor -- begin ");
  
  if (!isInitialized)
    {
      GateError("GateROGeometry::Construct() error" << Gateendl <<
		"Parameters of the RO geometry are not initialized");
      return;
    }
  
  pcreatorStore = GateObjectStore::GetInstance();
  //-------------------------------------------------------------------------
  // Create default material (air) for the world
  G4Element* N  = new G4Element("worldDefaultN","N" , 7., 14.01*g/mole );
  G4Element* O  = new G4Element("worldDefaultO"  ,"O" , 8., 16.00*g/mole);
  G4Material* Air = new G4Material("worldDefaultAir"  , 1.290*mg/cm3, 2);
  Air->AddElement(N, 0.7);
  Air->AddElement(O, 0.3);
  //-------------------------------------------------------------------------
  pworld = new GateBox(GetName(), "worldDefaultAir",  pworld_x, pworld_y, pworld_z, true);
  pworld->SetMaterialName("worldDefaultAir");
  
  sensitiveLogicalVolume = GetWorldVolume()->GetLogicalVolume();
  
  GateMessage("Physic", 1, " "<<Gateendl);
  GateMessage("Physic", 1, "----------------------------------------------------------"<<Gateendl);
  GateMessage("Physic", 1, "                    Ionization potential "<<Gateendl);

  const G4MaterialTable * theTable = G4Material::GetMaterialTable();
  for(unsigned int i =0;i<(*theTable).size();i++){
    if(theListOfIonisationPotential[(*theTable)[i]->GetName()]){
      (*theTable)[i]->GetIonisation()->SetMeanExcitationEnergy(theListOfIonisationPotential[(*theTable)[i]->GetName()]);
      GateMessage("Physic", 1, " - " << (*theTable)[i]->GetName() << "\t defaut value: I = " <<
                  G4BestUnit((*theTable)[i]->GetIonisation()->GetMeanExcitationEnergy(),"Energy") <<
                  "\t-->  new value: I = " <<
                  G4BestUnit((*theTable)[i]->GetIonisation()->GetMeanExcitationEnergy(),"Energy") << Gateendl);
    }
    else {
      GateMessage("Physic", 1, " - " << (*theTable)[i]->GetName() << "\t defaut value: I = " <<
                  G4BestUnit((*theTable)[i]->GetIonisation()->GetMeanExcitationEnergy(),"Energy") << Gateendl);
    }
  }
  GateMessage("Physic", 1, "----------------------------------------------------------"<<Gateendl);
  
  GateMessage("Geometry", 5, "  GateROGeometry constructor -- end ");
  isBuilt = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GateROGeometry::ConstructSD()
{
  //G4SDManager* SDman = G4SDManager::GetSDMpointer();

  if(!m_crystalSD) {
    G4String crystalSDname = "/gate/crystal";
    m_crystalSD = new GateCrystalSD(crystalSDname);
    //SDman->AddNewDetector(m_crystalSD);
    SetSensitiveDetector(sensitiveLogicalVolume, m_crystalSD);
  }

  if(!m_phantomSD) {
    G4String phantomSDname = "/gate/phantom";
    m_phantomSD = new GatePhantomSD(phantomSDname);
    //SDman->AddNewDetector(m_phantomSD);
    SetSensitiveDetector(sensitiveLogicalVolume, m_phantomSD);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GateROGeometry::DestroyGeometry()
{
  GateMessage("Geometry", 4,"Geometry is going to be destroyed. " << Gateendl);

  pworld->DestroyGeometry();
  nGeometryStatus = geometry_needs_rebuild;

  GateMessage("Geometry", 4,"nGeometryStatus = geometry_needs_rebuild     " << Gateendl);
  GateMessage("Geometry", 4,"Geometry has been destroyed." << Gateendl);
}

//---------------------------------------------------------------------------------
void GateROGeometry::BuildMagField()
{
  //apply a global uniform magnetic field along Z axis
  G4FieldManager* fieldMgr
    = G4TransportationManager::GetTransportationManager()->GetFieldManager();

  if(m_magField) delete m_magField;             //delete the existing magn field

  if(m_magFieldValue.mag()!=0.)                 // create a new one if non nul
    { m_magField = new G4UniformMagField(m_magFieldValue);
      fieldMgr->SetDetectorField(m_magField);
      fieldMgr->CreateChordFinder(m_magField);
    } else {
    m_magField = NULL;
    fieldMgr->SetDetectorField(m_magField);
  }
}
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
// Adds a Material Database
void GateROGeometry::AddFileToMaterialDatabase(const G4String& f)
{
  mMaterialDatabase.AddMDBFile(f);
}
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void GateROGeometry::SetMagField(G4ThreeVector fieldValue)
{
  m_magFieldValue = fieldValue;
}
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
#ifdef GATE_USE_OPTICAL
void GateROGeometry::BuildSurfaces()
{
  GateObjectStore* store = GateObjectStore::GetInstance();
  for (GateObjectStore::iterator p = store->begin(); p != store->end(); p++)
    {
      p->second->GetSurfaceList()->BuildSurfaces();
    }

}
#endif
//---------------------------------------------------------------------------------
  