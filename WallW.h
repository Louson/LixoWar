#ifndef _WALLW_H
#define _WALLW_H

#include "Sky.h"

class WallW : public Sky {
public :
	WallW(GLfloat _board_x, GLfloat _board_y, const char* _path);
};

#endif
