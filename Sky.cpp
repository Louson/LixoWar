#include <stdexcept>
#include <stdio.h>
#include <iostream>

#include "Sky.h"
#include "Board.h"


Sky::Sky(GLfloat _board_x, GLfloat _board_y, const char* _path) {

	set_normal(0, 0, 1);
	set_vertex(0,  _board_x/2, -_board_y/2, H_SKY);
	set_vertex(1,  _board_x/2,  _board_y/2, H_SKY);
	set_vertex(2, -_board_x/2,  _board_y/2, H_SKY);
	set_vertex(3, -_board_x/2, -_board_y/2, H_SKY);

	/* Ouverture du fichier image */
	readPPM(_path);
}

Sky::~Sky() {
	if (image) delete image;
}

void Sky::draw() {

	/* Texture set */
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,
		     0,
		     GL_RGB,
		     width, height, 0,
		     GL_RGB,
		     GL_UNSIGNED_BYTE,
		     image);
	
	/* Sky's drawing */
	glBegin(GL_QUADS); {
		glNormal3fv(n);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(v[0][0], v[0][1], v[0][2]);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(v[1][0], v[1][1], v[1][2]);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(v[2][0], v[2][1], v[2][2]);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(v[3][0], v[3][1], v[3][2]);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

}

void Sky::readPPM(const char* _path) {
	FILE *fp;
	int max_color_value;
	unsigned char *temp;
     	char magic[2];
	char white;
	char buff[30];
	int i;

	if ( !(fp = fopen(_path, "rb")) ) {
		throw invalid_argument("Sky image does not exist");
	}

	/* lecture of magic number */
	fread(magic, 2, sizeof(char), fp);
	cout << "magic = " << magic << endl;
	if ( magic[0] != 'P' || magic[1] != '6') {
		throw invalid_argument("Sky image isn't .ppm");
	}
	fread(&white, 1, sizeof(char), fp);

	/* width, height and max_color_value */
	i = 0;
	while(i < 3) {
		fgets(buff, 10, fp);
		if (buff[0] == '#') continue;
		switch(i) {
		case 0 :
			i += sscanf(buff, "%d %d %d",
				    &width, &height, &max_color_value);
			break;
		case 1 :
			i += sscanf(buff, "%d %d",
				    &height, &max_color_value);
			break;
		case 2 :
			i += sscanf(buff, "%d", &max_color_value);
			break;
		}
	}

	if (width<0) {
		throw invalid_argument("Sky's image is width negative");
	}
	if (height<0) {
		throw invalid_argument("Sky's image is height negative");
	}
	if (max_color_value<0 || max_color_value>65536) {
		throw invalid_argument("Sky's colors are strange");
	}

	/* Image lecture */
	if (max_color_value >= 256) {
		throw invalid_argument("Sky's got to much colors for me yet");
	}
// 	image = new unsigned char**[width];
// 	for (int c=0 ; c<width ;c++) {
// 		image[c] = new unsigned char*[height];
// 			for (int l=0 ; l<height ; l++)
// 				image[c][l] = new unsigned char[3];
// 	}
	cout<<"width="<<width<<", height="<<height<<endl;
	image = new unsigned char[width*height*3];
	
	fread(image, width*height*3, sizeof(char), fp);

	fclose(fp);	
}
