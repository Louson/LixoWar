#ifndef _COLOR_H
#define _COLOR_H

#include <GL/glut.h>

enum COLOR {BLUE = 0, RED, ORANGE, VIOLET};

class Color {
        public :
                Color(enum COLOR);
                Color(const GLfloat _emission[4], const GLfloat _ambient[4], const GLfloat _diffuse[4],
                                const GLfloat _specular[4], const GLfloat _shininess);
                void active();
        private :
                GLfloat emission[4];
                GLfloat ambient[4];
                GLfloat diffuse[4];
                GLfloat specular[4];
                GLfloat shininess;
                GLenum type;
};
#endif
