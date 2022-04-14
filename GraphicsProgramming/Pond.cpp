#include "Pond.h"
Pond::Pond() {
	vertices = 20;
	

}



void Pond::DrawDisc() {
	glPushMatrix();
	
	theta = (2 * 3.14) / vertices; 

	glBegin(GL_TRIANGLES);
	for (float angle = 0; angle < 2 * M_PI; angle += theta) {

		glTexCoord2f((0 / 2) + 0.5, (0 / 2) + 0.5);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, 0);

		glTexCoord2f((cos(angle) / 2) + 0.5, (sin(angle) / 2) + 0.5);
		glNormal3f(0, 0, -1);
		glVertex3f(cos(angle), sin(angle), 0);

		glTexCoord2f((cos(angle + theta) / 2) + 0.5, (sin(angle + theta) / 2) + 0.5);
		glNormal3f(0, 0, -1);
		glVertex3f(cos(angle + theta), sin(angle + theta), 0);

	}
	glEnd();
	glPopMatrix();
}
