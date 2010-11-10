#ifndef _WHEEL_H
#define _WHEEL_H

#include <GL/glut.h>
#include "Drawable.h"

#define N_SIDES 30
#define N_RINGS 30

#define R_BASE_RATIO 10.0
#define HEIGHT_RATIO 5.0

class Wheel : public Drawable{
    public :
        Wheel(GLfloat moto_size, bool right);
        void setPos(GLfloat _x, GLfloat _y, int);
        void draw();
    private :
        GLfloat x;
        GLfloat y;
        int angle;
        GLfloat r_base;
        GLfloat height;
        GLint sens;
};

#endif
