/*
 * SimulationDependencies.h
 *
 *  Created on: 23 Jan 2024
 *      Author: ntc132
 */

#ifndef SRC_SIMULATIONDEPENDENCIES_H_
#define SRC_SIMULATIONDEPENDENCIES_H_

#include <iostream>
#include <cstdio>

#include "Boundary.h"
#include "BoundaryWind.h"
#include "BoundaryZeroGradient.h"
#include "BoundaryWindLinearisedEuler.h"
#include "BoundaryWindPassiveScalar.h"

#include "Equations.h"
#include "EquationsEuler.h"
#include "EquationsEulerPassiveScalar.h"
#include "EquationsLinearisedEuler.h"

#include "Grid.h"
#include "Grid1D.h"
#include "GridRadial.h"

#include "InitialData.h"
#include "InitialDataHomogeneous.h"
#include "InitialDataHomogeneousLinearisedEuler.h"
#include "InitialDataHomogeneousPassiveScalar.h"
#include "InitialDataIsothermal.h"
#include "InitialDataSodShock.h"

#include "Output.h"
#include "OutputEuler.h"
#include "OutputEulerPassiveScalar.h"
#include "OutputLinearisedEuler.h"

#include "RiemannSolver.h"
#include "RiemannSolverHLLC.h"
#include "RiemannSolverRusanov.h"

#include "ShockFinder.h"
#include "ShockFinderEulerPassiveScalar.h"

#endif /* SRC_SIMULATIONDEPENDENCIES_H_ */
