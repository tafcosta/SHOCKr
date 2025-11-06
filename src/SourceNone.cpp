/*
 * SourceNone.cpp
 *
 *  Created on: 27 Sept 2025
 *      Author: ntc132
 */

#include "SourceNone.h"

std::vector<double> SourceNone::getSource(std::vector<double>& quantities, double radialDistance){

	std::vector<double> res = std::vector<double>(equations.nCons(), 0.0);

	return res;
}



SourceNone::~SourceNone() {
	// TODO Auto-generated destructor stub
}

