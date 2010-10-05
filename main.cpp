#include <iostream>
#include <vector>
#include <math.h>

#include "Config.h"
#include "Board.h"
#include "Camera_Ortho.h"

using namespace std;

Board b(BOARD_SIDE);
Camera_Ortho Cam_A;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	b.drawBoard();
	glutSwapBuffers();
}

void init() {

	/* Window settings */
	glutFullScreen();

	/* Enable object emission light */
	glColorMaterial(GL_FRONT_AND_BACK, GL_SHININESS);
	glEnable(GL_COLOR_MATERIAL);

	/* Use Depth Buffering */
	glEnable(GL_DEPTH_TEST);


	/* Setup the view of the cube */
	Cam_A.set_position(3*BOARD_SIDE, 2*BOARD_SIDE, 3*BOARD_SIDE, /*Cam position */
			   0.0, 0.0, 0.0, /* center position */
			   -9.0/11.0, -6.0/11.0, 13.0/11.0); /* up in positive z direction */
	Cam_A.set_view(/* X */ -0.75*BOARD_SIDE, 0.75*BOARD_SIDE,
		       /* Y */ -0.75*BOARD_SIDE, 0.75*BOARD_SIDE,
		       /* Z near */ 0.5*BOARD_SIDE*sqrt(22.0),
		       /* Z far */ 1.5*BOARD_SIDE*sqrt(22.0));
}

int main(int argc, char ** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Lixo War");

	glutDisplayFunc(display);
//	glutKeyboardFunc(clavier);
	init();

	/* Camera activated */
	Cam_A.activer();

	glutMainLoop();
	return 0;
}
