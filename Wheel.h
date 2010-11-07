#ifndef _WHEEL_H
#define _WHEEL_H

#include <GL/glut.h>
#include "Drawable.h"

#define N_SIDES 30
#define N_RINGS 30

#define R_BASE_RATIO 10.0
#define HEIGHT_RATIO 5.0

class Wheel : public Drawable{
public :
	Wheel(GLfloat _dx, GLfloat _dy, GLfloat _direction[2], GLfloat moto_size, GLint _sens);
    void setMotoPos(GLfloat _x, GLfloat _y);
	void draw();
private :
	GLfloat dx;
	GLfloat dy;
	GLfloat x;
	GLfloat y;
	GLfloat direction[2];
	GLfloat r_base;
	GLfloat height;
	GLint sens;
};

#endif
