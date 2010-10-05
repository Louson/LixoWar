#include "Located_Light.h"

Located_Light::Located_Light() {
}

Located_Light::Located_Light(GLenum n, GLfloat location[4], GLfloat color[4]) {
	N_LIGHT = n;
	for (int i=0 ; i < 4 ; i++) {
		Location[i] = location[i];
		Color_Diffuse[i] = color[i];
		Color_Ambient[i] = 0;
		Color_Specular[i] = 0;
	}
}
Located_Light::Located_Light(GLenum n, GLfloat location[4],
			     GLfloat diffuse[4],
			     GLfloat ambient[4],
			     GLfloat specular[4]) {
	N_LIGHT = n;
	for (int i=0 ; i < 4 ; i++) {
		Location[i] = location[i];
		Color_Diffuse[i] = diffuse[i];
		Color_Ambient[i] = ambient[i];
		Color_Specular[i] = specular[4];
	}
}

void Located_Light::init() {
	
}
