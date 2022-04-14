#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();
	// Other OpenGL / render setting should be applied here.
	

	// Initialise scene variables
	camera = new Camera(input);
	skybox = new SkyBox(camera,input);

	grass = SOIL_load_OGL_texture
	(
		"gfx/grass.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y
		//SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_INVERT_Y // Depending on texture file type some need inverted others don't.
	);
//	camera->setPosition(0, 0, 15);
	camera->setRotation(0, 0, 0);
	cottag.load("models/cottagesmall.obj", "gfx/cottage.png");
	tree.load("models/tree.obj", "gfx/treeTexture.png");
	pumpkin.load("models/pumpkins.obj", "gfx/pumpkin.png");
	//camera->invertcamera();
	sprintf_s(instruction, "Press v to change the camera.");
	//sprintf_s(instruction1, "Left Click to go back to the main camera");
	camera->setPosition(0, 1, 0);
	shadowPos = 1;
	if (camera->CheckInvert())
		camera->invertcamera();
	rotateLight = 270;

	//Well Wall
	vertices = 20;
	height1 = 20;



}

void Scene::handleInput(float dt)
{
	// Handle user input
	if(ChangeCamera == false&&warp==true)
		camera->handleInput(dt, width, height,warp);
	if (input->isKeyDown('i')) {
		camera->invertcamera();
		input->setKeyUp('i');
	}

	if (input->isKeyDown('v')) {
		ChangeCamera = !ChangeCamera;
		if (ChangeCamera ? TRUE : FALSE);
		input->setKeyUp('v');

	}
	if (input->isKeyDown('m'))
	{
		if (warp == false)
		{
			warp = true;
		}
		else
			warp = false;
	}

	if (input->isKeyDown('r'))
	{
		iswireframe = !iswireframe;
		glPolygonMode(GL_FRONT, iswireframe ? GL_LINE : GL_FILL);
		input->setKeyUp('r');
	}

}

void Scene::update(float dt)
{
	ShowCursor(false);
	// update scene related variables.

	// Calculate FPS for output
	calculateFPS();
	if (ChangeCamera == false)
		camera->update();
	
	rotateLight += 1.6 * dt;

}
void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |GL_STENCIL_BUFFER_BIT );

	// Reset transformations
	glLoadIdentity();
	// Set the camera

	if(ChangeCamera ==true)
		gluLookAt(0.8f, 1.0f, 0.15f, -4.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	if(ChangeCamera==false)
		gluLookAt(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z, camera->getLookAt().x, camera->getLookAt().y, camera->getLookAt().z, camera->getUp().x, camera->getUp().y, camera->getUp().z);
		
	// Render geometry/scene here -------------------------------------
	draw();
	
	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}
void Scene::Shadow() {

	//Shadows
	light.spotLt(0, 1, 0, "WARMWHITE"); // x 20, y 10, z 20

	shadow.generateShadowMatrix(shadowMatrix, lightpos, floorVerts);


	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.1f, 0.1f, 0.1f); // Shadow's colour 
	glPushMatrix();
	glMultMatrixf((GLfloat*)shadowMatrix); //translate to floor and draw shadow, remember to match any transforms on the object
	glScalef(0.5f, 0.5f, 0.5f);
	pumpkin.render();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glScalef(0.5f, 0.5f, 0.5f);
	glTranslatef(0, -1, 0);

	pumpkin.render();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}
void Scene::reflection()
{
	//doing reflection
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);

	glPushMatrix();
	drawquad(0.5);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glPushMatrix();
	glScalef(1.0, 1.0, -1.0);
	glTranslatef(0, 0, 0.3);
	glScalef(0.4f, 0.4f, 0.4f);
	pumpkin.render();
	glPopMatrix();

	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	drawquad(0.5);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	glScalef(0.4f, 0.4f, 0.4f);
	pumpkin.render();
	glPopMatrix();
}

