#ifndef _MOTO_H
#define _MOTO_H

#include <GL/glut.h>

#include "Camera_Persp.h"
#include "Drawable.h"

#define MOTO_SIZE 4.0
#define VIEW_DIST 200000.0

static const GLfloat MotoDiffuse[3] = {0, 1.0, 0};
static const GLfloat MotoAmbient[3] = {1.0, 0.0, 0.0};
static const GLfloat MotoSpecular[3] = {1.0, 0.0, 0.0};
static const GLfloat MotoShininess = 120;

class Moto : public Drawable{
public :
	Moto(GLfloat start_x, GLfloat start_y, GLfloat start_d[2]);
	void draw();
	void setCam();
	void activateCam();
    Camera_Persp * getPtCam();
private :
	GLfloat x;
	GLfloat y;
	GLfloat direction[2];
	Camera_Persp cam;
};

#endif
