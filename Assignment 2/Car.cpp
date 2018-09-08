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
	// (note given dimensions have been multiplied for better visualisation)

	// Chasis dimensions:
	double length = 30 * 0.5;
	double width = 20 * 0.5;
	double height = 10 * 0.5;
	double rotation = 0; // This needs to be here in order for rotation to work

	// Wheel dimensions:
	double frontRadius = 4 * 0.5;
	double backRadius = 8 * 0.5;
	double frontInnerRadius = 3 * 0.5;
	double backInnerRadius = 7 * 0.5;
	double thickness = 1 * 0.5;
	double distToWheelsX = (length / 2) - frontRadius;
	double distToWheelsZ = (width / 2) + (thickness / 2);

	// Roof dimensions
	double bottomLength = 20 * 0.5;
	double topLength = 10 * 0.5;
	double roofHeight = 5 * 0.5;
	double roofOffset = 4 * 0.5;

	// Spoiler dimensions
	double spoilerSideLength = 2 * 0.5;
	double spoilerBaseLength = 4 * 0.5;
	double spoilerTheta = 3.14 / 3;
	double distToSpoiler = (length / 2) - (spoilerBaseLength / 2);

	vm.remoteID = 0;	//set ID to 0

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
	vm.shapes.push_back(mainBody);

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
	vm.shapes.push_back(roof);

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
	vm.shapes.push_back(spoiler);

	/*
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
	*/

	shapeInitToShapes();
};

Car::Car(VehicleModel vehicleModel_) {
};

Car::~Car() {
}
VehicleModel Car::getVehicleModel() {
	return vm;
};

void Car::draw() {

	std::vector<Shape *>::iterator it;

	glPushMatrix();
	positionInGL();

	for (it = shapes.begin(); it != shapes.end(); it++) {
		(*it)->draw();

	}

	glPopMatrix();

};

void Car::shapeInitToShapes() {
	//this function converts ShapesInit vector into a Shapes vector so that the vehicle can be drawn

	for (int it = 0; it < vm.shapes.size(); it++) { 
		//iterate through the ShapesInit vector

		switch (vm.shapes[it].type) {
		case RECTANGULAR_PRISM: {
			RectPrism* rect = new RectPrism(vm.shapes[it].params.rect.xlen, vm.shapes[it].params.rect.ylen, vm.shapes[it].params.rect.zlen);
			rect->setPosition(vm.shapes[it].xyz[0], vm.shapes[it].xyz[1], vm.shapes[it].xyz[2]);
			rect->setRotation(vm.shapes[it].rotation);
			rect->setColor(vm.shapes[it].rgb[0], vm.shapes[it].rgb[1], vm.shapes[it].rgb[2]);
			addShape(rect);
			break;
		}
		case TRIANGULAR_PRISM: {
			TriPrism* tri = new TriPrism(vm.shapes[it].params.tri.alen, vm.shapes[it].params.tri.blen, vm.shapes[it].params.tri.depth, vm.shapes[it].params.tri.angle);
			tri->setPosition(vm.shapes[it].xyz[0], vm.shapes[it].xyz[1], vm.shapes[it].xyz[2]);
			tri->setRotation(vm.shapes[it].rotation);
			tri->setColor(vm.shapes[it].rgb[0], vm.shapes[it].rgb[1], vm.shapes[it].rgb[2]);
			addShape(tri);
			break;
		}
		case TRAPEZOIDAL_PRISM: {
			TrapPrism* trap = new TrapPrism(vm.shapes[it].params.trap.alen, vm.shapes[it].params.trap.blen, vm.shapes[it].params.trap.depth, vm.shapes[it].params.trap.height, vm.shapes[it].params.trap.aoff);
			trap->setPosition(vm.shapes[it].xyz[0], vm.shapes[it].xyz[1], vm.shapes[it].xyz[2]);
			trap->setRotation(vm.shapes[it].rotation);
			trap->setColor(vm.shapes[it].rgb[0], vm.shapes[it].rgb[1], vm.shapes[it].rgb[2]);
			addShape(trap);
			break;
		}
		case CYLINDER: {

			//should be stuff about wheels and checking if wheel
			//addShape(cyl);
			break;
		}
		default: {
			break;
		}
		}
	}

};