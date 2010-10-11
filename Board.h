#ifndef _GBOARD_H
#define _GBOARD_H

#include <GL/glut.h>
#include "Drawable.h"

class Board : public Drawable{
public :
	/**
	 * Constructeurs
	 */
	Board();
	Board(GLfloat side_x, GLfloat side_y);
	Board(GLfloat side_x, GLfloat side_y,
	      GLfloat d_lines_x, GLfloat d_lines_y);
	Board(GLfloat side_x, GLfloat side_y,
	      GLfloat d_lines_x, GLfloat d_lines_y,
	      GLfloat quality_x, GLfloat quality_y);

	/**
	 * Accesseurs
	 */
	void set_dim(GLfloat c);
	GLfloat get_side();
	void set_normal(GLfloat x, GLfloat y, GLfloat z);
	void set_vertex(int v, GLfloat x, GLfloat y, GLfloat z);
	/**
	 * Méthodes
	 */
	void draw();
private:
	GLfloat side_x;
	GLfloat side_y;
	GLfloat d_lines_x;
	GLfloat d_lines_y;
	GLfloat quality_x;
	GLfloat quality_y;
	GLfloat n[3];
	GLfloat v[4][3];
};

#endif
