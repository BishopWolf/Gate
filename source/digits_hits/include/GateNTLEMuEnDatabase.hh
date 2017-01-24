/*----------------------
   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See GATE/LICENSE.txt for further details
----------------------*/

/*!
  \file   GateNTLEMuEnDatabase
  \brief  Database of MuEn
  \authors: Halima Elazhar (halima.elazhar@ihpc.cnrs.fr)
            Thomas Deschler (thomas.deschler@iphc.cnrs.fr)
*/

#ifndef GATENTLEMUENDATABASE_HH
#define GATENTLEMUENDATABASE_HH

#include <vector>

//-----------------------------------------------------------------------------
static const std::vector<double> energyTableTLE = { // MeV
1.00000E-03,
1.03542E-03,
1.07210E-03,
1.07210E-03,
1.50000E-03,
2.00000E-03,
2.14550E-03,
2.14550E-03,
2.30297E-03,
2.47200E-03,
2.47200E-03,
2.64140E-03,
2.82240E-03,
2.82240E-03,
3.00000E-03,
3.60740E-03,
3.60740E-03,
4.00000E-03,
5.00000E-03,
6.00000E-03,
8.00000E-03,
1.00000E-02,
1.50000E-02,
2.00000E-02,
3.00000E-02,
4.00000E-02,
5.00000E-02,
6.00000E-02,
8.00000E-02,
1.00000E-01,
1.50000E-01,
2.00000E-01,
3.00000E-01,
4.00000E-01,
5.00000E-01,
6.00000E-01,
8.00000E-01,
1.00000E+00,
1.25000E+00,
1.50000E+00,
2.00000E+00,
3.00000E+00,
4.00000E+00,
5.00000E+00,
6.00000E+00,
8.00000E+00,
1.00000E+01,
1.50000E+01,
2.00000E+01
};
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
static const std::vector<double> energyTableTLE_ICRU44 = { // MeV
0.01,
0.015,
0.02,
0.03,
0.04,
0.05,
0.06,
0.08,
0.1,
0.15,
0.2,
0.3,
0.4,
0.5,
0.6,
0.8,
1,
1.5,
2,
3,
4,
5,
6,
8,
10,
15,
20,
30,
40,
50,
60,
80,
100
};
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
static const std::vector<double> MuEnMuscleTable =  { // cm²/g
3.709E+03,
3.383E+03,
3.085E+03,
3.091E+03,
1.247E+03,
5.574E+02,
4.564E+02,
4.606E+02,
3.762E+02,
3.069E+02,
3.121E+02,
2.579E+02,
2.130E+02,
2.143E+02,
1.796E+02,
1.046E+02,
1.083E+02,
7.992E+01,
4.116E+01,
2.377E+01,
9.888E+00,
4.964E+00,
1.396E+00,
5.638E-01,
1.610E-01,
7.192E-02,
4.349E-02,
3.258E-02,
2.615E-02,
2.544E-02,
2.745E-02,
2.942E-02,
3.164E-02,
3.249E-02,
3.269E-02,
3.254E-02,
3.177E-02,
3.074E-02,
2.938E-02,
2.808E-02,
2.584E-02,
2.259E-02,
2.045E-02,
1.895E-02,
1.786E-02,
1.639E-02,
1.547E-02,
1.421E-02,
1.361E-02
};
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
static const std::vector<double> MuEnLungTable =  {
3.791E+03,
3.459E+03,
3.155E+03,
3.167E+03,
1.280E+03,
5.727E+02,
4.690E+02,
4.732E+02,
3.865E+02,
3.154E+02,
3.206E+02,
2.650E+02,
2.189E+02,
2.229E+02,
1.870E+02,
1.091E+02,
1.110E+02,
8.181E+01,
4.210E+01,
2.431E+01,
1.010E+01,
5.067E+00,
1.423E+00,
5.740E-01,
1.635E-01,
7.286E-02,
4.393E-02,
3.282E-02,
2.625E-02,
2.550E-02,
2.748E-02,
2.945E-02,
3.167E-02,
3.252E-02,
3.272E-02,
3.257E-02,
3.179E-02,
3.077E-02,
2.940E-02,
2.810E-02,
2.586E-02,
2.262E-02,
2.048E-02,
1.898E-02,
1.789E-02,
1.643E-02,
1.551E-02,
1.427E-02,
1.367E-02
};
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
static const std::vector<double> MuEnCorticalBoneTable =  {
3.772E+03,
3.444E+03,
3.143E+03,
3.149E+03,
2.429E+03,
1.869E+03,
1.878E+03,
1.291E+03,
5.846E+02,
4.803E+02,
6.961E+02,
5.789E+02,
4.805E+02,
4.857E+02,
2.897E+02,
1.303E+02,
1.269E+02,
3.006E+02,
1.757E+02,
1.085E+02,
4.987E+01,
2.680E+01,
8.388E+00,
3.601E+00,
1.070E+00,
4.507E-01,
2.336E-01,
1.400E-01,
6.896E-02,
4.585E-02,
3.183E-02,
3.003E-02,
3.032E-02,
3.069E-02,
3.073E-02,
3.052E-02,
2.973E-02,
2.875E-02,
2.745E-02,
2.623E-02,
2.421E-02,
2.145E-02,
1.975E-02,
1.864E-02,
1.788E-02,
1.695E-02,
1.644E-02,
1.587E-02,
1.568E-02
};
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
static const std::vector<double> MuEnVacuumTable =  {
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.,
0.
};
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
static const std::vector<double> MuEn_ICRU44_Lung_Griffith_Table =  {
4.57E-01,
1.34E-01,
5.57E-02,
1.67E-02,
7.64E-03,
4.63E-03,
3.43E-03,
2.68E-03,
2.56E-03,
2.71E-03,
2.89E-03,
3.10E-03,
3.19E-03,
3.20E-03,
3.19E-03,
3.11E-03,
3.01E-03,
2.75E-03,
2.53E-03,
2.21E-03,
1.99E-03,
1.84E-03,
1.73E-03,
1.58E-03,
1.49E-03,
1.36E-03,
1.30E-03,
1.24E-03,
1.21E-03,
1.19E-03,
1.17E-03,
1.15E-03,
1.13E-03
};
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
static const std::vector<double> MuEn_ICRU44_Air_Table = {
4.65E-01,
1.30E-01,
5.27E-02,
1.50E-02,
6.71E-03,
4.04E-03,
3.01E-03,
2.40E-03,
2.32E-03,
2.49E-03,
2.67E-03,
2.87E-03,
2.95E-03,
2.97E-03,
2.95E-03,
2.88E-03,
2.79E-03,
2.54E-03,
2.34E-03,
2.05E-03,
1.87E-03,
1.74E-03,
1.64E-03,
1.52E-03,
1.45E-03,
1.35E-03,
1.31E-03,
1.28E-03,
1.25E-03,
1.24E-03,
1.22E-03,
1.20E-03,
1.19E-03
};
//-----------------------------------------------------------------------------

#endif
