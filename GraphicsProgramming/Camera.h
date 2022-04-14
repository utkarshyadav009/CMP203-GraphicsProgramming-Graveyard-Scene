#pragma once
#include "Input.h"
#include"Vector3.h"
#include<vector>
#include<math.h>
#include<iostream>
#include<stdio.h>
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
using namespace std;
class Camera
{
private:
	Input* input;

	Vector3 position;
	Vector3 rotation;
	Vector3 LookAt;
	Vector3 up;
	Vector3 forward;
	Vector3 right;
	Vector3 move;
	float mousex, mousey;
	float Pitch = 0 , Yaw = 0, Roll = 0; 
	float centre[1];

public:
	Camera(Input* in) {
		input = in;
	}
	void update();

	void setPosition(int, int, int);
	void setRotation(int, int, int);
	void setLookAt(int, int, int);
	void calLookAt();
	void invertcamera();
	void setUp(Vector3);
	void setForward(Vector3);
	void setRight(Vector3);
	bool CheckInvert();

	Vector3 getPosition() { return position; };
	Vector3 getLookAt() { return LookAt; };
	Vector3 getUp() { return up; };
	Vector3 getForward() { return forward; };
	Vector3	getRight() { return right; };

	void handleInput(float dt,float, float,bool);
};

