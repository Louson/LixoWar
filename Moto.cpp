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
    wheelNW(-_moto_size/2*(-start_d[0]+start_d[1]),
            _moto_size/3*(start_d[0]+start_d[1]),
            start_d, _moto_size,  false),

    wheelNE(_moto_size/2*(start_d[0]+start_d[1]),
            _moto_size/3*(-start_d[0]+start_d[1]),
            start_d, _moto_size, true),

    wheelSE(_moto_size/2*(-start_d[0]+start_d[1]),
            -_moto_size*(start_d[0]+start_d[1]),
            start_d, _moto_size, true),

    wheelSW(-_moto_size/2*(start_d[0]+start_d[1]),
            -_moto_size*(-start_d[0]+start_d[1]),
            start_d, _moto_size,  false)
{
    if (start_d[0]*start_d[1])
        throw(std::range_error("Direction initiale du véhicule impossible"));

    direction[0] = start_d[0];
    direction[1] = start_d[1];
    setCam();
}


void Moto::draw() {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MotoAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MotoDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MotoSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MotoShininess);

    wheelNW.setPos(x+-moto_size/2*(-direction[0]+direction[1]),
            y+moto_size/3*(direction[0]+direction[1]),
            direction);

    wheelNE.setPos(x+moto_size/2*(direction[0]+direction[1]),
            y+moto_size/3*(-direction[0]+direction[1]),
            direction);

    wheelSE.setPos(x+moto_size/2*(-direction[0]+direction[1]),
            y+-moto_size*(direction[0]+direction[1]),
            direction);

    wheelSW.setPos(x+-moto_size/2*(direction[0]+direction[1]),
            y+-moto_size*(-direction[0]+direction[1]),
            direction);

    wheelNW.draw();
    wheelNE.draw();
    wheelSE.draw();
    wheelSW.draw();

    glPushMatrix();
    glTranslatef(x-moto_size*direction[0], y-moto_size*direction[1], 0);
    glRotatef(90, -direction[1], direction[0], 0);
    glutWireCone(moto_size/3, moto_size*2, 20, 30);
    glPopMatrix();
}

void Moto::setCam() {
    cam.set_position(x-1*MOTO_SIZE*direction[0], y-1*MOTO_SIZE*direction[1], PERSP_HEIGHT*MOTO_SIZE,
            x+1.5*MOTO_SIZE*direction[0], y+1.5*MOTO_SIZE*direction[1], MOTO_SIZE,
            0, 0, 1);
    cam.set_view(100, SCREEN_RATIO, 0.05, VIEW_DIST);
}

void Moto::setCam_ext() {
    cam_ext.set_position(x, y, H_CAM, /*Cam position */
            x, y, 0, /* ref point position */
            direction[0], direction[1], 0); /* up vector */
    cam_ext.set_view(-SCREEN_RATIO*PROJ_SIZE, /* left */
            SCREEN_RATIO*PROJ_SIZE, /* right */
            /* Y */ -PROJ_SIZE, /* Down */
            PROJ_SIZE, /* up */
            0.5*H_CAM, /* Z near */
            1.5*H_CAM); /*Z far */
}

void Moto::activateCam() {
    setCam();
    cam.activate();
}

void Moto::activateCam_ext() {
    setCam_ext();
    cam_ext.activate();
}

Camera_Persp * Moto::getPtCam(){
    return &cam;
}

Camera_Ortho * Moto::getPtCam_ext(){
    return &cam_ext;
}

void Moto::move(int dx, bool turn ){
    int temp;
    /* we need to do some adjustements about the
     * direction of the moto when we use the keys
     */
    if(!turn){
        x += dx*direction[0];
        y += dx*direction[1];
    }else{
        /* if dx == 1 turn to right else, turn to left */
        temp = dx*direction[1];
        direction[1] = -dx*direction[0];
        direction[0] = temp;
    }
}
