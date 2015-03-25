/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See GATE/LICENSE.txt for further details
  ----------------------*/

#include "GateActionInitialization.hh"
#include "GatePrimaryGeneratorAction.hh"
#include "GateActions.hh"
#include "GateUserActions.hh"
#include "GateRecorderBase.hh"
#include "G4RunManager.hh"
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#endif

GateActionInitialization::GateActionInitialization(GateUserActions * cbm, GateRecorderBase * r):
G4VUserActionInitialization(), pCallbackMan(cbm), recorder(r)
{}

GateActionInitialization::~GateActionInitialization()
{}

void GateActionInitialization::BuildForMaster() const
{
	// In MT mode, to be clearer, the RunAction class for the master thread might be
	// different than the one used for the workers.
	// This RunAction will be called before and after starting the
	// workers.

}

void GateActionInitialization::Build() const
{   

 // Initialize the primary particles
SetUserAction( new GatePrimaryGeneratorAction() ); 

SetUserAction( new GateEventAction(pCallbackMan, recorder) );

SetUserAction( new GateRunAction(pCallbackMan, recorder) ); 

SetUserAction( new GateSteppingAction(pCallbackMan, recorder) );

	
} 