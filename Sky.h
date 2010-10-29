#ifndef _SKY_H
#define _SKY_H

#include <GL/glut.h>
#include <string>
#include "Plan.h"

#define H_SKY 3000

using namespace std;

class Sky : public Plan{
public :
	/**
	 * Constructeurs
	 */
	Sky(GLfloat _board_x, GLfloat _board_y, const char* _path);
	~Sky();

	/**
	 * Méthodes
	 */
	void draw();
	void readPPM(const char* _path);
protected:
	unsigned char *image;
	//Texture image;
	GLint width;
	GLint height;
};


#endif
