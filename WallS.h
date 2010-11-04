#ifndef _WALLS_H
#define _WALLS_H

#include "Sky.h"

class WallS : public Sky {
public :
	WallS(GLfloat _board_x, GLfloat _board_y, const char* _path);
};

#endif
