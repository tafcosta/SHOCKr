/*
 * ShockFinderEulerPassiveScalar.h
 *
 *  Created on: 16 Jan 2024
 *      Author: ntc132
 */

#ifndef SRC_SHOCKFINDEREULERPASSIVESCALAR_H_
#define SRC_SHOCKFINDEREULERPASSIVESCALAR_H_

#include "Equations.h"
#include "EquationsEuler.h"
#include "Grid.h"
#include "ShockFinder.h"

class ShockFinderEuler: public ShockFinder {
public:
	ShockFinderEuler(Grid& grid, EquationsEuler& equations) : ShockFinder(grid, equations) {};
	virtual ~ShockFinderEuler();

	static const int DENS = 0;
	static const int TEMP = 1;

	std::vector<int> findShockZones(double time, const std::string& filename) override;

private:
	void detectShockZone(int i, double divV, double gradientDens, double gradientTemp);
	void calculateDivV(int i);
	void calculateGradients(int i);

    void writeShockOutput(double time, const std::vector<int>& goodStarts, const std::vector<int>& goodEnds);
    double getShockPosition(int start, int end);
	double getKineticFlux(double rho, double velocity, double shockVelocity);

	double reverseShockPosOld = 0.;
	double forwardShockPosOld = 0.;
	double timeOld = -1.;

    std::string outputFilename;

};

#endif /* SRC_SHOCKFINDEREULERPASSIVESCALAR_H_ */
