#ifndef MTRN2500_RECTPRISM_H
#define MTRN2500_RECTPRISM_H

#include "Shape.hpp"

class RectPrism : public Shape {

public:
	RectPrism(); //default constructor
	RectPrism(double x_, double y_, double z_, double rotation_, double xLength_, double yLength_, double zLength_);
	~RectPrism();

	//Getter functions
	double getXLength();
	double getYLength();
	double getZLength();

	//Setter functions
	void setXLength(double xLength_);
	void setYLength(double yLength_);
	void setZLength(double zLength_);

	//Draw function
	void draw();

protected:
	double xLength, yLength, zLength;
};

#endif // for MTRN2500_RECTPRISM_H