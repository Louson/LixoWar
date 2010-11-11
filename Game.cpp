#include <iostream>
#include <cmath>

#include "Game.h"
#include "Drawable.h"
#include "Camera_Ortho.h"
#include "Camera_Persp.h"
#include "Camera.h"
#include "Light.h"
#include "Spot.h"

const char * SKY_PIC = "Images/ciel.ppm";

Game::Game(
                int _opponent_number,
                int _board_size_x, 
                int _board_size_y,
                GLfloat _quality_x, 
                GLfloat _quality_y,
                GLfloat _d_lines_x, 
                GLfloat _d_lines_y, 
                int _moto_size
          ) throw (ExceptionWrongBoardSize) :
        opponentNumber(_opponent_number),

        board_size_x(_board_size_x),
        board_size_y(_board_size_y),

        board(_board_size_x, _board_size_y,
                        _quality_x, _quality_y,
                        _d_lines_x, _d_lines_y),
        sky(2*_board_size_x, 2*_board_size_y,
                        SKY_PIC),
        wall(2*_board_size_x, 2*_board_size_y),
        moto_size(_moto_size)
{
        if(board_size_x < MIN_SIZE_BOARD || board_size_y < MIN_SIZE_BOARD)
                throw ExceptionWrongBoardSize(); 

        action = -1;

        /* motos */
        player.x = player.y = 0;
        player.angle = 0;
        player.pt_moto = new Moto(_moto_size);

        /* drawing elements */
        for(std::vector<Moto*>::iterator it = tab_motos.begin();it<tab_motos.end();it++)
                graph_elements.push_back(*it);
        graph_elements.push_back(player.pt_moto);
        graph_elements.push_back(&board);
        graph_elements.push_back(&sky);
        graph_elements.push_back(&wall);

        /* presence matrix */
        presence_matrix = new bool * [board_size_x];
        for(int i=0; i<board_size_x; i++)
                presence_matrix[i] = NULL;
        for(int i=0; i<board_size_x; i++)
                presence_matrix[i] = new bool[board_size_y];
        for(int i=0; i<board_size_x; i++)
                for(int j=0; j<board_size_y; j++)
                        presence_matrix[i][j] = false;

        /* light */
        GLfloat L_Location[3] = {_board_size_x/2.0, _board_size_y/2.0, (_board_size_x+_board_size_y)/4.0};
        GLfloat L_Diffuse[4] = L_DIFFUSE;
        GLfloat L_Ambient[4] = L_AMBIENT;
        GLfloat L_Specular[4] = L_SPECULAR;
        GLfloat L_Direction[3] = {-_board_size_x/2.0, -_board_size_y/2.0, -(_board_size_x+_board_size_y)/4.0};;
        lights.push_back(new Spot(GL_LIGHT0, L_Location,
                                L_Diffuse, L_Ambient, L_Specular,
                                L_Direction, L_EXPONENT, L_CUTOFF));

        resetLight();
}

void Game::draw(){

        player.pt_moto->setPos(player.x, player.y, player.angle);

        for(std::vector<Drawable *>::iterator it = graph_elements.begin(); it < graph_elements.end();it++)
                if(*it) (*it) -> draw();

        switch(action){
                case -1:
                        /* no action to do */
                        break;
                case 0:
                        if(player.angle % 90 != 0){
                                player.angle = (player.angle + 10) % 360;
                                usleep(ACTION_SLOWDOWN);
                                glutPostRedisplay();
                        }else
                                action = -1;
                        break;
                case 1:
                        if(player.angle % 90 != 0){
                                player.angle = (player.angle + 350) % 360;
                                usleep(ACTION_SLOWDOWN);
                                glutPostRedisplay();
                        }else
                                action = -1;
                        break;
                default:
                        break;
        }
}

Game::~Game(){
        for(std::vector<Light*>::iterator it = lights.begin(); it < lights.end();it++)
                delete *it;

        for(std::vector<Moto*>::iterator it = tab_motos.begin();it<tab_motos.end();it++)
                delete *it;

        delete player.pt_moto;

        for(int i=0; i<board_size_x; i++)
                delete [] presence_matrix[i];
        delete [] presence_matrix;
}

void Game::activatePerspCam(){
        setPerspCam();
        cam_persp.activate();
        resetLight();
}

void Game::activateOrthoCam(){
        setOrthoCam();
        cam_ortho.activate();
        resetLight();
}

void Game::resetLight(){
        for(std::vector<Light*>::iterator it = lights.begin(); it < lights.end();it++)
                (*it) -> init();
}

void Game::zoomOrthoCam(int gradient){
        cam_ortho.zoom(gradient);
}

void Game::motoMov(enum MOV mov){
        /* the comportement of negative modulo is undefined !!! */
        /* the cast is here to prevent overflow */
        switch(mov){
                case UP:
                        player.x += SPEED_INCREMENT*((int) cos(((float)player.angle)*M_PI/180.0));
                        player.y += SPEED_INCREMENT*((int) sin(((float)player.angle)*M_PI/180.0));
                        break;
                case DOWN:
                        player.x -= SPEED_INCREMENT*((int) cos(player.angle*M_PI/180));
                        player.y -= SPEED_INCREMENT*((int) sin(player.angle*M_PI/180));
                        break;
                case LEFT:
                        player.angle = (player.angle + 10) % 360;
                        action = 0;
                        break;
                case RIGHT:
                        player.angle = (player.angle + 350) % 360;
                        action = 1;
                        break;
        }
}

void Game::setPerspCam() {
        cam_persp.set_position(
                        /* cam pos */
                        player.x-MOTO_COEF*moto_size*cos(player.angle*M_PI/180), 
                        player.y-MOTO_COEF*moto_size*sin(player.angle*M_PI/180), 
                        PERSP_HEIGHT*moto_size,
                        /* ref point */
                        player.x,//+4*MOTO_COEF*moto_size*cos(player.angle*M_PI/180), 
                        player.y,//+4*MOTO_COEF*moto_size*sin(player.angle*M_PI/180), 
                        REF_HEIGHT*moto_size,
                        /* up vector */
                        0, 0, 1);
        cam_persp.set_view(FOVY, SCREEN_RATIO, 0.05, VIEW_DIST);
}

void Game::setOrthoCam() {
        cam_ortho.set_position(player.x, player.y, H_CAM, /*Cam position */
                        player.x, player.y, 0, /* ref point position */
                        1, 0, 0); /* up vector */
        cam_ortho.set_view(-SCREEN_RATIO*PROJ_SIZE, /* left */
                        SCREEN_RATIO*PROJ_SIZE, /* right */
                        /* Y */ -PROJ_SIZE, /* Down */
                        PROJ_SIZE, /* up */
                        0.5*H_CAM, /* Z near */
                        1.5*H_CAM); /*Z far */
}
