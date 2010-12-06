#ifndef _PLAN_TEXT_H
#define _PLAN_TEXT_H

#include "Texture.h"
#include "Plan.h"
#include "Color.h"

class PlanText: public Plan {
    private:
        Texture & ref_texture;
        Color color;
    public: 
        PlanText(Texture &, Color &);
        void draw();
};

#endif
