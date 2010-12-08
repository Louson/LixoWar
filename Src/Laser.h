#ifndef _LASER_H
#define _LASER_H

#include "Drawable.h"

class Laser: public Drawable {
        public:
                Laser(int, int);
                void draw(void) const;
                const bool testPos(const int, const int) const;
                void deactivate(void);

        private:
                int x_pos, y_pos;
};


#endif
