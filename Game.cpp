#include <cmath>

#include "Game.h"
#include "Board.h"
#include "Drawable.h"
#include "Camera_Ortho.h"
#include "Camera_Persp.h"
#include "Camera.h"
#include "Light.h"
#include "Spot.h"

Game::Game(int _opponent_number, int _board_size_x, int _board_size_y, bool _cam_ortho):
    opponentNumber(_opponent_number),
    board(_board_size_x, _board_size_y)
{
    /* motos */

    GLfloat m_direction[2] ={-1, 0};
    tab_motos.push_back(Moto(0, 0, m_direction));

    for(std::vector<Moto::Moto>::const_iterator it = tab_motos.begin();it<tab_motos.end();it++)
        graph_elements.push_back((Drawable*) &(*it));


    /* light */
    GLfloat L_Location[4] = L_LOCATION;
    GLfloat L_Diffuse[4] = L_DIFFUSE;
    GLfloat L_Ambient[4] = L_AMBIENT;
    GLfloat L_Specular[4] = L_SPECULAR;
    GLfloat L_Direction[3] = L_DIRECTION;
    lights.push_back((Light *) new Spot(GL_LIGHT0, L_Location,
                L_Diffuse, L_Ambient, L_Specular,
                L_Direction, L_EXPONENT, L_CUTOFF));

    for(std::vector<Light*>::iterator it = lights.begin(); it < lights.end();it++)
        (*it) -> init();




    /* Camera ortho init */
    cam_ortho.set_position(3*_board_size_x, 2*_board_size_y, 3*_board_size_x, /*Cam position */
            0.0, 0.0, 0.0, /* center position */
            0,0,1);
    cam_ortho.set_view(/* X */ -0.7*_board_size_x, 0.7*_board_size_x,
            /* Y */ -0.45*_board_size_y, 0.45*_board_size_y,
            /* Z near */ 0.86*_board_size_x*sqrt(22.0),
            /* Z far  */ 1.12*_board_size_x*sqrt(22.0));

    graph_elements.push_back((Drawable*) &board);

    /* cam */
    pt_cam_active = (_cam_ortho) ? (Camera * ) &cam_ortho : (Camera *) &cam_persp;
    pt_cam_active -> activate();

}

void Game::draw(){
    for(std::vector<Drawable::Drawable *>::const_iterator it = graph_elements.begin(); it < graph_elements.end();it++)
        (*it) -> draw();
}

Game::~Game(){
    for(std::vector<Light*>::iterator it = lights.begin(); it < lights.end();it++)
        delete *it;
}
