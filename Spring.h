#ifndef _SPRING_H_
#define _SPRING_H_

#include <Vector.h>

class Spring {
private:
	int i, j;
	double k;
	double l;

public:
	Spring();
	Spring(int, int, double, double);

	Vector getFirst();
	Vector getSecond();
	double getConstant();
	double getLength();

	void setFirst(int);
	void setSecond(int);
	void setConstant(double);
	void setLength(double);
};

#endif
