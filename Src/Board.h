#ifndef _GBOARD_H
#define _GBOARD_H

#include <GL/glut.h>
#include "Plan.h"
#include "Color.h"

#define B_DEPTH -2.0

/* needed by game.cpp */
#define NB_CASE_HALF_LINE_X 1
#define NB_CASE_HALF_LINE_Y 1
#define SIZE_CASE_X (GLfloat)(d_line_x/dim_line_x)
#define SIZE_CASE_Y (GLfloat)(d_line_y/dim_line_y)
#define HALF_LINE_SIZE_X (GLfloat)NB_CASE_HALF_LINE_X*SIZE_CASE_X
#define HALF_LINE_SIZE_Y (GLfloat)NB_CASE_HALF_LINE_Y*SIZE_CASE_Y


/**
 * Ambient détermine la couleur qui sera réfléchie
 */

class Board : public Plan{
public :
	/**
	 * Constructeurs
	 */
	Board(GLfloat side_x, GLfloat side_y,
	      GLfloat quality_x, GLfloat quality_y,
	      GLfloat d_lines_x, GLfloat d_lines_y,
	      GLfloat dim_lines_x, GLfloat dim_lines_y);
	
	/**
	 * Méthodes
	 */
	void draw();
private:
	GLfloat d_line_x;
	GLfloat d_line_y;
	GLfloat dim_line_x;
	GLfloat dim_line_y;
	GLfloat quality_x;
	GLfloat quality_y;
	Color boardColor;
	Color sideColor;
	Color lineColor;

	void drawEastLine(int j);
	void drawWestLine(int j);
	void drawNorthLine(int j);
	void drawSouthLine(int j);
};

#endif
