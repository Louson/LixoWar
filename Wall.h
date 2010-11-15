#ifndef _WALL_H
#define _WALL_H

#include "PlanText.h"
#include "Drawable.h"
#include "Color.h"

class Wall: public Drawable{
    private:
        int board_x, board_y;
        Texture texture;
        Color color;
        PlanText wall_n;
        PlanText wall_e;
        PlanText wall_s;
        PlanText wall_w;
    public:
        Wall(int _board_x, int _board_y);
        void draw();
};

#endif
