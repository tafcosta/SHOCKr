/*
 * ShockFinderEulerPassiveScalar.h
 *
 *  Created on: 16 Jan 2024
 *      Author: ntc132
 */

#ifndef SRC_SHOCKFINDEREULERPASSIVESCALAR_H_
#define SRC_SHOCKFINDEREULERPASSIVESCALAR_H_

#include "Equations.h"
#include "EquationsEulerPassiveScalar.h"
#include "Grid.h"
#include "ShockFinder.h"

class ShockFinderEulerPassiveScalar: public ShockFinder {
public:
	ShockFinderEulerPassiveScalar(Grid& grid, EquationsEulerPassiveScalar& equations) : ShockFinder(grid, equations) {};
	virtual ~ShockFinderEulerPassiveScalar();

	static const int DENS = 0;
	static const int TEMP = 1;

	std::vector<int> findShockZones(void) override;

private:
	void detectShockZone(int i, double divV, double gradientDens, double gradientTemp);
	void calculateDivV(int i);
	void calculateGradients(int i);
};

#endif /* SRC_SHOCKFINDEREULERPASSIVESCALAR_H_ */
