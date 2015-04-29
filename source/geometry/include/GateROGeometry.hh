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
#include "GateRTPhantomMgr.hh"

#include "globals.hh"

class G4UniformMagField;
class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class GateObjectStore;
class GateVVolume;
class GateBox;
class GateARFSD;

class GateROGeometry : public G4VUserParallelWorld
{
public:
  GateROGeometry(G4String);
  virtual ~GateROGeometry();
  
  void Initialize(GateBox*, G4VPhysicalVolume*);
  void UpdateROGeometry();
  
private:
  GateBox* pworld;

  G4double pworld_x;
  G4double pworld_y;
  G4double pworld_z;
  G4bool isBuilt;
  G4bool isInitialized;
  
  G4VPhysicalVolume*  pworldPhysicalVolume;
  G4LogicalVolume* sensitiveLogicalVolume;
  
  virtual void Construct();
  virtual void ConstructSD();
};

#endif
