#ifndef _WINDOW_H
#define _WINDOW_H

#include <string>

#include "Board.h"

namespace Window{

        void display(void);

        void create(const char * window_name, int * argc, char ** argv);  
        void init();
};

#endif
