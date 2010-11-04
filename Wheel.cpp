#include "Wheel.h"

Wheel::Wheel(GLfloat _x, GLfloat _y, GLfloat _direction[2], GLfloat moto_size) :
	x(_x), y(_y),
	r_int(moto_size/20.0),
	r_ext(moto_size/5.0) {
	direction[0] = _direction[0];
	direction[0] = _direction[1];
}

void Wheel::draw() {
	glBegin(GL_POLYGON);
	glPushMatrix();
	glutSolidTorus(r_int,
		       r_ext,
		       N_SIDES,
		       N_RINGS);
//	glRotatef(90, direction[0], direction[1], 0.0);
	glTranslatef(x, y, 0.0);
	glPopMatrix();
	glEnd();
}
