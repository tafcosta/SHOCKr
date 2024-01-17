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

	void calculateGradients(void) override;
	void findShockZones(void) override;
	void findShockDirection(void) override;


};

#endif /* SRC_SHOCKFINDEREULERPASSIVESCALAR_H_ */
