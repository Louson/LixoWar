#ifndef _COLOR_H
#define _COLOR_H

#include <GL/glut.h>

class Color {
public :
	Color();
	Color(GLfloat _emission[4], GLfloat _ambient[4], GLfloat _diffuse[4],
	      GLfloat _specular[4],GLfloat _shininess);
	void active();
private :
	GLfloat emission[3];
	GLfloat ambient[3];
	GLfloat diffuse[3];
	GLfloat specular[3];
	GLfloat shininess;
	GLenum type;
};

#endif
