// MTRN2500 Semester 2 2018
// Group 80
// Katherine and Rebecca 
// z5161528  and z5115440

// Style notes: Comments above the line they refer to. All lines less than 80
// characters to allow for double screen use. Comments begin with a capital 
// and a space is always left between the "//" and the start of the line.

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

#define WHEEL_RADIUS_RATIO 0.8

Car::Car() {
	// Variables that dictate the dimensions of the car (note that given
	// dimensions have been multiplied by 0.1 to better fit the screen size).
	// Dimensions can be multiplied by other calues for better visualisation

	// Main Body dimensions:
	double length = 30 * 0.1;
	double width = 20 * 0.1;
	double height = 10 * 0.1;
	double rotation = 0; 

	// Wheel dimensions:
	double frontRadius = 4 * 0.1;
	double backRadius = 8 * 0.1;
	double thickness = 1 * 0.1;
	double distToWheelsX = (length / 2) - frontRadius;
	double distToWheelsZ = (width / 2) + (thickness / 2);

	// This sets which wheels are meant to roll and steer
	bool frontRoll = 1;
	bool frontSteer = 1;
	bool backRoll = 1;
	bool backSteer = 0;

	// Roof dimensions
	double bottomLength = 20 * 0.1;
	double topLength = 10 * 0.1;
	double roofHeight = 5 * 0.1;
	double roofOffset = 4 * 0.1;

	// Spoiler dimensions
	double spoilerSideLength = 3 * 0.1;
	double spoilerBaseLength = 4 * 0.1;
	double spoilerTheta = 25;	//In degrees
	double distToSpoiler = (length / 2) - (spoilerBaseLength / 2);

	// Set vehicle ID to 0
	vm.remoteID = 0;	

	// Main body of vehicle
	ShapeParameter::RectangularParameters mainBodyParams{ length, height, width };
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
	ShapeParameter::TrapezoidalParameters roofParams{ bottomLength, topLength,
												roofHeight, roofOffset, width };
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
	ShapeParameter::TriangularParameters spoilerParams{ spoilerBaseLength, 
									spoilerSideLength, spoilerTheta, width };
	ShapeInit spoiler;
	spoiler.type = TRIANGULAR_PRISM;
	spoiler.params.tri = spoilerParams;
	spoiler.xyz[0] = -distToSpoiler;
	spoiler.xyz[1] = frontRadius + height;
	spoiler.xyz[2] = 0;
	spoiler.rotation = 0;
	spoiler.rgb[0] = 0.5;
	spoiler.rgb[1] = 0;
	spoiler.rgb[2] = 1;
	vm.shapes.push_back(spoiler);

	// WHEELS
	// Front Wheels
	ShapeParameter::CylinderParameters frontWheelParams{ frontRadius,
									thickness, frontRoll, frontSteer };
	ShapeInit rightFront;
	rightFront.type = CYLINDER;
	rightFront.params.cyl = frontWheelParams;
	rightFront.xyz[0] = distToWheelsX;
	rightFront.xyz[1] = 0;
	rightFront.xyz[2] = distToWheelsZ;
	rightFront.rotation = 0;
	rightFront.rgb[0] = 0.5;
	rightFront.rgb[1] = 0.5;
	rightFront.rgb[2] = 1;
	vm.shapes.push_back(rightFront);

	ShapeInit leftFront;
	leftFront.type = CYLINDER;
	leftFront.params.cyl = frontWheelParams;
	leftFront.xyz[0] = distToWheelsX;
	leftFront.xyz[1] = 0;
	leftFront.xyz[2] = -distToWheelsZ;
	leftFront.rotation = 0;
	leftFront.rgb[0] = 0.5;
	leftFront.rgb[1] = 0.5;
	leftFront.rgb[2] = 1;
	vm.shapes.push_back(leftFront);

	// Back Wheels
	ShapeParameter::CylinderParameters backWheelParams{ backRadius, thickness,
														backRoll, backSteer };
	ShapeInit rightBack;
	rightBack.type = CYLINDER;
	rightBack.params.cyl = backWheelParams;
	rightBack.xyz[0] = -distToWheelsX;
	rightBack.xyz[1] = 0;
	rightBack.xyz[2] = distToWheelsZ;
	rightBack.rotation = 0;
	rightBack.rgb[0] = 0.5;
	rightBack.rgb[1] = 0.5;
	rightBack.rgb[2] = 1;
	vm.shapes.push_back(rightBack);

	ShapeInit leftBack;
	leftBack.type = CYLINDER;
	leftBack.params.cyl = backWheelParams;
	leftBack.xyz[0] = -distToWheelsX;
	leftBack.xyz[1] = 0;
	leftBack.xyz[2] = -distToWheelsZ;
	leftBack.rotation = 0;
	leftBack.rgb[0] = 0.5;
	leftBack.rgb[1] = 0.5;
	leftBack.rgb[2] = 1;
	vm.shapes.push_back(leftBack);

	shapeInitToShapes();
};

Car::Car(VehicleModel vm_) {
	vm = vm_;

	shapeInitToShapes();
};

Car::~Car() {
};

VehicleModel Car::getVehicleModel() {
	return vm;
};

VehicleState Car::getVehicleState() {
	return vs;
}

