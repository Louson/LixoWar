#include <cmath>
#include <stdexcept>
#include <cstdlib>
#include <iostream>

#include "Config.h"
#include "Moto.h"

Moto::Moto(GLfloat start_x, GLfloat start_y, GLfloat start_d[2], GLfloat _moto_size):
    x(start_x),
    y(start_y),
    moto_size(_moto_size),
    wheelNW(start_x + (start_d[0]-start_d[1]/2.0)*_moto_size,
	    start_y + (start_d[0]/2.0+start_d[1])*_moto_size, start_d, _moto_size,  1),

    wheelNE(start_x + (start_d[0]+start_d[1]/2.0)*_moto_size,
	    start_y + (-start_d[0]/2.0+start_d[1])*_moto_size, start_d, _moto_size, 1),

    wheelSE(start_x + (-start_d[0]+start_d[1]/2.0)*_moto_size,
	    start_y + (-start_d[0]/2.0-start_d[1])*_moto_size, start_d, _moto_size, 1),

    wheelSW(start_x + (-start_d[0]-start_d[1]/2.0)*_moto_size,
	    start_y + (start_d[0]/2.0-start_d[1])*_moto_size, start_d, _moto_size,  1)
{
    if (start_d[0]*start_d[1])
        throw(std::range_error("Direction initiale du véhicule impossible"));

    direction[0] = start_d[0];
    direction[1] = start_d[1];
    setCam_ext();
    setCam();
}

void Moto::drawCube(){
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

        glNormal3fv(n[i]);
        glVertex3fv(v[faces[i][0]]);
        glVertex3fv(v[faces[i][1]]);
        glVertex3fv(v[faces[i][2]]);
        glVertex3fv(v[faces[i][3]]);
        glEnd();
    }
}

void Moto::draw() {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MotoAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MotoDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MotoSpecular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MotoShininess);
//	wheelNW.draw();
 	wheelNE.draw();
 	wheelSE.draw();
 	wheelSW.draw();

	glBegin(GL_LINES);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MotoAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MotoDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MotoSpecular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MotoShininess);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(100, 101, 0.0);
	glEnd();

//     for(int k=0; k<3; k++)
//         for(int j=0; j<4; j++)
//             for(int i = -2; i< 2; i++){
//                 float delta = 3.0 - (float) k;
//                 glPushMatrix();
//                 float random_value = (double) rand() / RAND_MAX * 0.3;
//                 switch(j){
//                     case 0:
//                         //glTranslatef((float)0.0+i*moto_size+moto_size/2,(float) random_value + delta, k*moto_size);
//                         break;
//                     case 1:
//                         //              glTranslatef((float) random_value + delta, (float)0.0+i*moto_size+moto_size/2, k*moto_size);
//                         break;
//                     case 2:
//                         //            glTranslatef((float)0.0+i*moto_size+moto_size/2,(float) random_value - delta, k*moto_size);
//                         break;
//                     case 3:
// 			    glTranslatef( - ((float) random_value - delta)*direction[0]
// 					  - ((float)0.0+i*moto_size+moto_size/2)*direction[1],
// 					  - ((float) random_value - delta)*direction[1]
// 					  - ((float)0.0+i*moto_size+moto_size/2)*direction[0],
// 					 k*moto_size);
//                         break;
//                 }
//                 drawCube();
//                 glPopMatrix();
//             }
}

void Moto::setCam() {
    cam.set_position(x-1*MOTO_SIZE*direction[0], y-1*MOTO_SIZE*direction[1], 2*MOTO_SIZE,
            x+1.5*MOTO_SIZE*direction[0], y+1.5*MOTO_SIZE*direction[1], MOTO_SIZE,
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
