#ifndef _GBOARD_H
#define _GBOARD_H

#include <GL/glut.h>

class Board {
public :
	/**
	 * Constructeurs
	 */
	Board();
	Board(GLfloat side_x, GLfloat side_y);

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
	void drawBoard();
private:
	GLfloat side_x;
	GLfloat side_y;
	GLfloat n[3];
	GLfloat v[4][3];
};

#endif
