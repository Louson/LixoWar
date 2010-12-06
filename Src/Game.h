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
        GLfloat d_line_x, d_line_y;
        GLfloat dim_line_x, dim_line_y;

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

        void speedIncrement(MOTO_STRUCT *, const enum MOV);
        int action; 

	void randomStart(GLfloat *x, GLfloat *y, int *angle);

	int funcX(GLfloat x);
	int funcY(GLfloat y);
	GLfloat inverseX(int px);
	GLfloat inverseY(int py);
    
        Sound & sound;
    public:
        class ExceptionWrongBoardSize:public std::exception{};
        Game(int _opponent_number,
	     int _board_size_x, int _board_size_y,
	     GLfloat quality_x, GLfloat quality_y,
	     GLfloat _d_line_x, GLfloat _d_line_y,
	     GLfloat _dim_line_x, GLfloat _dim_line_y,
	     int _moto_size, Sound &) throw (ExceptionWrongBoardSize);
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
