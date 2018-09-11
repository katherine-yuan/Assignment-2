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

#define WHEEL_RADIUS_RATIO 0.8

Car::Car() {

	// Variables that dictate the dimensions of the car 
	// (note given dimensions have been multiplied for better visualisation)

	// Main Body dimensions:
	double length = 30 * 0.1;
	double width = 20 * 0.1;
	double height = 10 * 0.1;
	double rotation = 0; // This needs to be here in order for rotation to work

	// Wheel dimensions:
	double frontRadius = 4 * 0.1;
	double backRadius = 8 * 0.1;
	double thickness = 1 * 0.1;
	double distToWheelsX = (length / 2) - frontRadius;
	double distToWheelsZ = (width / 2) + (thickness / 2);
	
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
	double spoilerTheta = 25;	//given in degrees
	double distToSpoiler = (length / 2) - (spoilerBaseLength / 2);

	vm.remoteID = 0;	//set ID to 0

	// Main body of vehicle
	ShapeParameter::RectangularParameters mainBodyParams {length, height, width};
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
	ShapeParameter::TrapezoidalParameters roofParams {bottomLength, topLength, roofHeight, roofOffset, width};
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
	ShapeParameter::TriangularParameters spoilerParams {spoilerBaseLength, spoilerSideLength, spoilerTheta, width};
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

	// Wheels
	// Front Wheels
	ShapeParameter::CylinderParameters frontWheelParams {frontRadius, thickness, frontRoll, frontSteer};
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
	ShapeParameter::CylinderParameters backWheelParams {backRadius, thickness, backRoll, backSteer};
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


void Car::update(double dt) {
	speed = clamp(MAX_BACKWARD_SPEED_MPS, speed, MAX_FORWARD_SPEED_MPS);
	steering = clamp(MAX_LEFT_STEERING_DEGS, steering, MAX_RIGHT_STEERING_DEGS);

	// update position by integrating the speed
	x += speed * dt * cos(rotation * PI / 180.0);
	z += speed * dt * sin(rotation * PI / 180.0);

	// update heading
	rotation += dt * steering * speed;

	while (rotation > 360) rotation -= 360;
	while (rotation < 0) rotation += 360;

	
	//update wheels rolling
	if (wheelRotation > 2 * PI) {
		wheelRotation = 0;
	}
	if (wheelRotation < -2 * PI) {
		wheelRotation = 0;
	}
	wheelRotation = wheelRotation + speed * dt;

	if (fabs(speed) < .1)
		speed = 0;
	if (fabs(steering) < .1)
		steering = 0;

};


void Car::draw() {

	std::vector<Shape *>::iterator it;

	for (int i = 0; i < shapes.size(); i++) {

		glPushMatrix();
		positionInGL();
		
		Wheel *wheelPtr = NULL;
		wheelPtr = dynamic_cast<Wheel*>(shapes[i]);
		if (wheelPtr != NULL) {
			if (wheelPtr->Steering()) {
				glPushMatrix();
				shapes[i]->setRotation(steering);
				shapes[i]->draw();
				glPopMatrix();
			} else {
				shapes[i]->draw();
			}
		} else {
			shapes[i]->draw();
		}
		
		//shapes[i]->draw();
		glPopMatrix();

	}


	
	// Bec - was trying to make the wheel rotate in draw with little success
	//Wheel *wheelPtr = NULL;
	//for (vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++) {
	//	glPushMatrix();
	//	positionInGl();
	//	wheelPtr = dynamic_cast<Wheel*> (*it);
	//	if (wheelPtr->Steering()) {
	//		wheelPtr->setSteer(-steering); // is this the right variable
	//	}
	//	else {
	//		wheelPtr->setSteer(0);
	//	}
	//	if (wheelPtr->Rolling()) {
	//		wheelPtr->setRoll(//soeed*5)
	//	}
	//	(*it)->draw();
	//	glPopMatrix();
	//}

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
			TriPrism* tri = new TriPrism(vm.shapes[it].params.tri.alen, vm.shapes[it].params.tri.blen, vm.shapes[it].params.tri.depth, vm.shapes[it].params.tri.angle * (PI/180));
			tri->setPosition(vm.shapes[it].xyz[0], vm.shapes[it].xyz[1], vm.shapes[it].xyz[2]);
			tri->setRotation(vm.shapes[it].rotation + 180);
			tri->setColor(vm.shapes[it].rgb[0], vm.shapes[it].rgb[1], vm.shapes[it].rgb[2]);
			addShape(tri);
			break;
		}
		case TRAPEZOIDAL_PRISM: {
			TrapPrism* trap = new TrapPrism(vm.shapes[it].params.trap.alen, vm.shapes[it].params.trap.blen, vm.shapes[it].params.trap.depth, vm.shapes[it].params.trap.height, vm.shapes[it].params.trap.aoff);
			trap->setPosition(vm.shapes[it].xyz[0], vm.shapes[it].xyz[1], vm.shapes[it].xyz[2]);
			trap->setRotation(vm.shapes[it].rotation + 180);
			trap->setColor(vm.shapes[it].rgb[0], vm.shapes[it].rgb[1], vm.shapes[it].rgb[2]);
			addShape(trap);
			break;
		}
		case CYLINDER: {

			//check if cylinder is a wheel
			if (vm.shapes[it].params.cyl.isRolling == true) {

				Wheel* wheel = new Wheel(vm.shapes[it].params.cyl.radius, vm.shapes[it].params.cyl.radius * WHEEL_RADIUS_RATIO, vm.shapes[it].params.cyl.depth, 0/*wheel speed*/, vm.shapes[it].params.cyl.isSteering, vm.shapes[it].params.cyl.isRolling);
				wheel->setPosition(vm.shapes[it].xyz[0], vm.shapes[it].xyz[1], vm.shapes[it].xyz[2]);
				wheel->setRotation(vm.shapes[it].rotation);
				wheel->setColor(vm.shapes[it].rgb[0], vm.shapes[it].rgb[1], vm.shapes[it].rgb[2]);
				addShape(wheel);
				break;
				
			} 
			else 
			{
				Cylinder* cyl = new Cylinder(vm.shapes[it].params.cyl.radius, vm.shapes[it].params.cyl.radius * WHEEL_RADIUS_RATIO, vm.shapes[it].params.cyl.depth);
				cyl->setPosition(vm.shapes[it].xyz[0], vm.shapes[it].xyz[1], vm.shapes[it].xyz[2]);
				cyl->setRotation(vm.shapes[it].rotation);
				cyl->setColor(vm.shapes[it].rgb[0], vm.shapes[it].rgb[1], vm.shapes[it].rgb[2]);
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
