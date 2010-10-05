#include <GL/glut.h>
#include <assert.h>

#include "Board.h"

GLfloat BoardColor[3] = {0, 0, 1};
GLfloat LineColor[3] = {1, 0, 0};

/**
 * Constructeurs
 */
Board::Board() {
}

Board::Board(float s) {
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
void Board::set_dim(float s) {
	assert(s>0);
	s = side;
}

float Board::get_side() {
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
	float lineh, linev;
	/* Antialiassing des lignes */
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);

	glBegin(GL_QUADS); {
		glColor3fv(BoardColor);
		glNormal3fv(n);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
		glVertex3fv(v[3]);
		glEnd();
	}
	glColor3fv(LineColor);
	for (int i=D_LINE; i<=side-D_LINE; i+=D_LINE) {
		lineh = i*v[0][1]+(side-i)*v[1][1];
		linev = i*v[3][0]+(side-i)*v[0][0];
		/* Lignes // (Ox) */
		glBegin(GL_LINES);
		glVertex3f(v[0][0], lineh/side, 0.1);
		glVertex3f(v[3][0], lineh/side, 0.1);
		glEnd();
		/* Lignes // (Oy) */
		glBegin(GL_LINES);
		glVertex3f(linev/side, v[0][1], 0.1);
		glVertex3f(linev/side, v[1][1], 0.1);
		glEnd();
	}
}
