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

#include <iostream>

using namespace std;

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
  
	while(!glfwWindowShouldClose(window)) {
    
  }
  
  glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}

