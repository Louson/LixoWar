#ifndef _CAMERA_PERSP_H
#define _CAMERA_PERSP_H

/**
 * Caméra en projection perspective.
 * Hérite de la classe Camera.
 */

#include "Camera.h"

class Camera_Persp : public Camera {
public :
	Camera_Persp();
	Camera_Persp(GLfloat position[3],
		     GLfloat center[3],
		     GLfloat up_direction[3],
		     GLfloat field, GLfloat ratio,
		     GLfloat near, GLfloat far);
	void set_view(GLfloat field, GLfloat ratio,
		      GLfloat near,GLfloat  far);
	void activer();
private :
	/* Camera field */
	GLfloat field;
	GLfloat ratio;
	GLfloat znear;
	GLfloat zfar;
};

#endif

