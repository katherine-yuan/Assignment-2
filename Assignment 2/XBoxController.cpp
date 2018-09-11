// XBoxController.cpp : Defines the entry point for the console application.

#include "XBoxController.h"
#include <iostream>

using namespace std;

GamePad::XBoxController::XBoxController(XInputWrapper* xinput, DWORD id)
{
	// Copy the input argument to the class member variable xinput (as outlined by David)
	this->xinput = xinput;

	// Set private variable to the id passed in
	controllerId = id;
}

DWORD GamePad::XBoxController::GetControllerId()
{
	// Return the stored controller ID
	return controllerId;
}

bool GamePad::XBoxController::GetControllerState()
{
	// Retrieve the current state of the specific controller and store in the controllerState struct
	if (XInputGetState(controllerId, &controllerState))
	{
		// If a state is found the if statement is true and so a controller state is found
		return true;
	}
	else
	{
		return false;
	}
}

bool GamePad::XBoxController::IsConnected()
{
	// Use the state function to check if a state can be queried
	if (GetControllerState() == ERROR_SUCCESS)
	{
		// Controller is connected
		return true;
	}
	if (GetControllerState() == ERROR_DEVICE_NOT_CONNECTED)
	{
		// No controller connection can be found 
		return false;
	}
	else
	{
		// A fail safe to account for unforseen errors
		cout << "Error in XBox connection" << endl;
		return false;
	}
}

bool GamePad::XBoxController::PressedA()
{
	GetControllerState();
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		// The button A was pressed therefore return true
		return true;
	}
	else
	{
		// The button A has not been pressed and therefore return false
		return false;
	}
}

bool GamePad::XBoxController::PressedB()
{
	GetControllerState();
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
	{
		// The button B was pressed therefore return true
		return true;
	}
	else
	{
		// The button B has not been pressed and therefore return false
		return false;
	}
}

bool GamePad::XBoxController::PressedX()
{
	GetControllerState();
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
	{
		// The button X was pressed therefore return true
		return true;
	}
	else
	{
		// The button X has not been pressed and therefore return false
		return false;
	}
}

bool GamePad::XBoxController::PressedY()
{
	GetControllerState();
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
	{
		// The button Y was pressed therefore return true
		return true;
	}
	else
	{
		// The button Y has not been pressed and therefore return false
		return false;
	}
}
bool GamePad::XBoxController::PressedLeftShoulder()
{
	GetControllerState();
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
	{
		// The left shoulder was pressed therefore return true
		return true;
	}
	else
	{
		// The left shoulder has not been pressed and therefore return false
		return false;
	}
}
bool GamePad::XBoxController::PressedRightShoulder()
{
	GetControllerState();
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		// The right shoulder was pressed therefore return true
		return true;
	}
	else
	{
		// The right shoulder has not been pressed and therefore return false
		return false;
	}
}
bool GamePad::XBoxController::PressedLeftDpad()
{
	GetControllerState();
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
	{
		// The dpad left button was pressed therefore return true
		return true;
	}
	else
	{
		// The dpad left button has not been pressed and therefore return false
		return false;
	}
}
bool GamePad::XBoxController::PressedRightDpad()
{
	GetControllerState();
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
	{
		// The dpad right button was pressed therefore return true
		return true;
	}
	else
	{
		// The dpad right button has not been pressed and therefore return false
		return false;
	}
}
bool GamePad::XBoxController::PressedUpDpad()
{
	GetControllerState();
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
	{
		// The dpad up button was pressed therefore return true
		return true;
	}
	else
	{
		// The dpad up button has not been pressed and therefore return false
		return false;
	}
}
bool GamePad::XBoxController::PressedDownDpad()
{
	GetControllerState();
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
	{
		// The dpad down button was pressed therefore return true
		return true;
	}
	else
	{
		// The dpad down button has not been pressed and therefore return false
		return false;
	}
}
bool GamePad::XBoxController::PressedStart()
{
	GetControllerState();
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_START)
	{
		// The start button was pressed therefore return true
		return true;
	}
	else
	{
		// The start button has not been pressed and therefore return false
		return false;
	}
}
bool GamePad::XBoxController::PressedBack()
{
	GetControllerState();
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
	{
		// The back button was pressed therefore return true
		return true;
	}
	else
	{
		// The back button has not been pressed and therefore return false
		return false;
	}
}
bool GamePad::XBoxController::PressedLeftThumb()
{
	GetControllerState();
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
	{
		// The left thumb button was pressed therefore return true
		return true;
	}
	else
	{
		// The left thumb button has not been pressed and therefore return false
		return false;
	}
}
bool GamePad::XBoxController::PressedRightThumb()
{
	GetControllerState();
	if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
	{
		// The right thumb button was pressed therefore return true
		return true;
	}
	else
	{
		// The right thumb button has not been pressed and therefore return false
		return false;
	}
}

