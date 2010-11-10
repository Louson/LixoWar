#ifndef _CAMERA_ORTHO_H
#define _CAMERA_ORTHO_H

/**
 * Caméra en projection orthographique.
 * Hérite de la classe Camera.
 */

#include "Camera.h"

#define ZOOM_MAX 73

class Camera_Ortho : public Camera {
public :
	Camera_Ortho();
	void set_view(GLfloat left, GLfloat right,
		      GLfloat down, GLfloat up,
		      GLfloat near,GLfloat  far);
        void activate();
        void zoom(GLfloat);
private :
        int gradient;	
        /* Camera field */
        GLfloat xmin;
	GLfloat xmax;
	GLfloat ymin;
	GLfloat ymax;
	GLfloat znear;
	GLfloat zfar;
};

#endif
