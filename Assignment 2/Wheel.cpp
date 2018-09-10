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

	//NEW WHEEL DRAWING TECHNIQUE
	glPushMatrix();
	positionInGL();
	setColorInGL();


	// Adjust to centre of base - should this be before or after
	glTranslated(0, radius, -length / 2);

	// Rotate axis accordingly
	if (isSteering) {
		glRotatef(steeringAngle, 0, 1, 0);
	}
	if (isRolling) {
		glTranslatef(0, radius, 0);
		glRotatef(-wheelSpeed, 0, 0, 1);
		glTranslatef(0, -radius, 0);
	}


	// Wheel rim
	glPushMatrix();
	// Create new cylinder object
	GLUquadricObj *wheelRim = gluNewQuadric();
	// Draw hollow cylinder body
	gluCylinder(wheelRim, radius, radius, length, SLICES, STACKS);

	// Draw caps using gluDisk - maybe don't need to make cap1 object, just attatch to wheel rim pointer
	GLUquadricObj *cap1 = gluNewQuadric();
	gluDisk(cap1, innerRadius, radius, SLICES, STACKS);
	glPushMatrix();
	glTranslated(0, 0, length);			//moves to draw the back disk
	GLUquadricObj *cap2 = gluNewQuadric();
	gluDisk(cap2, innerRadius, radius, SLICES, STACKS);

	glPopMatrix(); //at this point drawing origin is at the centre of the base of the wheel (where it touches the ground)

	// Spokes
	double spokeRadius = radius / 10;

	//ensures that the spoke width is not wider than the width of the wheel rim
	if (spokeRadius > length / 2) {
		spokeRadius = length / 2; 
	}

	glPushMatrix();
	glTranslated(0,  0, length / 2);			//move to the centre of the wheel
	glRotated(90, 0, 1, 0);						//rotate about y-axis to move z-axis to original x-axis direction
												//note that x-axis is now pointing out of the screen
	//GLUquadricObj *spoke1 = gluNewQuadric();

	gluCylinder(gluNewQuadric(), spokeRadius, spokeRadius, radius, SLICES, STACKS);

	glPushMatrix();
	glRotated(180, 0, 1, 0);					//flip to draw second half of spoke
	gluCylinder(gluNewQuadric(), spokeRadius, spokeRadius, radius, SLICES, STACKS);
	glPopMatrix();

	////GLUquadricObj *spoke2 = gluNewQuadric();

	//glPushMatrix();
	//glRotated(60, 1, 0, 0);						//rotate about x-axis to turn z-axis 60 degrees counter clockwise
	//gluCylinder(gluNewQuadric(), spokeRadius, spokeRadius, radius, SLICES, STACKS);
	//glRotated(180, 0, 1, 0);					
	//gluCylinder(gluNewQuadric(), spokeRadius, spokeRadius, radius, SLICES, STACKS);
	//glPopMatrix();

	////GLUquadricObj *spoke3 = gluNewQuadric();

	//glPushMatrix();
	//glRotated(-60, 1, 0, 0);					//rotate about x-axis to turn z-axis 60 degrees clockwise
	//gluCylinder(gluNewQuadric(), spokeRadius, spokeRadius, radius, SLICES, STACKS);
	//glRotated(180, 0, 1, 0);
	//gluCylinder(gluNewQuadric(), spokeRadius, spokeRadius, radius, SLICES, STACKS);
	//glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

void Wheel::setSteer(double steering) {
	steeringAngle = steering;
}

void Wheel::setRoll(double roll_) {
	wheelSpeed = roll_; //+ wheelSpeed;
}

void Wheel::rotateY() {
	glRotatef(steeringAngle, 0, 1, 0);
}

double Wheel::getRadius() {
	return radius;
}
double Wheel::getLength() {
	return length;
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
