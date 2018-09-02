
#include <math.h>

#include "MyVehicle.h"

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

MyVehicle::MyVehicle() {
};

MyVehicle::MyVehicle(double x_, double y_, double z_) {
	x = x_;
	y = y_;
	z = z_;
};

MyVehicle::~MyVehicle() {
};

void MyVehicle::draw() {

	//move to the vehicle's local frame of reference
	glPushMatrix();
	positionInGL();

	//all the local drawing code

	//draw main body of vehicle
	RectPrism mainBody(0, 0, 0, 0, 20, 10, 6);
	mainBody.draw();

	//draw top section
	TrapPrism topSection(3, 6, 0, 0, 14, 7, 10, 5, 3);
	topSection.draw();
	
	//draw base of front section
	RectPrism frontBase(13.5, 0, 0, 0, 7, 10, 4);
	frontBase.draw();

	//draw top of front section
	TriPrism frontTop(13.5, 4, 0, 0, 7, sqrt(53), 10, atan(2 / 7));
	frontTop.draw();

	//draw spoiler
	TriPrism spoiler(-9, 6, 0, 0, 2, sqrt(5), 10, atan(1 / 2));
	spoiler.draw();

	//move back to global frame of reference
	glPopMatrix();

};
