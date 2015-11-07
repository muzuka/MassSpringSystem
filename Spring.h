#ifndef _SPRING_H_
#define _SPRING_H_

/*
 * Spring connecting two particles
 * 
 * Written by: Sean Brown
 * 
 */

#include "Vector.h"

class Spring {
private:
	int i, j;
	double k;
	double l;

public:
	Spring();
	Spring(int, int, double, double);

	Particle getFirst(std::vector<Particle>);
	Particle getSecond(std::vector<Particle>);
	double getConstant();
	double getLength();

	void setFirst(int);
	void setSecond(int);
	void setConstant(double);
	void setLength(double);
};

#endif
