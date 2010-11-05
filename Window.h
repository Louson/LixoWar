#ifndef _WINDOW_H
#define _WINDOW_H

#include "Board.h"

/* KEYS */
#define KEY_ESC 0x001B
#define KEY_PLUS 43 
#define KEY_MINUS 45

#define VIEWPORT_NUMBER 2

#define MAP_VIEWPORT_POS_RATIO 6/7
#define MAP_VIEWPORT_SIZE_RATIO 1/7
#define MAP_VIEWPORT_PIXEL_DEP 20

namespace Window{

        enum{NORMAL_VIEWPORT, MAP_VIEWPORT};

        void display(void);
        void create(const char * window_name, int * argc, char ** argv);  
        void init();
        void keyboard(unsigned char cara,int x, int y);

        /* used to get the dimension of the windows */
        void windowReshape(int, int);
};

#endif
