#ifndef _GAME_H
#define _GAME_H

#include <vector>

#include "Moto.h"
#include "Board.h"
#include "Sky.h"
#include "Drawable.h"
#include "Camera.h"
#include "Camera_Ortho.h"
#include "Camera_Persp.h"
#include "Light.h"
#include "Wall.h"

#define L_LOCATION {5000.0, 5000.0, 5000.0}
#define L_DIRECTION {-2500.0, -2500.0, -5000.0}
#define L_EXPONENT 2
#define L_CUTOFF 70

class Game: public Drawable{

    private:
        /* game logistic */
        int opponentNumber;

        /* graphic components */
        Board board;
        Sky sky;
        Wall wall;
        //3	WallN wallN;
        /* 	WallW wallW; */
        /*  	WallS wallS; */
        /*  	WallE wallE; */

        std::vector<Light *> lights;

        Camera_Ortho * pt_cam_ortho;
        Camera_Persp * pt_cam_persp;
        Camera * pt_cam_active;

        std::vector<Moto*> tab_motos;
        Moto * pt_player;

        std::vector<Drawable*> graph_elements;

        void activeCam(void);

    public:
        Game(int _opponent_number,
                GLfloat _board_size_x,GLfloat _board_size_y,
                GLfloat quality_x, GLfloat quality_y,
                GLfloat d_line_x, GLfloat d_line_y, int _moto_size);
        ~Game();
        void draw();

        void setPerspCam(void);

        /* Ortho Camera */
        void setOrthoCam(void);
        void zoomOrthoCam(int);
};

#endif
