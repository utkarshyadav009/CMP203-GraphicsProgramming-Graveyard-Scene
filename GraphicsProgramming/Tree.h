// Tree class, represents a loaded tree  OBJ model
// handles the loading/processing of the tree file. Also loads and stores its own texture
#pragma once
#ifndef _TREE_H_
#define _TREE_H_


// INCLUDES //
#include <glut.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
#include<iostream>
using namespace std;

// MY CLASS INCLUDES //
#include <vector>
#include "Vector3.h"
#include "SOIL.h"

class Tree
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


};
#endif