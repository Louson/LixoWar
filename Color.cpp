#include "Color.h"

Color::Color() {
	type = GL_FRONT_AND_BACK;
}

Color::Color(GLfloat _emission[4], GLfloat _ambient[4], GLfloat _diffuse[4],
	     GLfloat _specular[4],GLfloat _shininess) : shininess(_shininess) {
	type = GL_FRONT_AND_BACK;
	for (int i=0 ; i<4 ; i++) {
		emission[i] = _emission[i];
		ambient[i] = _ambient[i];
		diffuse[i] = _diffuse[i];
		specular[i] = _specular[i];
	}
}

void Color::active() {
	glMaterialfv(type, GL_EMISSION, emission);
	glMaterialfv(type, GL_AMBIENT, ambient);
	glMaterialfv(type, GL_DIFFUSE, diffuse);
	glMaterialfv(type, GL_SPECULAR, specular);
	glMaterialf(type, GL_SHININESS, shininess);
}
