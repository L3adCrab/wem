#ifndef wem_random_h
#define wem_random_h

/*///////////////////////////////////////////////////////////////////////////////////
//  USAGE
//  By default functions are defined as extern.
//  To implement somewhere in source file before including header file
//  #define WEM_IMPLEMENTATION
//  Implementation should be defined only once.
//  
//  For use as static functions before including header file
//  #define WEM_STATIC
//  There if no need to define WEM_IMPLEMENTATION when using as static,
//  although WEM_STATIC will need to be somewhere defined in every source file where
//  library will be used. To circumvent this and whole library will be used as static
//  add the WEM_STATIC define to compiler (gcc/clang -DWEM_STATIC)
//
//  To include all weu library in souce file at once, include weu_master.h  
*////////////////////////////////////////////////////////////////////////////////////

#ifndef WEMDEF
    #ifdef WEM_STATIC
    #define WEMDEF static
    #define WEM_IMPLEMENTATION
    #else
    #define WEMDEF extern
    #endif
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SEED

WEMDEF void wem_random_setSeedRand();
WEMDEF void wem_random_setSeed(int seed);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INT

WEMDEF int wem_random_int();
WEMDEF int wem_random_intRange(int min, int max);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  FLOAT

WEMDEF float wem_random_float();
WEMDEF float wem_random_floatRange(float min, float max);

#ifdef WEM_IMPLEMENTATION

#include <stdlib.h>
#include <math.h>
#include <time.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SEED

void wem_random_setSeedRand() {
    srand(time(0));
}
void wem_random_setSeed(int seed) {
    srand(seed);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INT

int wem_random_int() {
    return rand();
}
int wem_random_intRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  FLOAT

float wem_random_float() {
    return (float)rand() / 0x7fff;
}
float wem_random_floatRange(float min, float max) {
    float f;
    do
    {
        f = (wem_random_float() * max) + min;
        if (f >= min && f <= max) return f;
    } while (1);
}

#endif
#endif