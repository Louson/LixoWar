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

#define MAX_SPEED       0.3
#define WALL_SIZE       10000

/* lights */
#define L_EXPONENT      2.0
#define L_CUTOFF        180
#define H_SPOT          5

#define MIN_SIZE_BOARD  10
/* #define Dx 6.0 */
/* #define Dy 6.0 */
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

Game::Game(
	int _opponent_number,
	int _board_size_x, int _board_size_y,
	GLfloat _quality_x, GLfloat _quality_y,
	GLfloat _d_lines_x, GLfloat _d_lines_y, 
	GLfloat _dim_lines_x, GLfloat _dim_lines_y, 
	int _moto_size,
	Sound & _sound,
	int _num_lasers
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
        moto_size(_moto_size),
        sound(_sound),
        begin_explosion(true),
        end_game(false)
{
        if(board_size_x < MIN_SIZE_BOARD || board_size_y < MIN_SIZE_BOARD)
                throw ExceptionWrongBoardSize(); 

        action = NOTHING;

        /* presence matrix initialization */
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
                        //cout<<presence_matrix[i][j];
                }//cout<<endl;
        }

        /* moto of the player */
        randomStart(&player.x, &player.y, &player.angle);
        player.presence_x = funcX(player.x);
        player.presence_y = funcY(player.y);
        player.numero = 0;
        player.speed = 0;
        player.pt_moto = new Moto(_moto_size, BLUE);

        /* lasers */
        str_laser.init_num = str_laser.cur_num = _num_lasers; 
        str_laser.tab = new Laser * [str_laser.init_num];
        for(int i = 0; i < str_laser.init_num; i++){
                GLfloat laser_x, laser_y;
                randomStart(&laser_x, &laser_y, NULL);
                str_laser.tab[i] = new Laser(laser_x, laser_y, dim_line_x/2, dim_line_y/2);
                graph_elements.push_back(str_laser.tab[i]);
        }

        /* opponents */
        tab_opp = new MOTO_STRUCT[opponentNumber];
        for (int i=0 ; i<opponentNumber ; i++) {
                randomStart(&tab_opp[i].x, &tab_opp[i].y, &tab_opp[i].angle);
                tab_opp[i].presence_x = funcX(tab_opp[i].x);
                tab_opp[i].presence_y = funcY(tab_opp[i].y);
                (tab_opp+i)->numero = i+1;
                (tab_opp+i)->speed = 0;
                (tab_opp+i)->pt_moto = new Moto(_moto_size, RED);
        }

        /* drawing elements */
        graph_elements.push_back(player.pt_moto);
        for (int i=0 ; i<opponentNumber ; i++) {
                graph_elements.push_back((tab_opp+i)->pt_moto);
        }
        graph_elements.push_back(&wall);
        graph_elements.push_back(&board);

        /* lights */
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

void Game::testNewCase(MOTO_STRUCT *motoTest) {
        bool is_laser = false;
        GLfloat temp_x = inverseX(motoTest->presence_x);
        GLfloat temp_y = inverseY(motoTest->presence_y);
        motoTest->presence_x = funcX(motoTest->x);
        motoTest->presence_y = funcY(motoTest->y);

        if ((motoTest->presence_x != funcX(temp_x)) || (motoTest->presence_y != funcY(temp_y)) ) {
                /* Si on se trouve sur une nouvelle case 
                 * We draw the previous beam ;
                 * We test the new case ;
                 */
                if (testPresence(motoTest)){

                        /* tests if it's a laser */
                        for(int i = 0; i < str_laser.init_num; i++){
                                if(str_laser.tab[i]->testPos(player.x, player.y)){
                                        sound.play(LASER);
                                        str_laser.tab[i]->deactivate();
                                        str_laser.cur_num--;
                                        if(str_laser.cur_num == 0){
                                                win = true;
                                        }
                                        is_laser = true;
                                }
                        }

                        if(is_laser)
                                ;
                        /* if it's a opponent */
                        else if (motoTest->numero) {
                                opponentNumber--;
                                if (!opponentNumber) {
                                        win = true;
				}
				motoTest->pt_moto->explode();
                                return;
                        }else{
                                end_game = true;
                                motoTest->pt_moto->explode();
                                return;
                        }
                }
                Beam *beam;
                if(motoTest->numero)
                        beam = new Beam(temp_x, temp_y, motoTest->angle, motoTest->angle, motoTest->numero, SIZE_CASE_X, SIZE_CASE_Y, RED);
                else
                        beam = new Beam(temp_x, temp_y, motoTest->angle, motoTest->angle, motoTest->numero, SIZE_CASE_X, SIZE_CASE_Y, BLUE);
                beams.push_back(beam);
                graph_elements.push_back(beam);
                presence_matrix[motoTest->presence_x][motoTest->presence_y] = true;
        }
}

