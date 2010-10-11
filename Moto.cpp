#include <cmath>
#include "Moto.h"

GLfloat MotoDiffuse[3] = {0, 1.0, 0};
GLfloat MotoAmbient[3] = {1.0, 0.0, 0.0};
GLfloat MotoSpecular[3] = {1.0, 0.0, 0.0};
GLfloat MotoShininess = 120;

Moto::Moto() {
}

Moto::Moto(GLfloat start_x, GLfloat start_y, GLfloat start_d[2])
	: x(start_x), y(start_y) {
	direction[0] = start_d[0];
	direction[1] = start_d[1];
    setCam();
}

void Moto::draw() {
// 	GLfloat n[5][3]={{1,0,0}, (0,1,0},
// 			  {-1,0,0}, {0,-1,0}, {0,0,1}};
// 	GLfloat v[8][3]={{-2,-2,0}, {2,-2,0},
// 			 {2,2,0}, {-2,2,0},
// 			 {-2,-2,4}, {2,-2,4},
// 			 {2,2,4}, {-2,2,4}};
	GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
		{-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
		{1.0, 0.0, 0.0}, {0.0, -1.0, 0.0},
		{0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
	GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
		{0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
		{4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
	GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

	/* plans x = -2 et x = 2 */
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -MOTO_SIZE/2.0;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] =  MOTO_SIZE/2.0;
	/* y = -2 et y = 2*/ 
	v[0][1] = v[1][1] = v[5][1] = v[4][1] = -MOTO_SIZE/2.0;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] =  MOTO_SIZE/2.0;
	/* z = 4 et z = 0 */
	v[4][2] = v[7][2] = MOTO_SIZE/2;
	v[0][2] = v[3][2] = MOTO_SIZE;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] =  0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MotoAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MotoDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MotoSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MotoShininess);

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

void Moto::setCam() {
	cam.set_position(x-3*MOTO_SIZE*direction[0], y-3*MOTO_SIZE*direction[1], 2*MOTO_SIZE,
			 x+MOTO_SIZE*direction[0], y+MOTO_SIZE*direction[1], 0,
			 0, 0, 1);
	cam.set_view(100, 1,
		     0.05, 3*MOTO_SIZE);		
}

void Moto::activateCam() {
	cam.activate();
}

Camera_Persp * Moto::getPtCam(){
    return &cam;
}
