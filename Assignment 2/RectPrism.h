/ Rebecca Schacht z5115440 2018/08/31

#pragma once
#ifndef MTRN2500_TRIPRISM_H
#define MTRN2500_TRIPRISM_H

#include "Shape.hpp"

class RectPrism : public Shape {

public:
	RectPrism(); //default constructor
	RectPrism(double x_, double y_, double z_, double length_, double depth_, double height_, double rotation_);
	~RectPrism(); // default destructor 

	// Getter Functions
	double getLength();
	double getDepth();
	double getHeight();

	// Setter Functions
	void setLength(double length_);
	void setDepth(double depth_);
	void setHeight(double height_);

	// Draw Function
	void draw();

protected:
	double length, depth, height;
};

#endif // for MTRN2500_TRIPRISM_H