// MTRN2500 Semester 2 2018
// Group 80
// Katherine and Rebecca 
// z5161528  and z5115440

// Style notes: Comments above the line they refer to. All lines less than 80
// characters to allow for double screen use. Comments begin with a capital 
// and a space is always left between the "//" and the start of the line.

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <unistd.h>
#include <sys/time.h>
#elif defined(WIN32)
#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#include <sys/time.h>
#endif


#include "Camera.hpp"
#include "Ground.hpp"
#include "KeyManager.hpp"

#include "Shape.hpp"
#include "Vehicle.hpp"

#include "RemoteDataManager.hpp"
#include "Messages.hpp"
#include "HUD.hpp"
#include "ObstacleManager.hpp"

#include "TriPrism.h"
#include "TrapPrism.h"
#include "RectPrism.h"
#include "Cylinder.h"
#include "Wheel.h"

#include "Car.h"

#include "XBoxController.h"
#include "XInputWrapper.h"

void display();
void reshape(int width, int height);
void idle();

void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void special_keydown(int keycode, int x, int y);
void special_keyup(int keycode, int x, int y);

void mouse(int button, int state, int x, int y);
void dragged(int x, int y);
void motion(int x, int y);

using namespace std;
using namespace scos;

// Used to store the previous mouse location so we
// can calculate relative mouse movement.
int prev_mouse_x = -1;
int prev_mouse_y = -1;

// Vehicle control related variables
Vehicle * vehicle = NULL;
double speed = 0;
double steering = 0;
bool LPressed = 0;

// Default goal location
std::deque<GoalState> goals;

std::map<int, Vehicle *> otherVehicles;

int frameCounter = 0;

// int _tmain(int argc, _TCHAR* argv[]) {
int main(int argc, char ** argv) {

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	glutInit(&argc, (char**)(argv));
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("MTRN3500 - GL");

	Camera::get()->setWindowDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutSpecialFunc(special_keydown);
	glutSpecialUpFunc(special_keyup);

	glutMouseFunc(mouse);
	glutMotionFunc(dragged);
	glutPassiveMotionFunc(motion);

	// -------------------------------------------------------------------------
	// Please uncomment the following line of code and replace 'MyVehicle'
	// with the name of the class you want to show as the current 
	// custom vehicle.
	// -------------------------------------------------------------------------

	vehicle = new Car();


	// Add test obstacles
	ObstacleManager::get()->addObstacle(Obstacle(10, 10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(10, -10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10, 10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10, -10, 1));

	// Add test goal
	GoalState g;
	g.x = 25;
	g.z = 0;
	goals.push_back(g);


	glutMainLoop();

	if (vehicle != NULL) {
		delete vehicle;
	}

	return 0;
}

void drawGoals()
{
	for (int i = 0; i < goals.size(); ++i) {
		GoalState goal = goals[i];

		glPushMatrix();
		glTranslatef(goal.x, 0, goal.z);
		glRotated(90, -1, 0, 0);
		static GLUquadric * quad = gluNewQuadric();

		// Make first goal purple
		if (i == 0)
			glColor3f(1, .3, 1);
		else
			glColor3f(1, 1, 1);

		gluCylinder(quad, .5, .5, 10, 5, 1);
		glPopMatrix();
	}
}


void display() {
	frameCounter++;
	// -------------------------------------------------------------------------
	//  This method is the main draw routine. 
	// -------------------------------------------------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (Camera::get()->isPursuitMode() && vehicle != NULL) {
		double x = vehicle->getX(), y = vehicle->getY(), z = vehicle->getZ();
		double dx = cos(vehicle->getRotation() * 3.141592765 / 180.0);
		double dy = sin(vehicle->getRotation() * 3.141592765 / 180.0);
		Camera::get()->setDestPos(x + (-20 * dx), y + 15, z + (-20 * dy));
		Camera::get()->setDestDir(dx, -0.25, dy);
	}
	Camera::get()->updateLocation();
	Camera::get()->setLookAt();

	Ground::draw();

// Draw other vehicles from the server
	for (std::map<int, Vehicle *>::iterator iter = otherVehicles.begin();
						iter != otherVehicles.end(); ++iter)
		iter->second->draw();

	// Draw my vehicle
	if (vehicle != NULL) {
		vehicle->draw();
	}

	// Draw obstacles
	ObstacleManager::get()->drawAll();

	// Draw goals
	drawGoals();

	// Draw HUD
	HUD::Draw();

	glutSwapBuffers();
};

void reshape(int width, int height) {

	Camera::get()->setWindowDimensions(width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};

void remoteDriver(Vehicle * vehicle, double x, double z, double r, double speed_, double steering_)
{
	// Filter 
	const double kSmoothingFactor = 0.5;
	vehicle->setX(vehicle->getX() * kSmoothingFactor + x * (1 - kSmoothingFactor));
	vehicle->setZ(vehicle->getZ() * kSmoothingFactor + z * (1 - kSmoothingFactor));

	vehicle->setRotation(r);
	vehicle->steering = steering_;
	vehicle->speed = speed_;
}

double getTime()
{
#if defined(WIN32)
	LARGE_INTEGER freqli;
	LARGE_INTEGER li;
	if (QueryPerformanceCounter(&li) && QueryPerformanceFrequency(&freqli)) {
		return double(li.QuadPart) / double(freqli.QuadPart);
	}
	else {
		static ULONGLONG start = GetTickCount64();
		return (GetTickCount64() - start) / 1000.0;
	}
#else
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec / 1000000.0);
#endif
}

