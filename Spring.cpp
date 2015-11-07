
#include "Spring.h"

Spring() {

}

Spring(int i, int j, double k, double l) {
	this->i = i;
	this->j = j;
	this->k = k;
	this->l = l;
}

Particle getFirst(std::vector<Particle> particles) {
	return particles[this->i];
}

Particle getSecond(std::vector<Particle>) {
	return particles[this->j];
}

double getConstant() {
	return k;
}

double getLength() {
	return l;
}

void setFirst(int i) {
	this->i = i;
}

void setSecond(int) {
	this->j = j;
}

void setConstant(double) {
	this->k = k;
}

void setLength(double) {
	this->l = l;
}