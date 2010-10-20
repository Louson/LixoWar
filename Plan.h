#ifndef _PLAN_H
#define _PLAN_H

#include <GL/glut.h>
#include "Drawable.h"

#define H_SKY 2000

class Plan : public Drawable{
public :
	/**
	 * Constructeurs
	 */
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
	virtual void draw();
protected:
	GLfloat side_x;
	GLfloat side_y;
	GLfloat n[3];
	GLfloat v[4][3];
};

#endif
