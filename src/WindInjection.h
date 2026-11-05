/*
 * WindInjection.h
 *
 *  Injects the wind as a source in the first few cells, instead of through
 *  the ghost cells. Use it with a reflecting inner boundary (innerBoundary
 *  injection), so that no gas leaves through r_in and no injected energy is
 *  lost if the wind is blocked.
 *
 *  Each step, the same mass, momentum and energy fluxes as the ghost-cell
 *  wind are added, spread evenly by volume over nCells cells above r_in:
 *
 *      Mdot = 4 pi r_in^2 rho_w v_w                 (so Mdot v_w = L/c)
 *      pdot = Mdot v_w
 *      Edot = Mdot (v_w^2/2 + gamma/(gamma-1) P_w/rho_w)
 *
 *  If the cells are slower than v_w, the kinetic energy that does not show up
 *  as bulk motion stays in the cells as heat (the wind shocks in place).
 */

#ifndef SRC_WINDINJECTION_H_
#define SRC_WINDINJECTION_H_

#include "Grid.h"
#include "EquationsEuler.h"

class WindInjection {
public:
	WindInjection(Grid& grid, EquationsEuler& equations, double rhoWind, double velWind,
	              double pressureWind, int nCells);
	virtual ~WindInjection();
	void apply(double dt);

	double massRate, momentumRate, energyRate;   // code units
	double energyInjected;                       // total so far, code units

private:
	Grid& grid;
	EquationsEuler& equations;
	int nCells;
	double volume;
};

#endif /* SRC_WINDINJECTION_H_ */
