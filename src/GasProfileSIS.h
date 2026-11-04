/*
 * GasProfileSIS.h
 *
 *  Singular isothermal sphere (King 2003): total density sigma^2 / (2 pi G r^2),
 *  of which a fraction f_g is gas,
 *
 *      rho_gas(r) = f_g sigma^2 / (2 pi G r^2),
 *      M_tot(r)   = 2 sigma^2 r / G,
 *
 *  in hydrostatic equilibrium in the potential of M_tot plus a central black
 *  hole of mass M_BH (pressure zero at infinity):
 *
 *      P(r) = rho_gas sigma^2 + f_g sigma^2 M_BH / (6 pi r^3).
 *
 *  All quantities in code units.
 */

#ifndef SRC_GASPROFILESIS_H_
#define SRC_GASPROFILESIS_H_

#include "GasProfile.h"

class GasProfileSIS : public GasProfile {

public:
	GasProfileSIS(double sigma, double gasFraction, double Gcode, double massBH = 0.0);
	virtual ~GasProfileSIS();

	double density(double r) const override;
	double pressure(double r) const override;
	double velocity(double r) const override;

	// Total gravitating mass (dark matter + gas) inside r, excluding the black hole
	double enclosedMass(double r) const override;

private:
	double sigma;
	double gasFraction;
	double Gcode;
	double massBH;
};

#endif /* SRC_GASPROFILESIS_H_ */
