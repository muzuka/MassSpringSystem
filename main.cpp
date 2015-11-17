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
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

GLFWwindow* window;
fstream     file;

// flags
bool debug = false;
bool gravity;
bool simulation;

// settings
double nearPlane  = 1.0f;
double farPlane   = 1000.0f;
double fov        = 60.0f;
double damp       = 0.0001f;
double zDepth     = -1.0f;
double timeStep   = 0.000001f;

// glfw info
int width       = 1024;
int height      = 768;
string windowName;

Vector camera;
vector<Particle> particles;
vector<Spring> springs;

void getGravity() {
  char input[256];

  file >> input;
  if(!string(input).compare(string("false"))) {
    gravity = false;
  }
  else {
    gravity = true;
  }
}

void getParticles(int num) {
  double x, y, z, w;

  for(int i = 0; i < num; i++) {
    file >> x;
    file >> y;
    file >> z;
    file >> w;
    particles.push_back(Particle(Vector(x, y, z), w));
  }
}

void getSprings(int num) {
  int i, j;
  double k, l;

  file.get();

  for(int a = 0; a < num; a++) {
    file >> i;
    file >> j;
    file >> k;
    file >> l;
    springs.push_back(Spring(i, j, k, l));
  }
}

void readFile(string filename) {
  char title[256];
  char mode;
  int  amount;
  int  stillParticle;

  file = fstream(filename.c_str(), fstream::in);

  if(!file.is_open()) {
    cout << "File couldn't be open" << endl;
    exit(EXIT_FAILURE);
  }

  file.getline(title, 256);
  windowName = string(title);

  // get gravity setting
  file >> mode;
  if(mode == 'g') {
    getGravity();
  }
  else {
    cout << "No gravity setting" << endl;
    exit(EXIT_FAILURE);
  }

  cout << "getting particles" << endl;
  // get particles
  file >> mode;
  if(mode == 'p') {
    file >> amount;
    file >> stillParticle;
    getParticles(amount);
    if(stillParticle >= 0) {
      particles[stillParticle].toggleMovement();
    }
  }
  else {
    cout << "improper particle section" << endl;
    exit(EXIT_FAILURE);
  }

  cout << "getting springs" << endl;
  // get springs
  file >> mode;
  if(mode == 's') {
    file >> amount;
    getSprings(amount);
  }
  else {
    cout << "improper spring section" << endl;
    exit(EXIT_FAILURE);
  }

  file.close();
  cout << "finished loading" << endl;
}

void init() {
  simulation = false;

  camera = Vector(0.0f, 0.0f, 0.0f);

  glPointSize(10.0f);
}

void update() {
  Vector v1, v2, v3; // for dampening
  Particle *p1, *p2;
  Vector forceOverLength;
  Vector force;
  Vector springVector;
  double springLength;
  double distanceFromRest;
  Vector dampeningForce;

  for(unsigned int i = 0; i < springs.size(); i++) {
	  p1 = &particles[springs[i].getFirst()];
	  p2 = &particles[springs[i].getSecond()];

	  springVector = p1->getPosition() - p2->getPosition();
	  springLength = springVector.length();
	  distanceFromRest = (springLength - springs[i].getLength());

    // check for length of 0
    if(springLength == 0.0f)
      forceOverLength = springVector;
    else
      forceOverLength = springVector/springLength;

    // prepare dampening
    Vector v1 = p1->getVelocity();
    Vector v2 = p2->getVelocity();
    v1.normalize();
    v2.normalize();
    Vector v3 = v1 - v2;
    v3.normalize();
    dampeningForce = v3 * damp;

    // calculate force
	  force = ((forceOverLength * (-springs[i].getConstant() * distanceFromRest)));// - dampeningForce;

	  p1->setForce(p1->getForce() + force);
	  p2->setForce(p2->getForce() - force);

    if(debug) {
      cout << "gravity = " << gravity << endl;
      cout << "v1 = ";
      p1->getVelocity().print();
      v1.print();
      cout << "v2 = ";
      p2->getVelocity().print();
      v2.print();
      cout << "v3 = ";
      v3.print();
      cout << "dampening force = ";
      dampeningForce.print();
      cout << "springVector = ";
      springVector.print();
      cout << "Spring length = " << springLength << endl;
      cout << "force = ";
      force.print();
    }
	}

	for(unsigned int i = 0; i < particles.size(); i++) {
    if(!particles[i].isStationary()) {
      if(gravity) {
        particles[i].setForce(particles[i].getForce() + Vector(0.0f, -9.81f, zDepth) * particles[i].getMass());
      }
		  particles[i].setVelocity(particles[i].getVelocity() + (particles[i].getForce() / (particles[i].getMass() * timeStep)));
		  particles[i].setPosition(particles[i].getPosition() + (particles[i].getVelocity() * timeStep));
		  particles[i].setForce(Vector(0.0f, 0.0f, 0.0f));
    }
	}
}

void render() {

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov, height/width, nearPlane, farPlane);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();
  glTranslatef(camera.getX(), camera.getY(), camera.getZ());

  for(unsigned int i = 0; i < springs.size(); i++) {
  	springs[i].render(particles);
  }
  
  glPopMatrix();

  glfwSwapBuffers(window);
  glfwPollEvents();
}

void keyboardFunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(action == GLFW_PRESS) {
    if(key == GLFW_KEY_ENTER) {
      update();
    }
    if(key == GLFW_KEY_SPACE) {
      simulation = !simulation;
    }
    if(key == GLFW_KEY_D) {
      debug = !debug;
    }
    if(key == GLFW_KEY_G) {
      gravity = !gravity;
    }
    if(key == GLFW_KEY_DOWN) {
      camera.setZ(camera.getZ() - 10.0f);
    }
    if(key == GLFW_KEY_UP) {
      camera.setZ(camera.getZ() + 10.0f);
    }
    if(key == GLFW_KEY_LEFT) {
      camera.setX(camera.getX() - 10.0f);
    }
    if(key == GLFW_KEY_RIGHT) {
      camera.setX(camera.getX() + 10.0f);
    }
    if(key == GLFW_KEY_P) {
      for(unsigned int i = 0; i < springs.size(); i++) {
        particles[springs[i].getFirst()].getPosition().print();
        particles[springs[i].getSecond()].getPosition().print();
      }
    }
  }
}

int main(int argc, char **argv)
{
  
  if(argc != 2) {
    cout << "Need a file." << endl;
    exit(EXIT_FAILURE);
  }

  readFile(string(argv[1]));

	if(!glfwInit()) {
    cout << "glfw failed to initialize" << endl;
		exit(EXIT_FAILURE);
	}
	
	window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
	if(!window) {
    cout << "Window failed to be created" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
  
	glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, keyboardFunc);

	init();
  
	while(!glfwWindowShouldClose(window)) {
    if(simulation) {
      update();
    }

    render();
  }
  
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}

