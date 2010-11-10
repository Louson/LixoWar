#include <cmath>
#include <iostream>
#include "Wheel.h"
#include "Moto.h"

using namespace std;

Wheel::Wheel(GLfloat moto_size, bool right) :
    r_base(moto_size/R_BASE_RATIO),
    height(moto_size/HEIGHT_RATIO)
{
    sens = right ? 1 : -1;
}

void Wheel::setPos(GLfloat _x, GLfloat _y, int _angle){
    x = _x;
    y = _y;
    angle = _angle;
}

void Wheel::draw() {
    glPushMatrix();
    glTranslatef(x, y, r_base);
    glRotatef(sens*90, cos(angle*M_PI/180), sin(angle*M_PI/180), 0);
    glutSolidCone(r_base,
            height,
            N_RINGS,
            N_SIDES);
    glPopMatrix();
}
