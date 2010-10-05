#include <math.h>

#include "Config.h"
#include "Camera_Ortho.h"

Camera_Ortho::Camera_Ortho() {
}

void Camera_Ortho::set_view(GLfloat left, GLfloat right,
			    GLfloat down, GLfloat up,
			    GLfloat near,GLfloat  far) {
	xmin = left;
	xmax = right;
	ymin = down;
	ymax = up;
	znear = near;
	zfar = far;
}

void Camera_Ortho::activer() {
	lookAt();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xmin, xmax, ymin, ymax, znear, zfar);	
}
