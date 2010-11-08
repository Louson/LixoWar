#include <iostream>
#include "Wheel.h"
#include "Moto.h"

using namespace std;

Wheel::Wheel(GLfloat _x, GLfloat _y, GLfloat _direction[2], GLfloat moto_size, bool right) :
    r_base(moto_size/R_BASE_RATIO),
    height(moto_size/HEIGHT_RATIO)
{
    sens = right ? 1 : -1;
    setPos(_x, _y, direction);
}

void Wheel::setPos(GLfloat _x, GLfloat _y, GLfloat _direction[2]){
    x = _x;
    y = _y;
    direction[0] = _direction[0];
    direction[1] = _direction[1];
}

void Wheel::draw() {
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(sens*90, direction[0], direction[1] , 0.0);
    glutSolidCone(r_base,
            height,
            N_RINGS,
            N_SIDES);
    glPopMatrix();
}
