#ifndef _MOTO_H
#define _MOTO_H

#include <GL/glut.h>

#include "Camera_Persp.h"
#include "Camera_Ortho.h"
#include "Drawable.h"
#include "Wheel.h"

#define MOTO_WIDTH 4.0
#define MOTO_LENGTH 4.0
#define VIEW_DIST 200000.0

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
	void setCam();
	void setCam_ext();
	void activateCam();
	Camera_Persp * getPtCam();
	void activateCam_ext();
	Camera_Ortho * getPtCam_ext();
    void move(int dx, int dy);
private :
	GLfloat x;
	GLfloat y;
	GLfloat direction[2];
	Camera_Persp cam;
	Camera_Ortho cam_ext;

	GLfloat moto_size;

	Wheel wheelNW;
	Wheel wheelNE;
	Wheel wheelSE;
	Wheel wheelSW;

	void drawCube(void);
};

#endif
