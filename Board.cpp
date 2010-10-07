#include <GL/glut.h>
#include <stdexcept>

#include "Config.h"
#include "Board.h"
#include "Moto.h"

using namespace std;

GLfloat BoardEmission[3] = {0.0, 1.0, 0.0};
GLfloat BoardDiffuse[3] = {0, 0.5, 1.0};
GLfloat BoardAmbient[3] = {1.0, 0.0, 0.0};
GLfloat BoardSpecular[3] = {1.0, 0.0, 0.0};
GLfloat BoardShininess = 120;
GLfloat LineColor[3] = {1, 0, 0};

/**
 * Constructeurs
 */
Board::Board() {
}

Board::Board(GLfloat x, GLfloat y): side_x(x), side_y(y) {

	if (side_x < 2*D_LINE_X || side_y < 2*D_LINE_Y) {
		throw(range_error("Dimensions insuffisantes"));
	}
	set_normal(0, 0, 1);
	set_vertex(0,  x/2, -y/2, 0);
	set_vertex(1,  x/2,  y/2, 0);
	set_vertex(2, -x/2,  y/2, 0);
	set_vertex(3, -x/2, -y/2, 0);
}

/* Mutateurs */
void Board::set_normal(GLfloat x, GLfloat y, GLfloat z) {
	n[0] = x;
	n[1] = y;
	n[2] = z;
}

void Board::set_vertex(int ve, GLfloat x, GLfloat y, GLfloat z) {
	v[ve][0] = x;
	v[ve][1] = y;
	v[ve][2] = z;
}

/**
 * Méthodes
 */
void Board::drawBoard() {
	GLfloat lineh, linev;
	GLfloat s_x = SIDE_X/QUALITY_X;
	GLfloat s_y = SIDE_Y/QUALITY_Y;
	Moto m(0, 0);

	/* Antialiassing des lignes */
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);

	m.drawMoto();

	/* Test de sphere */
// //	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, BoardColor);
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, BoardAmbient);
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BoardDiffuse);;
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, BoardSpecular);
// 	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, BoardShininess);
// 	glColor3f(1.0, 0, 0);
//  	gluSphere(gluNewQuadric(), 5000, 32, 32);
	/******************/

// 	glBegin(GL_LINES);
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, LineColor);
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, LineColor);
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LineColor);
// 	glVertex3f(0, 0, 0);
// 	glVertex3f(SIDE_X/2, SIDE_Y/2, 0);

	/* Board's drawing */
//	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, BoardEmission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, BoardAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BoardDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, BoardSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, BoardShininess);

	for (int i=0; i<QUALITY_X; i++)
		for (int j=0; j<QUALITY_Y; j++) {
			glBegin(GL_QUADS);
			glNormal3fv(n);
			glVertex3f(v[3][0]+i*s_x, v[3][1]+j*s_y, 0);
			glVertex3f(v[3][0]+(i+1)*s_x, v[3][1]+j*s_y, 0);
			glVertex3f(v[3][0]+(i+1)*s_x, v[3][1]+(j+1)*s_y, 0);
			glVertex3f(v[3][0]+i*s_x, v[3][1]+(j+1)*s_y, 0);
			glEnd();
		}


	/* Lines' drawing */
	for (int i=D_LINE_X ; i<=side_x-D_LINE_X ; i+=D_LINE_X) {
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, LineColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, LineColor);
 		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, LineColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LineColor);
		linev = i*v[3][0]+(side_x-i)*v[0][0];
		/* Lignes // (Oy) */
		glBegin(GL_LINES);
		glVertex3f(linev/side_x, v[0][1], 0.1);
		glVertex3f(linev/side_x, v[1][1], 0.1);
		glEnd();
	}
	for (int i=D_LINE_Y ; i<=side_y-D_LINE_Y ; i+=D_LINE_Y) {
		lineh = i*v[0][1]+(side_y-i)*v[1][1];
		/* Lignes // (Ox) */
		glBegin(GL_LINES);
		glVertex3f(v[0][0], lineh/side_y, 0.1);
		glVertex3f(v[3][0], lineh/side_y, 0.1);
		glEnd();
	}
}
