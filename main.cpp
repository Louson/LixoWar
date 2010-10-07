#include <string>


#include "Window.h"
#include "Config.h"
#include "Board.h"
#include "Camera_Ortho.h"
#include "File.h"
#include "main.h"

using namespace std;

Board * pt_board = new Board(SIDE_X,SIDE_Y);
Camera_Ortho Cam_A;

int main(int argc, char ** argv){

 
    /* recuperer valeurs fichiers */
    File config_file(PATH_CONFIG_FILE);

    /* lancer jeu */
    Window::create(WINDOW_NAME,&argc,argv);
    Window::init();


    glutKeyboardFunc(Window::keyboard);

    /* Camera activated */
    Cam_A.activer();
    glutMainLoop();
    return 0;
}
