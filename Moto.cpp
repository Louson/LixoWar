#include <cmath>
#include <stdexcept>

#include "Config.h"
#include "Moto.h"

Moto::Moto(GLfloat start_x, GLfloat start_y, GLfloat start_d[2], GLfloat _moto_size):
    x(start_x),
    y(start_y),
    moto_size(_moto_size)
{
    if (start_d[0]*start_d[1])
        throw(std::range_error("Direction initiale du véhicule impossible"));

    direction[0] = start_d[0];
    direction[1] = start_d[1];
    setCam_ext();
    setCam();
}

void Moto::draw() {
    glPushMatrix();
    glTranslatef(0.0f,5.0f,0.0f);
    glutSolidCube((GLdouble) moto_size);
    glPopMatrix();
    //#   glEnd();
    //#   return;

    GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
        {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0}, {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
    GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
        {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
        {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
    GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

    /* plans x = -2 et x = 2 */
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = x-moto_size/2.0;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = x+moto_size/2.0;
    /* y = -2 et y = 2*/ 
    v[0][1] = v[1][1] = v[5][1] = v[4][1] = y-moto_size/2.0;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = y+moto_size/2.0;
    /* z = 4 et z = 0 */
    v[4][2] = v[7][2] = moto_size;
    v[0][2] = v[3][2] = moto_size;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] =  0;

    for (int i=0 ; i<6 ; i++) {
       glBegin(GL_QUADS);
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MotoAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MotoDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MotoSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MotoShininess);

        glNormal3fv(n[i]);
        glVertex3fv(v[faces[i][0]]);
        glVertex3fv(v[faces[i][1]]);
        glVertex3fv(v[faces[i][2]]);
        glVertex3fv(v[faces[i][3]]);
        glEnd();
    }
}

void Moto::setCam() {
    cam.set_position(x-1.5*MOTO_SIZE*direction[0], y-1.5*MOTO_SIZE*direction[1], 1.5*MOTO_SIZE,
            x+MOTO_SIZE*direction[0], y+MOTO_SIZE*direction[1], MOTO_SIZE,
            0, 0, 1);
    cam.set_view(100, SCREEN_RATIO, 0.05, VIEW_DIST);
}

void Moto::setCam_ext() {
    cam_ext.set_position(0, 0, H_CAM, /*Cam position */
            x, y, 0,
            0, 1, 0);
    cam_ext.set_view(/* X */ -SCREEN_RATIO*2.0*MOTO_WIDTH,
            SCREEN_RATIO*2.0*MOTO_WIDTH,
            /* Y */ -2.0*MOTO_LENGTH,
            2.0*MOTO_LENGTH,
            /* Z near */ 0,
            /* Z far  */ 1.1*H_CAM);
}

void Moto::activateCam() {
    cam.activate();
}

void Moto::activateCam_ext() {
    cam_ext.activate();
}

Camera_Persp * Moto::getPtCam(){
    return &cam;
}

Camera_Ortho * Moto::getPtCam_ext(){
    return &cam_ext;
}
