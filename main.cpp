#include <iostream>
#include <vector>
#include <math.h>

#include "Board.h"

using namespace std;

Board b(1000);
const double side = b.get_side();

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	b.drawBoard();
	glutSwapBuffers();
}

void init() {

	glColorMaterial(GL_FRONT_AND_BACK, GL_SHININESS);
	glEnable(GL_COLOR_MATERIAL);


	/* Use Depth Buffering */
	glEnable(GL_DEPTH_TEST);
	/* Setup the view of the cube */
	glMatrixMode(GL_MODELVIEW);
 	gluLookAt(3*side, 2*side, 3*side, /* eye position */
 		  0.0, 0.0, 0.0, /* center position */
 		  0.0, 0.0, 1.0); /* up in positive y direction */
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
			/* aspect ratio */ 1.0,
			/* Z near */ 0.5*side*sqrt(22.0), /* Z far */ 1.5*side*sqrt(22.0));

}

int main(int argc, char ** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Lixo War");

	glutDisplayFunc(display);
//	glutKeyboardFunc(clavier);
	init();

	glutMainLoop();
	return 0;
}
