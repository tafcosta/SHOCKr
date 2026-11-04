/*
 * GasProfileSIS.cpp
 *
 *  See GasProfileSIS.h for the equations.
 */

#include <cmath>
#include "GasProfileSIS.h"

GasProfileSIS::GasProfileSIS(double sigma, double gasFraction, double Gcode, double massBH)
: sigma(sigma), gasFraction(gasFraction), Gcode(Gcode), massBH(massBH) {}

double GasProfileSIS::density(double r) const {
	return gasFraction * sigma * sigma / (2.0 * M_PI * Gcode * r * r);
}

double GasProfileSIS::pressure(double r) const {
	return density(r) * sigma * sigma
	       + gasFraction * sigma * sigma * massBH / (6.0 * M_PI * r * r * r);
}

double GasProfileSIS::velocity(double) const {
	return 0.0;
}

double GasProfileSIS::enclosedMass(double r) const {
	return 2.0 * sigma * sigma * r / Gcode;
}

GasProfileSIS::~GasProfileSIS() {}