// Define update since it is a virtual function in Vehicle.h
void Car::update(double dt) {
	speed = clamp(MAX_BACKWARD_SPEED_MPS, speed, MAX_FORWARD_SPEED_MPS);
	steering = clamp(MAX_LEFT_STEERING_DEGS, steering, MAX_RIGHT_STEERING_DEGS);

	// Update position by integrating the speed
	x += speed * dt * cos(rotation * PI / 180.0);
	z += speed * dt * sin(rotation * PI / 180.0);

	// Update heading
	rotation += dt * steering * speed;

	while (rotation > 360) rotation -= 360;
	while (rotation < 0) rotation += 360;

	if (fabs(speed) < .1)
		speed = 0;
	if (fabs(steering) < .1)
		steering = 0;
}

void Car::draw() {

	std::vector<Shape *>::iterator it;

	for (int i = 0; i < shapes.size(); i++) {
		// Iterate through each shape in the vector to draw each one
		glPushMatrix();
		positionInGL();

		// Create a wheel object pointer
		Wheel *wheelPtr = NULL;
		wheelPtr = dynamic_cast<Wheel*>(shapes[i]);

		// Check if the shape is a wheel
		if (wheelPtr != NULL) {
			// Check if the wheel should be steering
			if (wheelPtr->Steering()) {
				glPushMatrix();
				// Set the wheel to steer with the vehicle
				shapes[i]->setRotation(steering);
				glPopMatrix();
			}
			// Check if the wheel should be rolling
			if (wheelPtr->Rolling()) {
				glPushMatrix();
				// Set the wheel to roll respective to the wheels speed
				wheelPtr->setRoll(speed * 2);
				shapes[i]->draw();
				glPopMatrix();
			}
		}
		else {
			// Draw the shape normally
			shapes[i]->draw();
		}
		glPopMatrix();
	}
};

void Car::shapeInitToShapes() {
	// This function converts ShapesInit vector into a Shapes vector so that the
	// vehicle can be drawn.

	for (int it = 0; it < vm.shapes.size(); it++) {
		// Iterate through the ShapesInit vector
		switch (vm.shapes[it].type) {
		case RECTANGULAR_PRISM: {
			RectPrism* rect = new RectPrism(vm.shapes[it].params.rect.xlen,
				vm.shapes[it].params.rect.ylen, vm.shapes[it].params.rect.zlen);
			rect->setPosition(	vm.shapes[it].xyz[0], vm.shapes[it].xyz[1],
								vm.shapes[it].xyz[2]);
			rect->setRotation(vm.shapes[it].rotation);
			rect->setColor(	vm.shapes[it].rgb[0], vm.shapes[it].rgb[1],
							vm.shapes[it].rgb[2]);
			addShape(rect);
			break;
		}
		case TRIANGULAR_PRISM: {
			TriPrism* tri = new TriPrism(vm.shapes[it].params.tri.alen,
				vm.shapes[it].params.tri.blen, vm.shapes[it].params.tri.depth,
				vm.shapes[it].params.tri.angle * (PI / 180));
			tri->setPosition(	vm.shapes[it].xyz[0], vm.shapes[it].xyz[1],
								vm.shapes[it].xyz[2]);
			tri->setRotation(vm.shapes[it].rotation + 180);
			tri->setColor(	vm.shapes[it].rgb[0], vm.shapes[it].rgb[1],
							vm.shapes[it].rgb[2]);
			addShape(tri);
			break;
		}
		case TRAPEZOIDAL_PRISM: {
			TrapPrism* trap = new TrapPrism(vm.shapes[it].params.trap.alen,
				vm.shapes[it].params.trap.blen,
				vm.shapes[it].params.trap.depth,
				vm.shapes[it].params.trap.height, 
				vm.shapes[it].params.trap.aoff);
			trap->setPosition(	vm.shapes[it].xyz[0], vm.shapes[it].xyz[1],
								vm.shapes[it].xyz[2]);
			trap->setRotation(vm.shapes[it].rotation + 180);
			trap->setColor(	vm.shapes[it].rgb[0], vm.shapes[it].rgb[1],
							vm.shapes[it].rgb[2]);
			addShape(trap);
			break;
		}
		case CYLINDER: {
			// Check if the cylinder is a wheel
			if (vm.shapes[it].params.cyl.isRolling == true) {
				// If the cylinder is a wheel set steering and rotation
				Wheel* wheel = new Wheel(vm.shapes[it].params.cyl.radius, 
					vm.shapes[it].params.cyl.radius * WHEEL_RADIUS_RATIO,
					vm.shapes[it].params.cyl.depth, vs.speed,
					vm.shapes[it].params.cyl.isSteering,
					vm.shapes[it].params.cyl.isRolling);
				wheel->setPosition(	vm.shapes[it].xyz[0], vm.shapes[it].xyz[1],
									vm.shapes[it].xyz[2]);
				wheel->setRotation(vm.shapes[it].rotation);
				wheel->setColor(vm.shapes[it].rgb[0], vm.shapes[it].rgb[1],
								vm.shapes[it].rgb[2]);
				addShape(wheel);
				break;
			}
			else {
				// If the cylinder is not a wheel draw normally
				Cylinder* cyl = new Cylinder(vm.shapes[it].params.cyl.radius,
					vm.shapes[it].params.cyl.radius * WHEEL_RADIUS_RATIO,
					vm.shapes[it].params.cyl.depth);
				cyl->setPosition(	vm.shapes[it].xyz[0], vm.shapes[it].xyz[1],
									vm.shapes[it].xyz[2]);
				cyl->setRotation(vm.shapes[it].rotation);
				cyl->setColor(	vm.shapes[it].rgb[0], vm.shapes[it].rgb[1],
								vm.shapes[it].rgb[2]);
				addShape(cyl);
				break;
			}
		}
		default: {
			break;
		}
		}
	}
};
