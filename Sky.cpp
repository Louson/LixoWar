#include <string>
#include <stdexcept>
#include <stdio.h>
#include <iostream>

#include "Sky.h"
#include "Board.h"

Sky::Sky() {
}

Sky::Sky(GLfloat _board_x, GLfloat _board_y, const char* _path) {

	set_normal(0, 0, 1);
	set_vertex(0,  _board_x/2, -_board_y/2, H_SKY);
	set_vertex(1,  _board_x/2,  _board_y/2, H_SKY);
	set_vertex(2, -_board_x/2,  _board_y/2, H_SKY);
	set_vertex(3, -_board_x/2, -_board_y/2, H_SKY);

	cout<<_path<<endl;
	text = new Texture(_path);
}

Sky::~Sky() {
	if (image) delete image;
}

void Sky::draw() {

	/* Texture set */
	text->activate();

	/* Sky's drawing */
	glBegin(GL_QUADS); {
		glNormal3fv(n);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(v[0][0], v[0][1], v[0][2]);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(v[1][0], v[1][1], v[1][2]);
		glTexCoord2f(0, 0);
		glVertex3f(v[2][0], v[2][1], v[2][2]);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(v[3][0], v[3][1], v[3][2]);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

}
