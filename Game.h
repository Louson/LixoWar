#ifndef _GAME_H
#define _GAME_H
#include "Sound.h"

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

#define WALL_SIZE       10000

/* lights */
#define L_EXPONENT      2.0
#define L_CUTOFF        180
#define H_SPOT          5

#define MIN_SIZE_BOARD  10
#define SIZE_CASE_X 4
#define SIZE_CASE_Y 4
#define NB_CASE_HALF_LINE_X 1
#define NB_CASE_HALF_LINE_Y 1
#define HALF_LINE_SIZE_X NB_CASE_HALF_LINE_X*SIZE_CASE_X
#define HALF_LINE_SIZE_Y NB_CASE_HALF_LINE_Y*SIZE_CASE_Y

#define SPEED_INCREMENT 0.01

#define ACTION_SLOWDOWN         0
#define ROTATION_INCREMENT      2
/* cameras settings */
#define VIEW_DIST               200000.0
#define FOVY                    90
#define PERSP_HEIGHT            3
#define MOTO_COEF               2
#define REF_HEIGHT              2 
#define PROJ_SIZE               50

#define SUB_STEP    100
#define X_START    -100
#define TAN_FINISH  100

enum MOV {UP, DOWN, LEFT, RIGHT};

enum ACTIONS {NOTHING=-1, TURN_RIGHT, TURN_LEFT};

class Game: public Drawable{
    private:
	bool win;
	bool lose;

        /* game logistic */
        int opponentNumber;

        /* graphic components */
        int board_size_x, board_size_y;
        int d_line_x, d_line_y;

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
	int presence_x, presence_y;


        std::vector<Drawable*> graph_elements;

        void resetLight(void);
        void setOrthoCam(void);
        void setPerspCam(void);

        int action; 

	Sound sound;
        
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
	void cameraStart();

	bool testPresence();
	bool has_won();
	bool has_lost();
};

#endif
