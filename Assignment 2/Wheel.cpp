#include "Shape.hpp"
#include "Cylinder.h"
#include "RectPrism.h"
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

#define SPOKE_WIDTH 1

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

	glPushMatrix();
	positionInGL();
	setColorInGL();

	glRotated(-rotation, 0, 1, 0);		// rotate about y

	Cylinder wheelRim(0, 0, 0, 0, radius, innerRadius, length);
	wheelRim.setColor(0.5, 0.5, 0.5);	// set default colour to grey
	wheelRim.draw();

	glTranslated(0, radius, 0);			// move to the centre of the wheel
	glRotated(-90, 1, 0, 0);			// y-axis now points out of the page so that spokes can be drawn rotated
										// z-axis points upwards, x-axis remains pointing towards the left


	RectPrism spoke1(0, - length / 4, 0, 0, 2 * innerRadius, SPOKE_WIDTH, length / 2);
	spoke1.setColor(0.5, 0.5, 0.5);
	spoke1.draw();
	
	RectPrism spoke2(0, - length / 4, 0, 60, 2 * innerRadius, SPOKE_WIDTH, length / 2);
	spoke2.setColor(0.5, 0.5, 0.5);
	spoke2.draw();

	RectPrism spoke3(0, - length / 4, 0, -60, 2 * innerRadius, SPOKE_WIDTH, length / 2);
	spoke3.setColor(0.5, 0.5, 0.5);
	spoke3.draw();

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

//rotate about z-axis, steer about y-axis
//angular velocity = linear velocity / radius