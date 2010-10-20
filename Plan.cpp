#include <GL/glut.h>
#include <stdexcept>
#include <iostream>

#include "Config.h"
#include "Plan.h"

using namespace std;

/**
 * Constructeurs
 */
Plan::Plan(GLfloat x, GLfloat y): side_x(x), side_y(y) {

	set_normal(0, 0, 1);
	set_vertex(0,  x/2, -y/2, 0);
	set_vertex(1,  x/2,  y/2, 0);
	set_vertex(2, -x/2,  y/2, 0);
	set_vertex(3, -x/2, -y/2, 0);
}

/* Mutateurs */
void Plan::set_normal(GLfloat x, GLfloat y, GLfloat z) {
	n[0] = x;
	n[1] = y;
	n[2] = z;
}

void Plan::set_vertex(int ve, GLfloat x, GLfloat y, GLfloat z) {
	v[ve][0] = x;
	v[ve][1] = y;
	v[ve][2] = z;
}
