#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <...>

typedef unsigned char uchar;
extern const char ETX;

// use matrix handout 1 or 2
template <typename T>
class matrix { 
    void assign(int Nrows, int Ncols);
};

struct pixel { int row, col; };

struct RGB { 
    uchar R,G,B;
};

class ppm {  
    matrix<RGB> img;
};

#endif
