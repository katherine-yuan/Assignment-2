// Group 80
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
	// Default constructor for this shape
	length = 0;
	height = 0;
	depth = 0;

	// Variables used for drawing the rectangles
	halfLength = 0;
	halfDepth = 0;
	base = 0;
}

RectPrism::RectPrism(double length_, double height_, double depth_) {
	// Variables dictating the dimensions of the rectangles
	length = length_;
	height = height_;
	depth = depth_;

	// Variables used for drawing the rectangles
	halfLength = length / 2;
	halfDepth  = depth / 2;
	base = 0;
}

RectPrism::~RectPrism() {}

void RectPrism::draw() {
	// Set position
	glPushMatrix();
	positionInGL();
	setColorInGL();

	glBegin(GL_QUADS);

	// Rectagular prism bottom face 
	glVertex3f( halfLength, base, -halfDepth ); //Bottom front left corner
	glVertex3f( halfLength , base, halfDepth);  //Bottom back left corner
	glVertex3f(-halfLength, base, halfDepth);   //Bottom back right corner
	glVertex3f(-halfLength, base, -halfDepth);  //Bottom front right corner

	// Rectagular prism top face 
	glVertex3f( halfLength, height, -halfDepth ); //Top front left corner
	glVertex3f( halfLength, height, halfDepth );  //Top back left corner
	glVertex3f(-halfLength, height, halfDepth );  //Top back right corner
	glVertex3f(-halfLength, height, -halfDepth ); //Top front right corner

	// Rectagular prism front face 
	glVertex3f( halfLength, base, -halfDepth);   //Bottom front left corner
	glVertex3f( halfLength, height, -halfDepth); //Top front left corner
	glVertex3f(-halfLength, height, -halfDepth); //Top front right corner
	glVertex3f(-halfLength, base, -halfDepth);   //Bottom front right corner

	// Rectagular prism back face 
	glVertex3f( halfLength, base, halfDepth);    //Bottom back left corner
	glVertex3f( halfLength, height, halfDepth);  //Top back left corner
	glVertex3f(-halfLength, height, halfDepth ); //Top back right corner
	glVertex3f(-halfLength, base, halfDepth );   //Bottom back right corner

	// Rectagular prism left face 
	glVertex3f(halfLength, base, -halfDepth);    //Bottom front left corner
	glVertex3f(halfLength, base, halfDepth);     //Bottom back left corner
	glVertex3f(halfLength, height, halfDepth);   //Top back left corner
	glVertex3f(halfLength, height, -halfDepth ); //Top front left corner

	// Rectagular prism right face 
	glVertex3f(-halfLength, base, -halfDepth );  //Bottom front right corner
	glVertex3f(-halfLength, base, halfDepth);    //Bottom back right corner
	glVertex3f(-halfLength, height, halfDepth);  //Top back right corner
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
