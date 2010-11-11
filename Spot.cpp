#include <GL/glut.h>

#include "Spot.h"

Spot::Spot(GLenum n, GLfloat location[4],
	   GLfloat diffuse[4], GLfloat ambient[4], GLfloat specular[4],
	   GLfloat direct[3], GLfloat expon, GLfloat cut) {

//:glMatrixMode(GL_PROJECTION);
	N_LIGHT = n;
	for (int i=0 ; i < 3 ; i++) {
		Location[i] = location[i];
		Color_Diffuse[i] = diffuse[i];
		Color_Ambient[i] = ambient[i];
		Color_Specular[i] = specular[4];
		Direction[i] = direct[i];
	}
	Location[3] = 1.0;
	Color_Diffuse[3] = diffuse[3];
	Color_Ambient[3] = ambient[3];
	Color_Specular[3] = specular[3];
	Exponent = expon;
	Cutoff = cut;
}

void Spot::init() {
	glMatrixMode(GL_MODELVIEW);
	glEnable(N_LIGHT);
	glLightfv(N_LIGHT, GL_POSITION, Location);
	glLightfv(N_LIGHT, GL_DIFFUSE, Color_Diffuse);
	glLightfv(N_LIGHT, GL_AMBIENT, Color_Ambient);
	glLightfv(N_LIGHT, GL_SPECULAR, Color_Specular);
	
	glLightfv(N_LIGHT, GL_SPOT_DIRECTION, Direction);
	glLightf(N_LIGHT, GL_SPOT_EXPONENT, Exponent);
	glLightf(N_LIGHT, GL_SPOT_CUTOFF, Cutoff);
}
