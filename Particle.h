#ifndef _PARTICLE_H_
#define _PARTICLE_H_

/*
 * Particle with mass
 * 
 * Written by: Sean Brown
 * 
 */

 #include <Vector.h>
 
 class Particle {
 private:
   Vector pos;
   double mass;

 public:
 	Particle();
 	Particle(Vector);
 	Particle(Vector, double);

 	Vector getPosition();
 	double getMass();

 	void setPosition(Vector);
 	void setPosition(double, double, double);
 	void setMass(double);

 };

#endif
