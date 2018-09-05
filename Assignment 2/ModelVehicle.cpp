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
	double width = 20;
	double height = 10;
	double rotation = 0; // This needs to be here in order for rotation to work

	// Wheel dimensions:
	double frontRadius = 4;
	double backRadius = 8;
	double inRadius = 0;
	double thickness = 1;
	double distToWheelsX = (length / 2) - frontRadius;
	double distToWheelsZ = (width / 2) + (thickness / 2);

	//Roof dimensions
	double bottomLength = 20;
	double topLength = 10;
	double roofHeight = 5;
	double roofOffset = 4;

	//Spoiler dimensions
	double spoilerSideLength = 2;
	double spoilerBaseLength = 4;
	double spoilerTheta = 3.14 / 3;
	double distToSpoiler = (length / 2) - (spoilerBaseLength / 2);


	// Move to the vehicle's local frame of reference
	glPushMatrix();
	positionInGL();

	// Main body of vehicle
	RectPrism mainBody(x, y + frontRadius, z, rotation, length, width, height);
	mainBody.setColor(1, 0, 0.5);		//set color to pink
	mainBody.draw();

	//Roof of vehicle
	TrapPrism roof(x, y + frontRadius + height, z, rotation, bottomLength, topLength, width, roofHeight, roofOffset);
	roof.setColor(1, 0, 1);				//set color to purple
	roof.draw();
	
	// Front wheels 
	// Note that the right wheel must be rotated 180 degrees around the y axis for it to be in 
	// the required orientation.
	Cylinder frontRight(x + distToWheelsX, y, z + distToWheelsZ, rotation + 180, frontRadius, inRadius, thickness);
	frontRight.setColor(0, 0.5, 1); // set colour to light blue
	frontRight.draw();
	
	Cylinder frontLeft(x + distToWheelsX, y, z - distToWheelsZ, rotation, frontRadius, inRadius, thickness);
	frontLeft.setColor(0, 0.5, 1); // set colour to light blue
	frontLeft.draw();

	// Back wheels 
	Cylinder backRight(x - distToWheelsX, y, z + distToWheelsZ, rotation + 180, backRadius, inRadius, thickness);
	backRight.setColor(0, 0.5, 1); // set colour to light blue
	backRight.draw();
	Cylinder backLeft(x - distToWheelsX, y, z - distToWheelsZ, rotation, backRadius, inRadius, thickness);
	backLeft.setColor(0, 0.5, 1); // set colour to light blue
	backLeft.draw();

	//Spoiler
	TriPrism spoiler(x - distToSpoiler, y + frontRadius + height, z, rotation, spoilerBaseLength, spoilerSideLength, width, spoilerTheta);
	spoiler.setColor(1, 0, 0);							//set colour to red
	spoiler.draw();

	//move back to global frame of reference
	glPopMatrix();

};