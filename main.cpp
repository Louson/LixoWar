#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Window.h"
#include "Config.h"
#include "File.h"
#include "main.h"
#include "Game.h"

using namespace std;

Game * pt_game = NULL;

int main(int argc, char ** argv){

    int side_x, side_y, quality_x, quality_y, d_line_x, d_line_y;
    int moto_size;
    int opponent_number;
    
    /* init random seed for moto construction */
    srand(time(0));

    /* recuperer valeurs fichiers */
    try{
        File config_file(PATH_CONFIG_FILE);
        side_x = Config::fetchParam("board_size_x",SIDE_X,config_file);
        side_y = Config::fetchParam("board_size_y",SIDE_Y,config_file);

        quality_x = Config::fetchParam("quality_x",QUALITY_X,config_file);
        quality_y = Config::fetchParam("quality_y",QUALITY_Y,config_file);

        d_line_x = Config::fetchParam("d_line_x",D_LINE_X,config_file);
        d_line_y = Config::fetchParam("d_line_y",D_LINE_Y,config_file);

        opponent_number = Config::fetchParam("enemy_number",OPPONENT_NUMBER,config_file);

        moto_size = Config::fetchParam("moto_size", MOTO_SIZE, config_file);

    }catch(const File::ExceptionBadPath &){
        cout << PATH_CONFIG_FILE << " is absent" << endl;
        return RETURN_BAD_PATH;
    }


    /* Set window */
    Window::create(WINDOW_NAME,&argc,argv);
    Window::init();

    pt_game = new Game(opponent_number,
		       side_x, side_y,
		       quality_x, quality_y,
		       d_line_x, d_line_y,
               moto_size);

    glutMainLoop();
    return EXIT_SUCCESS;
}
