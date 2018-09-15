// MTRN2500 Semester 2 2018
// Katherine and Rebecca 
// z5161528  and z5115440

// Style notes: Comments above the line they refer to. All lines less than 80
// characters to allow for double screen use. Comments begin with a capital 
// and a space is always left between the "//" and the start of the line.

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
	// Default constructor for the wheel object
	radius = 0;
	innerRadius = 0.0;
	length = 0;

	wheelSpeed = 0;
	isSteering = 0;
	isRolling = 0;
}

Wheel::Wheel(double radius_, double innerRadius_, double length_, 
			 double wheelSpeed_, bool isSteering_, bool isRolling_) {
	// Overloaded constructor for the wheel object
	radius = radius_;
	innerRadius = innerRadius_;
	length = length_;

	wheelSpeed = wheelSpeed_;
	isSteering = isSteering_;
	isRolling = isRolling_;
}

Wheel::~Wheel() {}

bool Wheel::Steering() {
	// Checks whether the wheel is steering
	return isSteering;
}

bool Wheel::Rolling() {
	// Checks whether the wheel is rolling
	return isRolling;
}

void Wheel::draw() {
	glPushMatrix();
	positionInGL();
	setColorInGL();

	// Adjust to centre of the base of the wheel 
	glTranslated(0, radius, -length / 2);

	// Drawing the Wheel Rim
	glPushMatrix();
	// Create the new Wheel Rim object
	GLUquadricObj *wheelRim = gluNewQuadric();
	// Draw the hollow cylinder body
	gluCylinder(wheelRim, radius, radius, length, SLICES, STACKS);
	// Draw the first wheel rim cap
	gluDisk(wheelRim, innerRadius, radius, SLICES, STACKS);
	// Move to draw the back wheel rim cap
	glTranslated(0, 0, length);			
	gluDisk(wheelRim, innerRadius, radius, SLICES, STACKS);
	glPopMatrix();

	// At this point drawing origin is at the centre of the base of the 
	// wheel (where it touches the ground).


	// Drawing the Spokes
	double spokeRadius = radius / 10;
	// Ensuring that the spoke width is not wider than the width of the 
	// wheel rim.
	if (spokeRadius > length / 2) {
		// If it is wider, reset the spoke width
		spokeRadius = length / 2;
	}

	glPushMatrix();
	// Create the new Spoke object
	GLUquadricObj *spoke = gluNewQuadric();
	// Move to the centre of the wheel
	glTranslated(0, 0, length / 2);	
	// Rotate about the y-axis to move z-axis to original x-axis direction
	glRotated(90, 0, 1, 0);						
	// Rotate the wheel about the x-axis (Note that x-axis is now pointing 
	// out of the screen)
	glRotated(wheelSpeed, 1, 0, 0);
	gluCylinder(spoke, spokeRadius, spokeRadius, radius, SLICES, STACKS);

	glPushMatrix();
	// Flip to draw the second half of the spokes
	glRotated(180, 0, 1, 0);
	gluCylinder(spoke, spokeRadius, spokeRadius, radius, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	// Rotate about x-axis to turn z-axis 60 degrees counter clockwise
	glRotated(60, 1, 0, 0);						
	gluCylinder(spoke, spokeRadius, spokeRadius, radius, SLICES, STACKS);
	glRotated(180, 0, 1, 0);
	gluCylinder(spoke, spokeRadius, spokeRadius, radius, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	// Rotate about x-axis to turn z-axis 60 degrees clockwise
	glRotated(-60, 1, 0, 0);					
	gluCylinder(spoke, spokeRadius, spokeRadius, radius, SLICES, STACKS);
	glRotated(180, 0, 1, 0);
	gluCylinder(spoke, spokeRadius, spokeRadius, radius, SLICES, STACKS);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}


void Wheel::setRoll(double speed) {
	// Setting wheelSpeed to equal value of steering from the Vehicle class,
	// which is passed in when this function is called. This is updated every
	// time the vehicle moves.
	wheelSpeed = speed + wheelSpeed;
}
