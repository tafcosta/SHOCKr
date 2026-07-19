/*
 * GasProfileHomogeneous.cpp
 *
 *  Created on: 19 Jul 2026
 *      Author: Tiago Costa
 */

#ifndef GASPROFILEHOMOGENEOUS_H_
#define GASPROFILEHOMOGENEOUS_H_

#include "GasProfileHomogeneous.h"

GasProfileHomogeneous::GasProfileHomogeneous(double rho, double pressure, double velocity) : rho0(rho), P0(pressure), v0(velocity){}

GasProfileHomogeneous::~GasProfileHomogeneous(){}

double GasProfileHomogeneous::density(double) const{
    return rho0;
}

double GasProfileHomogeneous::pressure(double) const{
    return P0;
}

double GasProfileHomogeneous::velocity(double) const{
    return v0;
}

#endif
