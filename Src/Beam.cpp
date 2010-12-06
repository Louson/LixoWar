#include <iostream>
#include <cmath>

#include "Beam.h"

using namespace std;

const GLfloat emission_P1[4] = {0.3, 0.0, 0.0, 0.5};
const GLfloat ambient_P1[4] = {0.0, 0.0, 0.0, 0.0};
const GLfloat diffuse_P1[4]= {0.0, 0.0, 0.0, 0.0};
const GLfloat specular_P1[4]= {0.0, 0.0, 0.0, 0.0};
const GLfloat shininess_P1 = 20;

const GLfloat emission_P2[4]= {0.0, 0.0, 0.0, 0.0};
const GLfloat ambient_P2[4]= {0.0, 0.0, 0.0, 0.0};
const GLfloat diffuse_P2[4]= {0.0, 0.0, 0.0, 0.0};
const GLfloat specular_P2[4]= {0.0, 0.0, 0.0, 0.0};
const GLfloat shininess_P2 = 20;

const GLfloat emission_P3[4]= {0.0, 0.0, 0.0, 0.0};
const GLfloat ambient_P3[4]= {0.0, 0.0, 0.0, 0.0};
const GLfloat diffuse_P3[4]= {0.0, 0.0, 0.0, 0.0};
const GLfloat specular_P3[4]= {0.0, 0.0, 0.0, 0.0};
const GLfloat shininess_P3 = 20;

Beam::Beam(MOTO_STRUCT moto) :
	x(moto.x), y(moto.y)
{
	ante_dir[0] = cos(((float)moto.angle)*M_PI/180.0);
	ante_dir[1] = sin(((float)moto.angle)*M_PI/180.0);
	post_dir[0] = cos(((float)moto.angle)*M_PI/180.0);
	post_dir[1] = sin(((float)moto.angle)*M_PI/180.0);
}

Beam::~Beam(){
        delete color;
}

Beam::Beam(GLfloat _x, GLfloat _y, GLfloat _ante_angle, GLfloat _post_angle, GLint _num_moto, GLfloat _size_case_x, GLfloat _size_case_y) :
	x(_x), y(_y), size_case_x(_size_case_x), size_case_y(_size_case_y) {
	ante_dir[0] = cos(((float)_ante_angle)*M_PI/180.0);
	ante_dir[1] = sin(((float)_ante_angle)*M_PI/180.0);
	post_dir[0] = cos(((float)_post_angle)*M_PI/180.0);
	post_dir[1] = sin(((float)_post_angle)*M_PI/180.0);

	switch (_num_moto) {
	case 1 :
		color = new Color(emission_P1, ambient_P1, diffuse_P1, specular_P1, shininess_P1);
		break;
	case 2 :
		break;
	case 3 :
		break;
	default:
		break;
	}
}

void Beam::setPostAngle(int angle) {
	post_dir[0] = cos(((float)angle)*M_PI/180.0);
	post_dir[1] = sin(((float)angle)*M_PI/180.0);
}

void Beam::draw() {
// 	GLfloat ante_diff = (ante_dir[0] - ante_dir[1])/2.0;
// 	GLfloat post_diff = (post_dir[0] - post_dir[1])/2.0;
	color->active();

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



// 	glBegin(GL_QUADS); {
// 		glVertex3f(x+ ante_diff, y-ante_diff, 0.0);
// 		glVertex3f(x, y, H_BEAM);
// 		glVertex3f(x-ante_dir[0], y-ante_dir[1], H_BEAM);
// 		glVertex3f(x-ante_dir[0]-ante_dir[1]/2.0, y-ante_dir[1]-ante_dir[0]/2.0, 0.0);
// 		glEnd();}
// 	glBegin(GL_QUADS); {
// 		glVertex3f(x-ante_diff, y+ante_diff, 0.0);
// 		glVertex3f(x, y, H_BEAM);
// 		glVertex3f(x-ante_dir[0], y-ante_dir[1], H_BEAM);
// 		glVertex3f(x-ante_dir[0]+ante_dir[1]/2.0, y-ante_dir[1]+ante_dir[0]/2.0, 0.0);
// 		glEnd();}

// 	glBegin(GL_QUADS); {
// 		glVertex3f(x-post_diff, y+post_diff, 0.0);
// 		glVertex3f(x, y, H_BEAM);
// 		glVertex3f(x+post_dir[0], y+post_dir[1], H_BEAM);
// 		glVertex3f(x+post_dir[0]+post_dir[1]/2.0, y+post_dir[1]+post_dir[0]/2.0, 0.0);
// 		glEnd();}
// 	glBegin(GL_QUADS); {
// 		glVertex3f(x+post_diff, y-post_diff, 0.0);
// 		glVertex3f(x, y, H_BEAM);
// 		glVertex3f(x+post_dir[0], y+post_dir[1], H_BEAM);
// 		glVertex3f(x+post_dir[0]-post_dir[1]/2.0, y+post_dir[1]-post_dir[0]/2.0, 0.0);
// 		glEnd();}
}