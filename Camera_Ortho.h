#ifndef _CAMERA_ORTHO_H
#define _CAMERA_ORTHO_H

/**
 * Caméra en projection orthographique.
 * Hérite de la classe Camera.
 */

#include "Camera.h"

class Camera_Ortho : public Camera {
public :
	Camera_Ortho();
	Camera_Ortho(GLfloat position[3],
		     GLfloat center[3],
		     GLfloat up_direction[3],
		     GLfloat left, GLfloat right,
		     GLfloat down, GLfloat up,
		     GLfloat near, GLfloat far);
	void set_view(GLfloat left, GLfloat right,
		      GLfloat down, GLfloat up,
		      GLfloat near,GLfloat  far);
	void activer();
private :
	/* Camera field */
	GLfloat xmin;
	GLfloat xmax;
	GLfloat ymin;
	GLfloat ymax;
	GLfloat znear;
	GLfloat zfar;
};

#endif

