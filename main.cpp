#include <string>
#include <iostream>

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
    try{
        File config_file(PATH_CONFIG_FILE);
        int side_x = Config::fetchParam("board_size_x",SIDE_X,config_file);
        int side_y = Config::fetchParam("board_size_y",SIDE_Y,config_file);
        cout << side_x << " " << side_y << endl;
    }catch(const File::ExceptionBadPath &){
        cout << PATH_CONFIG_FILE << " is absent" << endl;
        return RETURN_BAD_PATH;
    }

    /* lancer jeu */
    Window::create(WINDOW_NAME,&argc,argv);
    Window::init();

    /* Camera activated */
    Cam_A.activate();
    glutMainLoop();
    return EXIT_SUCCESS;
}
