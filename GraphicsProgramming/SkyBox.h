#pragma once

#include "glut.h"
#include "Input.h"
#include "SOIL.h"
#include "Camera.h"
#include "Model.h"
#include<string>
class SkyBox
{
public:
	SkyBox(Camera* cam,Input* in) {
		camera = cam;
		input = in;
		model = new Model(input);
		//import skybox texture image
		model->load("models/largeSphere.obj");
		model->loadTexture();
	}
	void renderSkyBox();
	Camera* camera;
	Model* model;
	Input* input;
};

