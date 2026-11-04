/*
 * ComptonCooling.cpp
 *
 *  See ComptonCooling.h for the equations.
 */

#include <cmath>
#include "ComptonCooling.h"

namespace {
	const double ELECTRON_REST_ENERGY = 8.1871057769e-7;   // m_e c^2 [erg]
	const double THOMSON_CROSS_SECTION = 6.6524587e-25;    // [cm^2]
	const double BOLTZMANN_CONSTANT    = 1.380649e-16;     // [erg/K]
	const double PROTON_MASS           = 1.67262192e-24;   // [g]

	// Fully ionised gas with X = 0.76: mu = 0.59, n_tot / n_e = 1.92
	const double MEAN_MOLECULAR_WEIGHT = 0.6;
	const double PARTICLES_PER_ELECTRON = 1.92;
}

ComptonCooling::ComptonCooling(Grid& grid, EquationsEuler& equations, int mode,
                               double luminosityCgs, double comptonTemperature,
                               double unitLengthInCgs, double unitVelocityInCgs,
                               bool relativistic)
: energyRadiated(0.0), grid(grid), equations(equations), mode(mode), relativistic(relativistic)
{
	const double unitTimeInCgs = unitLengthInCgs / unitVelocityInCgs;

	// tau(r) in seconds for r in cm, then converted to code units
	const double tauCgsPerCm2 = 1.5 * M_PI * PARTICLES_PER_ELECTRON * ELECTRON_REST_ENERGY
	                            / (THOMSON_CROSS_SECTION * luminosityCgs);

	tauCoefficient = tauCgsPerCm2 * unitLengthInCgs * unitLengthInCgs / unitTimeInCgs;

	pressurePerDensity = BOLTZMANN_CONSTANT * comptonTemperature
	                     / (MEAN_MOLECULAR_WEIGHT * PROTON_MASS)
	                     / (unitVelocityInCgs * unitVelocityInCgs);

	thetaPerPressureOverDensity = MEAN_MOLECULAR_WEIGHT * PROTON_MASS
	                              * unitVelocityInCgs * unitVelocityInCgs / ELECTRON_REST_ENERGY;
}

double ComptonCooling::coolingTime(double r) const {
	return tauCoefficient * r * r;
}

double ComptonCooling::relativisticFactor(double p, double rho) const {
	if (!relativistic)
		return 1.0;
	const double theta = thetaPerPressureOverDensity * p / rho;
	return 4.0 * theta + 1.0 / (1.0 + 1.5 * theta);
}

void ComptonCooling::apply(double dt) {

	if (mode == 0)
		return;

	for (int i = grid.minXIndex; i <= grid.maxXIndex; i++) {

		std::vector<double>& q = grid.quantities[i];

		const double r       = grid.getX(i);
		const double rho     = q[EquationsEuler::DENS];
		const double rhoV2   = q[EquationsEuler::XMOM] * q[EquationsEuler::XMOM] / rho;
		const double p       = equations.getPressure(q);
		const double pCompton = rho * pressurePerDensity;

		if (mode == 2 && p <= pCompton)
			continue;

		const double tau  = coolingTime(r) / relativisticFactor(p, rho);
		const double pNew = pCompton + (p - pCompton) * std::exp(-dt / tau);
		const double eNew = equations.totalEnergy(pNew, rhoV2);

		const double dr = grid.dx;
		const double dV = 4.0 / 3.0 * M_PI * (std::pow(r + dr / 2, 3) - std::pow(r - dr / 2, 3));
		energyRadiated += (q[EquationsEuler::ENERGY] - eNew) * dV;

		q[EquationsEuler::ENERGY] = eNew;
	}
}

ComptonCooling::~ComptonCooling() {}
