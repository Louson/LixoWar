#include <iostream>
#include <cmath>

#include "Beam.h"

using namespace std;

Beam::Beam(MOTO_STRUCT moto, enum COLOR _color):
	x(moto.x), y(moto.y), color(_color)
{
	ante_dir[0] = cos(((float)moto.angle)*M_PI/180.0);
	ante_dir[1] = sin(((float)moto.angle)*M_PI/180.0);
	post_dir[0] = cos(((float)moto.angle)*M_PI/180.0);
	post_dir[1] = sin(((float)moto.angle)*M_PI/180.0);
}

Beam::Beam(GLfloat _x, GLfloat _y, GLfloat _ante_angle, GLfloat _post_angle, GLint _num_moto, GLfloat _size_case_x, GLfloat _size_case_y, enum COLOR _color) :
	x(_x), y(_y), size_case_x(_size_case_x), size_case_y(_size_case_y),
        color(_color)
{
	ante_dir[0] = cos(((float)_ante_angle)*M_PI/180.0);
	ante_dir[1] = sin(((float)_ante_angle)*M_PI/180.0);
	post_dir[0] = cos(((float)_post_angle)*M_PI/180.0);
	post_dir[1] = sin(((float)_post_angle)*M_PI/180.0);
}

void Beam::setPostAngle(int angle) {
	post_dir[0] = cos(((float)angle)*M_PI/180.0);
	post_dir[1] = sin(((float)angle)*M_PI/180.0);
}

void Beam::draw() {
	color.active();

	glBegin(GL_QUADS); {
		glNormal3i(0,0,1);
		glVertex3f(x-size_case_x/2.0, y-size_case_y/2.0, H_BEAM);
		glVertex3f(x+size_case_x/2.0, y-size_case_y/2.0, H_BEAM);
		glVertex3f(x+size_case_x/2.0, y+size_case_y/2.0, H_BEAM);
		glVertex3f(x-size_case_x/2.0, y+size_case_y/2.0, H_BEAM);
	}glEnd();
	glBegin(GL_QUADS); {
		glNormal3i(0,-1,0);
		glVertex3f(x-size_case_x/2.0, y-size_case_y/2.0, H_BEAM);
		glVertex3f(x+size_case_x/2.0, y-size_case_y/2.0, H_BEAM);
		glVertex3f(x+size_case_x/2.0, y-size_case_y/2.0, 0);
		glVertex3f(x-size_case_x/2.0, y-size_case_y/2.0, 0);
	}glEnd();
	glBegin(GL_QUADS); {
		glNormal3i(0,1,0);
		glVertex3f(x-size_case_x/2.0, y+size_case_y/2.0, H_BEAM);
		glVertex3f(x+size_case_x/2.0, y+size_case_y/2.0, H_BEAM);
		glVertex3f(x+size_case_x/2.0, y+size_case_y/2.0, 0);
		glVertex3f(x-size_case_x/2.0, y+size_case_y/2.0, 0);
	}glEnd();	
	glBegin(GL_QUADS); {
		glNormal3i(1,0,0);
		glVertex3f(x+size_case_x/2.0, y-size_case_y/2.0, H_BEAM);
		glVertex3f(x+size_case_x/2.0, y-size_case_y/2.0, 0);
		glVertex3f(x+size_case_x/2.0, y+size_case_y/2.0, 0);
		glVertex3f(x+size_case_x/2.0, y+size_case_y/2.0, H_BEAM);
	}glEnd();	
	glBegin(GL_QUADS); {
		glNormal3i(-1,0,0);
		glVertex3f(x-size_case_x/2.0, y-size_case_y/2.0, H_BEAM);
		glVertex3f(x-size_case_x/2.0, y-size_case_y/2.0, 0);
		glVertex3f(x-size_case_x/2.0, y+size_case_y/2.0, 0);
		glVertex3f(x-size_case_x/2.0, y+size_case_y/2.0, H_BEAM);
	}glEnd();
}
