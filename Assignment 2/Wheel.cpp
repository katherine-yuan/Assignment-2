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

	wheelSpeed = 0;
	isSteering = 0;
	isRolling = 0;
}

Wheel::Wheel(double radius_, double innerRadius_, double length_) {
	radius = radius_;
	innerRadius = innerRadius_;
	length = length_;

	x = y = z = 0.0;
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

Wheel::Wheel(double radius_, double innerRadius_, double length_, double wheelSpeed_, bool isSteering_, bool isRolling_) {
	radius = radius_;
	innerRadius = innerRadius_;
	length = length_;

	wheelSpeed = wheelSpeed_;
	isSteering = isSteering_;
	isRolling = isRolling_;

}

Wheel::~Wheel() {}

bool Wheel::Steering() {
	return isSteering;
}

bool Wheel::Rolling() {
	return isRolling;
}

void Wheel::draw() {

	glPushMatrix();
	positionInGL();
	setColorInGL();

	// Adjust to centre of base
	glTranslated(0, radius, -length / 2);

	// Wheel rim
	glPushMatrix();
	// Create new cylinder object
	GLUquadricObj *wheelRim = gluNewQuadric();

	// Draw hollow cylinder body
	gluCylinder(wheelRim, radius, radius, length, SLICES, STACKS);
	// Draw caps using gluDisk
	gluDisk(wheelRim, innerRadius, radius, SLICES, STACKS);
	glTranslated(0, 0, length);			//moves to draw the back disk
	gluDisk(wheelRim, innerRadius, radius, SLICES, STACKS);

	glPopMatrix(); //at this point drawing origin is at the centre of the base of the wheel (where it touches the ground)

	// Spokes
	double spokeRadius = radius / 10;
	
	//ensures that the spoke width is not wider than the width of the wheel rim
	if (spokeRadius > length / 2) {
		spokeRadius = length / 2;
	}
	glPushMatrix();
	glTranslated(0, 0, length / 2);				//move to the centre of the wheel
	glRotated(90, 0, 1, 0);						//rotate about y-axis to move z-axis to original x-axis direction
	
	//rotate wheel about x
	glRotated(wheelSpeed, 1, 0, 0);
												//note that x-axis is now pointing out of the screen
	gluCylinder(gluNewQuadric(), spokeRadius, spokeRadius, radius, SLICES, STACKS);

	glPushMatrix();
	glRotated(180, 0, 1, 0);					//flip to draw second half of spoke
	gluCylinder(gluNewQuadric(), spokeRadius, spokeRadius, radius, SLICES, STACKS);
	glPopMatrix();

	
	glPushMatrix();
	glRotated(60, 1, 0, 0);						//rotate about x-axis to turn z-axis 60 degrees counter clockwise
	gluCylinder(gluNewQuadric(), spokeRadius, spokeRadius, radius, SLICES, STACKS);
	glRotated(180, 0, 1, 0);
	gluCylinder(gluNewQuadric(), spokeRadius, spokeRadius, radius, SLICES, STACKS);
	glPopMatrix();

	glPushMatrix();
	glRotated(-60, 1, 0, 0);					//rotate about x-axis to turn z-axis 60 degrees clockwise
	gluCylinder(gluNewQuadric(), spokeRadius, spokeRadius, radius, SLICES, STACKS);
	glRotated(180, 0, 1, 0);
	gluCylinder(gluNewQuadric(), spokeRadius, spokeRadius, radius, SLICES, STACKS);
	glPopMatrix();
	
	glPopMatrix();

	glPopMatrix();
}

// This should be set to the value of steering from the Vehicle class. 
// It should be called and updated every time the vehicle moves
void Wheel::setRoll(double speed) {
	wheelSpeed = speed + wheelSpeed;
}

