#include <string>

#include "Window.h"
#include "Config.h"
#include "Board.h"
#include "Camera_Ortho.h"

using namespace std;

Board * pt_board = new Board(SIDE_X,SIDE_Y);
Camera_Ortho Cam_A;

int main(int argc, char ** argv){

	const char * window_name = "Lixo War 3000";
 
    /* recuperer valeurs fichiers */

    /* lancer jeu */
    Window::create(window_name,&argc,argv);
    Window::init();


    //	glutKeyboardFunc(clavier);

    /* Camera activated */
    Cam_A.activer();
    glutMainLoop();
    return 0;
}
