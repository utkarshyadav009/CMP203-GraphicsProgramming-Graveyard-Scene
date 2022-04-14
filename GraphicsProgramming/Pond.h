#pragma once
#include<iostream>
#define _USE_MATH_DEFINES
using namespace std;
#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "SOIL.h"
#include<math.h>



class Pond
{
	float theta1, theta2, theta;
	float r;
	int vertices;


public:
	Pond();
	void DrawDisc();

};

