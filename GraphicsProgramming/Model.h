// Model class, represents a loaded OBJ model
// handles the loading/processing of the model file. Also loads and stores its own texture
// NOT complete, for students to complete. Model data requires being sorted and the render function needs completed.
#ifndef _MODEL_H_
#define _MODEL_H_

// INCLUDES //

#include <glut.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
#include<iostream>
#include"Input.h"
#include <chrono>
#include <thread>


using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::cout;
using std::endl;
using std::this_thread::sleep_for;

// MY CLASS INCLUDES //
#include <vector>
#include "Vector3.h"
#include "SOIL.h"
#include<string>

typedef std::chrono::steady_clock the_clock;

class Model
{

public:

	Model(Input* in) {
		input = in;
	}
	bool load(char* modelFilename);
	void render();
	void loadTexture();
	void time_day(int);
	int getTime() { return time; }
protected:


	bool loadModel(char*);
	
	//Input
	Input* input;

	// model texture
	GLuint texture[24];
	vector<char*> filenames;

	//storage
	vector<Vector3> vertex, normals, texCoords; 

	//changing texture
	int time = 0;
	int j = 0;
};

#endif