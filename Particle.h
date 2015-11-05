#ifndef _PARTICLE_H_
#define _PARTICLE_H_

/*
 * Particle with mass
 * 
 * Written by: Sean Brown
 * 
 */

 #include "Vector.h"
 
 class Particle {
 private:
   Vector pos;
   Vector color;
   double mass;

 public:
 	Particle();                         // defaults: color = white, mass = 1.0f, pos = (0, 0, 0)
  Particle(Vector);                   // (pos)
 	Particle(Vector, Vector);           // (pos, color)
  Particle(Vector, double);           // (pos, mass)
 	Particle(Vector, Vector, double);   // (pos, color, mass)

 	Vector getPosition();
  Vector getColor();
 	double getMass();

 	void setPosition(Vector);
 	void setPosition(double, double, double);
  void setColor(Vector);
  void setColor(double, double, double);
 	void setMass(double);

 };

#endif
