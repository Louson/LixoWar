#include "Located_Light.h"

Located_Light::Located_Light() {
}

Located_Light::Located_Light(GLenum n, GLfloat location[3], GLfloat color[4]) {
	N_LIGHT = n;
	for (int i=0 ; i < 3 ; i++) {
		Location[i] = location[i];
		Color_Diffuse[i] = color[i];
//  		Color_Ambient[i] = color[i];
//  		Color_Specular[i] = color[i];
	}
	Location[3] = 1.0;
	Color_Diffuse[3] = color[3];
// 	Color_Ambient[3] = color[3];
// 	Color_Specular[3] = color[3];
	
}
Located_Light::Located_Light(GLenum n, GLfloat location[4],
			     GLfloat diffuse[4],
			     GLfloat ambient[4],
			     GLfloat specular[4]) {
	N_LIGHT = n;
	for (int i=0 ; i < 3 ; i++) {
		Location[i] = location[i];
		Color_Diffuse[i] = diffuse[i];
		Color_Ambient[i] = ambient[i];
		Color_Specular[i] = specular[4];
	}
	Location[3] = 1.0;
	Color_Diffuse[3] = diffuse[3];
	Color_Ambient[3] = ambient[3];
	Color_Specular[3] = specular[3];
}

void Located_Light::init() {
	glEnable(N_LIGHT);
//	glMatrixMode(GL_MODELVIEW);
	glLightfv(N_LIGHT, GL_POSITION, Location);
	glLightfv(N_LIGHT, GL_DIFFUSE, Color_Diffuse);
	glLightfv(N_LIGHT, GL_AMBIENT, Color_Ambient);
	glLightfv(N_LIGHT, GL_SPECULAR, Color_Specular);
	

/* POSITION LAMPE?*/
// 	GLfloat direction[3] = {-SIDE_X/2, SIDE_Y/2, SIDE_X/2};
// 	glLightfv(N_LIGHT, GL_SPOT_DIRECTION, direction);
// 	glLightf(N_LIGHT, GL_SPOT_EXPONENT, 20);
// 	glLightf(N_LIGHT, GL_SPOT_CUTOFF, 90.01);
// 	glLightf(N_LIGHT, GL_CONSTANT_ATTENUATION, 1.0);
// 	glLightf(N_LIGHT, GL_LINEAR_ATTENUATION, 0.00000000000000010);
// 	glLightf(N_LIGHT, GL_QUADRATIC_ATTENUATION, 1);
}
