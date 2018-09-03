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
	x = y = z = 0.0;
	rotation = 0.0;
	aLength = bLength = depth = height = offset = 0.0;
	red = green = blue = 1.0;
};

TrapPrism::TrapPrism(double x_, double y_, double z_, double rotation_, double aLength_, double bLength_, double depth_, double height_, double offset_) {
	x = x_;
	y = y_;
	z = z_;

	rotation = rotation_;

	aLength = aLength_;
	bLength = bLength_;
	depth = depth_;
	height = height_;
	offset = offset_;

	red = green = blue = 1.0;
};

TrapPrism::~TrapPrism() {
};

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

void TrapPrism::draw() {

	double aLengthHalf = aLength / 2;
	double depthHalf = depth / 2;

	double topLeftCornerX = aLengthHalf - offset;
	double topRightCornerX = aLengthHalf - offset - bLength;
	
	glPushMatrix();

	positionInGL();		//set position

	glBegin(GL_QUADS);

	setColor(0, 1, 0);	//set trapezoidal prism color to green
	setColorInGL();

	//base of the trapezoidal prism
	glVertex3f(aLengthHalf, 0, depthHalf);		//bottom far left corner
	glVertex3f(-aLengthHalf, 0, depthHalf);		//bottom far right corner
	glVertex3f(-aLengthHalf, 0, -depthHalf);	//bottom front right corner
	glVertex3f(aLengthHalf, 0, -depthHalf);		//bottom front left corner

	//top side of the trapezoidal prism
	glVertex3f(topLeftCornerX, height, depthHalf);			//top far left corner
	glVertex3f(topRightCornerX, height, depthHalf);			//top far right corner
	glVertex3f(topRightCornerX, height, -depthHalf);		//top front right corner
	glVertex3f(topLeftCornerX, height, -depthHalf);			//top front left corner

	//front side of trapezoidal prism
	glVertex3f(aLengthHalf, 0, -depthHalf);					//bottom front left corner
	glVertex3f(-aLengthHalf, 0, -depthHalf);				//bottom front right corner
	glVertex3f(topRightCornerX, height, -depthHalf);		//top front right corner
	glVertex3f(topLeftCornerX, height, -depthHalf);			//top front left corner

	//far(back) side of trapezoidal prism
	glVertex3f(aLengthHalf, 0, depthHalf);					//bottom far left corner
	glVertex3f(-aLengthHalf, 0, depthHalf);					//bottom far right corner
	glVertex3f(topRightCornerX, height, depthHalf);			//top far right corner
	glVertex3f(topLeftCornerX, height, depthHalf);			//top far left corner

	//left side of trapezoidal prism
	glVertex3f(aLengthHalf, 0, -depthHalf);					//bottom front left corner
	glVertex3f(aLengthHalf, 0, depthHalf);					//bottom far left corner
	glVertex3f(topLeftCornerX, height, depthHalf);			//top far left corner
	glVertex3f(topLeftCornerX, height, -depthHalf);			//top front left corner

	//right side of trapezoidal prism
	glVertex3f(-aLengthHalf, 0, -depthHalf);				//bottom front right corner
	glVertex3f(-aLengthHalf, 0, depthHalf);					//bottom far right corner
	glVertex3f(topRightCornerX, height, depthHalf);			//top far right corner
	glVertex3f(topRightCornerX, height, -depthHalf);		//top front right corner

	glEnd();

	glPopMatrix();

}