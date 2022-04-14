#include "Light.h"

Light::Light() {
	sunarc = 270;
	moonarc = 270;
}

Vector3 Light::selectColor(string color) { //color based on function input

	switch (hash<std::string>{}(color)) {

	case 750204685: //"BLUE"
		retColorVector.set(0.75f, 0.75f, 0.75f);
		//retColorVector.set(0.309f, 0.411f, 0.533f);
		return retColorVector;


	case 2823601493: //"WARMWHITE"
		retColorVector.set(1.f, 0.9f, 0.7f);
		return retColorVector;


	
	}
}


void Light::spotLt(float x, float y, float z, string color) {
	colorVector = selectColor(color);
	glPushMatrix();
	GLfloat Light_Ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat Light_Diffuse[] = { colorVector.x,colorVector.y,colorVector.z, 1.0f };
	GLfloat Light_Position[] = { x, y, z, 1.0f };
	GLfloat spot_Direction[] = { 0.0f, -1.0f, 0.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, Light_Position);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 175.f);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_Direction);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 50.0);
	glEnable(GL_LIGHT2);
	//light bulb
	glTranslatef(x, y, z);
	glScalef(0.5f, 0.1f, 0.1f);
	glColor3f(1, 1, 1);
	gluSphere(gluNewQuadric(), 0.20, 20, 20);
	glPopMatrix();
}


void Light::directionalLt(float x, float y, float z, string color) {
	colorVector = selectColor(color);
	glPushMatrix();
	GLfloat Light_Ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat Light_Diffuse[] = { colorVector.x,colorVector.y,colorVector.z, 1.0f };
	GLfloat Light_Position[] = { x, y, z, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);
	glEnable(GL_LIGHT0);
	//light bulb
	glTranslatef(x, y, z);
	//glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	gluSphere(gluNewQuadric(), 0.20, 20, 20);
	glEnable(GL_LIGHTING);
	//glPopMatrix();
	glPopMatrix();
}

void Light::pointLt(float x, float y, float z, string color,GLenum light,float lightPos) {  // a light that iluminates in every direction
	colorVector = selectColor(color);
	glPushMatrix();
	GLfloat Light_Ambient[] = { 0.7f, 0.7f, 0.7f, 0.7f };
	GLfloat Light_Diffuse[] = { colorVector.x,colorVector.y,colorVector.z, 1.0f };
	//GLfloat Light_Diffuse[] = { 0.309f,0.411f,0.533, 1.0f };
	GLfloat Light_Position[] = { x, y, z, 1.0f };
	glLightfv(light, GL_AMBIENT, Light_Ambient);
	glLightfv(light, GL_DIFFUSE, Light_Diffuse);
	glLightfv(light, GL_POSITION, Light_Position);

	if(sunarc>lightPos-180)
		glEnable(light);	
	if (sunarc < (lightPos - 180)) {
		glDisable(light);
		
		if (lightPos - 180 > sunarc + 180) {
			sunarc = sunarc + 360;
		}

	}
	//sun
	glTranslatef(x, y, z);
	glDisable(GL_LIGHTING);
	glColor3f(0.870f, 0.725f, 0.086f);
	gluSphere(gluNewQuadric(), 1.0, 40, 40);
	glEnable(GL_LIGHTING);
	glPopMatrix();

}
void Light::pointLt1(float x, float y, float z, string color, GLenum light, float lightPos) {  // a light that iluminates in every direction
	colorVector = selectColor(color);
	glPushMatrix();
	GLfloat Light_Ambient[] = { 0.7f, 0.7f, 0.7f, 0.7f };
	GLfloat Light_Diffuse[] = { colorVector.x,colorVector.y,colorVector.z, 1.0f };
	//GLfloat Light_Diffuse[] = { 0.309f,0.411f,0.533, 1.0f };
	GLfloat Light_Position[] = { x, y, z, 1.0f };
	glLightfv(light, GL_AMBIENT, Light_Ambient);
	glLightfv(light, GL_DIFFUSE, Light_Diffuse);
	glLightfv(light, GL_POSITION, Light_Position);
	if (moonarc > lightPos - 180)
		glEnable(light);
	//cout << moonarc << " : " << lightPos - 180 << endl;

	if (moonarc < (lightPos - 180)) {
		glDisable(light);

		if (lightPos - 180 > moonarc + 180) {
			moonarc = moonarc + 360;
		}

	}
	//sun
	glTranslatef(x, y, z);
	glDisable(GL_LIGHTING);
	glColor3f(0.729f, 0.729f, 0.694f);
	gluSphere(gluNewQuadric(), 0.50, 20, 20);
	glEnable(GL_LIGHTING);
	glPopMatrix();

}


void Light::ambientLt(string color) {

	colorVector = selectColor(color);
	glPushMatrix();
	GLfloat Light_Ambient[] = { colorVector.x,colorVector.y,colorVector.z, 0.1f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
	glEnable(GL_LIGHT0);
	glPopMatrix();
}