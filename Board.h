#ifndef _GBOARD_H
#define _GBOARD_H

#include <GL/glut.h>
#include "Plan.h"
#include "Color.h"

#define B_DEPTH -2.0

/**
 * Ambient détermine la couleur qui sera réfléchie
 */
extern GLfloat BoardEmission[4];
extern GLfloat BoardDiffuse[4];
extern GLfloat BoardAmbient[4];
extern GLfloat BoardSpecular[4];
extern GLfloat BoardShininess;

extern GLfloat SideEmission[4];
extern GLfloat SideDiffuse[4];
extern GLfloat SideAmbient[4];
extern GLfloat SideSpecular[4];
extern GLfloat SideShininess;

extern GLfloat LineEmission[4];
extern GLfloat LineDiffuse[4];
extern GLfloat LineAmbient[4];
extern GLfloat LineSpecular[4];
extern GLfloat LineShininess;


class Board : public Plan{
public :
	/**
	 * Constructeurs
	 */
	Board(GLfloat side_x, GLfloat side_y);
	Board(GLfloat side_x, GLfloat side_y,
	      GLfloat d_lines_x, GLfloat d_lines_y);
	Board(GLfloat side_x, GLfloat side_y,
	      GLfloat d_lines_x, GLfloat d_lines_y,
	      GLfloat quality_x, GLfloat quality_y);
	
	/**
	 * Méthodes
	 */
	void draw();
private:
	GLfloat d_lines_x;
	GLfloat d_lines_y;
	GLfloat quality_x;
	GLfloat quality_y;
	Color boardColor;
	Color sideColor;
	Color lineColor;
};

#endif
