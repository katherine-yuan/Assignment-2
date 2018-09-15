// Katherine Yuan z5161528 2018/08/29

#ifndef MTRN2500_TRIPRISM_H
#define MTRN2500_TRIPRISM_H

#include "Shape.hpp"

class TriPrism : public Shape {

public:
	TriPrism();		// Default constructor
	TriPrism(double aLength_, double bLength_, double depth_, double theta_);
	~TriPrism();	// Destructor

	//Getter functions
	double getALength();
	double getBLength();
	double getDepth();
	double getTheta();

	//Setter functions
	void setALength(double aLength_);
	void setBLength(double bLength_);
	void setDepth(double depth_);
	void setTheta(double theta_);

	//Draw function
	void draw();

protected:
	double aLength;
	double bLength;
	double depth;
	double theta;

	double aLengthHalf;
	double depthHalf;
	double topLeftCornerX;
	double topLeftCornerY;
};

#endif // for MTRN2500_TRIPRISM_H
