#include <iostream>
#include <cmath>
#include <assert.h>
#include <cstdlib>
#include <ctime>

#include "Game.h"
#include "Drawable.h"
#include "Camera_Ortho.h"
#include "Camera_Persp.h"
#include "Camera.h"
#include "Light.h"
#include "Spot.h"

const char * SKY_PIC = "Images/ciel.ppm";

Game::Game(
	int _opponent_number,
	int _board_size_x, 
	int _board_size_y,
	GLfloat _quality_x, 
	GLfloat _quality_y,
	GLfloat _d_lines_x, 
	GLfloat _d_lines_y, 
	GLfloat _dim_lines_x, 
	GLfloat _dim_lines_y, 
	int _moto_size
	) throw (ExceptionWrongBoardSize) :
	
	win(false), lose(false),

	opponentNumber(_opponent_number),
	
        board_size_x(_board_size_x),
        board_size_y(_board_size_y),
        d_line_x(_d_lines_x),
        d_line_y(_d_lines_y),
        dim_line_x(_dim_lines_x),
        dim_line_y(_dim_lines_y),

        board(_board_size_x, _board_size_y,
	      _quality_x, _quality_y,
	      _d_lines_x, _d_lines_y,
	      _dim_lines_x, _dim_lines_y),
        sky(2*_board_size_x, 2*_board_size_y,
	    SKY_PIC),
        wall(2*WALL_SIZE, 2*WALL_SIZE),
        moto_size(_moto_size)

{
	sound.playMainMusic();
        if(board_size_x < MIN_SIZE_BOARD || board_size_y < MIN_SIZE_BOARD)
                throw ExceptionWrongBoardSize(); 

        action = -1;

        /* presence matrix */
	cout<<dim_line_x<<endl;
	cout<<SIZE_CASE_X<<"lkjlkj"<<endl;
	int x_dim = 2+board_size_x/(float)SIZE_CASE_X;
	int y_dim = 2+board_size_y/(float)SIZE_CASE_Y;
        presence_matrix = new bool * [x_dim];

        for(int i=0; i<x_dim; i++)
                presence_matrix[i] = NULL;
        for(int i=0; i<x_dim; i++)
                presence_matrix[i] = new bool[y_dim];
        for(int i=0; i<x_dim; i++) {
                for(int j=0; j<y_dim; j++) {
			if(i*(x_dim-1-i)*j*(y_dim-1-j)) {
				presence_matrix[i][j] = false;
				if ( ((int)((i-1)/dim_line_x)*dim_line_x+NB_CASE_HALF_LINE_X<=i-1
				      && i-1<(int)((i-1)/dim_line_x+1)*dim_line_x-NB_CASE_HALF_LINE_X)
				     && ((int)((j-1)/dim_line_y)*dim_line_y+NB_CASE_HALF_LINE_Y<=j-1
					 && j-1<(int)((j-1)/dim_line_y+1)*dim_line_y-NB_CASE_HALF_LINE_Y) )
					presence_matrix[i][j] = true;
			}
			else presence_matrix[i][j] = true;
			//cout << presence_matrix[i][j];
		}
		//cout << endl;
	}

        /* motos */
	randomStart(&player.x, &player.y, &player.angle);
        player.speed = 0;
        player.pt_moto = new Moto(_moto_size);

        /* drawing elements */
        for(std::vector<Moto*>::iterator it = tab_motos.begin();it<tab_motos.end();it++)
                graph_elements.push_back(*it);
        graph_elements.push_back(player.pt_moto);
        graph_elements.push_back(&wall);
        graph_elements.push_back(&board);
        //graph_elements.push_back(&sky);


	/* light */
        LIGHT spot_sky;

        spot_sky.diffuse[0] = 1;
        spot_sky.diffuse[1] = 1;
        spot_sky.diffuse[2] = 1;

        spot_sky.ambient[0] = 0;
        spot_sky.ambient[1] = 0;
        spot_sky.ambient[2] = 0;

        spot_sky.specular[0] = 1;
        spot_sky.specular[1] = 1;
        spot_sky.specular[2] = 1;

        spot_sky.location[0] = 0;
        spot_sky.location[1] = 0;
        spot_sky.location[2] = H_SPOT;

        spot_sky.direction[0] = 0;
        spot_sky.direction[1] = 0;
        spot_sky.direction[2] = -1;

        spot_sky.diffuse[3] = spot_sky.ambient[3] = spot_sky.specular[3] = 1.0;

        spot_sky.constant_attenuation = 0.0005;
        spot_sky.linear_attenuation = 0;
        spot_sky.quadratic_attenuation = 0.001;

        int x_delta = board_size_x/d_line_x/4.0;
        int y_delta = board_size_y/d_line_y/4.0;

        lights.push_back(new Spot(&spot_sky, L_EXPONENT, L_CUTOFF));
        spot_sky.location[0] = x_delta*d_line_x;
        spot_sky.location[1] = y_delta*d_line_y;
        lights.push_back(new Spot(&spot_sky, L_EXPONENT, L_CUTOFF));
        spot_sky.location[0] = -x_delta*d_line_x;
        spot_sky.location[1] = y_delta*d_line_y;
        lights.push_back(new Spot(&spot_sky, L_EXPONENT, L_CUTOFF));
        spot_sky.location[0] = -x_delta*d_line_x;
        spot_sky.location[1] = -y_delta*d_line_y;
        lights.push_back(new Spot(&spot_sky, L_EXPONENT, L_CUTOFF));
        spot_sky.location[0] = x_delta*d_line_x;
        spot_sky.location[1] = -y_delta*d_line_y;
        lights.push_back(new Spot(&spot_sky, L_EXPONENT, L_CUTOFF));
}

