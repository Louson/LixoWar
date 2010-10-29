#include <string>
#include <stdexcept>
#include <stdio.h>
#include <iostream>

#include "Sky.h"
#include "Board.h"
#include "Texture.h"

Sky::Sky(GLfloat _board_x, GLfloat _board_y, const char* _path) {

	set_normal(0, 0, 1);
	set_vertex(0,  _board_x/2, -_board_y/2, H_SKY);
	set_vertex(1,  _board_x/2,  _board_y/2, H_SKY);
	set_vertex(2, -_board_x/2,  _board_y/2, H_SKY);
	set_vertex(3, -_board_x/2, -_board_y/2, H_SKY);

	cout<<_path<<endl;
	readPPM(_path);
//	image = Texture(_path, _board_x, _board_y);
}

Sky::~Sky() {
	if (&image) delete &image;
}

void Sky::draw() {

	/* Texture set */
//	image.activate();
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

void Sky::readPPM(const char* _path) {
	FILE *fp;
	int max_color_value;
     	char magic[3];
	char white;
	char buff[100];
	int i;

	if ( !(fp = fopen(_path, "rb")) ) {
		throw invalid_argument("Texture image does not exist");
	}

	/* lecture of magic number */
	fread(magic, 2, sizeof(char), fp);
	magic[2]='\0';
	cout << "magic = " << magic << endl;
	if ( magic[0] != 'P' || magic[1] != '6') {
		throw invalid_argument("Texture image isn't .ppm");
	}
	fread(&white, 1, sizeof(char), fp);

	/* width, height and max_color_value */
	i = 0;
	while(i < 3) {
		fgets(buff, 100, fp);
		if (buff[0] == '#') continue;
		//cout << i<<endl;
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
		default :
			cout<<i<<"default"<<endl;
			i=3;
			break;
		}
	}
	cout<<"width="<<width<<", height="<<height<<", col="<<max_color_value<<endl;

	if (width<0) {
		throw invalid_argument("Texture's image is width negative");
	}
	if (height<0) {
		throw invalid_argument("Texture's image is height negative");
	}
	if (max_color_value<0 || max_color_value>65536) {
		throw invalid_argument("Texture's colors are strange");
	}

	/* Image lecture */
	if (max_color_value >= 256) {
		throw invalid_argument("Texture's got to much colors for me yet");
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

	cout<<image[0]<<"__"<<image[width*height*3-1]<<endl;

	fclose(fp);	
}
