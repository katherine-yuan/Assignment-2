// Group 80

#pragma once
#ifndef XBOX_CONTROLLER_H
#define XBOX_CONTROLLER_H

#ifdef _WIN32
#include <Windows.h>
#endif

#include "XInputWrapper.h"

// Define global variables to be used with the deadzone and trigger functions 
#define MAX_TRIGGER 255
#define MAX_DISTANCE 32767

/*
* For MTRN2500 Students - These methods and their respective signatures must not be changed. If
* they are and human intervention is required then marks will be deducted. You are more than
* welcome to add private member variables and private methods to the provided classes, or create
* your own underlying classes to provide the requested functionality as long as all of the
* functionality for the XBoxController can be accessed using the methods in the provided classes.
*/

namespace GamePad {
	class Coordinate {
	public:
		Coordinate(SHORT x, SHORT y) : x(x), y(y) {}
		~Coordinate() = default;

		SHORT GetX() { return this->x; }
		SHORT GetY() { return this->y; }
		void SetX(SHORT x) { this->x = x; }
		void SetY(SHORT y) { this->y = y; }

	private:
		SHORT x;
		SHORT y;
	};

	class XBoxController {

	public:
		// Set up the constructor and destructor using XInputWrapper object
		XBoxController(XInputWrapper* xinput, DWORD id);
		~XBoxController() = default;

		// Methods which report information relating to the specific controller
		DWORD GetControllerId();

		// Methods which report particular aspects of the controller status
		bool IsConnected();
		bool PressedA();
		bool PressedB();
		bool PressedX();
		bool PressedY();
		bool PressedLeftShoulder();
		bool PressedRightShoulder();
		bool PressedLeftDpad();
		bool PressedRightDpad();
		bool PressedUpDpad();
		bool PressedDownDpad();
		bool PressedStart();
		bool PressedBack();
		bool PressedLeftThumb();
		bool PressedRightThumb();
		BYTE LeftTriggerLocation();
		BYTE RightTriggerLocation();

		GamePad::Coordinate LeftThumbLocation();
		GamePad::Coordinate RightThumbLocation();

		// Methods which set values that modify the behaviour of the controller
		void Vibrate(WORD left, WORD right);
		void SetDeadzone(unsigned int radius);

	private:
		// NOTE: All XInput function calls must be made through the XInputWrapper class
		XInputWrapper * xinput;

		// Methods which report information relating to the specific controller
		bool GetControllerState();

		// The stored controller ID number
		DWORD controllerId;

		// Struct where the state of the current controller is stored 
		XINPUT_STATE controllerState;

		// Member variable for storing the deadzone value
		short deadzone;
	};
};

#endif // XBOX_CONTROLLER_H#pragma once
