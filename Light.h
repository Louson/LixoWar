#ifndef _LIGHT_H
#define _LIGHT_H

#include <GL/glut.h>

typedef struct light {
        GLfloat location[3]; 
        GLfloat diffuse[4];
        GLfloat ambient[4];
        GLfloat specular[4]; 
        GLfloat direction[3];
} LIGHT;

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
