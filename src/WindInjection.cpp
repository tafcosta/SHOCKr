/*
 * WindInjection.cpp
 *
 *  See WindInjection.h.
 */

#include <cmath>
#include "WindInjection.h"
#include "EquationsEulerPassiveScalar.h"

WindInjection::WindInjection(Grid& grid, EquationsEuler& equations, double rhoWind, double velWind,
                             double pressureWind, int nCells)
: energyInjected(0.0), grid(grid), equations(equations), nCells(nCells)
{
	const double rIn   = grid.xmin;
	const double gamma = equations.gamma;

	massRate     = 4.0 * M_PI * rIn * rIn * rhoWind * velWind;
	momentumRate = massRate * velWind;
	energyRate   = massRate * (0.5 * velWind * velWind + gamma / (gamma - 1.0) * pressureWind / rhoWind);

	volume = 4.0 / 3.0 * M_PI * (std::pow(rIn + nCells * grid.dx, 3) - std::pow(rIn, 3));
}

void WindInjection::apply(double dt) {

	const bool hasScalar = equations.nCons() > EquationsEulerPassiveScalar::PASS;

	for (int i = grid.minXIndex; i < grid.minXIndex + nCells; i++) {
		std::vector<double>& q = grid.quantities[i];

		q[EquationsEuler::DENS]   += massRate     * dt / volume;
		q[EquationsEuler::XMOM]   += momentumRate * dt / volume;
		q[EquationsEuler::ENERGY] += energyRate   * dt / volume;

		if (hasScalar)
			q[EquationsEulerPassiveScalar::PASS] += massRate * dt / volume;
	}

	energyInjected += energyRate * dt;
}

WindInjection::~WindInjection() {}
