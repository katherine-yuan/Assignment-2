// Rebecca Schacht z5115440 2018/08/31

#ifndef MTRN2500_CYLINDER_H
#define MTRN2500_CYLINDER_H

#include "Shape.hpp"

// Global variables to allow cylinder shape to form
#define STACKS 1    // The number of subdivisions along the z axis
#define SLICES 1000 // The number of subdivisions around the z axis

class Cylinder : public Shape {

public:
	Cylinder(); //default constructor
	Cylinder(double x_, double y_, double z_, double rotation_, double radius_, double innerRadius_, double length_);
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
	double radius, innerRadius, length;
};

#endif // for MTRN2500_CYLINDER_H
