#ifndef _GBOARD_H
#define _GBOARD_H

#include <GL/glut.h>

#define D_LINE 50

class Board {
public :
	/**
	 * Constructeurs
	 */
	Board();
	Board(float s);

	/**
	 * Accesseurs
	 */
	void set_dim(float c);
	float get_side();
	void set_normal(float x, float y, float z);
	void set_vertex(int v, float x, float y, float z);
	/**
	 * Méthodes
	 */
	void drawBoard();
private:
	float side;
	GLfloat n[3];
	GLfloat v[4][3];
};

#endif
