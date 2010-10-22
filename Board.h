#ifndef _GBOARD_H
#define _GBOARD_H

#include <GL/glut.h>
#include "Plan.h"

extern GLfloat BoardEmission[3];
extern GLfloat BoardDiffuse[3];
extern GLfloat BoardAmbient[3];
extern GLfloat BoardSpecular[3];
extern GLfloat BoardShininess;
extern GLfloat LineColor[3];


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
};

#endif
