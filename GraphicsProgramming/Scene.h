// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include"shadow1.h"
#include <vector>
#include"SkyBox.h"
#include"Camera.h"
#include"Model.h"
#include"cottage.h"
#include"Light.h"
#include"Gravestone.h"
#include"Tree.h"
#include"Pumpkin.h"
#include"Pond.h"
class Scene{

public:
	Scene(Input *in);
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);
	//making the main plane
	void makePlane(int);
	//drawing all the elements
	void draw();
	//drawing all the objects
	void graveyardstones();
	//drawing a quad 
	void drawquad(float);
	//drawing reflection 
	void reflection();
	//shadow
	void Shadow();
	//clouds
	void DrawWell();
protected:
	// configure opengl render pipeline
	void initialiseOpenGL();
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();


	// Class Objects and pointers
	Camera* camera;
	SkyBox* skybox;
	Light light;
	cottage cottag;
	Gravestone grave;
	Tree tree;
	Pumpkin pumpkin;
	shadow1 shadow;
	Pond pond;
	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];
	char instruction[40];
	char instruction1[50]; 
	// position and stuff variables
	int light_position=0;
	
	//base plane texture
	GLuint grass;

	//changing camera 
	bool ChangeCamera = false;
	bool iswireframe = false;
	bool warp = false;


	//shadow
	float shadowPos;
	float rotateLight;

	float lightpos[3] = { 0,1,0};
	float shadowMatrix[16];
	GLfloat floorVerts[12] = { -1, -1,-1,
							 -1, -1, 1,
							  1, -1,-1,
							  1, -1, 1 };



	//well
	float theta1, theta2, theta;
	float r;
	int vertices;
	int halfheight;
	int height1;
};

#endif