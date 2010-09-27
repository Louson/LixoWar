#ifndef _GBOARD_H
#define _GBOARD_H

#include "main.h"
#include <GL/glut.h>


class Board {
public :
	/**
	 * Constructeurs
	 */
	Board();
	Board(double dx, double dy);

	/**
	 * Accesseurs
	 */
	void set_dim(double dx, double dy);
	double get_dx();
	double get_dy();
	void set_normal(float x, float y, float z);
	void set_vertex(int v, float x, float y, float z);
	/**
	 * Méthodes
	 */
	void drawBoard();
private:
	double dx;
	double dy;
	GLfloat n[3];
	GLfloat v[4][3];
};

#endif
