#ifndef MTRN2500_CAR_H
#define MTRN2500_CAR_H

#include "Vehicle.hpp"
#include "Messages.hpp"

#define PI 3.14159265359

class Car : public Vehicle {

public:

	friend class Wheel;

	Car();	//default constructor
	Car(VehicleModel vm_);
	~Car();	//destructor

	VehicleModel getVehicleModel();
	VehicleState getVehicleState();

	void update(double dt);

	double getAngle();

	void draw();


protected:
	VehicleModel vm;
	VehicleState vs;
	void shapeInitToShapes();
	double wheelRotation;

	double angle;	
};

#endif // for MTRN2500_CAR_H