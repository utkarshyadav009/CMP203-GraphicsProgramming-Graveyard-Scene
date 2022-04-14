#pragma once
// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
#include "SOIL.h"
#include"Vector3.h"


class Gravestone
{
protected:
	GLuint grave;
	int x = 0.5;
public:
	Gravestone() {
		grave = SOIL_load_OGL_texture
		(
			"gfx/gravestone.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y // Depending on texture file type some need inverted others don't.
		);

	}
	void rendercube(float,float,float);
	void make_stone();
	void make_cross();

};

