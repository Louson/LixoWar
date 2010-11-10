#include <iostream>
#include <cmath>

#include "Game.h"
#include "Drawable.h"
#include "Camera_Ortho.h"
#include "Camera_Persp.h"
#include "Camera.h"
#include "Light.h"
#include "Spot.h"

#define SKY_PIC "Images/ciel.ppm"

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
                        string(SKY_PIC).c_str()),
        wall(2*_board_size_x, 2*_board_size_y)
{
        if(board_size_x < MIN_SIZE_BOARD || board_size_y < MIN_SIZE_BOARD)
                throw ExceptionWrongBoardSize(); 

        /* motos */
        player.x = player.y = 0;
        player.direction[0] = 1.0;
        player.direction[1] = 0;
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

        player.pt_moto->setPos(player.x, player.y, player.direction);

        for(std::vector<Drawable *>::iterator it = graph_elements.begin(); it < graph_elements.end();it++)
                if(*it) (*it) -> draw();
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
        int temp;
        switch(mov){
                case UP:
                        player.x += SPEED_INCREMENT*player.direction[0];
                        player.y += SPEED_INCREMENT*player.direction[1];
                        break;
                case DOWN:
                        player.x -= SPEED_INCREMENT*player.direction[0];
                        player.y -= SPEED_INCREMENT*player.direction[1];
                        break;
                case LEFT:
                        temp = -player.direction[1];
                        player.direction[1] = player.direction[0];
                        player.direction[0] = temp;
                        break;
                case RIGHT:
                        temp = player.direction[1];
                        player.direction[1] = -player.direction[0];
                        player.direction[0] = temp;
                        break;
        }
}

void Game::setPerspCam() {
        cam_persp.set_position(player.x-1*MOTO_SIZE*player.direction[0], player.y-1*MOTO_SIZE*player.direction[1], PERSP_HEIGHT*MOTO_SIZE,
                        player.x+1.5*MOTO_SIZE*player.direction[0], player.y+1.5*MOTO_SIZE*player.direction[1], MOTO_SIZE,
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
