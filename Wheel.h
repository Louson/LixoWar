#ifndef _WHEEL_H
#define _WHEEL_H

#include <GL/glut.h>
#include "Drawable.h"

#define N_SIDES 30
#define N_RINGS 30

class Wheel : public Drawable{
public :
	Wheel(GLfloat _x, GLfloat _y, GLfloat _direction[2], GLfloat moto_size, GLint _sens);
	void draw();
private :
	GLfloat x;
	GLfloat y;
	GLfloat direction[2];
	GLfloat r_base;
	GLfloat height;
	GLint sens;
};

#endif
