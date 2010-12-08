#include "Color.h"

static const GLfloat TAB_COLOR[][4] = {{0.2, 0.2, 0.8, 1}, {0.8, 0.2, 0.2, 1}};
static const GLfloat EMISSION[] = {0, 0, 0, 1};
static const GLfloat SPECULAR[] = {1.0, 1.0, 1.0, 1};
static const GLfloat SHININESS = 120;


Color::Color(enum COLOR _color):
        shininess(SHININESS)
{
        type = GL_FRONT_AND_BACK;
	for (int i=0 ; i<4 ; i++) {
		emission[i] = EMISSION[i];
		ambient[i] = TAB_COLOR[_color][i];
		diffuse[i] = TAB_COLOR[_color][i];
		specular[i] = SPECULAR[i];
	}

}

Color::Color(const GLfloat _emission[4], const GLfloat _ambient[4], const GLfloat _diffuse[4],
	     const GLfloat _specular[4], const GLfloat _shininess) : 
        shininess(_shininess) 
{
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
