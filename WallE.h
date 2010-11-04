#ifndef _WALLE_H
#define _WALLE_H

#include "Sky.h"

class WallE : public Sky {
public :
	WallE(GLfloat _board_x, GLfloat _board_y, const char* _path);
};

#endif
