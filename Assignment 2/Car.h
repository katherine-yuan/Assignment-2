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

	void draw();  

	//// functions for setting 
	//void setPrevX(double prevX_);
	//void setPrevY(double prevY_);
	//void setPrevRotation(double prevRotation_);
	//void setPrevSteer(double prevSteer_);
	//void setPrevSpeed(double prevSpeed_);


protected:
	VehicleModel vm;
	VehicleState vs;
	void shapeInitToShapes();
	double wheelRotation;

	//// variables for follow mode
	//double prevX;
	//double prevY;
	//double prevRotation;
	//double prevSteer;
	//double prevSpeed;

};

#endif // for MTRN2500_CAR_H