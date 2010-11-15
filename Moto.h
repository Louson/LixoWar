#ifndef _MOTO_H
#define _MOTO_H

#include <GL/glut.h>

#include "Drawable.h"
#include "Wheel.h"
#include "Color.h"

#define MOTO_WIDTH      4.0
#define MOTO_LENGTH     4.0

/* Wheels settings */
#define FRONT_WHEELS_H_DISTANCE_RATIO   1/4
#define BACK_WHEELS_H_DISTANCE_RATIO    1/2
#define FRONT_WHEELS_W_DISTANCE_RATIO   1/3

class Moto : public Drawable{
public :
	Moto(GLfloat moto_size);
	void draw();
	void setPos(int _x, int _y, int _angle);

private :
        Color color;
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
        double x;
        double y;
        int angle;
        float speed;
        Moto * pt_moto;
} MOTO_STRUCT;

#endif
