#ifndef wem_random_h
#define wem_random_h

#ifndef WEMDEF
    #ifdef WEM_EXTERN
    #define WEMDEF extern
    #else
    #define WEMDEF static
    #define WEM_IMPLEMENTATION
    #endif
#endif

#ifdef WEM_IMPLEMENTATION

#include <stdlib.h>
#include <math.h>
#include <time.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SEED

WEMDEF void wem_random_setSeedRand() {
    srand(time(0));
}
WEMDEF void wem_random_setSeed(int seed) {
    srand(seed);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INT

WEMDEF int wem_random_int() {
    return rand();
}
WEMDEF int wem_random_intRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  FLOAT

WEMDEF float wem_random_float() {
    return (float)rand() / 0x7fff;
}
WEMDEF float wem_random_floatRange(float min, float max) {
    float f;
    do
    {
        f = (wem_random_float() * max) + min;
        if (f >= min && f <= max) return f;
    } while (1);
}

#endif
#endif