#include <cmath>
#include <stdexcept>
#include <cstdlib>
#include <iostream>

#include "Game.h"
#include "Config.h"
#include "Moto.h"

Moto::Moto(GLfloat _moto_size):
        moto_size(_moto_size),
        wheelNW(_moto_size, false),
        wheelNE(_moto_size, true),
        wheelSE(_moto_size, true),
        wheelSW(_moto_size, false)
{}

void Moto::setPos(int _x, int _y, int _direction[2]){
        if (_direction[0]*_direction[1])
                throw(std::range_error("Direction initiale du véhicule impossible"));
        x = _x;
        y = _y;
        direction[0] = _direction[0];
        direction[1] = _direction[1];
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
