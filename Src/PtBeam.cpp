#include "PtBeam.h"

PtBeam::PtBeam() {
	pt_beam = NULL;
}

PtBeam::~PtBeam() {
	delete pt_beam;
}

void PtBeam::create(GLfloat _x, GLfloat _y, GLfloat _ante_dir[2], GLfloat _post_dir[2], GLint _num_moto) {
	pt_beam = new Beam(_x, _y, _ante_dir, _post_dir, _num_moto);
}

bool PtBeam::exists() {
	return (bool)pt_beam;
}
