#include <iostream>
#include <vector>
#include <math.h>

#include "Constantes.h"
#include "Board.h"

using namespace std;

Board b(BOARD_SIDE);
//Camera_Ortho Cam0 = Camera_Ortho();

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	b.drawBoard();
	glutSwapBuffers();
}

void init() {

	/* Caractéristiques de la fenêtre */
	glutFullScreen();

	/* Autorisation des luminosités des objets */
	glColorMaterial(GL_FRONT_AND_BACK, GL_SHININESS);
	glEnable(GL_COLOR_MATERIAL);

	/* Use Depth Buffering */
	glEnable(GL_DEPTH_TEST);

	/* Setup the view of the cube */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3*BOARD_SIDE, 2*BOARD_SIDE, 3*BOARD_SIDE, /* eye position */
		  0.0, 0.0, 0.0, /* center position */
 		  -9.0/11.0, -6.0/11.0, 13.0/11.0); /* up in positive z direction */

 	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.75*BOARD_SIDE, 0.75*BOARD_SIDE, -0.75*BOARD_SIDE, 0.75*BOARD_SIDE,
		/* Z near */ 0.5*BOARD_SIDE*sqrt(22.0), /* Z far */ 1.5*BOARD_SIDE*sqrt(22.0));


// 	gluPerspective( /* field of view in degree */ 20.0,
// 			/* aspect ratio */ 1.0,
// 			/* Z near */ 0.5*BOARD_SIDE*sqrt(22.0), /* Z far */ 1.5*BOARD_SIDE*sqrt(22.0));

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
