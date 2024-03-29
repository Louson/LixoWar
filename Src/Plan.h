#ifndef _PLAN_H
#define _PLAN_H

#include <GL/glut.h>
#include "Drawable.h"

class Plan : public Drawable{
public :
	/**
	 * Constructeurs
	 */
	Plan();
	Plan(GLfloat side_x, GLfloat side_y);

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
protected:
	GLfloat side_x;
	GLfloat side_y;
	GLfloat n[3];
	GLfloat v[4][3];
};

#endif
