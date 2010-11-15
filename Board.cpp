#include <GL/glut.h>
#include <stdexcept>
#include <iostream>

#include "Config.h"
#include "Board.h"

using namespace std;

const GLfloat BoardEmission[] = {0.0, 0.0, 0.0, 1};
const GLfloat BoardDiffuse[] = {125.0/255, 145.0/255, 0, 1.0};
const GLfloat BoardAmbient[] = {125.0/255, 145.0/255, 0, 1.0};
const GLfloat BoardSpecular[] = {1, 1, 1, 1,};
const GLfloat BoardShininess = 70;

const GLfloat SideEmission[] = {0.0, 0.0, 0.0, 1};
const GLfloat SideDiffuse[] = {201.0/255, 222.0/255, 85.0/255, 1};
const GLfloat SideAmbient[] = {201.0/255, 222.0/255, 85.0/255, 1};
const GLfloat SideSpecular[] = {0, 0, 0, 1};
const GLfloat SideShininess = 70;

const GLfloat LineEmission[4] = {0.0, 0.0, 0.0, 1};
const GLfloat LineDiffuse[4] = {1, 1, 157.0/255, 1};
const GLfloat LineAmbient[4] = {1, 1, 157.0/255, 1};
const GLfloat LineSpecular[4] = {0, 0, 0, 1};
const GLfloat LineShininess = 70;


/**
 * Constructeurs
 */
Board::Board(GLfloat x, GLfloat y,
	     GLfloat q_x, GLfloat q_y,
	     GLfloat d_line_x, GLfloat d_line_y):
	boardColor(BoardEmission, BoardAmbient, BoardDiffuse, BoardSpecular, BoardShininess),
	sideColor(SideEmission, SideAmbient, SideDiffuse, SideSpecular, SideShininess),
	lineColor(LineEmission, LineAmbient, LineDiffuse, LineSpecular, LineShininess)
{
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

	for (int j=0; j<quality_y; j++)
			/* Lines' drawing */
			for (int k=0 ; k<=side_x ; k+=d_lines_x) {
				linev = k*v[3][0]+(side_x-k)*v[0][0];
				/* Lignes // (Oy) */
				sideColor.active();
				glPointSize(1.0);
				glBegin(GL_QUADS);
				glNormal3f(-1.0, 0.0, 0.0);
				glVertex3f(linev/side_x-1, v[0][1]+j*s_y, 0.0);
				glVertex3f(linev/side_x-1, v[0][1]+(j+1)*s_y, 0.0);
				glVertex3f(linev/side_x-1, v[0][1]+(j+1)*s_y, B_DEPTH);
				glVertex3f(linev/side_x-1, v[0][1]+j*s_y, B_DEPTH);
				glEnd();
				glBegin(GL_QUADS);
				glNormal3f(1.0, 0.0, 0.0);
				glVertex3f(linev/side_x+1, v[0][1]+j*s_y, 0.0);
				glVertex3f(linev/side_x+1, v[0][1]+(j+1)*s_y, 0.0);
				glVertex3f(linev/side_x+1, v[0][1]+(j+1)*s_y, B_DEPTH);
				glVertex3f(linev/side_x+1, v[0][1]+j*s_y, B_DEPTH);
				glEnd();
				lineColor.active();
				glBegin(GL_QUADS);
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f(linev/side_x-1, v[0][1]+j*s_y, 0.0);
				glVertex3f(linev/side_x-1, v[0][1]+(j+1)*s_y, 0.0);
				glVertex3f(linev/side_x+1, v[0][1]+(j+1)*s_y, 0.0);
				glVertex3f(linev/side_x+1, v[0][1]+j*s_y, 0.0);
				glEnd();
			}

	for (int i=0; i<quality_x; i++)
		for (int k=0 ; k<=side_y ; k+=d_lines_y) {
			lineh = k*v[0][1]+(side_y-k)*v[1][1];
			/* Lignes // (Ox) */
			sideColor.active();
			glBegin(GL_QUADS);
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(v[0][0]+1-i*s_x, lineh/side_y-1, 0.0);
			glVertex3f(v[0][0]-1-(i+1)*s_x, lineh/side_y-1, 0.0);
			glVertex3f(v[0][0]-1-(i+1)*s_x, lineh/side_y-1, B_DEPTH);
			glVertex3f(v[0][0]+1-i*s_x, lineh/side_y-1, B_DEPTH);
			glEnd();
			glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(v[0][0]+1-i*s_x, lineh/side_y+1, 0.0);
			glVertex3f(v[0][0]-1-(i+1)*s_x, lineh/side_y+1, 0.0);
			glVertex3f(v[0][0]-1-(i+1)*s_x, lineh/side_y+1, B_DEPTH);
			glVertex3f(v[0][0]+1-i*s_x, lineh/side_y+1, B_DEPTH);
			glEnd();
			lineColor.active();
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(v[0][0]+1-i*s_x, lineh/side_y-1, 0.0);
			glVertex3f(v[0][0]-1-(i+1)*s_x, lineh/side_y-1, 0.0);
			glVertex3f(v[0][0]-1-(i+1)*s_x, lineh/side_y+1, 0.0);
			glVertex3f(v[0][0]+1-i*s_x, lineh/side_y+1, 0.0);
			glEnd();
			glPointSize(1.0);
		}
        
        /* Board's drawing */
        for (int i=0; i<quality_x; i++)
		for (int j=0; j<quality_y; j++) {
			boardColor.active();
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(v[3][0]+i*s_x, v[3][1]+j*s_y, B_DEPTH);
			glVertex3f(v[3][0]+(i+1)*s_x, v[3][1]+j*s_y, B_DEPTH);
			glVertex3f(v[3][0]+(i+1)*s_x, v[3][1]+(j+1)*s_y, B_DEPTH);
			glVertex3f(v[3][0]+i*s_x, v[3][1]+(j+1)*s_y, B_DEPTH);
			glEnd();
		}
	
}
