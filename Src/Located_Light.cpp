#include "Located_Light.h"

Located_Light::Located_Light(LIGHT * light):
        Light(light)
{
	for (int i=0 ; i < 3 ; i++) {
		location[i] = light->location[i];
		diffuse[i] = light->diffuse[i];
		ambient[i] = light->ambient[i];
		specular[i] = light->specular[i];
	}
	location[3] = 1.0;
	diffuse[3] = light->diffuse[3];
	ambient[3] = light->ambient[3];
	specular[3] = light->specular[3];
}

void Located_Light::set_attenuation(GLfloat constant, GLfloat linear, GLfloat Quad) {
	glLightf(light, GL_CONSTANT_ATTENUATION, constant);
	glLightf(light, GL_LINEAR_ATTENUATION, linear);
	glLightf(light, GL_QUADRATIC_ATTENUATION, Quad);
}

void Located_Light::init() {
	glEnable(light);
	glMatrixMode(GL_MODELVIEW);
	glLightfv(light, GL_POSITION, location);
	glLightfv(light, GL_DIFFUSE, diffuse);
	glLightfv(light, GL_AMBIENT, ambient);
	glLightfv(light, GL_SPECULAR, specular);
}
