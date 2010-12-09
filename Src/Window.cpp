#include <cassert>
#include <cmath>
#include <ctime>
#include <GL/freeglut.h>
#include <iostream>
#include <string>

#include "Color.h"
#include "Game.h"
#include "Window.h"

#define WAITING_TIME 5*CLOCKS_PER_SEC
#define GLUT_KEY_ENTER 13

static const unsigned char * END_TEXT = (unsigned char *) 
        "Type ENTER to continue or ESC to quit.";
static const unsigned char * WIN_TEXT = (unsigned char *) 
        "You win !\n\n";
static const unsigned char * LOST_TEXT = (unsigned char *) 
        "GAME OVER !\n\nYou lost ...";

extern Game * pt_game;

namespace Window {
        static int window_width, window_height;
        static bool _leaveGame = false;
}

/**
 * Create the window
 */
void Window::create(const char * window_name, int * argc, char ** argv){
        glutInit(argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutCreateWindow(window_name);
        glutFullScreen();
}

bool Window::leaveGame(void)
{
        return Window::_leaveGame;
}

/**
 * Because of the limitations of GLUT C bindings,
 * this function needs to be static => it's impossible to 
 * use Functor with glut/freeglut
 */
void Window::display(void) 
{
        assert(pt_game!=NULL);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0,0,0,0);

        if(pt_game->has_lost() || pt_game->has_won()){

                glDisable(GL_LIGHTING);
                glDisable(GL_DEPTH_TEST);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();

                glViewport(0, 0, window_width, window_height);
                glRasterPos3f(-0.5, 0,0);

                if(pt_game->has_lost())
                        glutBitmapString(GLUT_BITMAP_HELVETICA_18, LOST_TEXT);
                else
                        glutBitmapString(GLUT_BITMAP_HELVETICA_18, WIN_TEXT);

                glutBitmapString(GLUT_BITMAP_HELVETICA_18, END_TEXT);
        }else{
                for(int i=0; i<VIEWPORT_NUMBER; i++){
                        glMatrixMode(GL_MODELVIEW);
                        glLoadIdentity();
                        glMatrixMode(GL_PROJECTION);
                        glLoadIdentity();

                        switch(i){
                                case(NORMAL_VIEWPORT):
                                        glViewport(0, 0, window_width, window_height);
                                        pt_game->activatePerspCam();
                                        break;
                                case(MAP_VIEWPORT):
                                        glViewport(window_width*MAP_VIEWPORT_POS_RATIO, 
                                                        window_height*MAP_VIEWPORT_POS_RATIO,
                                                        window_width*MAP_VIEWPORT_SIZE_RATIO-MAP_VIEWPORT_PIXEL_DEP,
                                                        window_height*MAP_VIEWPORT_SIZE_RATIO-MAP_VIEWPORT_PIXEL_DEP);
                                        pt_game->activateOrthoCam();
                                        break;
                        }

                        pt_game -> draw();
                }
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
        glutSpecialFunc(&Window::specialKeyboard);
	glutTimerFunc(1000, &Window::timer, 0);
	glutTimerFunc(2000, &Window::timer, 0);
	glutTimerFunc(3000, &Window::timer, 0);
	glutTimerFunc(3000, &Window::timer, 1);

        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

        /* Use Depth Buffering */
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_NORMALIZE);
        glShadeModel(GL_SMOOTH);
        glClearDepth(1.0f);                         // Depth Buffer Setup
        glDepthFunc(GL_LEQUAL); 
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

        /* Textures */

        /* Lights settings
         *
         *if the light is set before the cam, the location depends of the
         * cam settings
         */
        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING);

        GLfloat ambientLight[4] = {0.5, 0.5, 0.5, 1.0}; 
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

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
        switch(cara){
                case GLUT_KEY_ENTER:
                        /* if the game is finished, we wait for an action then
                         * we restart the game
                         */
                        if(pt_game->has_lost() || pt_game->has_won())
                                glutLeaveMainLoop();
                        break;
                case KEY_ESC:
                        Window::_leaveGame = true;
                        glutLeaveMainLoop();
                        break;
                case KEY_PLUS:
                        pt_game->zoomOrthoCam(2);
                        glutPostRedisplay();
                        break;
                case KEY_MINUS:
                        pt_game->zoomOrthoCam(-2);
                        glutPostRedisplay();
                        break;
                default:
                        std::cout << "cara: "<<(int)cara<<" x: "<<x<<" y: "<<y<<std::endl;
                        break;
        }
}

void Window::specialKeyboard(int key, int x, int y){
        switch(key){
                case GLUT_KEY_UP:
                        pt_game->motoMov(UP);
                        break;
                case GLUT_KEY_RIGHT:
                        pt_game->motoMov(RIGHT);
                        break;
                case GLUT_KEY_DOWN:
                        pt_game->motoMov(DOWN);
                        break;
                case GLUT_KEY_LEFT:
                        pt_game->motoMov(LEFT);
                        break;
                default:
                        cout << "Special: "<<key<<endl;
                        return;
        }
        glutPostRedisplay();
}

void Window::timer(int value) {
	if (!value)
		cout << "BIP"<< endl;
	else
		/* We can start */
		pt_game->youCanStart();
}
