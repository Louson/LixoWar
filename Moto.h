#ifndef _MOTO_H
#define _MOTO_H

#include <GL/glut.h>

#include "Camera_Persp.h"
#include "Drawable.h"

#define MOTO_SIZE 100

class Moto : public Drawable{
public :
	Moto();
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
