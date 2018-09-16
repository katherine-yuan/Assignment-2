// Group 80
// Rebecca Schacht z5115440 2018/08/31

#ifndef MTRN2500_RECTPRISM_H
#define MTRN2500_RECTPRISM_H

#include "Shape.hpp"

class RectPrism : public Shape {

public:
	RectPrism(); // Default constructor
	RectPrism(double length_, double depth_, double height_);
	~RectPrism(); // Default destructor 

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
	double length;
	double depth;
	double height;
	double halfLength;
	double halfDepth;
	double base;
};

#endif // for MTRN2500_RECTPRISM_H
