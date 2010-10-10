#ifndef _GAME_H
#define _GAME_H

#include <vector>

#include "Moto.h"
#include "Board.h"
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
        //Moto * tab_motos;
        std::vector<Moto::Moto> tab_motos;
        Board board;

        std::vector<Light *> lights;

        Camera_Ortho cam_ortho;
        Camera_Persp cam_persp;
        Camera * pt_cam_active;
        
        std::vector<Drawable::Drawable*> graph_elements;

        // Moto *** tab_game;

    public:
        Game(int _opponent_number, int _board_size_x, int _board_size_y, bool cam_ortho);
        ~Game();
        void draw();

};

#endif
