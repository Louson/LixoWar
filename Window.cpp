#include <string>
#include <cassert>
#include <GL/glut.h>
#include <cmath>

#include "Window.h"
#include "Camera_Ortho.h"
#include "Config.h"

extern Board * pt_board;
extern Camera_Ortho Cam_A;

/**
 * Create the window
 */
void Window::create(const char * window_name, int * argc, char ** argv){
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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

    /* Enable object emission light */
    glColorMaterial(GL_FRONT_AND_BACK, GL_SHININESS);
    glEnable(GL_COLOR_MATERIAL);

    /* Use Depth Buffering */
    glEnable(GL_DEPTH_TEST);

    /* Setup the view of the cube */
    Cam_A.set_position(3*SIDE_X, 2*SIDE_Y, 3*SIDE_X, /*Cam position */
            0.0, 0.0, 0.0, /* center position */
            -9.0/11.0, -6.0/11.0, 13.0/11.0); /* up in positive z direction */
    Cam_A.set_view(/* X */ -0.75*SIDE_X, 0.75*SIDE_X,
            /* Y */ -0.75*SIDE_Y, 0.75*SIDE_Y,
            /* Z near */ 0.5*SIDE_X*sqrt(22.0),
            /* Z far */ 1.5*SIDE_X*sqrt(22.0));
}
