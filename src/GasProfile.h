/*
 * GasProfile.h
 *
 *  Created on: 19 Jul 2026
 *      Author: Tiago Costa
 */

#ifndef SRC_GASPROFILE_H_
#define SRC_GASPROFILE_H_

class GasProfile {

public:
    GasProfile();
    virtual ~GasProfile();

    virtual double density(double r)  const = 0;
    virtual double pressure(double r) const = 0;
    virtual double velocity(double r) const;
};

#endif /* SRC_GASPROFILE_H_ */
