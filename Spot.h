#ifndef _SPOT_H
#define _SPOT_H

#include <GL/glut.h>

#include "Config.h"
#include "Located_Light.h"

/* Paramètres de la lampe 0 */
#define L_LOCATION {SIDE_X, SIDE_Y, SIDE_X}
#define L_DIFFUSE {1.0, 1.0, 1.0, 1.0}
#define L_AMBIENT {0.01, 0.01, 0.01, 1.0}
#define L_SPECULAR {1.0, 1.0, 1.0, 1.0}
#define L_DIRECTION {-SIDE_X, -SIDE_Y, -SIDE_X}
#define L_EXPONENT 2
#define L_CUTOFF 20
extern GLfloat L_Location[3];
extern GLfloat L_Diffuse[4];
extern GLfloat L_Ambient[4];
extern GLfloat L_Specular[4];
extern GLfloat direction[3];

class Spot : public Located_Light {
public :
	Spot(GLenum n, GLfloat location[4],
	     GLfloat diffuse[4], GLfloat ambient[4], GLfloat specular[4],
	     GLfloat direction[3], GLfloat exponent, GLfloat cutoff);
	void init();
private :
	GLfloat Direction[3];
	GLfloat Exponent;
	GLfloat Cutoff;
};

#endif
