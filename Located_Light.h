#ifndef _LOCATED_LIGHT_H
#define _LOCATED_LIGHT_H

#include <GL/glut.h>

#include "Config.h"
#include "Light.h"

#define L_LOCATION {0, 0, -4.1*SIDE_X}
#define L_DIFFUSE {1.0, 1.0, 1.0, 1.0}
#define L_AMBIENT {0.01, 0.01, 0.01, 1.0}
#define L_SPECULAR {1.0, 1.0, 1.0, 1.0}
extern GLfloat L_Location[3];
extern GLfloat L_Diffuse[4];
extern GLfloat L_Ambient[4];
extern GLfloat L_Specular[4];

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
