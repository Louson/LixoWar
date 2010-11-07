#include <iostream>

#include "Beam.h"

using namespace std;

GLfloat emission_P1[4] = {0.3, 0.0, 0.0, 0.5};
GLfloat ambient_P1[4] = {0.0, 0.0, 0.0, 0.0};
GLfloat diffuse_P1[4]= {0.0, 0.0, 0.0, 0.0};
GLfloat specular_P1[4]= {0.0, 0.0, 0.0, 0.0};
GLfloat shininess_P1 = 20;

GLfloat emission_P2[4]= {0.0, 0.0, 0.0, 0.0};
GLfloat ambient_P2[4]= {0.0, 0.0, 0.0, 0.0};
GLfloat diffuse_P2[4]= {0.0, 0.0, 0.0, 0.0};
GLfloat specular_P2[4]= {0.0, 0.0, 0.0, 0.0};
GLfloat shininess_P2 = 20;

GLfloat emission_P3[4]= {0.0, 0.0, 0.0, 0.0};
GLfloat ambient_P3[4]= {0.0, 0.0, 0.0, 0.0};
GLfloat diffuse_P3[4]= {0.0, 0.0, 0.0, 0.0};
GLfloat specular_P3[4]= {0.0, 0.0, 0.0, 0.0};
GLfloat shininess_P3 = 20;

Beam::Beam() {}

Beam::Beam(GLfloat _x, GLfloat _y, GLfloat _ante_dir[2], GLfloat _post_dir[2], GLint _num_moto) :
	x(_x), y(_y) {
	for (int i=0 ; i<2 ; i++) {
		ante_dir[i] = _ante_dir[i];
		post_dir[i] = _post_dir[i];
	}

	switch (_num_moto) {
	case 1 :
		color = Color(emission_P1, ambient_P1, diffuse_P1, specular_P1, shininess_P1);
		break;
	case 2 :
		break;
	case 3 :
		break;
	default:
		break;
	}
}

void Beam::draw() {
	GLfloat ante_diff = (ante_dir[0] - ante_dir[1])/2.0;
	GLfloat post_diff = (post_dir[0] - post_dir[1])/2.0;
	color.active();
	glBegin(GL_QUADS); {
		glVertex3f(x+ ante_diff, y-ante_diff, 0.0);
		glVertex3f(x, y, H_BEAM);
		glVertex3f(x-ante_dir[0], y-ante_dir[1], H_BEAM);
		glVertex3f(x-ante_dir[0]-ante_dir[1]/2.0, y-ante_dir[1]-ante_dir[0]/2.0, 0.0);
		glEnd();}
	glBegin(GL_QUADS); {
		glVertex3f(x-ante_diff, y+ante_diff, 0.0);
		glVertex3f(x, y, H_BEAM);
		glVertex3f(x-ante_dir[0], y-ante_dir[1], H_BEAM);
		glVertex3f(x-ante_dir[0]+ante_dir[1]/2.0, y-ante_dir[1]+ante_dir[0]/2.0, 0.0);
		glEnd();}

	glBegin(GL_QUADS); {
		glVertex3f(x-post_diff, y+post_diff, 0.0);
		glVertex3f(x, y, H_BEAM);
		glVertex3f(x+post_dir[0], y+post_dir[1], H_BEAM);
		glVertex3f(x+post_dir[0]+post_dir[1]/2.0, y+post_dir[1]+post_dir[0]/2.0, 0.0);
		glEnd();}
	glBegin(GL_QUADS); {
		glVertex3f(x+post_diff, y-post_diff, 0.0);
		glVertex3f(x, y, H_BEAM);
		glVertex3f(x+post_dir[0], y+post_dir[1], H_BEAM);
		glVertex3f(x+post_dir[0]-post_dir[1]/2.0, y+post_dir[1]-post_dir[0]/2.0, 0.0);
		glEnd();}
}
