#include "WallW.h"

WallW::WallW(GLfloat _board_x, GLfloat _board_y, const char* _path) {

	set_normal(1, 0, 0);
	set_vertex(0, -_board_x/2, -_board_y/2, 0);
	set_vertex(1, -_board_x/2,  _board_y/2, 0);
	set_vertex(2, -_board_x/2,  _board_y/2, H_SKY);
	set_vertex(3, -_board_x/2, -_board_y/2, H_SKY);

	text = new Texture(_path);
}
