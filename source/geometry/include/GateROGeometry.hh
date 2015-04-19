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

#include "GateDetectorConstruction.hh"

class GateROGeometry : public G4VUserParallelWorld
{
public:
  GateROGeometry(G4String& parallelWorldName);
  virtual ~GateROGeometry();

public:
  virtual void Construct();

private:
  //GateDetectorConstruction * pdet;

};

#endif