void Game::draw(){
        assert(player.x<=2*SIZE_CASE_X+board_size_x/2.0);
        assert(player.x>=-2*SIZE_CASE_X-board_size_x/2.0);
        assert(player.y<=2*SIZE_CASE_Y+board_size_y/2.0);
        assert(player.y>=-2*SIZE_CASE_Y-board_size_y/2.0);

        if(end_game){
                if(begin_explosion){
                        begin_explosion = false;
                        sound.play(EXPLOSION);
                }
                if(player.pt_moto->getEndExplosion())
                        lose = true;
        }else{
                /* player position calculation */
                player.x += player.speed*((int) cos(((float)player.angle)*M_PI/180.0));
                player.y += player.speed*((int) sin(((float)player.angle)*M_PI/180.0));
                player.pt_moto->setPos(player.x, player.y, player.angle);

                /* enemy position calculation */
                for (int i=0 ; i<opponentNumber ; i++) {
                        MOTO_STRUCT *enemy = tab_opp+i;
                        enemy->x += enemy->speed*((int) cos(((float)enemy->angle)*M_PI/180.0));
                        enemy->y += enemy->speed*((int) sin(((float)enemy->angle)*M_PI/180.0));
                        enemy->pt_moto->setPos(enemy->x, enemy->y, enemy->angle);
                        enemyMov(enemy);
                        testNewCase(enemy);
                }

                /* colision detection */
                testNewCase(&player);
        }

        for (int i=0 ; i< opponentNumber ; i++) 
                (tab_opp+i)->pt_moto->setPos((tab_opp+i)->x, (tab_opp+i)->y, (tab_opp+i)->angle);

        for(std::vector<Drawable *>::iterator it = graph_elements.begin(); it < graph_elements.end();it++)
                if(*it) (*it) -> draw();

        /* action management */ 
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
        for(std::vector<Beam*>::iterator it = beams.begin();it<beams.end();it++)
                delete *it;
        delete player.pt_moto;
        for(int i=0; i<2+board_size_x/(float)SIZE_CASE_X; i++)
                delete [] presence_matrix[i];
        delete [] presence_matrix;
        for(int i = 0; i < str_laser.init_num; i++)
                delete str_laser.tab[i];
        delete [] str_laser.tab;
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

void Game::speedIncrement(MOTO_STRUCT *pt_moto, enum MOV mov)
{
        assert(pt_moto != NULL);

        switch(mov){
                case UP:
                        if(pt_moto->speed + SPEED_INCREMENT > MAX_SPEED)
                                pt_moto->speed = MAX_SPEED;
                        else
                                pt_moto->speed += SPEED_INCREMENT;
                        break;
                default:
                        if(pt_moto->speed - SPEED_INCREMENT < 0)
                                pt_moto->speed = 0;
                        else
                                pt_moto->speed -= SPEED_INCREMENT;
                        break;
        }
}

void Game::motoMov(enum MOV mov){
        /* the comportement of negative modulo is undefined !!! */
        /* the cast is here to prevent overflow */
        switch(mov){
                case UP:
                        speedIncrement(&player, UP);
                        break;
                case DOWN:
                        speedIncrement(&player, DOWN);
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

/**
 * Déplace l'ennemi dans la bonne direction
 */
void Game::enemyMov(MOTO_STRUCT *enemy) {
        switch (choseDirection(enemy->x, enemy->y, enemy->angle)) {
                case UP:
                        speedIncrement(enemy, UP);
                        break;
                case DOWN:
                        enemy->angle = (enemy->angle + 180) % 360;
                        break;
                case LEFT:
                        enemy->angle = (enemy->angle + 90) % 360;
                        break;
                case RIGHT:
                        enemy->angle = (enemy->angle + 270) % 360;
                        break;
        }
}

/**
 * Renvoie la meilleure direction
 */
enum MOV Game::choseDirection(GLfloat x, GLfloat y, int angle) {
        int max, lower;
        enum MOV res = UP;
        int cosr;
        int sinr;

        switch ((angle%360+360)%360) {
                case 0 :
                        cosr = 1;
                        sinr = 0;
                        break;
                case 90 :
                        cosr = 0;
                        sinr = 1;
                        break;
                case 180 :
                        cosr = -1;
                        sinr = 0;
                        break;
                case 270 :
                        cosr = 0;
                        sinr = -1;
                        break;
        }

	/* Tout droit */
        max = look(funcX(x), funcY(y), cosr, sinr);
	/* à droite */
        lower = look(funcX(x), funcY(y), sinr, -cosr);
        if ( max < lower ) {
                max = lower;
                res = RIGHT;
        }
	/* à gauche */
        lower = look(funcX(x), funcY(y), -sinr, -cosr);
        if ( max < lower) {
                max = lower;
                res = LEFT;
        }
	/* en arrière */
        //	lower = look(funcX(x), funcY(y), cosr, -sinr);
        // 	if ( max > lower) {
        // 		max = lower;
        // 		res = DOWN;
        // 	}
        return res;
}

/**
 * Calcule la distance libre dans la direction donnée
 */
int Game::look(int px, int py, int kx, int ky) {
        int resx = px;
        int resy = py;
        assert(kx*ky == 0);
        assert(kx*kx+ky*ky==1);
        do {
                resx += kx;
                resy += ky;
        } while (!presence_matrix[resx][resy]);
        if (kx + ky > 0)
                return (resx-px)+(resy-py);
        else return (px-resx)+(py-resy);
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

bool Game::testPresence(MOTO_STRUCT *motoTest) {
        if (presence_matrix[motoTest->presence_x][motoTest->presence_y]) {
                return true;
        }
        return false;
}

void Game::randomStart(GLfloat *x, GLfloat *y, int *angle) {
        int px, py;
        do {
                px = 1+(board_size_x/(float)SIZE_CASE_X)*rand()/(float)RAND_MAX;
                py = 1+(board_size_y/(float)SIZE_CASE_Y)*rand()/(float)RAND_MAX;
        } while (presence_matrix[px][py]
                        || px == funcX(board_size_x/2.0+1)
                        || px == funcX(-board_size_x/2.0-1)
                        || py == funcY(board_size_y/2.0+1)
                        || py == funcY(-board_size_y/2.0-1));

        if(x) *x = inverseX(px);
        if(y) *y = inverseY(py);;
        if(angle) *angle = 90* (int) (rand()%4 -1);
        presence_matrix[px][py] = true;
}

/**
 * Retourne la case de la matrice associé à la position
 */
int Game::funcX(GLfloat x) {
        return 1+(int)((x+board_size_x/2.0)/(float)(SIZE_CASE_X));
}
int Game::funcY(GLfloat y) {
        return 1+(int)((y+board_size_y/2.0)/(float)(SIZE_CASE_Y));
}
/**
 * Retourne la position associée à la case
 */
GLfloat Game::inverseX(int px) {
        return SIZE_CASE_X*(px-0.5)-board_size_x/2.0;
}
GLfloat Game::inverseY(int py) {
        return SIZE_CASE_Y*(py-0.5)-board_size_y/2.0;
}
