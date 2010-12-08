#ifndef _MOTO_H
#define _MOTO_H

#include <GL/glut.h>

#include "Color.h"
#include "Drawable.h"
#include "Explosion.h"
#include "Wheel.h"

#define MOTO_WIDTH      4.0
#define MOTO_LENGTH     4.0

/* Wheels settings */
#define FRONT_WHEELS_H_DISTANCE_RATIO   1/4
#define BACK_WHEELS_H_DISTANCE_RATIO    1/2
#define FRONT_WHEELS_W_DISTANCE_RATIO   1/3

enum COLOR {BLUE = 0, RED};

class Moto : public Drawable{
public :
	Moto(GLfloat moto_size, enum COLOR);
        ~Moto(void);
	void draw();
	void setPos(GLfloat _x, GLfloat _y, int _angle);
        void explode(void);
        bool getEndExplosion(void) const;

private :
        Color color;
	GLfloat x;
	GLfloat y;

	GLint angle;

	GLfloat moto_size;

	Wheel wheelNW;
	Wheel wheelNE;
	Wheel wheelSE;
	Wheel wheelSW;

        Explosion *pt_explosion;
};

typedef struct moto_struct {
        GLfloat x;
        GLfloat y;
	int presence_x;
	int presence_y;
        int angle;
        GLfloat speed;
        Moto * pt_moto;
} MOTO_STRUCT;

typedef struct enemy_struct {
        int numero;
	GLfloat x;
        GLfloat y;
	int presence_x;
	int presence_y;
        int angle;
        GLfloat speed;
        Moto * pt_moto;
} ENEMY_STRUCT;

#endif
