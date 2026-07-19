/*
 * InitialDataRadial.cpp
 *
 *  Created on: 19 Jul 2026
 *      Author: Tiago Costa
 */

#include "InitialDataRadial.h"
#include "InitialData.h"
#include "Equations.h"
#include "EquationsEuler.h"
#include "EquationsEulerPassiveScalar.h"
#include "SimulationDependencies.h"
#include <cmath>

void InitialDataRadial::setInitialData()
{
    auto* euler = static_cast<EquationsEuler*>(&equations);

    for(int i=0;i<grid.nx+2*grid.nGhost;i++){

        double r = grid.getX(i);

        double rho = gas.density(r);
        double P   = gas.pressure(r);
        double v   = gas.velocity(r);

        grid.quantities[i][EquationsEuler::DENS]   = rho;
        grid.quantities[i][EquationsEuler::XMOM]   = rho*v;
        grid.quantities[i][EquationsEuler::ENERGY] = euler->totalEnergy(P, rho*v*v);

        if (dynamic_cast<EquationsEulerPassiveScalar*>(&equations) != nullptr)
        	grid.quantities[i][EquationsEulerPassiveScalar::PASS] = 0.0;
    }
}


InitialDataRadial::~InitialDataRadial() {
	// TODO Auto-generated destructor stub
}

