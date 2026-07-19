/*
 * SourceGravity.h
 *
 *  Created on: 27 Sept 2025
 *      Author: Tiago Costa
 */

#ifndef SRC_SOURCEGRAVITY_H_
#define SRC_SOURCEGRAVITY_H_

#include "Source.h"
#include "GasProfile.h"

class SourceGravity: public Source {
public:
	SourceGravity(Grid& grid, EquationsEuler& equations, const GasProfile& profile, double massBH, double G_internal) : Source(grid, equations), gasProfile(profile), massBH(massBH), Grav(G_internal){}

    std::vector<double> getSource(std::vector<double>& quantities,
                                  double radialDistance) override;

    ~SourceGravity() override;

private:
    const GasProfile& gasProfile;

    double massBH;
    double Grav;
};

#endif /* SRC_SOURCEGRAVITY_H_ */
