#ifndef _SKY_H
#define _SKY_H

#include "PlanText.h"

#define H_SKY 3000

using namespace std;

class Sky : public Drawable {
    protected:
        Texture text;
        PlanText sky;
    public :
        Sky(GLfloat _board_x, GLfloat _board_y, const char* _path);
        void draw();
};

#endif
