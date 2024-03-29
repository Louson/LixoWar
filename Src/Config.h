#ifndef _CONFIG_H
#define _CONFIG_H

#include "File.h"

/* Screen settings */
#define SCREEN_RATIO (16.0/9.0)

/* Board settings */
#define SIDE_X 10000
#define SIDE_Y 10000
#define QUALITY_X 1    /* Number of subdivisions along (Ox) */
#define QUALITY_Y 1    /* Number of subdivisions along (Oy) */
#define D_LINE_X 25    /* Space dimensions between two lines */
#define D_LINE_Y 25
#define DIM_LINE_X 6.0   /* Cases between two lines */
#define DIM_LINE_Y 6.0
#define OPPONENT_NUMBER 1
#define NUM_LASERS 4

#define MOTO_SIZE 1
/* Camera height */
#define H_CAM 10

namespace Config{
    int fetchParam(const string & paramName,int defaultValue, const File & configFile);
};

/* Enemy speed */

#endif
