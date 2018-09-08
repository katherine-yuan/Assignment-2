#ifndef MTRN2500_CAR_H
#define MTRN2500_CAR_H

#include "Vehicle.hpp"
#include "Messages.hpp"

class Car : public Vehicle {

public:

	Car();	//default constructor
	Car(VehicleModel vehicleModel_);
	~Car();	//destructor

//	void update(double dt);

	void draw();

protected:
	VehicleModel vm;
	VehicleState vs;
	void shapeInitToShapes();

};

#endif // for MTRN2500_CAR_H