#ifndef _CAMERA_H
#define _CAMERA_H

#include <GL/glut.h>


/**
 * Nécessite deux sous-classes : en mode projection et en mode
 * orthographique
 */

class Camera {
public :
	Camera();
	void lookAt();
	void set_position(GLfloat x, GLfloat y, GLfloat z,
			  GLfloat xcenter, GLfloat ycenter, GLfloat zcenter,
			  GLfloat xup, GLfloat yup, GLfloat zup);
private :
	/* Camera settings */
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat x_center;
	GLfloat y_center;
	GLfloat z_center;
	GLfloat x_up_direction;
	GLfloat y_up_direction;
	GLfloat z_up_direction;
};


#endif
