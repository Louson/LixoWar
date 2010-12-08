#ifndef _BEAM_H
#define  _BEAM_H

#include <GL/glut.h>
#include "Moto.h"
#include "Drawable.h"
#include "Color.h"

#define H_BEAM 1.0

class Beam : public Drawable {
public :
	Beam(MOTO_STRUCT moto, enum COLOR);
	Beam(GLfloat _x, GLfloat _y, GLfloat _ante_angle, GLfloat _post_angle
	     , GLint _num_moto, GLfloat _size_case_x, GLfloat _size_case_y, enum COLOR);
	void setPostAngle(int angle);
	void draw();
private:
	GLfloat x;
	GLfloat y;
	GLfloat size_case_x;
	GLfloat size_case_y;
	GLfloat ante_dir[2];
	GLfloat post_dir[2];
        Color color;
};

#endif
