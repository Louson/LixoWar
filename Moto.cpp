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

        wheelNW(_moto_size, false),
        wheelNE(_moto_size, true),
        wheelSE(_moto_size, true),
        wheelSW(_moto_size, false)
{
        if (start_d[0]*start_d[1])
                throw(std::range_error("Direction initiale du véhicule impossible"));

        direction[0] = start_d[0];
        direction[1] = start_d[1];
}

void Moto::draw() {

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MotoAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MotoDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MotoSpecular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MotoShininess);

        wheelNW.setPos(x+(-moto_size*FRONT_WHEELS_H_DISTANCE_RATIO*direction[1]+
                                moto_size*FRONT_WHEELS_W_DISTANCE_RATIO*direction[0]),
                        y+(moto_size*FRONT_WHEELS_W_DISTANCE_RATIO*direction[1]+
                                moto_size*FRONT_WHEELS_H_DISTANCE_RATIO*direction[0]),
                        direction);

        wheelNE.setPos(x+(moto_size*FRONT_WHEELS_H_DISTANCE_RATIO*direction[1]+
                                moto_size*FRONT_WHEELS_W_DISTANCE_RATIO*direction[0]),
                        y+(moto_size*FRONT_WHEELS_W_DISTANCE_RATIO*direction[1]+
                                -moto_size*FRONT_WHEELS_H_DISTANCE_RATIO*direction[0]),
                        direction);

        wheelSE.setPos(x+(moto_size*BACK_WHEELS_H_DISTANCE_RATIO*direction[1]+
                                -moto_size*direction[0]),
                        y+(-moto_size*direction[1]+
                                -moto_size*BACK_WHEELS_H_DISTANCE_RATIO*direction[0]),
                        direction);

        wheelSW.setPos(x+(-moto_size*BACK_WHEELS_H_DISTANCE_RATIO*direction[1]+
                                -moto_size*direction[0]),
                        y+(-moto_size*direction[1]+
                                moto_size*BACK_WHEELS_H_DISTANCE_RATIO*direction[0]),
                        direction);

        wheelNW.draw();
        wheelNE.draw();
        wheelSE.draw();
        wheelSW.draw();

        /* Body */
        glPushMatrix();
        glTranslatef(x-moto_size*direction[0], y-moto_size*direction[1], 0);
        glRotatef(90, -direction[1], direction[0], 0);
        glutWireCone(moto_size/3, moto_size*2, 20, 30);
        glPopMatrix(); 
}

void Moto::setPerspCam() {
        cam_persp.set_position(x-1*MOTO_SIZE*direction[0], y-1*MOTO_SIZE*direction[1], PERSP_HEIGHT*MOTO_SIZE,
                        x+1.5*MOTO_SIZE*direction[0], y+1.5*MOTO_SIZE*direction[1], MOTO_SIZE,
                        0, 0, 1);
        cam_persp.set_view(FOVY, SCREEN_RATIO, 0.05, VIEW_DIST);
}

void Moto::setOrthoCam() {
        cam_ortho.set_position(x, y, H_CAM, /*Cam position */
                        x, y, 0, /* ref point position */
                        1, 0, 0); /* up vector */
        cam_ortho.set_view(-SCREEN_RATIO*PROJ_SIZE, /* left */
                        SCREEN_RATIO*PROJ_SIZE, /* right */
                        /* Y */ -PROJ_SIZE, /* Down */
                        PROJ_SIZE, /* up */
                        0.5*H_CAM, /* Z near */
                        1.5*H_CAM); /*Z far */
}

Camera_Persp * Moto::getPtCamPersp(){
        return &cam_persp;
}

Camera_Ortho * Moto::getPtCamOrtho(){
        return &cam_ortho;
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
