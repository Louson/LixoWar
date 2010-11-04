#ifndef _WINDOW_H
#define _WINDOW_H

#include "Board.h"

#define KEY_ESC         0x001B

namespace Window{

        void display(void);

        void create(const char * window_name, int * argc, char ** argv);  
        void init();

        void keyboard(unsigned char cara,int x, int y);

        void windowReshape(int, int);
};

#endif
