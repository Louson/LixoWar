#ifndef _BEAM_H
#define  _BEAM_H

#include <GL/glut.h>
#include "Drawable.h"
#include "Color.h"

#define H_BEAM 1.0

class Beam : public Drawable {
public :
	Beam(GLfloat _x, GLfloat _y, GLfloat _ante_dir[2], GLfloat _post_dir[2], GLint _num_moto);
	void draw();
private:
	GLfloat x;
	GLfloat y;
	GLfloat ante_dir[2];
	GLfloat post_dir[2];
	Color color;
};

#endif
