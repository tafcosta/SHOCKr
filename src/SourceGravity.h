/*
 * SourceGravity.h
 *
 *  Created on: 27 Sept 2025
 *      Author: ntc132
 */

#ifndef SRC_SOURCEGRAVITY_H_
#define SRC_SOURCEGRAVITY_H_

#include "Source.h"

class SourceGravity: public Source {
public:
	SourceGravity(Grid& grid, EquationsEuler& equations, double massBH, double G_internal) : Source(grid, equations), massBH(massBH), Grav(G_internal) {};
	virtual ~SourceGravity();

	double massBH;
	double Grav;

	std::vector<double> getSource(std::vector<double>& quantities, double radialDistance);

};

#endif /* SRC_SOURCEGRAVITY_H_ */
