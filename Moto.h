#ifndef _MOTO_H
#define _MOTO_H

#include <GL/glut.h>
#include "Camera_Persp.h"

class Moto {
public :
	Moto();
	Moto(GLfloat start_x, GLfloat start_y, GLfloat start_d[2]);
	void drawMoto();
	void setCam();
	void activateCam();
private :
	GLfloat x;
	GLfloat y;
	GLfloat direction[2];
	Camera_Persp cam;
};

#endif
