#include <GL/glut.h>
#include <stdexcept>
#include <iostream>

#include "Config.h"
#include "Board.h"

using namespace std;

GLfloat BoardEmission[3] = {0.0, 0.0, 0.0};
GLfloat BoardDiffuse[3] = {0, 0.3, 0.3};
GLfloat BoardAmbient[3] = {0.4, 0.4, 0.4};
GLfloat BoardSpecular[3] = {0, 0, 0};
GLfloat BoardShininess = 20;

GLfloat SideEmission[3] = {0.0, 0.0, 0.0};
GLfloat SideDiffuse[3] = {0, 0, 0.3};
GLfloat SideAmbient[3] = {0.0, 0.0, 0.0};
GLfloat SideSpecular[3] = {0, 0, 0};
GLfloat SideShininess = 20;

GLfloat LineEmission[3] = {0.0, 0.0, 0.0};
GLfloat LineDiffuse[3] = {0.3, 0.7, 0.7};
GLfloat LineAmbient[3] = {0.0, 0.0, 0.0};
GLfloat LineSpecular[3] = {0, 0, 0};
GLfloat LineShininess = 20;


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
	boardColor = Color(BoardEmission, BoardAmbient, BoardDiffuse, BoardSpecular, BoardShininess);
	sideColor = Color(SideEmission, SideAmbient, SideDiffuse, SideSpecular, SideShininess);
	lineColor = Color(LineEmission, LineAmbient, LineDiffuse, LineSpecular, LineShininess);
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
	for (int i=0 ; i<=side_x ; i+=d_lines_x) {
		linev = i*v[3][0]+(side_x-i)*v[0][0];
		/* Lignes // (Oy) */
	sideColor.active();
		glPointSize(1.0);
 		glBegin(GL_QUADS);
 		glVertex3f(linev/side_x-1, v[0][1], 0.0);
 		glVertex3f(linev/side_x-1, v[1][1], 0.0);
  		glVertex3f(linev/side_x-1, v[1][1], B_DEPTH);
  		glVertex3f(linev/side_x-1, v[0][1], B_DEPTH);
 		glEnd();
 		glBegin(GL_QUADS);
 		glVertex3f(linev/side_x+1, v[0][1], 0.0);
 		glVertex3f(linev/side_x+1, v[1][1], 0.0);
  		glVertex3f(linev/side_x+1, v[1][1], B_DEPTH);
  		glVertex3f(linev/side_x+1, v[0][1], B_DEPTH);
 		glEnd();
	lineColor.active();
 		glBegin(GL_QUADS);
 		glVertex3f(linev/side_x-1, v[0][1], 0.0);
 		glVertex3f(linev/side_x-1, v[1][1], 0.0);
  		glVertex3f(linev/side_x+1, v[1][1], 0.0);
  		glVertex3f(linev/side_x+1, v[0][1], 0.0);
 		glEnd();
	}
	for (int i=d_lines_y ; i<=side_y-d_lines_y ; i+=d_lines_y) {
		lineh = i*v[0][1]+(side_y-i)*v[1][1];
		/* Lignes // (Ox) */
	sideColor.active();
		glBegin(GL_QUADS);
		glVertex3f(v[0][0], lineh/side_y-1, 0.0);
		glVertex3f(v[3][0], lineh/side_y-1, 0.0);
		glVertex3f(v[3][0], lineh/side_y-1, B_DEPTH);
		glVertex3f(v[0][0], lineh/side_y-1, B_DEPTH);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3f(v[0][0], lineh/side_y+1, 0.0);
		glVertex3f(v[3][0], lineh/side_y+1, 0.0);
		glVertex3f(v[3][0], lineh/side_y+1, B_DEPTH);
		glVertex3f(v[0][0], lineh/side_y+1, B_DEPTH);
		glEnd();
	lineColor.active();
		glBegin(GL_QUADS);
		glVertex3f(v[0][0], lineh/side_y-1, 0.0);
		glVertex3f(v[3][0], lineh/side_y-1, 0.0);
		glVertex3f(v[3][0], lineh/side_y+1, 0.0);
		glVertex3f(v[0][0], lineh/side_y+1, 0.0);
		glEnd();
		glPointSize(1.0);
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
	boardColor.active();
	for (int i=0; i<quality_x; i++)
		for (int j=0; j<quality_y; j++) {
			glBegin(GL_QUADS);
			glNormal3fv(n);
			glVertex3f(v[3][0]+i*s_x, v[3][1]+j*s_y, B_DEPTH);
			glVertex3f(v[3][0]+(i+1)*s_x, v[3][1]+j*s_y, B_DEPTH);
			glVertex3f(v[3][0]+(i+1)*s_x, v[3][1]+(j+1)*s_y, B_DEPTH);
			glVertex3f(v[3][0]+i*s_x, v[3][1]+(j+1)*s_y, B_DEPTH);
			glEnd();
		}
	
	glDisable(GL_FOG);

}
