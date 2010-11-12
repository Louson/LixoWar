#include <cmath>
#include <stdexcept>
#include <cstdlib>
#include <iostream>

#include "Game.h"
#include "Moto.h"

Moto::Moto(GLfloat _moto_size):
        moto_size(_moto_size),
        wheelNW(_moto_size, false),
        wheelNE(_moto_size, true),
        wheelSE(_moto_size, true),
        wheelSW(_moto_size, false)
{}

void Moto::setPos(int _x, int _y, int _angle){
        x = _x;
        y = _y;
        angle = _angle;
}

void Moto::draw() {
	glMatrixMode(GL_MODELVIEW);
        
        GLfloat val_sin = sin(angle*M_PI/180);
        GLfloat val_cos = cos(angle*M_PI/180);

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MotoAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MotoDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MotoSpecular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MotoShininess);

        wheelNW.setPos(x+(-moto_size*FRONT_WHEELS_H_DISTANCE_RATIO*val_sin+
                                moto_size*FRONT_WHEELS_W_DISTANCE_RATIO*val_cos),
                        y+(moto_size*FRONT_WHEELS_W_DISTANCE_RATIO*val_sin+
                                moto_size*FRONT_WHEELS_H_DISTANCE_RATIO*val_cos),
                        angle);

        wheelNE.setPos(x+(moto_size*FRONT_WHEELS_H_DISTANCE_RATIO*val_sin+
                                moto_size*FRONT_WHEELS_W_DISTANCE_RATIO*val_cos),
                        y+(moto_size*FRONT_WHEELS_W_DISTANCE_RATIO*val_sin+
                                -moto_size*FRONT_WHEELS_H_DISTANCE_RATIO*val_cos),
                        angle);

        wheelSE.setPos(x+(moto_size*BACK_WHEELS_H_DISTANCE_RATIO*val_sin+
                                -moto_size*val_cos),
                        y+(-moto_size*val_sin+
                                -moto_size*BACK_WHEELS_H_DISTANCE_RATIO*val_cos),
                        angle);

        wheelSW.setPos(x+(-moto_size*BACK_WHEELS_H_DISTANCE_RATIO*val_sin+
                                -moto_size*val_cos),
                        y+(-moto_size*val_sin+
                                moto_size*BACK_WHEELS_H_DISTANCE_RATIO*val_cos),
                        angle);

        wheelNW.draw();
        wheelNE.draw();
        wheelSE.draw();
        wheelSW.draw();

        /* Body */
        glPushMatrix();
        glTranslatef(x-moto_size*cos(angle*M_PI/180), y-moto_size*sin(angle*M_PI/180), 0);
        glRotatef(angle, 0, 0, 1);
        glRotatef(90, 0, 1, 0);
        glutWireCone(moto_size/3, moto_size*2, 20, 30);
        glPopMatrix(); 
}
