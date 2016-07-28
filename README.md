# MassSpringSystem
An OpenGL implentation of mass spring animation.

## Controls

* SPACE key -> toggles animation
* ENTER key -> steps through animation
* G key -> toggles gravity

## Getting Started

These instructions will help with running the program.

Use this as the base compile instruction

~~~
g++ -o main main.cpp Particle.cpp Spring.cpp Vector.cpp -std=c++0x
~~~

OpenGL has platform specific flags so try these anywhere around "-o main" and after g++.

For Mac:
~~~
-framework Opengl
~~~

For Linux:
~~~
-lGL
~~~

For Windows:
~~~
-lopengl32
~~~

You will need GLFW installed to run this program.
Just add the following if you have GLFW installed.
~~~
-lglfw3
~~~

## Custom files

You can make your own files using this format:

* Line 1: Title (can be anything, will appear in window)
* Line 2: g
* Line 3: true or false (true for gravity, false for no gravity)
* Line 4: p n i

n = number of particles

i = which particle is static (-1 for none)

For each Particle:
* Line 4 + n: x y z w
* Line 4 + (n + 1): s m

m = number of springs

For each spring:
* Line 4 + m + (n + 1): i j k l

i = first particle index

j = second particle index

k = constant

l = rest length
