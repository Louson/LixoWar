#ifndef _LASER_H
#define _LASER_H

#include "Color.h"
#include "Drawable.h"

class Laser: public Drawable {
        public:
                Laser(const GLfloat, const GLfloat, const int, const int);
                void draw(void);
                const bool testPos(const int, const int) const;
                void deactivate(void);

        private:
                GLfloat x_pos, y_pos;
                double dim_line_x, dim_line_y;
                bool activated;
                Color base_color, top_color;
};
#endif
