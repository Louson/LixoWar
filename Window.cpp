#include <string>
#include <cassert>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

#include "Window.h"
#include "Camera_Ortho.h"
#include "Config.h"
#include "Located_Light.h"

extern Board * pt_board;
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
    glutSwapBuffers();
}

/**
 * Init the windows
 */
void Window::init(){

    glutDisplayFunc(&Window::display);
    glutKeyboardFunc(&Window::keyboard);

    /* Enable object emission light */
    //  glColorMaterial(GL_FRONT_AND_BACK, GL_SHININESS);
    // 	glEnable(GL_COLOR_MATERIAL);

   /* Lights settings */

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    //   	glEnable(GL_LIGHT1);
    //  	GLfloat ocation[4] = {10000.0, 0.0, 10000.0, 1.0};
    // 	GLfloat iffuse[4] = {1.0, 1.0, 1.0, 1.0};
    // 	GLfloat mbient[4] = {0.01, 0.01, 0.01, 1.0};
    // 	GLfloat pecular[4] = {1.0, 1.0, 1.0, 1.0};
    //  	glLightfv(GL_LIGHT1, GL_POSITION, ocation);
    // 	glLightfv(GL_LIGHT1, GL_DIFFUSE, iffuse);
    // 	glLightfv(GL_LIGHT1, GL_AMBIENT, mbient);
    // 	glLightfv(GL_LIGHT1, GL_SPECULAR, pecular);

    GLfloat L_Location[4] = L_LOCATION;
    GLfloat L_Diffuse[4] = L_DIFFUSE;
    GLfloat L_Ambient[4] = L_AMBIENT;
    GLfloat L_Specular[4] = L_SPECULAR;
    glMatrixMode(GL_PROJECTION);
    Located_Light Light0(GL_LIGHT0, L_Location, L_Diffuse, L_Ambient, L_Specular);
    Light0.init();

    /* Use Depth Buffering */
    glEnable(GL_DEPTH_TEST);

    /* Setup the view of the cube */
    Cam_A.set_position(3*SIDE_X, 2*SIDE_Y, 3*SIDE_X, /*Cam position */
		       0.0, 0.0, 0.0, /* center position */
		       0,0,1);
//            -9.0/11.0, -6.0/11.0, 13.0/11.0); /* up direction */
    Cam_A.set_view(/* X */ -0.75*SIDE_X, 0.75*SIDE_X,
            /* Y */ -0.75*SIDE_Y, 0.75*SIDE_Y,
            /* Z near */ 0.5*SIDE_X*sqrt(22.0),
            /* Z far */ 1.5*SIDE_X*sqrt(22.0));
}

void Window::keyboard(unsigned char cara,int x, int y){

    switch((int) cara){
        case KEY_ESC:
            exit(EXIT_SUCCESS);
            break;
        default:
            std::cout << "cara: "<<(int)cara<<" x: "<<x<<" y: "<<y<<std::endl;
            break;
    }
}
