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
        private:
                static int light_number;
                void setLight(void);
        protected :
                int light;
                GLfloat diffuse[4];
                GLfloat ambient[4];
                GLfloat specular[4];
        public:
                Light();
                virtual void init() = 0;
};
#endif
