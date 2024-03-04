/*
 * InitialDataPowerLawPassiveScalar.cpp
 *
 *  Created on: 4 Mar 2024
 *      Author: ntc132
 */

#include "InitialDataPowerLawPassiveScalar.h"
#include "InitialData.h"
#include "Equations.h"
#include "EquationsEulerPassiveScalar.h"

void InitialDataPowerLawPassiveScalar::setInitialData() {
    InitialDataPowerLaw::setInitialData();

    for(int i = 0; i < grid.nx + 2*grid.nGhost; i++)
        grid.quantities[i][EquationsEulerPassiveScalar::PASS] = 0.;
}
InitialDataPowerLawPassiveScalar::~InitialDataPowerLawPassiveScalar() {
	// TODO Auto-generated destructor stub
}

