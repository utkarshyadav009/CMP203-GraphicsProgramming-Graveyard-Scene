#include "SkyBox.h"

void SkyBox::renderSkyBox()
{
	glPushMatrix();
	glTranslatef(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	model->render();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}