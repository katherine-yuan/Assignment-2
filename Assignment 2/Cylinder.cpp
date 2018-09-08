// Rebecca Schacht z5115440 2018/08/31

#include "Shape.hpp"
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

Cylinder::Cylinder() {
	// Default constructor for this shape
	innerRadius = 0.0;
	radius = 5;
	length = 10;
	x = y = z = 0.0;
	rotation = 0.0;
	red = green = blue = 1.0;
}

Cylinder::Cylinder(double radius_, double innerRadius_, double length_) {
	radius = radius_;
	innerRadius = innerRadius_;
	length = length_;

	x = y = z = 0.0;
	rotation = 0.0;
	red = green = blue = 1.0;
}

Cylinder::Cylinder(double x_, double y_, double z_, double rotation_, double radius_, double innerRadius_, double length_) {
	x = x_;
	y = y_;
	z = z_;
	rotation = rotation_;

	radius = radius_;
	innerRadius = innerRadius_;
	length = length_;

	red = blue = green = 1.0;
}

Cylinder::~Cylinder() {}

void Cylinder::draw() {
	
	// Set position
	glPushMatrix();
	positionInGL();
	setColorInGL();

	// Create new cylinder object
	GLUquadricObj *cylinder = gluNewQuadric();

	// Adjust centre to server shape specifications given
	glTranslatef(0, radius, - length / 2);

	// Draw hollow cylinder body
	gluCylinder(cylinder, radius, radius, length, SLICES, STACKS);

	// Draw caps using gluDisk
	gluDisk(cylinder, innerRadius, radius, SLICES, STACKS);

	glTranslated(0, 0, length); //moves to draw the back disk
	gluDisk(cylinder, innerRadius, radius, SLICES, STACKS); //changed numbers to #defined versions here
	
	glPopMatrix();
}

// Getters
double Cylinder::getLength() {
	return length;
}
double Cylinder::getRadius() {
	return radius;
}
double Cylinder::getInRadius() {
	return innerRadius;
}
// Setters
void Cylinder::setLength(double length_) {
	length = length_;
}
void Cylinder::setRadius(double radius_) {
	radius = radius_;
}
void Cylinder::setInRadius(double innerRadius_) {
	innerRadius = innerRadius_;
}
