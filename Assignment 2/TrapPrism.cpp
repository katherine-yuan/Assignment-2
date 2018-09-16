// Group 80
// Katherine Yuan z5161528 2018/08/29

#include "Shape.hpp"
#include "TrapPrism.h"

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

TrapPrism::TrapPrism() {
	// Default constructor for this shape
	aLength = 0;
	bLength = 0;
	depth   = 0;
	height  = 0;
	offset  = 0;

	// Variables to assist with drawing the trapezium
	aLengthHalf = 0;
	depthHalf   = 0;
	topLeftCornerX  = 0;
	topRightCornerX = 0;
}

TrapPrism::TrapPrism(double aLength_, double bLength_, double depth_, double height_, double offset_) {
	aLength = aLength_;
	bLength = bLength_;
	depth  = depth_;
	height = height_;
	offset = offset_;

	// Variables to assist with drawing the trapezium
	aLengthHalf = aLength / 2;
	depthHalf = depth / 2;
	topLeftCornerX = aLengthHalf - offset;
	topRightCornerX = aLengthHalf - offset - bLength;
};

TrapPrism::~TrapPrism() {
};

void TrapPrism::draw() {
	glPushMatrix();
	positionInGL();		
	setColorInGL();

	glBegin(GL_QUADS);

	// Base of the trapezoidal prism
	glVertex3f(aLengthHalf, 0, depthHalf);		//Bottom far left corner
	glVertex3f(-aLengthHalf, 0, depthHalf);		//Bottom far right corner
	glVertex3f(-aLengthHalf, 0, -depthHalf);	//Bottom front right corner
	glVertex3f(aLengthHalf, 0, -depthHalf);		//Bottom front left corner

	// Top side of the trapezoidal prism
	glVertex3f(topLeftCornerX, height, depthHalf);			//Top far left corner
	glVertex3f(topRightCornerX, height, depthHalf);			//Top far right corner
	glVertex3f(topRightCornerX, height, -depthHalf);		//Top front right corner
	glVertex3f(topLeftCornerX, height, -depthHalf);			//Top front left corner

	// Front side of trapezoidal prism
	glVertex3f(aLengthHalf, 0, -depthHalf);					//Bottom front left corner
	glVertex3f(-aLengthHalf, 0, -depthHalf);				//Bottom front right corner
	glVertex3f(topRightCornerX, height, -depthHalf);		//Top front right corner
	glVertex3f(topLeftCornerX, height, -depthHalf);			//Top front left corner

	// Far(back) side of trapezoidal prism
	glVertex3f(aLengthHalf, 0, depthHalf);					//Bottom far left corner
	glVertex3f(-aLengthHalf, 0, depthHalf);					//Bottom far right corner
	glVertex3f(topRightCornerX, height, depthHalf);			//Top far right corner
	glVertex3f(topLeftCornerX, height, depthHalf);			//Top far left corner

	// Left side of trapezoidal prism
	glVertex3f(aLengthHalf, 0, -depthHalf);					//Bottom front left corner
	glVertex3f(aLengthHalf, 0, depthHalf);					//Bottom far left corner
	glVertex3f(topLeftCornerX, height, depthHalf);			//Top far left corner
	glVertex3f(topLeftCornerX, height, -depthHalf);			//Top front left corner

	// Right side of trapezoidal prism
	glVertex3f(-aLengthHalf, 0, -depthHalf);				//Bottom front right corner
	glVertex3f(-aLengthHalf, 0, depthHalf);					//Bottom far right corner
	glVertex3f(topRightCornerX, height, depthHalf);			//Top far right corner
	glVertex3f(topRightCornerX, height, -depthHalf);		//Top front right corner

	glEnd();

	glPopMatrix();

}

// Getters 
double TrapPrism::getALength() {
	return aLength;
};

double TrapPrism::getBLength() {
	return bLength;
};

double TrapPrism::getDepth() {
	return depth;
};

double TrapPrism::getHeight() {
	return height;
};

double TrapPrism::getOffset() {
	return offset;
};

// Setters
void TrapPrism::setALength(double aLength_) {
	aLength = aLength_;
};

void TrapPrism::setBLength(double bLength_) {
	bLength = bLength_;
};

void TrapPrism::setDepth(double depth_) {
	depth = depth_;
};

void TrapPrism::setHeight(double height_) {
	height = height_;
};

void TrapPrism::setOffset(double offset_) {
	offset = offset_;
};
