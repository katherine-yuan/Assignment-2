// MTRN2500 Semester 2 2018
// Group 80
// Katherine and Rebecca 
// z5161528  and z5115440

#ifndef MTRN2500_CAR_H
#define MTRN2500_CAR_H

#include "Vehicle.hpp"
#include "Messages.hpp"

#define PI 3.14159265359

class Car : public Vehicle {

public:

	Car();	// Default constructor
	Car(VehicleModel vm_);
	~Car();	// Destructor

	VehicleModel getVehicleModel();
	VehicleState getVehicleState();

	void update(double dt);

	void draw();

protected:
	VehicleModel vm;
	VehicleState vs;
	void shapeInitToShapes();
	double wheelRotation;
};

#endif // for MTRN2500_CAR_H
