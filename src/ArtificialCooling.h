/*
 * ArtificialCooling.h
 *
 *  Test switch that imposes the radiative losses King's momentum-driven model
 *  assumes. Not a physical cooling function.
 *
 *  mode 0: off
 *  mode 1: wind cooled. Any cell whose wind fraction (passive scalar / density)
 *          is at least windFractionThreshold is set to the wind temperature
 *          (P/rho = windPressure/windDensity) every step, so the shocked wind
 *          keeps no thermal energy and pushes only with its momentum.
 *  mode 2: wind and shell cooled. As mode 1, and any other cell with
 *          P/rho > haloPressurePerDensity is set back to that value, so the
 *          forward shock is isothermal at the halo temperature and the
 *          swept-up halo gas collapses into a thin shell.
 *
 *  energyRemoved records the thermal energy taken out (code units).
 */

#ifndef SRC_ARTIFICIALCOOLING_H_
#define SRC_ARTIFICIALCOOLING_H_

#include "Grid.h"
#include "EquationsEuler.h"

class ArtificialCooling {
public:
	ArtificialCooling(Grid& grid, EquationsEuler& equations, int mode,
	                  double windPressurePerDensity, double haloPressurePerDensity,
	                  double windFractionThreshold = 0.5);
	virtual ~ArtificialCooling();
	void apply();

	double energyRemoved;

private:
	Grid& grid;
	EquationsEuler& equations;
	int mode;
	double windPressurePerDensity, haloPressurePerDensity, windFractionThreshold;
};

#endif /* SRC_ARTIFICIALCOOLING_H_ */
