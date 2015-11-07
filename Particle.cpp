
#include "Particle.h"


Particle() {// defaults: color = white, mass = 1.0f, pos = (0, 0, 0)
	this->pos = Vector(0.0f, 0.0f, 0.0f);
	this->velocity = Vector(0.0f, 0.0f, 0.0f);
	this->color = Vector(1.0f, 1.0f, 1.0f);
	this->force = Vector(0.0f, 0.0f, 0.0f);
	this->mass = 1.0f;
}
  
Particle(Vector p) {
	Particle();
	this->pos = p;
}

Particle(Vector p, Vector c){
	Particle(p);
	this->color = c;
}
  
Particle(Vector p, double m) {
	Particle(p);
	this->mass = m;
}

Particle(Vector p, Vector c, double m) {
	Particle(p, m);
	this->color = c;
}

Vector getPosition() {
	return this->pos;
}

Vector getVelocity() {
	return this->velocity;
}

Vector getColor() {
	return this->color;
}

Vector getForce() {
	return this->force;
}

double getMass() {
	return this->mass;
}

void setPosition(Vector p) {
	this->pos = p;
}

void setPosition(double x, double y, double z) {
	this->pos = Vector(x, y, z);
}

void setVelocity(Vector v) {
	this->velocity = v;
}

void setVelocity(double x, double y, double z) {
	this->velocity = Vector(x, y, z);
}

void setColor(Vector c) {
	this->color = c;
}

void setColor(double r, double g, double b) {
	this->color = Vector(r, g, b);
}

void setForce(Vector f) {
	this->force = f;
}

void setForce(double x, double y, double z) {
	this->force = Vector(x, y, z);
}

void setMass(double m) {
	this->mass = m;
}