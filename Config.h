#ifndef _CONFIG_H
#define _CONFIG_H

#include "File.h"

/* Board settings */
#define SIDE_X 10000    /* Board's dimensions in meters*/
#define SIDE_Y 10000
#define QUALITY_X 1  /* Number of subdivisions along (Ox) */
#define QUALITY_Y 1  /* Number of subdivisions along (Oy) */
#define D_LINE_X 100    /* Space dimensions between two lines */
#define D_LINE_Y 100

namespace Config{
    int fetchParam(const string & paramName,int defaultValue, const File & configFile);
};

#endif
