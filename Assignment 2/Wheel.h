// MTRN2500 Semester 2 2018
// Group 80
// Katherine and Rebecca 
// z5161528  and z5115440

#ifndef MTRN2500_WHEEL_H
#define MTRN2500_WHEEL_H

#include "Cylinder.h"

class Wheel : public Cylinder {

public:

	// Default constructor
	Wheel(); 
	Wheel(double radius_, double innerRadius_, double length_, double wheelSpeed_, bool isSteering_, bool isRolling_);
	// Default destructor 
	~Wheel(); 

	// Draw Function
	void draw();

	// Steering and rolling functions
	void setRoll(double roll_);
	bool Steering();
	bool Rolling();

protected:
	double radius;
	double innerRadius;
	double length;
	double spokeRadius;

	double wheelSpeed;
	bool   isSteering;
	bool   isRolling;

};

#endif // for MTRN2500_WHEEL_H
