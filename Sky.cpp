#include "Sky.h"

Sky::Sky(GLfloat _board_x, GLfloat _board_y, const char* _path):
    text(_path),
    sky(text)
{
    sky.set_normal(0, 0, 1);
    sky.set_vertex(0,  _board_x/2, -_board_y/2, H_SKY);
    sky.set_vertex(1,  _board_x/2,  _board_y/2, H_SKY);
    sky.set_vertex(2, -_board_x/2,  _board_y/2, H_SKY);
    sky.set_vertex(3, -_board_x/2, -_board_y/2, H_SKY);
}

void Sky::draw(){
    sky.draw();
}
