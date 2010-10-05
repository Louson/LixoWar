#ifndef _LOCATED_LIGHT_H
#define _LOCATED_LIGHT_H

#include <GL/glut.h>

#include "Light.h"

class Located_Light : public Light {
public :
	Located_Light();
	Located_Light(GLenum n, GLfloat location[4], GLfloat color[4]);
	Located_Light(GLenum n, GLfloat location[4],
		      GLfloat diffuse[4], GLfloat ambient[4], GLfloat specular[4]);
	void init();
private :
	GLfloat Location[4];
};

#endif
