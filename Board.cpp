#include <GL/glut.h>
#include <stdexcept>
#include <iostream>

#include "Config.h"
#include "Board.h"

using namespace std;

//GLfloat BoardEmission[3] = {0.0, 1.0, 0.0};
GLfloat BoardDiffuse[3] = {0, 0.5, 0.5};
GLfloat BoardAmbient[3] = {1.0, 1.0, 1.0};
GLfloat BoardSpecular[3] = {1.0, 0, 0};
GLfloat BoardShininess = 120;

GLfloat LineDiffuse[3] = {0.5, 1, 1};
GLfloat LineAmbient[3] = {1.0, 1.0, 1.0};
GLfloat LineSpecular[3] = {0, 0, 0};
GLfloat LineShininess = 120;


/**
 * Constructeurs
 */
Board::Board(GLfloat x, GLfloat y,
	     GLfloat d_line_x, GLfloat d_line_y) {

	if (x < 2*d_line_x || y < 2*d_line_y) {
		throw(range_error("Dimensions insuffisantes"));
	}
	side_x = x;
	side_y = y;
	d_lines_x = d_line_x;
	d_lines_y = d_line_y;
	set_normal(0, 0, 1);
	set_vertex(0,  x/2, -y/2, 0);
	set_vertex(1,  x/2,  y/2, 0);
	set_vertex(2, -x/2,  y/2, 0);
	set_vertex(3, -x/2, -y/2, 0);
}

Board::Board(GLfloat x, GLfloat y,
	     GLfloat q_x, GLfloat q_y,
	     GLfloat d_line_x, GLfloat d_line_y) {

	if (x < 2*d_line_x || y < 2*d_line_y) {
		throw(range_error("Dimensions insuffisantes"));
	}
	side_x = x;
	side_y = y;
	d_lines_x = d_line_x;
	d_lines_y = d_line_y;
	quality_x = q_x;
	quality_y = q_y;
	set_normal(0, 0, 1);
	set_vertex(0,  x/2, -y/2, 0);
	set_vertex(1,  x/2,  y/2, 0);
	set_vertex(2, -x/2,  y/2, 0);
	set_vertex(3, -x/2, -y/2, 0);

}

/**
 * Méthodes
 */
void Board::draw() {
	GLfloat lineh, linev;
	GLfloat s_x = side_x/quality_x;
	GLfloat s_y = side_y/quality_y;

	GLfloat fog_color[4] = {0.70, 0.70, 0.70, 1.0};

	/* Test de sphere */
// //	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, BoardColor);
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, BoardAmbient);
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BoardDiffuse);;
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, BoardSpecular);
// 	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, BoardShininess);
// 	glColor3f(1.0, 0, 0);
//  	gluSphere(gluNewQuadric(), 5000, 32, 32);
	/******************/

	/* Lines' drawing */
//	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, LineColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, LineAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, LineDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LineSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, LineShininess);
	for (int i=d_lines_x ; i<=side_x-d_lines_x ; i+=d_lines_x) {
		linev = i*v[3][0]+(side_x-i)*v[0][0];
		/* Lignes // (Oy) */
		glBegin(GL_LINES);
		glVertex3f(linev/side_x, v[0][1], 0.001);
		glVertex3f(linev/side_x, v[1][1], 0.001);
		glEnd();
	}
	for (int i=d_lines_y ; i<=side_y-d_lines_y ; i+=d_lines_y) {
		lineh = i*v[0][1]+(side_y-i)*v[1][1];
		/* Lignes // (Ox) */
		glBegin(GL_LINES);
		glVertex3f(v[0][0], lineh/side_y, 0.00);
		glVertex3f(v[3][0], lineh/side_y, 0.00);
		glEnd();
	}


	/* Fog settings */
// 	glEnable(GL_FOG);
// 	glHint(GL_FOG_HINT, GL_NICEST);
// 	glFogi(GL_FOG, GL_LINEAR);
// 	glFogfv(GL_FOG_COLOR, fog_color);
// 	glFogf(GL_FOG_START, 1.0);
// 	glFogf(GL_FOG_END, 1.5);
// 	glFogf(GL_FOG_DENSITY, 0.35);


	/* Board's drawing */
//	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, BoardEmission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, BoardAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BoardDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, BoardSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, BoardShininess);

	for (int i=0; i<quality_x; i++)
		for (int j=0; j<quality_y; j++) {
			glBegin(GL_QUADS);
			glNormal3fv(n);
			glVertex3f(v[3][0]+i*s_x, v[3][1]+j*s_y, 0);
			glVertex3f(v[3][0]+(i+1)*s_x, v[3][1]+j*s_y, 0);
			glVertex3f(v[3][0]+(i+1)*s_x, v[3][1]+(j+1)*s_y, 0);
			glVertex3f(v[3][0]+i*s_x, v[3][1]+(j+1)*s_y, 0);
			glEnd();
		}
	
	glDisable(GL_FOG);

}
