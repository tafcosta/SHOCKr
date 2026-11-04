/*
 * ComptonCooling.h
 *
 *  Compton cooling and heating by the AGN radiation field.
 *
 *  For ionised gas, Compton scattering drives the gas temperature towards the
 *  Compton temperature T_C of the AGN spectrum,
 *
 *      dT/dt = -(T - T_C) / tau(r),
 *      tau(r) = (3 pi / 2) (n_tot / n_e) m_e c^2 r^2 / (sigma_T L),
 *
 *  which does not depend on density or temperature (non-relativistic electrons,
 *  one temperature for electrons and ions, optically thin). Over a timestep this
 *  is integrated exactly,
 *
 *      T_new = T_C + (T_old - T_C) exp(-dt / tau(r)),
 *
 *  so it is stable for any dt. Only the thermal energy changes.
 *
 *  Optional relativistic correction (relativistic = true): for a thermal
 *  (Maxwell-Juttner) electron distribution the Compton power is larger by
 *  f(theta) = K3(1/theta)/K2(1/theta), theta = k T / m_e c^2. We use
 *  f = 4 theta + 1/(1 + 1.5 theta), accurate to better than 1% for all theta.
 *  tau is then divided by f, evaluated at the start of the step.
 *
 *  mode 0: off
 *  mode 1: cooling and heating (gas relaxes to T_C from above and below)
 *  mode 2: cooling only (gas below T_C is left unchanged)
 */

#ifndef SRC_COMPTONCOOLING_H_
#define SRC_COMPTONCOOLING_H_

#include "Grid.h"
#include "EquationsEuler.h"

class ComptonCooling {
public:
	ComptonCooling(Grid& grid, EquationsEuler& equations, int mode,
	               double luminosityCgs, double comptonTemperature,
	               double unitLengthInCgs, double unitVelocityInCgs,
	               bool relativistic = false);
	virtual ~ComptonCooling();

	void apply(double dt);

	// Cooling time at radius r (code units), non-relativistic
	double coolingTime(double r) const;

	// Relativistic correction factor for gas with pressure p and density rho
	double relativisticFactor(double p, double rho) const;

	// Thermal energy removed (positive) or added (negative) so far, code units
	double energyRadiated;

private:
	Grid& grid;
	EquationsEuler& equations;
	int mode;
	bool relativistic;

	double tauCoefficient;   // tau = tauCoefficient * r^2, code units
	double pressurePerDensity;  // P_C / rho = k T_C / (mu m_p), code units
	double thetaPerPressureOverDensity;  // theta = this * P / rho
};

#endif /* SRC_COMPTONCOOLING_H_ */
