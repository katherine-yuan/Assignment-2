#ifndef MTRN2500_MODELVEHICLE_H
#define MTRN2500_MODELVEHICLE_H

#include "Vehicle.hpp"

class ModelVehicle : public Vehicle {

public:

	ModelVehicle();	//default constructor
	ModelVehicle(double x_, double y_, double z_, double rotation_);	//default constructor
	~ModelVehicle();	//destructor

	void draw();

protected:

};

#endif // for MTRN2500_MODELVEHICLE_H
