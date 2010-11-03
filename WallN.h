#ifndef _WALLN_H
#define _WALLN_H

#include "Sky.h"

class WallN : public Sky {
public :
	WallN(GLfloat _board_x, GLfloat _board_y, const char* _path);
};

#endif
