#ifndef MTRN2500_TRAPPRISM_H
#define MTRN2500_TRAPPRISM_H

#include "Shape.hpp"

class TrapPrism : public Shape {

public:
	TrapPrism();	//default constructor
	TrapPrism(double x_, double y_, double z_, double rotation_, double aLength_, double bLength_, double depth_, double height_, double offset_);
	~TrapPrism();	//destructor

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
	double aLength, bLength, depth, height, offset;
};

#endif // for MTRN2500_TRAPPRISM_H