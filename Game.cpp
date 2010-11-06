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

Game::Game(int _opponent_number,
        GLfloat _board_size_x,GLfloat _board_size_y,
        GLfloat _quality_x, GLfloat _quality_y,
        GLfloat _d_lines_x, GLfloat _d_lines_y, int _moto_size):
    opponentNumber(_opponent_number),

    board(_board_size_x, _board_size_y,
            _quality_x, _quality_y,
            _d_lines_x, _d_lines_y),
    sky(2*_board_size_x, 2*_board_size_y,
            string(SKY_PIC).c_str()),
    wall(2*_board_size_x, 2*_board_size_y)
{
    /* motos */
    GLfloat m_direction[2] ={0.0, 1.0};
    GLfloat x_init=0;
    GLfloat y_init=0;
    pt_player = new Moto(x_init, y_init, m_direction, (GLfloat) _moto_size);
    pt_cam_persp = pt_player->getPtCam();
    tab_motos.push_back(pt_player);

    for(std::vector<Moto*>::iterator it = tab_motos.begin();it<tab_motos.end();it++)
        graph_elements.push_back(*it);

    /* Camera otho init - Vue de haut */
    pt_cam_ortho = pt_player->getPtCam_ext();

    graph_elements.push_back(&board);
    graph_elements.push_back(&sky);
    graph_elements.push_back(&wall);

    /* cam */
    pt_cam_active = (pt_cam_ortho) ? (Camera * ) pt_cam_ortho : (Camera *) pt_cam_persp;
    pt_cam_active -> activate();

    /* light */
    GLfloat L_Location[3] = L_LOCATION;
    GLfloat L_Diffuse[4] = L_DIFFUSE;
    GLfloat L_Ambient[4] = L_AMBIENT;
    GLfloat L_Specular[4] = L_SPECULAR;
    GLfloat L_Direction[3] = L_DIRECTION;
    lights.push_back(new Spot(GL_LIGHT0, L_Location,
			      L_Diffuse, L_Ambient, L_Specular,
			      L_Direction, L_EXPONENT, L_CUTOFF));

    for(std::vector<Light*>::iterator it = lights.begin(); it < lights.end();it++)
        (*it) -> init();

}

void Game::draw(){
    for(std::vector<Drawable *>::iterator it = graph_elements.begin(); it < graph_elements.end();it++)
        (*it) -> draw();
}

Game::~Game(){
    for(std::vector<Light*>::iterator it = lights.begin(); it < lights.end();it++)
        delete *it;
}

void Game::setPerspCam(){
    pt_cam_active = pt_cam_persp;
    activeCam();
}

void Game::setOrthoCam(){
    pt_cam_active = pt_cam_ortho;
    activeCam();
}

void Game::activeCam(){
    pt_cam_active->activate();
    for(std::vector<Light*>::iterator it = lights.begin(); it < lights.end();it++)
        (*it) -> init();
}

void Game::zoomOrthoCam(int gradient){
    pt_cam_ortho -> zoom(gradient);
}
