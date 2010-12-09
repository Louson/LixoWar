#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#include "Drawable.h"

class Explosion : public Drawable{
        public:
                Explosion(const int, const int, const int);
                void draw(void);
                bool getEnd(void) const;
                bool getApogee(void) const;

        private:
                int center_x, center_y;
                double radius;
                bool increment, explosion_finished;
                bool apogee;
                int moto_size;

                void changeRadius(void);
                void changeColor(void);
};
#endif
