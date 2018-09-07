//Same design as ModelVehicle, using vector of ShapeInits

#include <math.h>

#include "Car.h"

#include "RectPrism.h"
#include "TriPrism.h"
#include "TrapPrism.h"
#include "Cylinder.h"
#include "Wheel.h"

#include "Messages.hpp"

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

Car::Car() {

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
	double frontInnerRadius = 3;
	double backInnerRadius = 7;
	double thickness = 1;
	double distToWheelsX = (length / 2) - frontRadius;
	double distToWheelsZ = (width / 2) + (thickness / 2);

	// Roof dimensions
	double bottomLength = 20;
	double topLength = 10;
	double roofHeight = 5;
	double roofOffset = 4;

	// Spoiler dimensions
	double spoilerSideLength = 2;
	double spoilerBaseLength = 4;
	double spoilerTheta = 3.14 / 3;
	double distToSpoiler = (length / 2) - (spoilerBaseLength / 2);

	vehicleModel.remoteID = 0;	//set ID to 0

	// Main body of vehicle
	ShapeParameter::RectangularParameters mainBodyParams{ length, width, height };
	ShapeInit mainBody;
	mainBody.type = RECTANGULAR_PRISM;
	mainBody.params.rect = mainBodyParams;
	mainBody.xyz[0] = 0;
	mainBody.xyz[1] = frontRadius;
	mainBody.xyz[2] = 0;
	mainBody.rotation = 0;
	mainBody.rgb[0] = 1;
	mainBody.rgb[1] = 0;
	mainBody.rgb[2] = 0.5;
	vehicleModel.shapes.push_back(mainBody);

	// Roof of vehicle
	ShapeParameter::TrapezoidalParameters roofParams{ bottomLength, topLength, roofHeight, roofOffset, width };
	ShapeInit roof;
	roof.type = TRAPEZOIDAL_PRISM;
	roof.params.trap = roofParams;
	roof.xyz[0] = 0;
	roof.xyz[1] = frontRadius + height;
	roof.xyz[2] = 0;
	roof.rotation = 0;
	roof.rgb[0] = 1;
	roof.rgb[1] = 0;
	roof.rgb[2] = 1;
	vehicleModel.shapes.push_back(roof);

	// Spoiler
	ShapeParameter::TriangularParameters spoilerParams{ spoilerBaseLength, spoilerSideLength, spoilerTheta, width };
	ShapeInit spoiler;
	spoiler.type = TRIANGULAR_PRISM;
	spoiler.params.tri = spoilerParams;
	spoiler.xyz[0] = -distToSpoiler;
	spoiler.xyz[1] = frontRadius + height;
	spoiler.xyz[2] = 0;
	spoiler.rotation = 0;
	spoiler.rgb[0] = 1;
	spoiler.rgb[1] = 0;
	spoiler.rgb[2] = 0;
	vehicleModel.shapes.push_back(spoiler);

	// Will come back to do the wheels, need to fix Wheel.h and Wheel.cpp first
	// Front wheels 
	Wheel frontRight(x + distToWheelsX, y, z + distToWheelsZ, 0, frontRadius, frontInnerRadius, thickness);
	frontRight.draw();
	Wheel frontLeft(x + distToWheelsX, y, z - distToWheelsZ, 0, frontRadius, frontInnerRadius, thickness);
	frontLeft.draw();

	// Back wheels 
	Wheel backRight(x - distToWheelsX, y, z + distToWheelsZ, 0, backRadius, backInnerRadius, thickness);
	backRight.draw();
	Wheel backLeft(x - distToWheelsX, y, z - distToWheelsZ, 0, backRadius, backInnerRadius, thickness);
	backLeft.draw();
};

Car::Car(VehicleModel vehicleModel_) {
};

Car::~Car() {
};

void Car::draw() {

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
	double frontInnerRadius = 3;
	double backInnerRadius = 7;
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
	//glPushMatrix();
	//positionInGL();

	vm.remoteID = 0;

	// Main body of vehicle
	RectPrism mainBody(x, y + frontRadius, z, rotation, length, width, height);
	mainBody.setColor(1, 0, 0.5);		//set color to pink
	mainBody.draw();

	ShapeParameter mainBodyParams{ length, width, height };
	float mainBodyPosition[3] = { x, y + frontRadius, z };
	float mainBodyColor[3] = { 1, 0 , 0.5 };	//set to pink

	ShapeInit mainBody = { RECTANGULAR_PRISM, mainBodyParams, *mainBodyPosition, rotation, *mainBodyColor };
	


	//Roof of vehicle
	TrapPrism roof(x, y + frontRadius + height, z, rotation, bottomLength, topLength, width, roofHeight, roofOffset);
	roof.setColor(1, 0, 1);				//set color to purple
	roof.draw();

	// Front wheels 
	Wheel frontRight(x + distToWheelsX, y, z + distToWheelsZ, 0, frontRadius, frontInnerRadius, thickness);
	frontRight.draw();

	Wheel frontLeft(x + distToWheelsX, y, z - distToWheelsZ, 0, frontRadius, frontInnerRadius, thickness);
	frontLeft.draw();

	// Back wheels 
	Wheel backRight(x - distToWheelsX, y, z + distToWheelsZ, 0, backRadius, backInnerRadius, thickness);
	backRight.draw();
	Wheel backLeft(x - distToWheelsX, y, z - distToWheelsZ, 0, backRadius, backInnerRadius, thickness);
	backLeft.draw();

	//Spoiler
	TriPrism spoiler(x - distToSpoiler, y + frontRadius + height, z, rotation, spoilerBaseLength, spoilerSideLength, width, spoilerTheta);
	spoiler.setColor(1, 0, 0);			//set colour to red
	spoiler.draw();

	//move back to global frame of reference
	glPopMatrix();

};