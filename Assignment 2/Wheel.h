#ifndef MTRN2500_WHEEL_H
#define MTRN2500_WHEEL_H

#include "Cylinder.h"

class Wheel : public Cylinder {

public:
	Wheel(); //default constructor
	Wheel(double x_, double y_, double z_, double rotation_, double radius_, double innerRadius_, double length_, double spokes_);
	~Wheel(); // default destructor 

	// Draw Function
	void draw();

protected:
	int spokes; //no of spokes? not sure if this should be customisable or if we just go with a set number
};

#endif // for MTRN2500_WHEEL_H
