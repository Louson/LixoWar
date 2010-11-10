#include <iostream>

#include "Camera_Ortho.h"

Camera_Ortho::Camera_Ortho():
        gradient(0)
{};

void Camera_Ortho::set_view(GLfloat left, GLfloat right,
                GLfloat down, GLfloat up,
                GLfloat near,GLfloat  far) {
        xmin = left;
        xmax = right;
        ymin = down;
        ymax = up;
        znear = near;
        zfar = far;

        /* zoom management */
        xmin += gradient*16/9;
        xmax -= gradient*16/9;
        ymin += gradient;
        ymax -= gradient;
}

void Camera_Ortho::activate() {
        lookAt();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(xmin, xmax, ymin, ymax, znear, zfar);	
}

void Camera_Ortho::zoom(GLfloat _gradient){
        if(xmin + (gradient+_gradient) * 16/9 > ZOOM_MAX)
                return;
        std::cout<<xmin + gradient +_gradient*16/9<<std::endl;
        gradient += _gradient;
}
