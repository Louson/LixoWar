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
Sound * pt_sound = NULL;

int main(int argc, char *argv[])
{
        int side_x, side_y, quality_x, quality_y, d_line_x, d_line_y, dim_line_x, dim_line_y, num_lasers;
        int moto_size;
        int opponent_number;
        pt_sound = new Sound();
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

                dim_line_x = Config::fetchParam("dim_line_x",DIM_LINE_X,config_file);
                dim_line_y = Config::fetchParam("dim_line_y",DIM_LINE_Y,config_file);

                opponent_number = Config::fetchParam("enemy_number",OPPONENT_NUMBER,config_file);

                moto_size = Config::fetchParam("moto_size", MOTO_SIZE, config_file);
                num_lasers = Config::fetchParam("num_lasers", NUM_LASERS, config_file);

        }catch(const File::ExceptionBadPath &){
                cout << PATH_CONFIG_FILE << " is absent" << endl;
                return RETURN_BAD_PATH;
        }


        /* sound */
        try{
                pt_sound->init();
        }catch(File::ExceptionParamInexistent &){
                cout << "Error in sound configuration file" << endl;
                exit(EXIT_FAILURE);
        }catch(File::ExceptionBadPath &){
                cout << "Sound configuration file inexistent" << endl;
                exit(EXIT_FAILURE);
        }

        /* Set window */
        while(!Window::leaveGame()){
                Window::create(WINDOW_NAME,&argc,argv);
                Window::init();

                pt_game = new Game(opponent_number,
                                side_x, side_y,
                                quality_x, quality_y,
                                d_line_x, d_line_y,
                                dim_line_x, dim_line_y,
                                moto_size, pt_sound, num_lasers);

                glutMainLoop();
                delete pt_game;
        }
        delete pt_sound;

        return EXIT_SUCCESS;
}
