
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
	x = y = z = 0.0;
	rotation = 0.0;
	red = green = blue = 1.0;
};

TriPrism::TriPrism(double x_, double y_, double z_, double rotation_, double aLength_, double bLength_, double depth_, double theta_) {
	x = x_;
	y = y_;
	z = z_;
	aLength = aLength_;
	bLength = bLength_;
	depth = depth_;
	theta = theta_;

	rotation = 0.0;
	red = green = blue = 1.0;
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
	//code here
}