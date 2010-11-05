#ifndef _PLAN_TEXT_H
#define _PLAN_TEXT_H

#include "Texture.h"
#include "Plan.h"

class PlanText: public Plan {
    private:
        Texture & ref_texture;
    public: 
        PlanText(Texture &);
        void draw();
};

#endif
