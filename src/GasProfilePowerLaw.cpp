/*
 * GasProfilePowerLaw.cpp
 *
 *  Created on: 19 Jul 2026
 *      Author: Tiago Costa
 */

#include "GasProfilePowerLaw.h"
#include <cmath>

GasProfilePowerLaw::GasProfilePowerLaw(double rho0_, double P0_, double v0_, double r0_, double alpha_) : rho0(rho0_), P0(P0_), v0(v0_), r0(r0_), alpha(alpha_){}

double GasProfilePowerLaw::density(double r) const{
    return rho0 * std::pow(r0/r, alpha);
}

double GasProfilePowerLaw::pressure(double) const{
    return P0;
}

double GasProfilePowerLaw::velocity(double) const{
    return v0;
}

double GasProfilePowerLaw::enclosedMass(double r) const{
    return 4.0 * M_PI * rho0 * std::pow(r0, alpha) * std::pow(r, 3.0 - alpha) / (3.0 - alpha);
}

GasProfilePowerLaw::~GasProfilePowerLaw() {
	// TODO Auto-generated destructor stub
}

