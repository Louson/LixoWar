#ifndef _SPOT_H
#define _SPOT_H

#include <GL/glut.h>

#include "Config.h"
#include "Located_Light.h"

class Spot : public Located_Light {
        public :
                Spot(LIGHT * light, GLfloat exponent, GLfloat cutoff);
                void init();
        private :
                GLfloat direction[4];
                GLfloat exponent;
                GLfloat cutoff;
};

#endif
