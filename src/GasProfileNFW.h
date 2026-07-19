/*
 * GasProfileNFW.h
 *
 *  Created on: 19 Jul 2026
 *      Author: Tiago Costa
 */

#ifndef SRC_GASPROFILENFW_H_
#define SRC_GASPROFILENFW_H_

#include "GasProfile.h"

class GasProfileNFW : public GasProfile {

public:

	GasProfileNFW(double haloMass, double haloConcentration, double baryonFraction, double unitLengthInCgs, double unitMassInCgs, double unitTimeInCgs);
	virtual ~GasProfileNFW();

    double density(double r) const override;
    double pressure(double r) const override;
    double velocity(double r) const override;

private:
    double rhoScale;
    double rScale;
    double Gcode;
    double baryonFraction;
};

#endif /* SRC_GASPROFILENFW_H_ */
