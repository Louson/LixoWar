#include <GL/freeglut.h>
#include <cmath>

#include "Laser.h"

#define UP_COORD 70

#define EPSILON 3

Laser::Laser(const GLfloat _x, const GLfloat _y, const int _dim_line_x, const int _dim_line_y):
        x_pos(_x), y_pos(_y),
        dim_line_x(_dim_line_x), dim_line_y(_dim_line_y),
        activated(true), base_color(ORANGE), top_color(ORANGE)
{
}

void Laser::draw(void)
{
        if(!activated)
                return;

        glPushMatrix();
       
        glTranslatef(x_pos, y_pos, 0);

        glBegin(GL_TRIANGLES);
        top_color.active();
        glVertex3f(0, 0, UP_COORD);
        base_color.active();
        glVertex3f(dim_line_x/2, 0, 0);
        glVertex3f(0, dim_line_y, 0);
        glEnd();

        glBegin(GL_TRIANGLES);
        top_color.active();
        glVertex3f(0, 0, UP_COORD);
        base_color.active();
        glVertex3f(0, dim_line_y, 0);
        glVertex3f(-dim_line_x/2, 0, 0);
        glEnd();
        
        glBegin(GL_TRIANGLES);
        top_color.active();
        glVertex3f(0, 0, UP_COORD);
        base_color.active();
        glVertex3f(-dim_line_x/2, 0, 0);
        glVertex3f(dim_line_x/2, 0, 0);
        glEnd();

        /* bottom triangle for the map */
        glBegin(GL_TRIANGLES);
        base_color.active();
        glVertex3f(0, dim_line_y, 1);
        glVertex3f(-dim_line_x/2, 0, 1);
        glVertex3f(dim_line_x/2, 0, 1);
        glEnd();

        glPopMatrix();
}

const bool Laser::testPos(const int _x, const int _y) const
{
        return std::abs(_x - x_pos) < EPSILON && std::abs(_y - y_pos) < EPSILON;
}

void Laser::deactivate(void)
{
        activated = false;
}
