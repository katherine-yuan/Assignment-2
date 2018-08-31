// Rebecca Schacht z5115440 2018/08/31

#pragma once
#ifndef MTRN2500_TRIPRISM_H
#define MTRN2500_TRIPRISM_H

#include "Shape.hpp"

class Cylinder : public Shape {

public:
	Cylinder(); //default constructor
	Cylinder(double x_, double y_, double z_, double radius_, double innerRadius_, double length_, double rotation_);
	~Cylinder(); // default destructor 

	// Getter Functions
	double getLength();
	double getRadius();
	double getInRadius();

	// Setter Functions
	void setLength(double length_);
	void setRadius(double radius_);
	void setInRadius(double innerRadius_);

	// Draw Function
	void draw();

protected:
	double radius, innerRadius, length, slices, stacks;
};

#endif // for MTRN2500_TRIPRISM_H