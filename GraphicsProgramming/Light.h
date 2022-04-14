#pragma once
// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include <iostream>
#include"Vector3.h"
#include<string>
using namespace std;

class Light
{
public:
	Light();
	Vector3 selectColor(string color);

	void spotLt(float x, float y, float z, string color);
	void directionalLt(float x, float y, float z, string color);
	void pointLt(float x, float y, float z, string color, GLenum light,float);
	void pointLt1(float x, float y, float z, string color, GLenum light, float);
	void ambientLt(string color);




protected:
	float sunarc;
	float moonarc;

private:
	Vector3 colorVector;
	Vector3 retColorVector;
};