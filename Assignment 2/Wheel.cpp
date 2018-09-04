#include "Shape.hpp"
#include "Cylinder.h"
#include "Wheel.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined(WIN32)
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

Wheel::Wheel() {
	// Default constructor for this shape
	innerRadius = 0.0;
	radius = 5;
	length = 10;
	rotation = 0.0;
	red = green = blue = 1.0;
}

Wheel::Wheel(double x_, double y_, double z_, double rotation_, double radius_, double innerRadius_, double length_) {
	x = x_;
	y = y_;
	z = z_;
	rotation = rotation_;

	radius = radius_;
	innerRadius = innerRadius_;
	length = length_;

	red = blue = green = 1.0;
}

Wheel::~Wheel() {}

void Wheel::draw() {

	// Set position
	glPushMatrix();
	positionInGL();
	setColorInGL();

	Cylinder wheelRim(0, 0, 0, 0, radius, innerRadius, length);
	wheelRim.draw();


	glPopMatrix();
}

/* 
So apparently we're supposed to use dynamic casting to identify wheels, and if they're wheels, make them rotate and steer
Also, use "M" Message to interact with the server so we can draw our vehicle on the server. Supposed to use a vector of shapes to do this,
with each shape in the vector being a struct containing the parameters for the shape
Also, with looking at bool isRolling; bool isSteering; use these to check if it is a cylinder which is a wheel
since it might be just a cylinder as part of the car and shouldn't rotate/steer. The back wheels also are supposed to rotate but not steer
Not sure if we need to put these bool variables under Cylinder.h or Wheel.h though
*/