#ifndef MTRN2500_WHEEL_H
#define MTRN2500_WHEEL_H

#include "Cylinder.h"

class Wheel : public Cylinder {

public:
	Wheel(); //default constructor
	Wheel(double x_, double y_, double z_, double rotation_, double radius_, double innerRadius_, double length_);
	~Wheel(); // default destructor 

	// Draw Function
	void draw();

protected:
	
};

#endif // for MTRN2500_WHEEL_H