void Scene::draw()
{
	//skybox
	glPushMatrix();
	skybox->renderSkyBox();
	glPopMatrix();

	//sun
	glPushMatrix();
	glRotatef(rotateLight, 0, 0, 1);
	light.pointLt(0, 10, 0, "WARMWHITE",GL_LIGHT0,rotateLight);
	glPopMatrix();

	//moon
	glPushMatrix();
	glRotatef(rotateLight + 180, 0, 0, 1);
	light.pointLt1(0, 10, 0, "BLUE",GL_LIGHT1,rotateLight+180);
	glPopMatrix();

	//base
	glPushMatrix();
	makePlane(20);
	glPopMatrix();

	//Pond
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glScalef(1, 0.03, 1);
	//glRotatef(90, 1, 0, 0);
	glTranslatef(-1.5, 0, -4);
	glColor3f(0.51, 0.32, 0.27);
	DrawWell();

	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-1.5, -4, -0.5);
	glColor3f(0.61, 0.82, 0.85);
	pond.DrawDisc();
	glEnable(GL_LIGHTING);
	glPopMatrix();


	//cottage
	glPushMatrix();
	cottag.render();
	glPopMatrix();
	
	//reflection
	glPushMatrix();
	glTranslatef(-0.5, 0.5, -0.3);
	glRotatef(90, 0, 1, 0);
	glScalef(0.5f, 0.5f, 0.5f);
	reflection();
	glPopMatrix();

	//shadow
	glPushMatrix();
	glTranslatef(1.5, 0.5, 0);
	glScalef(0.5, 0.5, 0.5);
	Shadow();
	glPopMatrix();

	//tree
	glPushMatrix();
	glTranslatef(1, 0, -2.5);
	tree.render();
	glPopMatrix();

	//gravestones
	glPushMatrix();
	graveyardstones();
	glPopMatrix();
}
void Scene::drawquad(float dimension) {

	glPushMatrix();
	glColor4f(0.8f, 0.8f, 1.0f, 0.8f);
	//glTranslatef(0, 0.01, 0);
	//
	//glRotatef(-5, 0, 0, 1);
	glScalef(dimension, dimension, dimension);
	glBegin(GL_QUADS);
	glVertex3f(-0.5f, -0.5f, 0);
	glVertex3f(0.5f, -0.5f, 0);
	glVertex3f(0.5f, 0.5f, 0);
	glVertex3f(-0.5f, 0.5f, 0);
	glEnd();
	glPopMatrix();
}
void Scene::graveyardstones() {
	//first line 

	glPushMatrix();
	glTranslatef(-4, 0.1, 4);
	grave.make_stone();


	glTranslatef(0, 0, -2);
	grave.make_cross();

	glTranslatef(0, 0, -2);
	grave.make_stone();

	glTranslatef(0, 0, -2);
	grave.make_cross();

	glPopMatrix();

	//second line

	glPushMatrix();
	glTranslatef(-2, 0.1, 4);
	grave.make_cross();

	glTranslatef(0, 0, -2);
	grave.make_stone();

	glTranslatef(0, 0, -2);
	grave.make_cross();

	glTranslatef(0, 0, -2);
	grave.make_stone();
	glPopMatrix();

	//third line

	glPushMatrix();
	glTranslatef(4, 0.1, 4);
	grave.make_stone();

	glTranslatef(0, 0, -2);
	grave.make_cross();

	glTranslatef(0, 0, -2);
	grave.make_stone();

	glTranslatef(0, 0, -2);
	grave.make_cross();
	glPopMatrix();

	//forth line

	glPushMatrix();
	glTranslatef(2, 0.1, 4);
	grave.make_stone();

	glTranslatef(0, 0, -2);
	grave.make_cross();

	glTranslatef(0, 0, -2);
	grave.make_stone();

	glTranslatef(0, 0, -2);
	grave.make_cross();

	glPopMatrix();
}
void Scene::makePlane(int dimension) {

	glPushMatrix();
	
	const float sq_size = 0.5f;

	glRotatef(-90.f, 1.f, 0.f, 0.f);
	glTranslatef(-sq_size * dimension / 2.f, -sq_size * dimension / 2.f, 0.f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grass);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_QUADS);
	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++)
		{
			glNormal3f(0.f, 0.f, 1.f);

			glTexCoord2f(x*sq_size, y * sq_size);
			glVertex3f(x * sq_size, y * sq_size, 0.0f);
			glTexCoord2f(x * sq_size, (y * sq_size) + sq_size);
			glVertex3f(x * sq_size, (y * sq_size) + sq_size, 0.0f);
			glTexCoord2f((x * sq_size) + sq_size, (y * sq_size) + sq_size);
			glVertex3f((x * sq_size) + sq_size, (y * sq_size) + sq_size, 0.0f);
			glTexCoord2f((x * sq_size) + sq_size, y * sq_size);
			glVertex3f((x * sq_size) + sq_size, y * sq_size, 0.0f);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}
void Scene::DrawWell() {
	const float steptheta = 2 * M_PI / vertices;
	const float stepheight = height1 / vertices;
	const float textstep = 1.f / vertices;

	float x, y = 0;

	halfheight = 0;
	//glTranslatef(0, -3, 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	glBegin(GL_QUADS);
	for (int i = 0; i < vertices; i++) {
		theta = 0;
		x = 0;

		float nexthalfheight = halfheight + stepheight;

		for (int j = 0; j < vertices; j++) {
			float nexttheta = theta + steptheta;
			//vertex 1
			glTexCoord2f(
				x,
				y
			);
			glVertex3f(
				cos(theta),
				halfheight,
				sin(theta)
			);

			glNormal3f(
				cos(theta),
				halfheight,
				sin(theta)
			);

			//vertex 2
			glTexCoord2f(
				x + textstep,
				y
			);

			glVertex3f(
				cos(nexttheta),
				halfheight,
				sin(nexttheta)
			);
			glNormal3f(
				cos(nexttheta),
				halfheight,
				sin(nexttheta)
			);

			//vertex 3
			glTexCoord2f(
				x + textstep,
				y + textstep
			);

			glVertex3f(
				cos(nexttheta),
				nexthalfheight,
				sin(nexttheta)
			);
			glNormal3f(
				cos(nexttheta),
				nexthalfheight,
				sin(nexttheta)
			);

			//vertex 4

			glTexCoord2f(
				x,
				y + textstep
			);

			glVertex3f(
				cos(theta),
				nexthalfheight,
				sin(theta)
			);
			glNormal3f(
				cos(theta),
				nexthalfheight,
				sin(theta)
			);

			theta = nexttheta;
		}
		halfheight = nexthalfheight;
	}
	glEnd();

}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	//glClearColor(79/255, 105/255, 136/255, 1.0f);
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
	displayText(-1.f, 0.84f, 1.f, 0.f, 0.f, instruction);
	//displayText(-1.f, 0.78f, 1.f, 0.f, 0.f, instruction1);

}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
