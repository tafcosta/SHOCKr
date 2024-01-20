/*
 * RiemannSolverHLLC.cpp
 *
 *  Created on: 20 Jan 2024
 *      Author: ntc132
 */

#include "RiemannSolverHLLC.h"
#include "Equations.h"
#include "EquationsEuler.h"
#include "Grid.h"

#include <iostream>

std::vector<double> RiemannSolverHLLC::numericalFlux(std::vector<double>& quantitiesLeft, std::vector<double>& quantitiesRight){
	double* fluxLeft;
	double* fluxRight;
	std::vector<double> quantitiesLeftStar(equations.nCons());
	std::vector<double> quantitiesRightStar(equations.nCons());
	double csLeft, csRight, uLeft, uRight, sLeft, sRight, sStar;
	std::vector<double> flux_vector(equations.nCons());

	double rhoV2Left  = quantitiesLeft[EquationsEuler::XMOM] * quantitiesLeft[EquationsEuler::XMOM] / quantitiesLeft[EquationsEuler::DENS];
	double rhoV2Right = quantitiesRight[EquationsEuler::XMOM] * quantitiesRight[EquationsEuler::XMOM] / quantitiesRight[EquationsEuler::DENS];
	double pLeft = (static_cast<EquationsEuler*>(&equations))->getPressure(quantitiesLeft[EquationsEuler::ENERGY], rhoV2Left);
	double pRight = (static_cast<EquationsEuler*>(&equations))->getPressure(quantitiesRight[EquationsEuler::ENERGY], rhoV2Right);


	uLeft  = quantitiesLeft[EquationsEuler::XMOM]  / quantitiesLeft[EquationsEuler::DENS];
	uRight = quantitiesRight[EquationsEuler::XMOM] / quantitiesRight[EquationsEuler::DENS];
	csLeft = (static_cast<EquationsEuler*>(&equations))->getSoundSpeed(quantitiesLeft);
	csRight= (static_cast<EquationsEuler*>(&equations))->getSoundSpeed(quantitiesRight);

	sLeft  = std::min(uLeft - csLeft, uRight - csRight);
	sRight = std::max(uLeft + csLeft, uRight + csRight);
	sStar  =  (pRight - pLeft + quantitiesLeft[EquationsEuler::XMOM] * (sLeft - uLeft) - quantitiesRight[EquationsEuler::XMOM] * (sRight - uRight)) \
			/ (quantitiesLeft[EquationsEuler::DENS] * (sLeft - uLeft) - quantitiesRight[EquationsEuler::XMOM] * (sRight - uRight));

	fluxLeft  = equations.getFlux(quantitiesLeft);
	fluxRight = equations.getFlux(quantitiesRight);

	quantitiesLeftStar[EquationsEuler::DENS]   = quantitiesLeft[EquationsEuler::DENS]   * (sLeft - uLeft) / (sLeft - sStar);
	quantitiesLeftStar[EquationsEuler::XMOM]   = quantitiesLeftStar[EquationsEuler::DENS] * sStar;
	quantitiesLeftStar[EquationsEuler::ENERGY] = quantitiesLeftStar[EquationsEuler::DENS]                     \
			* quantitiesLeft[EquationsEuler::ENERGY]/quantitiesLeft[EquationsEuler::DENS] + (sStar - uLeft)   \
			* (sStar + pLeft/(quantitiesLeft[EquationsEuler::DENS] * (sLeft - uLeft)));

	quantitiesRightStar[EquationsEuler::DENS]   = quantitiesRight[EquationsEuler::DENS] * (sRight - uRight) / (sRight - sStar);
	quantitiesRightStar[EquationsEuler::XMOM]   = quantitiesRightStar[EquationsEuler::DENS] * sStar;
	quantitiesRightStar[EquationsEuler::ENERGY] = quantitiesRightStar[EquationsEuler::DENS]                    \
			* quantitiesRight[EquationsEuler::ENERGY]/quantitiesRight[EquationsEuler::DENS] + (sStar - uRight) \
			* (sStar + pRight/(quantitiesRight[EquationsEuler::DENS] * (sRight - uRight)));


	for(int k = 0; k < equations.nCons(); k++){
		if(sLeft >= 0)
			flux_vector[k] = fluxLeft[k];
		else if((sLeft <= 0) && (sStar >= 0))
			flux_vector[k] = fluxLeft[k]  + sLeft  * (quantitiesLeftStar[k] - quantitiesLeft[k]);
		else if((sStar <= 0) && (sRight >= 0))
			flux_vector[k] = fluxRight[k] + sRight * (quantitiesRightStar[k] - quantitiesRight[k]);
		else if(sRight <= 0)
			flux_vector[k] = fluxRight[k];

	}

	if(maxSpeed < std::max(abs(sLeft), abs(sRight)))
		maxSpeed = std::max(abs(sLeft), abs(sRight));

	return flux_vector;
}


RiemannSolverHLLC::~RiemannSolverHLLC() {
	// TODO Auto-generated destructor stub
}

