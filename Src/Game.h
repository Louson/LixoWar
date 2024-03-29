#ifndef _GAME_H
#define _GAME_H

#include <vector>

#include "Board.h"
#include "Camera.h"
#include "Camera_Ortho.h"
#include "Camera_Persp.h"
#include "Drawable.h"
#include "Explosion.h"
#include "Laser.h"
#include "Light.h"
#include "Moto.h"
#include "PtBeam.h"
#include "Sound.h"
#include "Wall.h"

enum MOV {UP, DOWN, LEFT, RIGHT};

enum ACTIONS {NOTHING=-1, TURN_RIGHT, TURN_LEFT};

enum CARD {NORTH, EAST, SOUTH, WEST};

typedef struct str_laser {
        Laser **tab;
        int init_num;
        int cur_num;
} STR_LASER;

class Game: public Drawable{
    private:
	bool win;
	bool lose;
	bool iCanStart;

        /* game logistic */
        int opponentNumber;

        /* graphic components */
        int board_size_x, board_size_y;
        GLfloat d_line_x, d_line_y;
        GLfloat dim_line_x, dim_line_y;

        Board board;
        Wall wall;

        std::vector<Light *> lights;

        Camera_Ortho cam_ortho;
        Camera_Persp cam_persp;

        int moto_size;

        MOTO_STRUCT player;
	MOTO_STRUCT *tab_opp;

	std::vector<Beam *> beams;

        /* Board object presence matrix */
        bool ** presence_matrix;
	int presence_x, presence_y;

        std::vector<Drawable*> graph_elements;

        void resetLight(void);
        void setOrthoCam(void);
        void setPerspCam(void);

        void speedIncrement(MOTO_STRUCT *, const enum MOV);
        int action; 

	void randomStart(GLfloat *x, GLfloat *y, int *angle);

	int funcX(GLfloat x);
	int funcY(GLfloat y);
	GLfloat inverseX(int px);
	GLfloat inverseY(int py);
        
        Sound *pt_sound;
        
        STR_LASER str_laser;

        bool begin_explosion;
        bool end_game;

    public:
        class ExceptionWrongBoardSize:public std::exception{};
        Game(int _opponent_number,
	     int _board_size_x, int _board_size_y,
	     GLfloat quality_x, GLfloat quality_y,
	     GLfloat _d_line_x, GLfloat _d_line_y,
	     GLfloat _dim_line_x, GLfloat _dim_line_y,
	     int _moto_size, Sound *, int) throw (ExceptionWrongBoardSize);
        ~Game();

        void draw();
	void testNewCase(MOTO_STRUCT *motoTest);

        /* actions */
        void motoMov(enum MOV);
	void enemyMov(MOTO_STRUCT *enemy);
	enum MOV choseDirection(GLfloat x, GLfloat y, int angle);
	enum MOV directionChose(int epx, int epy, int angle);
	int look(int px, int py, int kx, int ky);
        void zoomOrthoCam(int);

        /* Cameras */
        void activatePerspCam(void);
        void activateOrthoCam(void);
	void cameraStart();

	bool testPresence(MOTO_STRUCT *motoTest);
	bool has_won();
	bool has_lost();

	void youCanStart();
};

#endif
