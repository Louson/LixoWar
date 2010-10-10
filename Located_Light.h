#ifndef _LOCATED_LIGHT_H
#define _LOCATED_LIGHT_H

#include <GL/glut.h>

#include "Config.h"
#include "Light.h"


class Located_Light : public Light {
public :
	Located_Light();
	Located_Light(GLenum n, GLfloat location[4], GLfloat color[4]);
	Located_Light(GLenum n, GLfloat location[4],
		      GLfloat diffuse[4], GLfloat ambient[4], GLfloat specular[4]);
	void set_attenuation(GLfloat constant, GLfloat linear, GLfloat Quad);

	void init();
protected :
	GLfloat Location[4];
};

#endif
