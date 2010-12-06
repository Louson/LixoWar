#include <GL/glut.h>

#include "Spot.h"

Spot::Spot(LIGHT * light, GLfloat _exponent, GLfloat _cutoff):
        Located_Light(light)
{
        for (int i=0 ; i < 3 ; i++) 
                direction[i] = light->direction[i];
        direction[3] = 1.0;
        exponent = _exponent;
        cutoff = _cutoff;
}

void Spot::init() {
        glMatrixMode(GL_MODELVIEW);
        glEnable(light);

        Located_Light::init();
        glLightfv(light, GL_SPOT_DIRECTION, direction);
        glLightf(light, GL_SPOT_EXPONENT, exponent);
        glLightf(light, GL_SPOT_CUTOFF, cutoff);
}
