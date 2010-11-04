#include <string>
#include <cassert>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#include "Window.h"
#include "Game.h"

extern Game * pt_game;

/**
 * Create the window
 */
void Window::create(const char * window_name, int * argc, char ** argv){
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glutCreateWindow(window_name);
    glutFullScreen();
}

/**
 * Because of the limitations of GLUT C bindings,
 * this function needs to be static => it's impossible to 
 * use Functor
 */
void Window::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    /* drawing main function */
    assert(pt_game !=NULL);
    pt_game -> draw();

    glutSwapBuffers();
}

/**
 * Init the windows
 */
void Window::init(){

	glutDisplayFunc(&Window::display);
	glutKeyboardFunc(&Window::keyboard);

	/* Use Depth Buffering */
	glEnable(GL_DEPTH_TEST);

	/* Textures */

	/* Lights settings
	 *
	 *if the light is set before the cam, the location depends of the
	 * cam settings
	 */
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);

	/**
	 * Graphics settings
	 */
	
	/* Lines antialiassing */
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);

}

void Window::keyboard(unsigned char cara,int x, int y){

	switch((int) cara){
	case KEY_ESC:
		glutLeaveMainLoop();
		break;
	case 'c' :
        pt_game->exchangeCam();
        glutPostRedisplay();
		break;
	default:
		std::cout << "cara: "<<(int)cara<<" x: "<<x<<" y: "<<y<<std::endl;
		break;
	}
}
