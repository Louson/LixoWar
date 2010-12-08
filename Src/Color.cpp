#include "Color.h"

/* BLUE = 0, RED, ORANGE, VIOLET */
static const GLfloat TAB_COLOR[][4] = {{38.0/255, 74.0/255, 89.0/255, 1}, {186.0/255, 47.0/255, 29.0/255, 1},
        {245.0/255, 115.0/255, 54.0/255, 1}, {127.0/255, 22.0/255, 55.0/255, 1}};
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
