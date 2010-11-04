#include <stdexcept>
#include <stdio.h>
#include <iostream>

#include "Texture.h"

Texture::Texture(const char* _path) {
	readPPM(_path);
}

void Texture::activate() {
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
}

void Texture::readPPM(const char* _path) {
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
	image = new unsigned char[width*height*3];

	fread(image, width*height*3, sizeof(char), fp);

	fclose(fp);	
	
}
