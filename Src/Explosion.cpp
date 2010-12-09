#include <GL/freeglut.h>

#include "Color.h"
#include "Explosion.h"

#define MAX_RADIUS 3
#define RADIUS_INCREMENT 0.05

static const GLfloat Emission[] = {0.0, 0.0, 0.0, 1};
static const GLfloat Diffuse[] = {1, 0.5, 0 , 1.0};
static GLfloat Ambient[] = {1, 0.5 , 0,  1.0};
static const GLfloat Specular[] = {1, 1, 1, 1,};
static const GLfloat Shininess = 70;

Explosion::Explosion(const int _x, const int _y, const int _moto_size):
        center_x(_x), center_y(_y),
        radius(0), increment(true),
        explosion_finished(false),
        apogee(false),
        moto_size(_moto_size)
{
}

bool Explosion::getApogee(void) const
{
        return apogee;
}

bool Explosion::getEnd(void) const
{
        return explosion_finished;
}
void Explosion::changeRadius(void)
{
        if(increment){
                if(radius + RADIUS_INCREMENT > MAX_RADIUS*moto_size){
                        radius = MAX_RADIUS;
                        apogee = true;
                        increment = false;
                }else{
                        radius = radius + RADIUS_INCREMENT;
                }
        }else{
                if(radius - RADIUS_INCREMENT < 0){
                        radius = 0;
                        explosion_finished = true;
                }else
                        radius -= RADIUS_INCREMENT;
        }
}

void Explosion::changeColor(void)
{
        Ambient[2] = radius/(3*MAX_RADIUS*moto_size);
        Ambient[1] = radius/(2*MAX_RADIUS*moto_size);
        Color color(Emission, Ambient, Diffuse, Specular, Shininess);
        color.active();
}

void Explosion::draw(void)
{
        changeRadius();
        changeColor();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(center_x, center_y, 0);
        glutSolidSphere((GLdouble) radius, (GLint) 100, (GLint) 100);
        glPopMatrix(); 
}
