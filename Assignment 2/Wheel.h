#ifndef MTRN2500_WHEEL_H
#define MTRN2500_WHEEL_H

#include "Cylinder.h"

class Wheel : public Cylinder {

public:

	friend class Car;

	Wheel(); //default constructor
	Wheel(double radius_, double innerRadius_, double length_);
	Wheel(double radius_, double innerRadius_, double length_, double wheelSpeed_, bool isSteering_, bool isRolling_);
	Wheel(double x_, double y_, double z_, double rotation_, double radius_, double innerRadius_, double length_);
	~Wheel(); // default destructor 

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
	double wheelSpeed;

	double rollingRate;
	bool isSteering;
	bool isRolling;

};

#endif // for MTRN2500_WHEEL_H
