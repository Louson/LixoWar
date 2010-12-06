#ifndef _CAMERA_PERSP_H
#define _CAMERA_PERSP_H

/**
 * Caméra en projection perspective.
 * Hérite de la classe Camera.
 */

#include "Camera.h"

class Camera_Persp : public Camera {
        public :
                void set_view(GLfloat field, GLfloat ratio, GLfloat near, GLfloat far);
                void activate();
        private :
                /* Camera field */
                GLfloat field;
                GLfloat ratio;
                GLfloat znear;
                GLfloat zfar;
};

#endif
