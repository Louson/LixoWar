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
#include "PtBeam.h"

/* lights */
#define L_LOCATION {5000.0, 5000.0, 5000.0}
#define L_DIRECTION {-2500.0, -2500.0, -5000.0}
#define L_EXPONENT 2
#define L_CUTOFF 70

#define MIN_SIZE_BOARD  1

#define SPEED_INCREMENT 1

#define ACTION_SLOWDOWN         100
#define ROTATION_INCREMENT      2
/* cameras settings */
#define VIEW_DIST               200000.0
#define FOVY                    100
#define PERSP_HEIGHT            3
#define MOTO_COEF               2
#define REF_HEIGHT              2 
#define PROJ_SIZE               50

enum MOV {UP, DOWN, LEFT, RIGHT};

enum ACTIONS {NOTHING=-1, TURN_RIGHT, TURN_LEFT};

typedef struct moto_struct {
        int x;
        int y;
        int angle;
        Moto * pt_moto;
} MOTO_STRUCT;

typedef struct light {
        GLfloat location[3]; 
        GLfloat diffuse[4];
        GLfloat ambient[4];
        GLfloat specular[4]; 
        GLfloat direction[3];
} LIGHT;

class Game: public Drawable{
    private:
        /* game logistic */
        int opponentNumber;

        /* graphic components */
        int board_size_x, board_size_y;
        Board board;
        Sky sky;
        Wall wall;

        std::vector<Light *> lights;

        Camera_Ortho cam_ortho;
        Camera_Persp cam_persp;
	
        std::vector<Moto*> tab_motos;
        int moto_size;

        MOTO_STRUCT player;

	std::vector<Beam *> beams;

        /* Board object presence matrix */
        bool ** presence_matrix;

        std::vector<Drawable*> graph_elements;

        void resetLight(void);
        void setOrthoCam(void);
        void setPerspCam(void);

        int action; 
        
    public:
        class ExceptionWrongBoardSize:public std::exception{};
        Game(int _opponent_number,
                int _board_size_x, int _board_size_y,
                GLfloat quality_x, GLfloat quality_y,
                GLfloat d_line_x, GLfloat d_line_y, int _moto_size) throw (ExceptionWrongBoardSize);
        ~Game();

        void draw();

        /* actions */
        void motoMov(enum MOV);
        void zoomOrthoCam(int);

        /* Cameras */
        void activatePerspCam(void);
        void activateOrthoCam(void);
};

#endif
