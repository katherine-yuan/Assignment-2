
#include "MyVehicle.h"

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

MyVehicle::~MyVehicle() {
};

void MyVehicle::draw() {

	//move t the vehicle's local frame of reference
	glPushMatrix();
	positionInGL();

	//all the local drawing code

	//move back to global frame of reference
	glPopMatrix();

};
