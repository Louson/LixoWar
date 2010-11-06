#include "Camera_Ortho.h"
#include <iostream>

Camera_Ortho::Camera_Ortho(){};

void Camera_Ortho::set_view(GLfloat left, GLfloat right,
        GLfloat down, GLfloat up,
        GLfloat near,GLfloat  far) {
    xmin = left;
    xmax = right;
    ymin = down;
    ymax = up;
    znear = near;
    zfar = far;
}

void Camera_Ortho::activate() {
    lookAt();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(xmin, xmax, ymin, ymax, znear, zfar);	
}

void Camera_Ortho::zoom(GLfloat gradient){
    /* prevent the map to be inversed */
    if(xmin + gradient *16/9 > ZOOM_MAX)
        return;

    xmin += gradient*16/9;
    xmax -= gradient*16/9;
    ymin += gradient;
    ymax -= gradient;

}
