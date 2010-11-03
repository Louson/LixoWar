#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <GL/glut.h>

using namespace std;

class Texture {
public:
	Texture(const char* _path);
	void readPPM(const char* path);
	void activate();
private:
	unsigned char* image;
	GLint width;
	GLint height;
};

#endif
