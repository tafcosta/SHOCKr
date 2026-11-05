/*
 * ArtificialCooling.cpp
 *
 *  See ArtificialCooling.h.
 */

#include <algorithm>
#include <cmath>
#include "ArtificialCooling.h"
#include "EquationsEulerPassiveScalar.h"

ArtificialCooling::ArtificialCooling(Grid& grid, EquationsEuler& equations, int mode,
                                     double windPressurePerDensity, double haloPressurePerDensity,
                                     double windFractionThreshold)
: energyRemoved(0.0), grid(grid), equations(equations), mode(mode),
  windPressurePerDensity(windPressurePerDensity), haloPressurePerDensity(haloPressurePerDensity),
  windFractionThreshold(windFractionThreshold) {}

void ArtificialCooling::apply() {

	if (mode == 0)
		return;

	for (int i = grid.minXIndex; i <= grid.maxXIndex; i++) {

		std::vector<double>& q = grid.quantities[i];

		const double rho   = q[EquationsEuler::DENS];
		const double rhoV2 = q[EquationsEuler::XMOM] * q[EquationsEuler::XMOM] / rho;
		const double p     = equations.getPressure(q);
		const double windFraction = q[EquationsEulerPassiveScalar::PASS] / rho;

		double pNew = p;
		if (windFraction >= windFractionThreshold)
			pNew = std::min(p, rho * windPressurePerDensity);
		else if (mode == 2)
			pNew = std::min(p, rho * haloPressurePerDensity);

		if (pNew < p) {
			const double eNew = equations.totalEnergy(pNew, rhoV2);
			const double r  = grid.getX(i);
			const double dr = grid.dx;
			const double dV = 4.0 / 3.0 * M_PI * (std::pow(r + dr / 2, 3) - std::pow(r - dr / 2, 3));
			energyRemoved += (q[EquationsEuler::ENERGY] - eNew) * dV;
			q[EquationsEuler::ENERGY] = eNew;
		}
	}
}

ArtificialCooling::~ArtificialCooling() {}