void Game::draw(){
	player.x += player.speed*((int) cos(((float)player.angle)*M_PI/180.0));
	player.y += player.speed*((int) sin(((float)player.angle)*M_PI/180.0));

//	cout<<"x="<<player.x<< " y="<<player.y<<" px="<<presence_x<<" py="<<presence_y<<endl;

 	assert(player.x<=2*SIZE_CASE_X+board_size_x/2.0);
 	assert(player.x>=-2*SIZE_CASE_X-board_size_x/2.0);
 	assert(player.y<=2*SIZE_CASE_Y+board_size_y/2.0);
 	assert(player.y>=-2*SIZE_CASE_Y-board_size_y/2.0);

	GLfloat x = inverseX(presence_x);
	GLfloat y = inverseY(presence_y);
	if (player.x<x-SIZE_CASE_X/2.0 || player.x>x+SIZE_CASE_X/2.0
	    || player.y<y-SIZE_CASE_Y/2.0 || player.y>y+SIZE_CASE_Y/2.0) {
		/* Si on se trouve sur une nouvelle case 
		 * We draw the previous beam ;
		 * We test the new case ;
		 */
		Beam *beam;
		beam = new Beam(x, y, player.angle, player.angle, 1, SIZE_CASE_X, SIZE_CASE_Y);
		beams.push_back(beam);
		graph_elements.push_back(beam);

		if (testPresence()) {
			lose = true;
		}
		presence_matrix[presence_x][presence_y] = true;
	}

	player.pt_moto->setPos(player.x, player.y, player.angle);

        for(std::vector<Drawable *>::iterator it = graph_elements.begin(); it < graph_elements.end();it++)
                if(*it) (*it) -> draw();

        switch(action){
                case NOTHING:

                        /* no action to do */
                        break;
                case TURN_LEFT:
                        if(player.angle % 90 != 0){
                                player.angle = (player.angle + ROTATION_INCREMENT) % 360;
                                usleep(ACTION_SLOWDOWN);
                                glutPostRedisplay();
                        }else
                                action = NOTHING;
                        break;
                case TURN_RIGHT:
                        if(player.angle % 90 != 0){
                                player.angle = (player.angle + 360 - ROTATION_INCREMENT) % 360;
                                usleep(ACTION_SLOWDOWN);
                        }else
                                action = NOTHING;
                        break;
                default:
                        break;
        }
	glutPostRedisplay();
}

Game::~Game(){
        for(std::vector<Light*>::iterator it = lights.begin(); it < lights.end();it++)
                delete *it;
        for(std::vector<Moto*>::iterator it = tab_motos.begin();it<tab_motos.end();it++)
                delete *it;
        for(std::vector<Beam*>::iterator it = beams.begin();it<beams.end();it++)
                delete *it;
        delete player.pt_moto;
        for(int i=0; i<2+board_size_x/(float)SIZE_CASE_X; i++)
                delete [] presence_matrix[i];
        delete [] presence_matrix;
}

void Game::activatePerspCam(){
        setPerspCam();
        cam_persp.activate();
        resetLight();
}

void Game::activateOrthoCam(){
        setOrthoCam();
        cam_ortho.activate();
        resetLight();
}

