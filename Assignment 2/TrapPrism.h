// Group 80
// Katherine Yuan z5161528 2018/08/29

#ifndef MTRN2500_TRAPPRISM_H
#define MTRN2500_TRAPPRISM_H

#include "Shape.hpp"

class TrapPrism : public Shape {

public:
	TrapPrism();	// Default constructor
	TrapPrism(double aLength_, double bLength_, double depth_, double height_, double offset_);
	~TrapPrism();	// Destructor

	//Getter functions
	double getALength();
	double getBLength();
	double getDepth();
	double getHeight();
	double getOffset();

	//Setter functions
	void setALength(double aLength_);
	void setBLength(double bLength_);
	void setDepth(double depth_);
	void setHeight(double height_);
	void setOffset(double offset_);

	//Draw function
	void draw();

protected:
	double aLength; 
	double bLength;
	double depth;
	double height;
	double offset;

	double aLengthHalf;
	double depthHalf;
	double topLeftCornerX;
	double topRightCornerX;
};

#endif // for MTRN2500_TRAPPRISM_H
