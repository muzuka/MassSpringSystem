#ifndef _SPRING_H_
#define _SPRING_H_

/*
 * Spring connecting two particles
 * 
 * Written by: Sean Brown
 * 
 */


#include "Vector.h"
#include "Particle.h"

class Spring {
private:
	int i, j;
	double k;
	double l;

public:
	Spring();
	Spring(int, int, double, double); // i, j, k, length

	void render(std::vector<Particle>);

	int getFirst();
	int getSecond();
	double getConstant();
	double getLength();

	void setFirst(int);
	void setSecond(int);
	void setConstant(double);
	void setLength(double);
};

#endif
