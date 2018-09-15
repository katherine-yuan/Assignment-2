// Katherine Yuan z5161528 2018/08/29

#include <math.h>

#include "Shape.hpp"
#include "TriPrism.h"

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

TriPrism::TriPrism() {
	aLength = 0;
	bLength = 0;
	depth = 0;
	theta = 0;

	// Variables that assist with the draw function
	double aLengthHalf = 0;
	double depthHalf   = 0;
	double topLeftCornerX = 0;
	double topLeftCornerY = 0;
}

TriPrism::TriPrism(double aLength_, double bLength_, double depth_, double theta_) {
	aLength = aLength_;
	bLength = bLength_;
	depth = depth_;
	theta = theta_;

	// Variables that assist with the draw function
	double aLengthHalf = aLength / 2;
	double depthHalf = depth / 2;
	double topLeftCornerX = aLengthHalf - bLength * cos(theta);
	double topLeftCornerY = bLength * sin(theta);
};

TriPrism::~TriPrism() {
};

void TriPrism::draw() {
	glPushMatrix();
	positionInGL();
	setColorInGL();

	// DRAWING QUADS
	glBegin(GL_QUADS);

	// Base of the triangular prism
	glVertex3f(aLengthHalf, 0 , depthHalf);		//Bottom far left corner
	glVertex3f(-aLengthHalf, 0, depthHalf);		//Far right corner
	glVertex3f(-aLengthHalf, 0, -depthHalf);	//Front right corner
	glVertex3f(aLengthHalf, 0, -depthHalf);		//Bottom front left corner

	// Left side of the triangular prism
	glVertex3f(topLeftCornerX, topLeftCornerY, -depthHalf);		//Top front left corner
	glVertex3f(aLengthHalf, 0, -depthHalf);						//Bottom front left corner
	glVertex3f(aLengthHalf, 0, depthHalf);						//Bottom far left corner
	glVertex3f(topLeftCornerX, topLeftCornerY, depthHalf);		//Top far left corner

	// Top side of the triangular prism
	glVertex3f(topLeftCornerX, topLeftCornerY, -depthHalf);		//Top front left corner
	glVertex3f(-aLengthHalf, 0, -depthHalf);					//Front right corner
	glVertex3f(-aLengthHalf, 0, depthHalf);						//Far right corner
	glVertex3f(topLeftCornerX, topLeftCornerY, depthHalf);		//Top far left corner

	glEnd();

	// DRAWING TRIANGLES 
	glBegin(GL_TRIANGLES);

	// Front of triangular prism
	glVertex3f(aLengthHalf, 0, -depthHalf);						//Bottom front left corner
	glVertex3f(topLeftCornerX, topLeftCornerY, -depthHalf);		//Top front left corner
	glVertex3f(-aLengthHalf, 0, -depthHalf);					//Front right corner

	// Back of triangular prism
	glVertex3f(aLengthHalf, 0, depthHalf);						//Bottom far left corner
	glVertex3f(topLeftCornerX, topLeftCornerY, depthHalf);		//Top far left corner
	glVertex3f(-aLengthHalf, 0, depthHalf);						//Far right corner

	glEnd();
	
	glPopMatrix();
}

// Getters
double TriPrism::getALength() {
	return aLength;
};

double TriPrism::getBLength() {
	return bLength;
};

double TriPrism::getDepth() {
	return depth;
};

double TriPrism::getTheta() {
	return theta;
};

// Setters
void TriPrism::setALength(double aLength_) {
	aLength = aLength_;
};

void TriPrism::setBLength(double bLength_) {
	bLength = bLength_;
};

void TriPrism::setDepth(double depth_) {
	depth = depth_;
}

void TriPrism::setTheta(double theta_) {
	theta = theta_;
};
