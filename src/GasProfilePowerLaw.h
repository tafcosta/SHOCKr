/*
 * GasProfilePowerLaw.h
 *
 *  Created on: 19 Jul 2026
 *      Author: Tiago Costa
 */

#ifndef SRC_GASPROFILEPOWERLAW_H_
#define SRC_GASPROFILEPOWERLAW_H_

#include "GasProfile.h"

class GasProfilePowerLaw : public GasProfile {

public:

    GasProfilePowerLaw(double rho0, double P0, double v0, double r0, double alpha);

    virtual ~GasProfilePowerLaw();

    double density(double r) const override;
    double pressure(double r) const override;
    double velocity(double r) const override;

private:

    double rho0;
    double P0;
    double v0;
    double r0;
    double alpha;
};

#endif /* SRC_GASPROFILEPOWERLAW_H_ */
