#include <string>
#include <cassert>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

#include "Window.h"
#include "Camera_Ortho.h"
#include "Config.h"
#include "Located_Light.h"
#include "Spot.h"
#include "Moto.h"

extern Board * pt_board;

GLfloat m_direction[2] ={-1, 0};
Moto m(0, 0, m_direction);

extern Camera_Ortho Cam_A;

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
    pt_board -> drawBoard();
    m.drawMoto();
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

	/* Camera init */
	Cam_A.set_position(3*SIDE_X, 2*SIDE_Y, 3*SIDE_X, /*Cam position */
			   0.0, 0.0, 0.0, /* center position */
			   0,0,1);
	Cam_A.set_view(/* X */ -0.7*SIDE_X, 0.7*SIDE_X,
		       /* Y */ -0.45*SIDE_Y, 0.45*SIDE_Y,
		       /* Z near */ 0.86*SIDE_X*sqrt(22.0),
		       /* Z far  */ 1.12*SIDE_X*sqrt(22.0));

	m.setCam();
//	m.activateCam();

	/* Lights settings
	 *
	 *if the light is set before the cam, the location depends of the
	 * cam settings
	 */
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
// 	glEnable(GL_LIGHT1);
// 	GLfloat ocation[4] = {10000.0, 0.0, 10000.0, 1.0};
// 	GLfloat iffuse[4] = {1.0, 1.0, 1.0, 1.0};
// 	GLfloat mbient[4] = {0.01, 0.01, 0.01, 1.0};
// 	GLfloat pecular[4] = {1.0, 1.0, 1.0, 1.0};
// 	glLightfv(GL_LIGHT1, GL_POSITION, ocation);
// 	glLightfv(GL_LIGHT1, GL_DIFFUSE, iffuse);
// 	glLightfv(GL_LIGHT1, GL_AMBIENT, mbient);
// 	glLightfv(GL_LIGHT1, GL_SPECULAR, pecular);
	GLfloat L_Location[4] = L_LOCATION;
	GLfloat L_Diffuse[4] = L_DIFFUSE;
	GLfloat L_Ambient[4] = L_AMBIENT;
	GLfloat L_Specular[4] = L_SPECULAR;
	GLfloat L_Direction[3] = L_DIRECTION;
	glMatrixMode(GL_PROJECTION);
	Spot Light0(GL_LIGHT0, L_Location,
		    L_Diffuse, L_Ambient, L_Specular,
		    L_Direction, L_EXPONENT, L_CUTOFF);
	Light0.init();

}

void Window::keyboard(unsigned char cara,int x, int y){

	switch((int) cara){
	case KEY_ESC:
		exit(EXIT_SUCCESS);
		break;
	case 'm' :
		m.activateCam();;
		break;
	default:
		std::cout << "cara: "<<(int)cara<<" x: "<<x<<" y: "<<y<<std::endl;
		break;
	}
}
