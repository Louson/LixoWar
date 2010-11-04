#include <cmath>
#include <stdexcept>
#include <cstdlib>
#include <iostream>

#include "Config.h"
#include "Moto.h"

Moto::Moto(GLfloat start_x, GLfloat start_y, GLfloat start_d[2], GLfloat _moto_size):
    x(start_x),
    y(start_y),
    moto_size(_moto_size),
    wheelNW(start_x + (start_d[0]-start_d[1]/2.0)*_moto_size,
            start_y + (start_d[0]/2.0+start_d[1])*_moto_size, start_d, _moto_size,  -1),

    wheelNE(start_x + (start_d[0]+start_d[1]/2.0)*_moto_size,
            start_y + (-start_d[0]/2.0+start_d[1])*_moto_size, start_d, _moto_size, 1),

    wheelSE(start_x + (-start_d[0]+start_d[1]/2.0)*_moto_size,
            start_y + (-start_d[0]/2.0-start_d[1])*_moto_size, start_d, _moto_size, 1),

    wheelSW(start_x + (-start_d[0]-start_d[1]/2.0)*_moto_size,
            start_y + (start_d[0]/2.0-start_d[1])*_moto_size, start_d, _moto_size,  -1)
{
    if (start_d[0]*start_d[1])
        throw(std::range_error("Direction initiale du véhicule impossible"));

    direction[0] = start_d[0];
    direction[1] = start_d[1];
    setCam_ext();
    setCam();
}


void Moto::draw() {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MotoAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MotoDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MotoSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MotoShininess);
    wheelNW.draw();
    wheelNE.draw();
    wheelSE.draw();
    wheelSW.draw();

    glPushMatrix();
    glTranslatef(-direction[0], -direction[1], 0);
    glRotatef(-90, direction[1], direction[0], 0);
    glutWireCone(moto_size/3, moto_size*2, 20, 30);
    glPopMatrix();

}

void Moto::setCam() {
    cam.set_position(x-1*MOTO_SIZE*direction[0], y-1*MOTO_SIZE*direction[1], 2*MOTO_SIZE,
            x+1.5*MOTO_SIZE*direction[0], y+1.5*MOTO_SIZE*direction[1], MOTO_SIZE,
            0, 0, 1);
    cam.set_view(100, SCREEN_RATIO, 0.05, VIEW_DIST);
}

void Moto::setCam_ext() {
    cam_ext.set_position(0, 0, H_CAM, /*Cam position */
            x, y, 0,
            0, 1, 0);
    cam_ext.set_view(/* X */ -SCREEN_RATIO*2.0*MOTO_WIDTH,
            SCREEN_RATIO*2.0*MOTO_WIDTH,
            /* Y */ -2.0*MOTO_LENGTH,
            2.0*MOTO_LENGTH,
            /* Z near */ 0,
            /* Z far  */ 1.1*H_CAM);
}

void Moto::activateCam() {
    cam.activate();
}

void Moto::activateCam_ext() {
    cam_ext.activate();
}

Camera_Persp * Moto::getPtCam(){
    return &cam;
}

Camera_Ortho * Moto::getPtCam_ext(){
    return &cam_ext;
}
