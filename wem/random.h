#ifndef WEM_RANDOM_H
#define WEM_RANDOM_H

#ifdef WEMDLL
    #ifdef _WIN32
        #ifdef DLLBUILD
            #define WEMDEF __declspec(dllexport)
        #else
            #define WEMDEF __declspec(dllimport)
        #endif
    #else
        #define WEMDEF
    #endif
#else
    #define WEMDEF extern
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