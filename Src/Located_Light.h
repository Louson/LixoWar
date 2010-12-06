#ifndef _LOCATED_LIGHT_H
#define _LOCATED_LIGHT_H

#include <GL/glut.h>

#include "Config.h"
#include "Light.h"

class Located_Light : public Light {
public :
	Located_Light(LIGHT * light);
	void set_attenuation(GLfloat constant, GLfloat linear, GLfloat Quad);
	void init();
protected :
	GLfloat location[4];
};

#endif
