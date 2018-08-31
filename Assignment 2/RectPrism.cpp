// Rebecca Schacht z5115440 2018/08/31

#include "Shape.hpp"
#include "RectPrism.h"

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

RectPrism::RectPrism() {
	// Default constructor for this shape - do we need to do this?
	length = depth = height = 0;
	rotation = 0.0;
	red = green = blue = 1.0;
}

RectPrism::RectPrism(double x_, double y_, double z_, double length_, double depth_, double height_, double rotation_) {
	x = x_;
	y = y_;
	z = z_;

	rotation = rotation_;

	length = length_;
	depth = depth_;
	height = height_;

	red = blue = green = 1.0;
}

RectPrism::~RectPrism() {}

void RectPrism::draw() {

	double halfLength = length / 2;
	double halfDepth = depth / 2; 
	double base = y;

	// Set position
	glPushMatrix();
	positionInGL();

	//trying to draw a rectangle
	glBegin(GL_QUADS);

	// base 
	glVertex3f(halfLength, base, -halfDepth ); //Bottom front left corner
	glVertex3f(halfLength , base, halfDepth); //Bottom back left corner
	glVertex3f(-halfLength, base, halfDepth); //Bottom back right corner
	glVertex3f(-halfLength, base, -halfDepth); //Bottom front right corner

	// top 
	glVertex3f(halfLength, height, -halfDepth ); //Top front left corner
	glVertex3f(halfLength, height, halfDepth ); //Top back left corner
	glVertex3f(-halfLength, height, halfDepth ); //Top back right corner
	glVertex3f(-halfLength, height, -halfDepth ); //Top front right corner

	//front
	glVertex3f(halfLength, base, -halfDepth); //Bottom front left corner
	glVertex3f(halfLength, height, -halfDepth); //Top front left corner
	glVertex3f(-halfLength, height, -halfDepth); //Top front right corner
	glVertex3f(-halfLength, base, -halfDepth); //Bottom front right corner

	//back
	glVertex3f(halfLength, base, halfDepth); //Bottom back left corner
	glVertex3f(halfLength, height, halfDepth); //Top back left corner
	glVertex3f(-halfLength, height, halfDepth ); //Top back right corner
	glVertex3f(-halfLength, base, halfDepth ); //Bottom back right corner

	//left side
	glVertex3f(halfLength, base, -halfDepth); //Bottom front left corner
	glVertex3f(halfLength, base, halfDepth); //Bottom back left corner
	glVertex3f(halfLength, height, halfDepth); //Top back left corner
	glVertex3f(halfLength, height, -halfDepth ); //Top front left corner

	//right side
	glVertex3f(-halfLength, base, -halfDepth ); //Bottom front right corner
	glVertex3f(-halfLength, base, halfDepth); //Bottom back right corner
	glVertex3f(-halfLength, height, halfDepth); //Top back right corner
	glVertex3f(-halfLength, height, -halfDepth); //Top front right corner

	glEnd();

	glPopMatrix();
}
// Getters
double RectPrism::getLength() {
	return length;
}
double RectPrism::getDepth() {
	return depth;
}
double RectPrism::getHeight() {
	return height;
}
// Setters
void RectPrism::setLength(double length_) {
	length = length_;
}
void RectPrism::setDepth(double depth_) {
	depth = depth_;
}
void RectPrism::setHeight(double height_) {
	height = height_;
}
