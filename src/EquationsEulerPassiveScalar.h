/*
 * EquationsEulerPassiveScalar.h
 *
 *  Created on: 15 Jan 2024
 *      Author: ntc132
 */

#ifndef SRC_EQUATIONSEULERPASSIVESCALAR_H_
#define SRC_EQUATIONSEULERPASSIVESCALAR_H_

#include "EquationsEuler.h"

class EquationsEulerPassiveScalar: public EquationsEuler {
public:
	EquationsEulerPassiveScalar(double gamma) : EquationsEuler(gamma) {};

	virtual ~EquationsEulerPassiveScalar();

	int nCons(void) override;
	static const int PASS  = 3;

	double* getFlux(std::vector<double>& quantities) override;

};

#endif /* SRC_EQUATIONSEULERPASSIVESCALAR_H_ */
