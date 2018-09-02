#ifndef MTRN2500_MYVEHICLE_H
#define MTRN2500_MYVEHICLE_H

#include "Vehicle.hpp"

class MyVehicle : public Vehicle {

public:

	MyVehicle();	//default constructor
	MyVehicle(double x_, double y_, double z_);	//default constructor
	~MyVehicle();	//destructor

	void draw();

protected:

};

#endif // for MTRN2500_MYVEHICLE_H

