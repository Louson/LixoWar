#include "Camera.h"
#include "Config.h"

void Camera::set_position(GLfloat xp, GLfloat yp, GLfloat zp,
			  GLfloat xc, GLfloat yc, GLfloat zc,
			  GLfloat xup, GLfloat yup, GLfloat zup) {
	x = xp;
	y = yp;
	z = zp;
	x_center = xc;
	y_center = yc;
	z_center = zc;
	x_up_direction = xup;
	y_up_direction = yup;
	z_up_direction = zup;
}

void Camera::lookAt() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
		  x_center, y_center, z_center,
		  x_up_direction, y_up_direction, z_up_direction);
	
}
