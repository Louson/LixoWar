#include "PlanText.h"

const GLfloat WallEmission[] = {0.2, 0.2, 0.2, 1};
const GLfloat WallDiffuse[] = {1, 1, 1, 1};
const GLfloat WallAmbient[] = {1, 1, 1, 1};
const GLfloat WallSpecular[] = {1, 1, 1, 1};
const GLfloat WallShininess = 70;

PlanText::PlanText(Texture & _ref_text, Color & _color):
        ref_texture(_ref_text),
        color(_color)
{
}

void PlanText::draw(){
    /* Sky's drawing */
    ref_texture.activate();
    color.active();
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
