#include <math.h>

#include "ModelVehicle.h"

#include "RectPrism.h"
#include "TriPrism.h"
#include "TrapPrism.h"
#include "Cylinder.h"

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

ModelVehicle::ModelVehicle() {
};

ModelVehicle::ModelVehicle(double x_, double y_, double z_, double rotation_) {
	// Rotation variable was added so user can input required rotation when constructing this object
	x = x_;
	y = y_;
	z = z_;
	rotation = rotation_;
};

ModelVehicle::~ModelVehicle() {
};

void ModelVehicle::draw() {

	// Variables that dictate the dimensions of the car 
	// (note given dimensions have been multiplied by 10 for better visualisation)

	// Chasis dimensions:
	double length = 30;
	double width  = 20;
	double height = 10;
	double rotation = 0; // This needs to be here in order for rotation to work

	// Wheel dimensions:
	double frontRadius = 4;
	double backRadius = 8;
	double inRadius = 0;
	double thickness = 1;


	// Move to the vehicle's local frame of reference
	glPushMatrix();
	positionInGL();

	// Main body of vehicle
	RectPrism mainBody(x, y+4, z, rotation, length, width, height);
	mainBody.draw();

	// Front wheels 
	// Note that the right wheel must be rotated 180 degrees around the y axis for it to be in 
	// the required orientation.
	Cylinder frontRight(x + 11, y + 4, z + 11, rotation+180, frontRadius, inRadius, thickness);
	frontRight.draw();
	Cylinder frontLeft(x + 11, y + 4, z - 11, rotation, frontRadius, inRadius, thickness);
	frontLeft.draw();

	// Back wheels 
	Cylinder backRight(x - 11, y + 8, z + 11, rotation + 180, backRadius, inRadius, thickness);
	backRight.draw();
	Cylinder backLeft(x - 11, y + 8, z - 11, rotation, backRadius, inRadius, thickness);
	backLeft.draw();

	//move back to global frame of reference
	glPopMatrix();

};