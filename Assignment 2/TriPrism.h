#ifndef MTRN2500_TRIPRISM_H
#define MTRN2500_TRIPRISM_H

// Katherine Yuan z5161528 2018/08/29

#include "Shape.hpp"

class TriPrism : public Shape {

public:
	TriPrism();		//default constructor
	TriPrism(double x_, double y_, double z_, double rotation_, double aLength_, double bLength_, double depth_, double theta_);
	~TriPrism();	//destructor

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
	double aLength, bLength, depth, theta;
	//theta is in radians
};

#endif // for MTRN2500_TRIPRISM_H