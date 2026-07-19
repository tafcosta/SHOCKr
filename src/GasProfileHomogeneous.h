/*
 * GasProfileHomogeneous.h
 *
 *  Created on: 19 Jul 2026
 *      Author: Tiago Costa
 */

#ifndef SRC_GASPROFILEHOMOGENEOUS_H_
#define SRC_GASPROFILEHOMOGENEOUS_H_

#include "GasProfile.h"

class GasProfileHomogeneous : public GasProfile {

public:

    GasProfileHomogeneous(double rho, double pressure, double velocity);

    virtual ~GasProfileHomogeneous();

    double density(double r) const override;
    double pressure(double r) const override;
    double velocity(double r) const override;

private:

    double rho0;
    double P0;
    double v0;
};

#endif /* SRC_GASPROFILEHOMOGENEOUS_H_ */
