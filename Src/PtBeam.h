#ifndef _PTBEAM_H
#define _PTBEAM_H

#include <GL/glut.h>

#include "Beam.h"

class PtBeam {
public:
	PtBeam();
	~PtBeam();
	void create(GLfloat _x, GLfloat _y, GLfloat _ante_dir[2], GLfloat _post_dir[2], GLint _num_moto);
	bool exists();
private:
	Beam *pt_beam;
};

#endif
