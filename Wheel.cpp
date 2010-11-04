#include <iostream>
#include "Wheel.h"
#include "Moto.h"

using namespace std;

Wheel::Wheel(GLfloat _x, GLfloat _y, GLfloat _direction[2], GLfloat moto_size, GLint _sens) :
	x(_x), y(_y),
	r_base(moto_size/R_BASE_RATIO), height(moto_size/HEIGHT_RATIO), sens(_sens) {
	direction[0] = _direction[0];
	direction[1] = _direction[1];
}

void Wheel::draw() {
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glRotatef(sens*90, direction[0], direction[1] , 0.0);
	glutSolidCone(r_base,
		      height,
		      N_RINGS,
		      N_SIDES);
	glPopMatrix();
}
