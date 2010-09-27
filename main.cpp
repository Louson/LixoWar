#include <iostream>
#include <vector>

#include "Board.h"

using namespace std;

Board b(5000, 5000);

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	b.drawBoard();
	glutSwapBuffers();
}

void init() {

	glColorMaterial(GL_FRONT_AND_BACK, GL_SHININESS);
	glEnable(GL_COLOR_MATERIAL);


	/* Use Depth Buffering */
	glEnable(GL_DEPTH_TEST);
	/* Setup the view of the cube */
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
			/* aspect ratio */ 1.0,
			/* Z near */ 1.0, /* Z far */ 10.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(3, 1, 3, /* eye position */
		  0.0, 0.0, 0.0, /* center position */
		  0.0, 0.0, 1.0); /* up in positive y direction */

	/* Adjust cube position */
// 	glTranslatef(0.0, 0.0, -1.0);
// 	glRotatef(60, 1.0, 0.0, 0.0);
// 	glRotatef(-20, 0.0, 0.0, 1.0);

}

int main(int argc, char ** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Troc");

	glutDisplayFunc(display);
//	glutKeyboardFunc(clavier);
	init();

	glutMainLoop();
	return 0;
}
