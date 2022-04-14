#include "Camera.h"
#include <stdio.h>


static const float mov_speed = 10.f;
static const float rotate_speed = 30.f;
void Camera::update()
{
	float cosR, cosP, cosY;  //temp values for sin/cos from 
	float sinR, sinP, sinY;
	
	// Roll, Pitch and Yallare variables stored by the camera
	// handle rotation
	// Only want to calculate these values once, when rotation changes, not every frame. 
	cosY= cosf(Yaw*3.1415 / 180);
	cosP= cosf(Pitch*3.1415/180);
	cosR= cosf(Roll*3.1415/180);
	sinY= sinf(Yaw*3.1415/180);
	sinP= sinf(Pitch*3.1415/180);
	sinR = sinf(Roll * 3.1415 / 180);



	 
	//This using the parametric equation of a sphere
	// Calculate the three vectors to put into glu Lookat
	// Look direction, position and the up vector
	// This function could also calculate the right vector
	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;



	// Look At Point
	// To calculate add Forward Vector to Camera position.
	// Up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;
	
	
	// Side Vector (right)
	// this is a cross product between the forward and up vector.
	// If you don’t need to calculate this, don’t do it. 

	right = forward.cross(up);

	LookAt = position + forward;
}


void Camera::handleInput(float dt,float width,float height,bool warp)
{
	if (input->isKeyDown('w'))
	{
		position.add(forward, mov_speed * dt);
	}

	if (input->isKeyDown('s'))
	{
		position.add(forward, -mov_speed * dt);
		
	}
	if (input->isKeyDown('a'))
	{
		position.add(right, -mov_speed * dt);
	}
	if (input->isKeyDown('d'))
	{
		position.add(right, mov_speed * dt);
	}

	//rotation
	
	//if (input->isKeyDown('l'))
	//{
	//	Roll += rotate_speed * dt;
	//}
	//if (input->isKeyDown('j'))
	//{
	//	Roll -= rotate_speed * dt;
	//}
	//if (input->isKeyDown('i'))
	//{
	//	Pitch += rotate_speed * dt;
	//}
	//if (input->isKeyDown('k'))
	//{
	//	Pitch -= rotate_speed * dt;
	//}if (input->isKeyDown('o'))
	//{
	//	Yaw += rotate_speed * dt;
	//}
	//if (input->isKeyDown('p'))
	//{
	//	Yaw -= rotate_speed * dt;
	//}
	
	//mouse Movement
	mousex = input->getMouseX();
	mousey = input->getMouseY();
	
	centre[0] = (width / 2);
	centre[1] = (height / 2);


	Yaw -= -(mousex - centre[0]) * dt * 2.f;
	Pitch += -(mousey - centre[1]) * dt * 2.f;

	if (warp == true) {
		glutWarpPointer(centre[0], centre[1]);
	}

	//printf("rot: %f, %f, %f\n", Yaw, Pitch, Roll);
}
void Camera::invertcamera() {
	Roll = 180;
}
bool Camera::CheckInvert() {
	if (Roll > 180) {
		return true;
	}
	else
		false;
}
void Camera::setLookAt(int x, int y, int z) {
	LookAt.x = x;
	LookAt.y = y;
	LookAt.z = z;

}
void Camera::setPosition(int x,int y,int z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Camera::setRotation(int x, int y, int z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;

}

void Camera::calLookAt()
{
	LookAt = position + forward;

}


void Camera::setForward(Vector3 a)
{
	forward.set(a.getX(), a.getY(), a.getZ());

}


void Camera::setRight(Vector3 a)
{
	right.set(a.getX(), a.getY(),a.getZ());
}


void Camera::setUp(Vector3 a)
{
	up.set(a.getX(), a.getY(), a.getZ());
}