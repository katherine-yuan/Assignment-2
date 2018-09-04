#include "Shape.hpp"
#include "Cylinder.h"
#include "Wheel.h"

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

Wheel::Wheel() {
	// Default constructor for this shape
	innerRadius = 0.0;
	radius = 5;
	length = 10;
	rotation = 0.0;
	red = green = blue = 1.0;
}

Wheel::Wheel(double x_, double y_, double z_, double rotation_, double radius_, double innerRadius_, double length_, double spokes_) {
	x = x_;
	y = y_;
	z = z_;
	rotation = rotation_;

	radius = radius_;
	innerRadius = innerRadius_;
	length = length_;

	spokes = spokes_;

	red = blue = green = 1.0;
}

Wheel::~Wheel() {}

void Wheel::draw() {

	// Set position
	glPushMatrix();
	positionInGL();
	setColorInGL();



	glPopMatrix();
}