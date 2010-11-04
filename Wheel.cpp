#include <iostream>
#include "Wheel.h"

using namespace std;

Wheel::Wheel(GLfloat _x, GLfloat _y, GLfloat _direction[2], GLfloat moto_size, GLint _sens) :
	x(_x), y(_y),
	r_base(moto_size/10.0), height(moto_size/5.0), sens(_sens) {
	direction[0] = _direction[0];
	direction[1] = _direction[1];
}

void Wheel::draw() {
	glPushMatrix();
	glTranslatef(0, 0, height/2.0);
	glRotatef(sens*90, direction[0], direction[1], 0.0);
	glTranslatef(1, 0.0, 1);
	glutSolidCone(r_base,
		      height,
		      N_RINGS,
		      N_SIDES);
	glPopMatrix();
}
