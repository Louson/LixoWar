#ifndef _GAME_H
#define _GAME_H

#include <vector>

#include "Moto.h"
#include "Board.h"
#include "Sky.h"
#include "WallN.h"
#include "Drawable.h"
#include "Camera.h"
#include "Camera_Ortho.h"
#include "Camera_Persp.h"
#include "Light.h"

class Game: public Drawable{

private:
        /* game logistic */
        int opponentNumber;
  
        /* graphic components */
        Board board;
	Sky sky;
	WallN wallN;

        std::vector<Light *> lights;

        Camera_Ortho * pt_cam_ortho;
        Camera_Persp * pt_cam_persp;
        Camera * pt_cam_active;

        std::vector<Moto*> tab_motos;
        Moto * pt_player;

        std::vector<Drawable*> graph_elements;

    public:
        Game(int _opponent_number,
	     GLfloat _board_size_x,GLfloat _board_size_y,
	     GLfloat quality_x, GLfloat quality_y,
	     GLfloat d_line_x, GLfloat d_line_y, int _moto_size);
        ~Game();
        void draw();
        void exchangeCam();

};

#endif
