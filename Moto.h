#ifndef _MOTO_H
#define _MOTO_H

#include <GL/glut.h>

#include "Camera_Persp.h"
#include "Camera_Ortho.h"
#include "Drawable.h"
#include "Wheel.h"

#define MOTO_WIDTH      4.0
#define MOTO_LENGTH     4.0

/* Wheels settings */
#define FRONT_WHEELS_DISTANCE_RATIO     1/4
#define BACK_WHEELS_DISTANCE_RATIO      1/2

/* projection settings */
#define VIEW_DIST       200000.0
#define FOVY            100

#define PROJ_SIZE 50
#define PERSP_HEIGHT 3

static const GLfloat MotoDiffuse[3] = {0.1, 0.2, 0.4};
static const GLfloat MotoAmbient[3] = {0.2, 0.2, 0.2};
static const GLfloat MotoSpecular[3] = {1.0, 0.0, 0.0};
static const GLfloat MotoShininess = 120;

class Moto : public Drawable{
public :
	Moto(GLfloat start_x, GLfloat start_y, GLfloat start_d[2], GLfloat moto_size);
	void draw();
	Camera_Persp * getPtCamPersp();
	Camera_Ortho * getPtCamOrtho();
        void move(int dx, bool turn = false);
        void setOrthoCam(void);
	void setPerspCam(void);

private :
	GLfloat x;
	GLfloat y;
	GLfloat direction[2];
	Camera_Persp cam_persp;
	Camera_Ortho cam_ortho;

	GLfloat moto_size;

	Wheel wheelNW;
	Wheel wheelNE;
	Wheel wheelSE;
	Wheel wheelSW;
};

#endif
