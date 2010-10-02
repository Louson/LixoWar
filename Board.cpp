#include <GL/glut.h>
#include "Board.h"
#include <assert.h>

/**
 * Constructeurs
 */
Board::Board() {
}

Board::Board(double s) {
	assert(s>0);
	side = s;
	set_normal(0, 0, 1);
	set_vertex(0,  s/2, -s/2, 0);
	set_vertex(1,  s/2,  s/2, 0);
	set_vertex(2, -s/2,  s/2, 0);
	set_vertex(3, -s/2, -s/2, 0);
}

/**
 * Accesseurs
 */
void Board::set_dim(double s) {
	assert(s>0);
	s = side;
}

double Board::get_side() {
	assert( side>0 );
	return side;
}

void Board::set_normal(float x, float y, float z) {
	n[0] = x;
	n[1] = y;
	n[2] = z;
}

void Board::set_vertex(int ve, float x, float y, float z) {
	v[ve][0] = x;
	v[ve][1] = y;
	v[ve][2] = z;
}

/**
 * Méthodes
 */
void Board::drawBoard() {
	
	glBegin(GL_QUADS); {
		glColor3f(0, 0, 1);
		glNormal3fv(n);
		glVertex3fv(v[0]);
		glColor3f(1, 0, 0);
		glVertex3fv(v[1]);
		glColor3f(0, 1, 0);
		glVertex3fv(v[2]);
		glColor3f(0, 0, 0);
		glVertex3fv(v[3]);
		glEnd();
	}
}
