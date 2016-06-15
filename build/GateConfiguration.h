/* GATE : configuration file */

#ifndef GATE_CONFIGURATION_H
#define GATE_CONFIGURATION_H
//This file is interpreted by cmake, to define macros based on the cmake configuration options
// Check : GATE_ANALYSIS_USE_FILE        = ON

#define GATE_USE_ROOT                 ON
/* #undef GATE_USE_OPTICAL */
#define GATE_ANALYSIS_USE_GENERAL     ON
#define GATE_ANALYSIS_USE_FILE        ON
/* #undef GATE_USE_LMF */
/* #undef GATE_USE_ECAT7 */
#define GATE_USE_GEANT4_UIVIS         ON

#ifdef GATE_USE_ROOT
 #define G4ANALYSIS_USE_ROOT 1
#endif

#ifdef GATE_ANALYSIS_USE_GENERAL
 #define G4ANALYSIS_USE_GENERAL 1
#endif

#ifdef GATE_ANALYSIS_USE_FILE
 #define  G4ANALYSIS_USE_FILE 1
#endif

//#define G4VERSION                  10.1.2
#define G4VERSION_MAJOR              10
#define G4VERSION_MINOR              1
#define G4VERSION_PATCH              2
/* #undef GATE_USE_GPU */
/* #undef CUDA_FOUND */

#ifndef G4VERSION_MINOR
   #define G4VERSION_MINOR 0
#endif

#ifndef G4VERSION_PATCH
   #define G4VERSION_PATCH 0
#endif

// WARNING : Replace all G4VERSION_3 and other with a correct test
#if (G4VERSION_MAJOR > 9) || ((G4VERSION_MAJOR==9) && (G4VERSION_MINOR >=3))
   #define G4VERSION9_3 1
#endif

// WARNING : Replace all G4VERSION_3 and other with a correct test
#if (G4VERSION_MAJOR > 9) || ((G4VERSION_MAJOR==9) && (G4VERSION_MINOR >=6))
   #define Geant496_COMPATIBILITY 1
#endif

#define GATE_USE_OPENGL               TRUE

#endif // GATE_CONFIGURATION_H
