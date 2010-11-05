#include "Wall.h"
#include "Sky.h"

const char * PATH_TEXTURE = "Images/neutron.ppm";

Wall::Wall(int _board_x, int _board_y):
    board_x(_board_x),
    board_y(_board_y),
    texture(PATH_TEXTURE),
    wall_n(texture),
    wall_e(texture),
    wall_s(texture),
    wall_w(texture)
{
    wall_n.set_normal(0, -1, 0);
    wall_n.set_vertex(0,  board_x/2, board_y/2, 0);
    wall_n.set_vertex(1, -board_x/2, board_y/2, 0);
    wall_n.set_vertex(2, -board_x/2, board_y/2, H_SKY);
    wall_n.set_vertex(3,  board_x/2, board_y/2, H_SKY);

    wall_e.set_normal(-1, 0, 0);
    wall_e.set_vertex(0, _board_x/2,  _board_y/2, 0);
    wall_e.set_vertex(1, _board_x/2, -_board_y/2, 0);
    wall_e.set_vertex(2, _board_x/2, -_board_y/2, H_SKY);
    wall_e.set_vertex(3, _board_x/2,  _board_y/2, H_SKY);

    wall_w.set_normal(1, 0, 0);
    wall_w.set_vertex(0, -_board_x/2, -_board_y/2, 0);
    wall_w.set_vertex(1, -_board_x/2,  _board_y/2, 0);
    wall_w.set_vertex(2, -_board_x/2,  _board_y/2, H_SKY);
    wall_w.set_vertex(3, -_board_x/2, -_board_y/2, H_SKY);

    wall_s.set_normal(0, 1, 0);
    wall_s.set_vertex(0, -_board_x/2, -_board_y/2, 0);
    wall_s.set_vertex(1,  _board_x/2, -_board_y/2, 0);
    wall_s.set_vertex(2,  _board_x/2, -_board_y/2, H_SKY);
    wall_s.set_vertex(3, -_board_x/2, -_board_y/2, H_SKY);




}

void Wall::draw(){
    wall_n.draw();
    wall_e.draw();
    wall_s.draw();
    wall_w.draw();
}
