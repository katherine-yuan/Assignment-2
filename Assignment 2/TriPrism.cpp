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

//Note: theta should be given in radians
TriPrism::TriPrism() {
	x = y = z = 0.0;
	rotation = 0.0;
	aLength = bLength = depth = theta = 0.0;
	red = green = blue = 1.0;
}

TriPrism::TriPrism(double aLength_, double bLength_, double depth_, double theta_) {
	aLength = aLength_;
	bLength = bLength_;
	depth = depth_;
	theta = theta_;

	x = y = z = 0.0;
	rotation = 0.0;
	red = green = blue = 1.0;		//set default colour to white
};

TriPrism::TriPrism(double x_, double y_, double z_, double rotation_, double aLength_, double bLength_, double depth_, double theta_) {
	x = x_;
	y = y_;
	z = z_;
	rotation = rotation_;

	aLength = aLength_;
	bLength = bLength_;
	depth = depth_;
	theta = theta_;
	
	red = green = blue = 1.0;		//set default colour to white
};

TriPrism::~TriPrism() {
};

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

void TriPrism::draw() {

	glPushMatrix();

	positionInGL();
	//glRotated(-90, 0, 0, 1);
	//glTranslated(bLength*sin(theta), 0, 0);

	double aLengthHalf = aLength / 2;
	double depthHalf = depth / 2;

	double topLeftCornerX = aLengthHalf - bLength * cos(theta);
	double topLeftCornerY = bLength * sin(theta);

	setColorInGL();

	//DRAWING QUADS
	glBegin(GL_QUADS);

	//base of the triangular prism
	glVertex3f(aLengthHalf, 0 , depthHalf);		//bottom far left corner
	glVertex3f(-aLengthHalf, 0, depthHalf);		//far right corner
	glVertex3f(-aLengthHalf, 0, -depthHalf);	//front right corner
	glVertex3f(aLengthHalf, 0, -depthHalf);		//bottom front left corner

	//left side of the triangular prism
	glVertex3f(topLeftCornerX, topLeftCornerY, -depthHalf);		//top front left corner
	glVertex3f(aLengthHalf, 0, -depthHalf);						//bottom front left corner
	glVertex3f(aLengthHalf, 0, depthHalf);						//bottom far left corner
	glVertex3f(topLeftCornerX, topLeftCornerY, depthHalf);		//top far left corner

	//top side of the triangular prism
	glVertex3f(topLeftCornerX, topLeftCornerY, -depthHalf);		//top front left corner
	glVertex3f(-aLengthHalf, 0, -depthHalf);					//front right corner
	glVertex3f(-aLengthHalf, 0, depthHalf);						//far right corner
	glVertex3f(topLeftCornerX, topLeftCornerY, depthHalf);		//top far left corner

	glEnd();

	//DRAWING TRIANGLES 
	glBegin(GL_TRIANGLES);

	//front of triangular prism
	glVertex3f(aLengthHalf, 0, -depthHalf);						//bottom front left corner
	glVertex3f(topLeftCornerX, topLeftCornerY, -depthHalf);		//top front left corner
	glVertex3f(-aLengthHalf, 0, -depthHalf);					//front right corner

	//back of triangular prism
	glVertex3f(aLengthHalf, 0, depthHalf);						//bottom far left corner
	glVertex3f(topLeftCornerX, topLeftCornerY, depthHalf);		//top far left corner
	glVertex3f(-aLengthHalf, 0, depthHalf);						//far right corner

	glEnd();
	
	glPopMatrix();
}