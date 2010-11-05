#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <GL/glut.h>

using namespace std;

class Texture {
public:
	Texture(const char* _path);
    ~Texture();
	void readPPM(const char* path);
	void activate();
    void disable();
private:
	unsigned char* image;
	GLint width;
	GLint height;
};

#endif
