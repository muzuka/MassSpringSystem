#ifndef _PARTICLE_H_
#define _PARTICLE_H_

/*
 * Particle with mass
 * 
 * Written by: Sean Brown
 * 
 */


 #include <vector>
 #include "Vector.h"
 
 class Particle {
 private:
   bool   stationary;
   Vector pos;
   Vector velocity;
   Vector color;
   Vector force;
   double mass;

 public:
  Particle();                         // defaults: color = white, mass = 1.0f, pos = (0, 0, 0)
  Particle(Vector);                   // (pos)
 	Particle(Vector, Vector);           // (pos, color)
  Particle(Vector, double);           // (pos, mass)
 	Particle(Vector, Vector, double);   // (pos, color, mass)

  void render();
  
  void toggleMovement();

  bool   isStationary();
 	Vector getPosition();
  Vector getVelocity();
  Vector getColor();
  Vector getForce();
 	double getMass();

  void setStationary(bool);
 	void setPosition(Vector);
 	void setPosition(double, double, double);
  void setVelocity(Vector);
  void setVelocity(double, double, double);
  void setColor(Vector);
  void setColor(double, double, double);
  void setForce(Vector);
  void setForce(double, double, double);
 	void setMass(double);

 };

#endif
