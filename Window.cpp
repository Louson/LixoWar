#include <string>
#include <cassert>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#include "Window.h"
#include "Game.h"

extern Game * pt_game;

namespace Window {
    int window_width, window_height;
}

/**
 * Create the window
 */
void Window::create(const char * window_name, int * argc, char ** argv){
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST | GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);                         // Depth Buffer Setup
    glDepthFunc(GL_LEQUAL); 
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glutCreateWindow(window_name);
    glutFullScreen();
}

/**
 * Because of the limitations of GLUT C bindings,
 * this function needs to be static => it's impossible to 
 * use Functor with glut/freeglut
 */
void Window::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    /* drawing main function */
    assert(pt_game !=NULL);

    for(int i=0; i<VIEWPORT_NUMBER; i++){
        switch(i){
            case(NORMAL_VIEWPORT):
                glViewport(0, 0, window_width, window_height);
                pt_game->setPerspCam();
                break;
            case(MAP_VIEWPORT):
                pt_game->setOrthoCam();
                glViewport(window_width*MAP_VIEWPORT_POS_RATIO, 
                        window_height*MAP_VIEWPORT_POS_RATIO,
                        window_width*MAP_VIEWPORT_SIZE_RATIO-MAP_VIEWPORT_PIXEL_DEP,
                        window_height*MAP_VIEWPORT_SIZE_RATIO-MAP_VIEWPORT_PIXEL_DEP);
                break;
        }
        pt_game -> draw();
    }
    glFlush();
    glutSwapBuffers();
}

void Window::windowReshape(int x, int y){
    Window::window_width = x;
    Window::window_height = y;
}

/**
 * Init the windows
 */
void Window::init(){

    glutDisplayFunc(&Window::display);
    glutKeyboardFunc(&Window::keyboard);
    glutReshapeFunc(&Window::windowReshape);
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
        case KEY_PLUS:
            pt_game->zoomOrthoCam(1);
            glutPostRedisplay();
            break;
        case KEY_MINUS:
            pt_game->zoomOrthoCam(-1);
            glutPostRedisplay();
            break;
        default:
            std::cout << "cara: "<<(int)cara<<" x: "<<x<<" y: "<<y<<std::endl;
            break;
    }
}