void idle() {
	
	// Initiate a new instance of an xbox controller
	XInputWrapper xinput{};
	int newController = 0;

	speed    = 0;
	steering = 0;

	GamePad::XBoxController currentController(&xinput, 0);

	// Checks whether the xbox controller is connected
	if (currentController.IsConnected()) {
		// If it's connected, car should be controlled by the xbox
		// Keyboard commands will not work when xbox is connected

		// Control the camera with the Xbox
		if (currentController.PressedX()) {
			Camera::get()->strafeLeft();
		}
		else if (currentController.PressedLeftShoulder()) {
			Camera::get()->strafeDown();
		}
		else if (currentController.PressedB()) {
			Camera::get()->strafeRight();
		}
		else if (currentController.PressedA()) {
			Camera::get()->moveBackward();
		}
		else if (currentController.PressedY()) {
			Camera::get()->moveForward();
		}
		else if (currentController.PressedRightShoulder()) {
			Camera::get()->strafeUp();
		}
		// Controlling the vehicle 
		if (currentController.PressedDownDpad()) {
			speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
		}
		if (currentController.PressedUpDpad()) {
			speed = Vehicle::MAX_FORWARD_SPEED_MPS;
		}
		if (currentController.PressedLeftDpad()) {
			steering = Vehicle::MAX_LEFT_STEERING_DEGS * -1;
		}
		if (currentController.PressedRightDpad()) {
			steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -1;
		}

	}
	else {
		// If the controller is not connected operate through keyboard.
		// Functions are in the same order as above.
		if (KeyManager::get()->isAsciiKeyPressed('a')) {
			Camera::get()->strafeLeft();
		}

		if (KeyManager::get()->isAsciiKeyPressed('c')) {
			Camera::get()->strafeDown();
		}

		if (KeyManager::get()->isAsciiKeyPressed('d')) {
			Camera::get()->strafeRight();
		}

		if (KeyManager::get()->isAsciiKeyPressed('s')) {
			Camera::get()->moveBackward();
		}

		if (KeyManager::get()->isAsciiKeyPressed('w')) {
			Camera::get()->moveForward();
		}

		if (KeyManager::get()->isAsciiKeyPressed(' ')) {
			Camera::get()->strafeUp();
		}

		// Controlling the vehicle 
		if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_LEFT)) {
			steering = Vehicle::MAX_LEFT_STEERING_DEGS * -1;
		}

		if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
			steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -1;
		}

		if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_UP)) {
			speed = Vehicle::MAX_FORWARD_SPEED_MPS;
		}

		if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_DOWN)) {
			speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
		}

	}

	// Attempt to do data communications every 4 frames if we've created a local vehicle
	if (frameCounter % 4 == 0 && vehicle != NULL) {

		// If not connected, attempt to connect every 2 seconds
		if (!RemoteDataManager::IsConnected()) {
			if (frameCounter % 120 == 0) {

				// Erase other vehicles
				for (std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) {
					delete iter->second;
				}
				otherVehicles.clear();

				// Uncomment this line to connect to the robotics server.
				RemoteDataManager::Connect("www.robotics.unsw.edu.au", "18081");

				// On connect, let's tell the server what we look like
				if (RemoteDataManager::IsConnected()) {
					ObstacleManager::get()->removeAll();

					VehicleModel vm;
					vm.remoteID = 0;

					vm = dynamic_cast<Car*>(vehicle)->getVehicleModel();


					RemoteDataManager::Write(GetVehicleModelStr(vm));
				}
			}
		}

		// If we're connected, send our vehicle state to the server
		if (RemoteDataManager::IsConnected()) {
			VehicleState vs;
			vs.remoteID = 0;
			vs.x = vehicle->getX();
			vs.z = vehicle->getZ();
			vs.rotation = vehicle->getRotation();
			vs.speed = vehicle->getSpeed();
			vs.steering = vehicle->getSteering();
			RemoteDataManager::Write(GetVehicleStateStr(vs));
		}

		// If we're still connected, receive and handle response messages from the server
		if (RemoteDataManager::IsConnected()) {
			std::vector<RemoteMessage> msgs = RemoteDataManager::Read();
			for (unsigned int i = 0; i < msgs.size(); i++) {

				RemoteMessage msg = msgs[i];
				//cout << msg.payload << endl;

				switch (msg.type) {
				
				// New models
				case 'M':
				{
					std::vector<VehicleModel> models = GetVehicleModels(msg.payload);
					for (unsigned int i = 0; i < models.size(); i++) {
						VehicleModel vm = models[i];

						// Uncomment the line below to create remote vehicles
						otherVehicles[vm.remoteID] = new Car(vm);

					}
					break;
				}

				// Vehicle states
				case 'S':
				{
					std::vector<VehicleState> states = GetVehicleStates(msg.payload);
					for (unsigned int i = 0; i < states.size(); i++) {
						VehicleState vs = states[i];

						std::map<int, Vehicle*>::iterator iter = otherVehicles.find(vs.remoteID);
						if (iter != otherVehicles.end()) {
							Vehicle * veh = iter->second;
							remoteDriver(veh, vs.x, vs.z, vs.rotation, vs.speed, vs.steering);
						}
					}
					break;
				}

				// Goal state
				case 'G':
				{
					goals = GetGoals(msg.payload);
					break;
				}

				// Obstacle state
				case 'O':
				{
					std::vector<ObstacleState> obs = GetObstacles(msg.payload);
					for (unsigned int i = 0; i < obs.size(); i++) {
						Obstacle o(obs[i].x, obs[i].z, obs[i].radius);
						ObstacleManager::get()->addObstacle(o);
					}
					break;
				}

				// Disconnect list
				case 'D':
				{
					std::vector<int> disconnectedIDs = GetVehicleDisconnects(msg.payload);
					for (unsigned int i = 0; i < disconnectedIDs.size(); i++) {
						int id = disconnectedIDs[i];
						std::map<int, Vehicle*>::iterator iter = otherVehicles.find(id);
						if (iter != otherVehicles.end()) {
							delete iter->second;
							otherVehicles.erase(iter);
						}
					}
					break;
				}

				// Error message
				case 'E':
				{
					cerr << "Server error: " << msg.payload << endl;
					break;
				}

				}
			}
		}
	}


	const float sleep_time_between_frames_in_seconds = 0.025;

	static double previousTime = getTime();
	const double currTime = getTime();
	const double elapsedTime = currTime - previousTime;
	previousTime = currTime;

	// Do a simulation step
	if (vehicle != NULL) {
		if (!LPressed) {
			vehicle->update(speed, steering, elapsedTime);
		}
		else {
			// Insert code for chasing the vehicle

			//Iterate through other vehicles
			//for (std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) {
				//double currentID = otherVehicles.find(vs.remoteID);
				//if (otherVehicles[1]) {
					//Make vehicle position on top of other 
					double x = otherVehicles[1]->getX();
					double y = otherVehicles[1]->getY();
					double z = otherVehicles[1]->getZ();

					// Fixing rotation problems
					double rotation = otherVehicles[1]->getRotation();
					double myRotation = vehicle->getRotation();

					//if (myRotation > 180) {
					//	myRotation = myRotation - 360;
					//}

					//double angle = myRotation - 180 * atan2(z, x) / PI;

					//if (abs(angle) >= Vehicle::MAX_LEFT_STEERING_DEGS) {
					//	angle = Vehicle::MAX_LEFT_STEERING_DEGS*angle/abs(angle);
					//}

					//vehicle->setRotation(rotation+40);
					vehicle->setPosition(x, y, z);
					vehicle->setRotation(rotation);
					// Make vehicle follow
					steering = otherVehicles[1]->getSteering();
					speed = otherVehicles[1]->getSpeed();
					//vehicle->update(speed, Vehicle::MAX_LEFT_STEERING_DEGS, (elapsedTime + 5));
					vehicle->update(otherVehicles[1]->getSpeed(), otherVehicles[1]->getSteering(), elapsedTime);

				//};
			//}
		}
	}
	for (std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) {
		iter->second->update(elapsedTime);
	}

	display();