void Game::resetLight(){
        for(std::vector<Light*>::iterator it = lights.begin(); it < lights.end();it++)
                (*it) -> init();
}

void Game::zoomOrthoCam(int gradient){
        cam_ortho.zoom(gradient);
}

void Game::motoMov(enum MOV mov){
        /* the comportement of negative modulo is undefined !!! */
        /* the cast is here to prevent overflow */
        
        switch(mov){
                case UP:
                        player.speed += SPEED_INCREMENT;
			break;
                case DOWN:
                        player.speed -= SPEED_INCREMENT;
                        break;
                case LEFT:
                        player.angle = (player.angle + ROTATION_INCREMENT) % 360;
                        action = TURN_LEFT;
                        break;
                case RIGHT:
                        player.angle = (player.angle + 360 - ROTATION_INCREMENT) % 360;
                        action = TURN_RIGHT;
                        break;
        }
}

void Game::setPerspCam() {
        cam_persp.set_position(
                        /* cam pos */
                        player.x-MOTO_COEF*moto_size*cos(player.angle*M_PI/180), 
                        player.y-MOTO_COEF*moto_size*sin(player.angle*M_PI/180), 
                        PERSP_HEIGHT*moto_size,
                        /* ref point */
                        player.x,
                        player.y,
                        REF_HEIGHT*moto_size,
                        /* up vector */
                        0, 0, 1);
        cam_persp.set_view(FOVY, SCREEN_RATIO, 0.05, VIEW_DIST);
}

void Game::setOrthoCam() {
        cam_ortho.set_position(player.x, player.y, H_CAM, /*Cam position */
                        player.x, player.y, 0, /* ref point position */
                        1, 0, 0); /* up vector */
        cam_ortho.set_view(-SCREEN_RATIO*PROJ_SIZE, /* left */
                        SCREEN_RATIO*PROJ_SIZE, /* right */
                        /* Y */ -PROJ_SIZE, /* Down */
                        PROJ_SIZE, /* up */
                        0.5*H_CAM, /* Z near */
                        1.5*H_CAM); /*Z far */
}

void Game::cameraStart() {
	GLfloat taux = H_CAM/TAN_FINISH;
	for (int i=0 ; i<SUB_STEP ; i++) {
		GLfloat angle = player.angle + 2*i*M_PI/(float)SUB_STEP;
		cam_persp.set_position(player.x + X_START*cos(angle), player.y + H_CAM*sin(angle), H_CAM*(1-exp(-cos(angle)/taux)),
				       player.x, player.y, 0.0,
				       1.0, 1.0 ,1.0);
		cam_persp.activate();
		resetLight();
	}
}

bool Game::has_won() {
	return win;
}
bool Game::has_lost() {
	return lose;
}

bool Game::testPresence() {
	presence_x = funcX(player.x);
	presence_y = funcY(player.y);
	if (presence_matrix[presence_x][presence_y]) {
		cout << "Wow wow wow stop" <<endl;
		return true;
	}
	return false;
}

void Game::randomStart(GLfloat *x, GLfloat *y, int *angle) {
	srand((unsigned)time(0));

	do {
	presence_x = 1+(board_size_x/(float)SIZE_CASE_X)*rand()/(float)RAND_MAX;
	presence_y = 1+(board_size_y/(float)SIZE_CASE_Y)*rand()/(float)RAND_MAX;
	} while (presence_matrix[presence_x][presence_y]
		 || presence_x == funcX(board_size_x/2.0+1)
		 || presence_x == funcX(-board_size_x/2.0-1)
		 || presence_y == funcY(board_size_y/2.0+1)
		 || presence_y == funcY(-board_size_y/2.0-1));

	*x = inverseX(presence_x);
	*y = inverseY(presence_y);;
	*angle = 90* (int) (rand()%4 -1);
	presence_matrix[presence_x][presence_y] = true;
}

/**
 * Retourne la case de la matrice associé à la postition
 */
int Game::funcX(GLfloat x) {
	return 1+(int)((x+board_size_x/2.0)/(float)(SIZE_CASE_X));
}
int Game::funcY(GLfloat y) {
	return 1+(int)((y+board_size_y/2.0)/(float)(SIZE_CASE_Y));
}

GLfloat Game::inverseX(int px) {
	return SIZE_CASE_X*(px-0.5)-board_size_x/2.0;
}
GLfloat Game::inverseY(int py) {
	return SIZE_CASE_Y*(py-0.5)-board_size_y/2.0;
}
