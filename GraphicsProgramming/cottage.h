// cottage class, represents a loaded cottage OBJ model
// handles the loading/processing of the cottage file. Also loads and stores its own texture
#ifndef _COTTAGE_H_
#define _COTTAGE_H_


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

class cottage
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