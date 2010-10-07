#ifndef _MOTO_H
#define _MOTO_H

#include <GL/glut.h>
#include "Camera_Persp.h"

class Moto {
public :
	Moto();
	Moto(GLfloat start_x, GLfloat start_y);
	void drawMoto();
	void setCam();
private :
	GLfloat x;
	GLfloat y;
	Camera_Persp cam;
};

#endif
