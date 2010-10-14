#include "Camera_Persp.h"

void Camera_Persp::set_view(GLfloat f, GLfloat r, GLfloat near, GLfloat far) {
	field = f;
	ratio = r;
	znear = near;
	zfar = far;
}

void Camera_Persp::activate() {
	lookAt();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 	gluPerspective(field, ratio, znear, zfar);
}
