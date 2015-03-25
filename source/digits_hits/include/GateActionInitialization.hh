/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See GATE/LICENSE.txt for further details
  ----------------------*/ 

#ifndef GateActionInitialization_H
#define GateActionInitialization_H

#include "G4VUserActionInitialization.hh"
#include "GateUserActions.hh"
#include "GateRecorderBase.hh"

class GateUserActions;
class GateRecorderBase;

class GateActionInitialization: public G4VUserActionInitialization
{
  public:
    GateActionInitialization(GateUserActions * cbm, GateRecorderBase * r);
    virtual ~GateActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

private:
    GateUserActions* pCallbackMan;
    GateRecorderBase* recorder;
};

#endif