#include "PlanText.h"

PlanText::PlanText(Texture & _ref_text):
    ref_texture(_ref_text)
{
}

void PlanText::draw(){
    /* Sky's drawing */
    ref_texture.activate();
    glBegin(GL_QUADS); 
    {
        glNormal3fv(n);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(v[0][0], v[0][1], v[0][2]);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(v[1][0], v[1][1], v[1][2]);
        glTexCoord2f(0, 0);
        glVertex3f(v[2][0], v[2][1], v[2][2]);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(v[3][0], v[3][1], v[3][2]);
    }
    glEnd();
    ref_texture.disable();
}
