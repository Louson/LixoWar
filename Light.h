#ifndef _LIGHT_H
#define _LIGHT_H

#include <GL/glut.h>

class Light {
    protected :
        GLenum N_LIGHT;
        GLfloat Color_Diffuse[4];
        GLfloat Color_Ambient[4];
        GLfloat Color_Specular[4];
    public:
        virtual void init() = 0;
};

#endif
