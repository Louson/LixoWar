#ifndef _MOTO_H
#define _MOTO_H

#include <GL/glut.h>

#include "Drawable.h"
#include "Wheel.h"

#define MOTO_WIDTH      4.0
#define MOTO_LENGTH     4.0

/* Wheels settings */
#define FRONT_WHEELS_H_DISTANCE_RATIO   1/4
#define BACK_WHEELS_H_DISTANCE_RATIO    1/2
#define FRONT_WHEELS_W_DISTANCE_RATIO   1/3

static const GLfloat MotoDiffuse[3] = {0.1, 0.2, 0.4};
static const GLfloat MotoAmbient[3] = {0.2, 0.2, 0.2};
static const GLfloat MotoSpecular[3] = {1.0, 0.0, 0.0};
static const GLfloat MotoShininess = 120;

class Moto : public Drawable{
public :
	Moto(GLfloat moto_size);
	void draw();
	void setPos(int _x, int _y, int _angle);

private :
	GLfloat x;
	GLfloat y;

	GLint angle;

	GLfloat moto_size;

	Wheel wheelNW;
	Wheel wheelNE;
	Wheel wheelSE;
	Wheel wheelSW;
};

typedef struct moto_struct {
        int x;
        int y;
        int angle;
        Moto * pt_moto;
} MOTO_STRUCT;

#endif