#ifdef _WIN32 
	Sleep(sleep_time_between_frames_in_seconds * 1000);
#else
	usleep(sleep_time_between_frames_in_seconds * 1e6);
#endif
};

void keydown(unsigned char key, int x, int y) {

	// Keys that will be held down for extended periods of time will be handled
	// in the idle function
	KeyManager::get()->asciiKeyPressed(key);

	// Keys that react once when pressed rather than need to be held down
	// can be handled normally, like this...
	switch (key) {
	case 27: // ESC key
		exit(0);
		break;
	case '0':
		Camera::get()->jumpToOrigin();
		break;
	case 'p':
		Camera::get()->togglePursuitMode();
		break;
	case 'l':
		// lock the chasing on or off
		LPressed = !LPressed;
		break;
	}

};

void keyup(unsigned char key, int x, int y) {
	KeyManager::get()->asciiKeyReleased(key);
};

void special_keydown(int keycode, int x, int y) {

	KeyManager::get()->specialKeyPressed(keycode);

};

void special_keyup(int keycode, int x, int y) {
	KeyManager::get()->specialKeyReleased(keycode);
};

void mouse(int button, int state, int x, int y) {

};

void dragged(int x, int y) {

	if (prev_mouse_x >= 0) {

		int dx = x - prev_mouse_x;
		int dy = y - prev_mouse_y;

		Camera::get()->mouseRotateCamera(dx, dy);
	}

	prev_mouse_x = x;
	prev_mouse_y = y;
};

void motion(int x, int y) {

	prev_mouse_x = x;
	prev_mouse_y = y;
};


