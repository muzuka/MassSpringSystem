/*
 * main.cpp
 * 
 * Written by: Sean Brown
 * 
 * Particle:
 * x, y, z - vectors of 3 (position
 * m - real number (mass)
 * 
 * Spring:
 * index i, j - integer (particles)
 * k - real number (spring constant)
 * l - real number (distance of rest state)
 * 
 * Force on particle p
 *   Fp = sum of forces connected to p
 * 
 * Force between particles
 *   Fp-pi = -spring.k(||p - pi|| - spring.l)(p - pi)/(||p - pi||)
 * 
 */

#define _GLFW_X11
#define _GLFW_GLX
#define _GLFW_USE_OPENGL
#define _GLFW_HAS_GLXGETPROCADDRESS
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "Spring.h"
#include "Particle.h"
#include <vector>
#include <iostream>

using namespace std;

GLFWwindow* window;

double zDepth = -1.0f;
double timeStep = 0.001f;
int width = 1024;
int height = 768;

vector<Particle> particles;
vector<Spring> springs;

void init() {
   Vector pos[] = {Vector(0.0f, 0.0f, zDepth), Vector(0.0f, -0.5f, zDepth)};

   for(int i = 0; i < 2; i++) {
   		particles.push_back(Particle(pos[i]));
   }
   
   particles[0].toggle();

   springs.push_back(Spring(0, 1, 0.01f, 1.0f));

   glPointSize(20.0f);
}

void update() {
	Particle *p1, *p2;
	Vector springVector;
	double springLength;
	double distanceFromRest;

	for(unsigned int i = 0; i < springs.size(); i++) {
		p1 = &particles[springs[i].getFirst()];
		p2 = &particles[springs[i].getSecond()];

		springVector = p1->getPosition() - p2->getPosition();
		springLength = springVector.length();
		distanceFromRest = (springLength - springs[i].getLength());

		Vector force = (springVector/springLength) * (-springs[i].getConstant() * distanceFromRest);
  		p1->setForce(p1->getForce() + force);
  		p2->setForce(p2->getForce() - force);
  	}
  	for(unsigned int i = 0; i < particles.size(); i++) {
      if(!particles[i].isStationary()) {
        particles[i].setForce(particles[i].getForce() + Vector(0.0f, -9.81f, zDepth));
  		  particles[i].setVelocity(particles[i].getForce() / (particles[i].getMass() * timeStep));
  		  particles[i].setPosition(particles[i].getVelocity() * timeStep);
  		  particles[i].setForce(Vector(0.0f, 0.0f, zDepth));
      }
  	}
}

void render() {

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, height/width, 0.0f, 1000.0f);

  	for(unsigned int i = 0; i < springs.size(); i++) {
  		springs[i].render(particles);
  	}
  	

  	glfwSwapBuffers(window);
    glfwPollEvents();
}

void keyboardFunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(key == GLFW_KEY_ENTER) {
    cout << "updated" << endl;
    update();
  }
}

int main(int argc, char **argv)
{
  
	if(!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	
	window = glfwCreateWindow(width, height, "Mass Spring Simulation CPSC 587", NULL, NULL);
	if(!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
  
	glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, keyboardFunc);

	init();
  
	while(!glfwWindowShouldClose(window)) {
		//update();

    	render();
  }
  
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}

