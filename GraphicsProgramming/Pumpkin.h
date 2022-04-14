#pragma once
#include <glut.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
#include<iostream>
#include"Input.h"
#include <chrono>
#include <thread>


#include <vector>
#include "Vector3.h"
#include "SOIL.h"
#include<string>

using namespace std;

class Pumpkin
{
public:
	bool load(char* modelFilename, char* textureFilename);
	void render();

private:

	void loadTexture(char*);
	bool loadModel(char*);

	// model texture
	GLuint texture;

	// Stoagre for sorted data
	//vector<Vector3> vertex, normals, texCoords;
	vector<Vector3> vertex, normals, texCoords;

	//changing texture
};