BYTE GamePad::XBoxController::LeftTriggerLocation()
{
	GetControllerState();
	// Check that the controller is connected
	if (IsConnected())
	{
		// Query the trigger location and return
		BYTE leftTrigger = controllerState.Gamepad.bLeftTrigger;
		return leftTrigger;
	}
}

BYTE GamePad::XBoxController::RightTriggerLocation()
{
	GetControllerState();
	// Check that the controller is connected
	if (IsConnected())
	{
		// Query the trigger location and return
		BYTE rightTrigger = controllerState.Gamepad.bRightTrigger;
		return rightTrigger;
	}
}

GamePad::Coordinate GamePad::XBoxController::LeftThumbLocation()
{
	// Adapted from microsoft xinput documentation
	GetControllerState();

	float LX = controllerState.Gamepad.sThumbLX;
	float LY = controllerState.Gamepad.sThumbLY;

	//// Determine how far the controller has moved
	float magnitude = sqrt(LX*LX + LY*LY);

	float normalizedMagnitude = 0;

	// Check if the controller is outside the set circular deadzone 
	if (magnitude > deadzone)
	{
		// Cut off the magnitude at its expected maximum value
		if (magnitude > MAX_DISTANCE)
		{
			magnitude = MAX_DISTANCE;
		}
		// Adjust the magnitude relative to the end of the deadzones
		magnitude = magnitude - deadzone;

		// Normalize the magnitude with respect to its expected range giving
		// a magnitude scale of 0.0 to 1.0
		normalizedMagnitude = magnitude / (MAX_DISTANCE - deadzone);
	}
	else
	{
		// If the controller is in the deadzone, zero out the magnitude
		// Note that this includes points lying on the deadzone circumference
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
	}

	// Now use these values to create the new coordinates for the right thumbstick object
	float scaledLX = LX * normalizedMagnitude;
	float scaledLY = LY * normalizedMagnitude;

	// Change to shorts to be used in coordinate class
	short finalLX = short(scaledLX);
	short finalLY = short(scaledLY);

	// Make a coordinate class for the right thumbstick with determined x and y values
	GamePad::Coordinate leftCoordinate(finalLX, finalLY);
	return leftCoordinate;
}

GamePad::Coordinate GamePad::XBoxController::RightThumbLocation()
{
	// Adapted from microsoft xinput documentation
	GetControllerState();

	float RX = controllerState.Gamepad.sThumbRX;
	float RY = controllerState.Gamepad.sThumbRY;

	//// Determine how far the controller has moved
	float magnitude = sqrt(RX*RX + RY*RY);

	float normalizedMagnitude = 0;

	// Check if the controller is outside the set circular deadzone 
	if (magnitude > deadzone)
	{
		// Cut off the magnitude at its expected maximum value
		if (magnitude >= MAX_DISTANCE)
		{
			magnitude = MAX_DISTANCE;
		}
		// Adjust the magnitude relative to the end of the deadzones
		magnitude = magnitude - deadzone;

		// Normalize the magnitude with respect to its expected range giving
		// a magnitude scale of 0.0 to 1.0
		normalizedMagnitude = magnitude / (MAX_DISTANCE - deadzone);
	}
	else
	{
		// If the controller is in the deadzone, zero out the magnitude
		// Note that this includes points lying on the deadzone circumference
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
	}

	// Now use these values to create the new coordinates for the right thumbstick object
	float scaledRX = RX * normalizedMagnitude;
	float scaledRY = RY * normalizedMagnitude;

	// Change to shorts to be used in coordinate class
	short finalRX = short(scaledRX);
	short finalRY = short(scaledRY);

	// Make a coordinate class for the right thumbstick with determined x and y values
	GamePad::Coordinate rightCoordinate(finalRX, finalRY);
	return rightCoordinate;
}


void GamePad::XBoxController::Vibrate(WORD left, WORD right)
{
	// Create a Vibration State
	XINPUT_VIBRATION Vibration;

	// Set every value in the vibration state struct to zero
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	// Set the vibration values to those passed into the function
	Vibration.wLeftMotorSpeed = left;
	Vibration.wRightMotorSpeed = right;

	// Initiate vibration
	XInputSetState(controllerId, &Vibration);
}

void GamePad::XBoxController::SetDeadzone(unsigned int radius)
{
	// Set the radius value of the deadzone to one input into the function
	deadzone = radius;
}