#include "Sky.h"

static const GLfloat WallEmission[] = {0.2, 0.2, 0.2, 1};
static const GLfloat WallDiffuse[] = {1, 1, 1, 1};
static const GLfloat WallAmbient[] = {1, 1, 1, 1};
static const GLfloat WallSpecular[] = {1, 1, 1, 1};
static const GLfloat WallShininess = 70;

Sky::Sky(GLfloat _board_x, GLfloat _board_y, const char* _path):
        color(WallEmission, WallAmbient, WallDiffuse, WallSpecular, WallShininess),
        text(_path),
        sky(text, color)
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
