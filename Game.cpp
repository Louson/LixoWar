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
#define WALLN_PIC "Images/neutron.ppm"
#define WALLW_PIC "Images/neutron.ppm"
#define WALLS_PIC "Images/neutron.ppm"
#define WALLE_PIC "Images/neutron.ppm"

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
    wallN(2*_board_size_x, 2*_board_size_y,
            string(WALLN_PIC).c_str())//,
    // 	wallW(2*_board_size_x, 2*_board_size_y,
    // 	      string(WALLW_PIC).c_str()),
    //   	wallS(2*_board_size_x, 2*_board_size_y,
    //   	      string(WALLS_PIC).c_str()),
    //     	wallE(2*_board_size_x, 2*_board_size_y,
    //     	      string(WALLE_PIC).c_str())
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


    /* Camera ortho init - Vue globale */
    //     cam_ortho.set_position(3*_board_size_x, 2*_board_size_y, 3*_board_size_x, /*Cam position */
    //             0.0, 0.0, 0.0, /* center position */
    //             0,0,1);
    //     cam_ortho.set_view(/* X */ -0.7*_board_size_x, 0.7*_board_size_x,
    //             /* Y */ -0.45*_board_size_y, 0.45*_board_size_y,
    //             /* Z near */ 0.86*_board_size_x*sqrt(22.0),
    //             /* Z far  */ 1.12*_board_size_x*sqrt(22.0));

    graph_elements.push_back(&board);
    graph_elements.push_back(&sky);
    graph_elements.push_back(&wallN);
    // 	graph_elements.push_back(&wallW);
    // 	graph_elements.push_back(&wallS);
    // 	graph_elements.push_back(&wallE);

    /* cam */
    pt_cam_active = (pt_cam_ortho) ? (Camera * ) pt_cam_ortho : (Camera *) pt_cam_persp;
    pt_cam_active -> activate();

    /* light */
    GLfloat L_Location[4] = {_board_size_x, _board_size_y, _board_size_x};
    GLfloat L_Diffuse[4] = L_DIFFUSE;
    GLfloat L_Ambient[4] = L_AMBIENT;
    GLfloat L_Specular[4] = L_SPECULAR;
    GLfloat L_Direction[3] = {-_board_size_x, -_board_size_y, -_board_size_x};
    lights.push_back(new Spot(GL_LIGHT0, L_Location,
                L_Diffuse, L_Ambient, L_Specular,
                L_Direction, L_EXPONENT, L_CUTOFF));

    for(std::vector<Light*>::iterator it = lights.begin(); it < lights.end();it++)
        (*it) -> init();

}

void Game::draw(){
    glMatrixMode(GL_MODELVIEW);

    //Set The Viewport To The Top Left.  It Will Take Up Half The Screen Width And Height
    int window_height = 100;
    int window_width = 200;
    glViewport (0, 0, 1440, 900);
    //glViewport (0, window_height/2, window_width/2, window_height/2);
/*    glMatrixMode (GL_PROJECTION);                       // Select The Projection Matrix
    glLoadIdentity ();                          // Reset The Projection Matrix
    // Set Up Ortho Mode To Fit 1/4 The Screen (Size Of A Viewport)
    gluOrtho2D(0, window_width/2, window_height/2, 0);
    glBegin(GL_QUADS);                          // Begin Drawing A Single Quad
    // We Fill The Entire 1/4 Section With A Single Textured Quad.
    glTexCoord2f(1.0f, 0.0f); glVertex2i(window_width/2, 0              );
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0,              0              );
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0,              window_height/2);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(window_width/2, window_height/2);
    glEnd();                                
*/
   
    for(std::vector<Drawable *>::iterator it = graph_elements.begin(); it < graph_elements.end();it++)
        (*it) -> draw();

 glViewport(1000,800, 1440, 900);
    for(std::vector<Drawable *>::iterator it = graph_elements.begin(); it < graph_elements.end();it++)
        (*it) -> draw();

    glFlush();
}

Game::~Game(){
    for(std::vector<Light*>::iterator it = lights.begin(); it < lights.end();it++)
        delete *it;
}

void Game::exchangeCam(){
    pt_cam_active = (pt_cam_active == pt_cam_ortho) ? (Camera *) pt_cam_persp : (Camera*) pt_cam_ortho;
    pt_cam_active->activate();
    for(std::vector<Light*>::iterator it = lights.begin(); it < lights.end();it++)
        (*it) -> init();
}
