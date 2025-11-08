#ifndef wem_mathf_h
#define wem_mathf_h

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

WEMDEF float wem_smoothstep(float start, float end, float t);
WEMDEF float wem_smootherstep(float start, float end, float t);
WEMDEF float wem_smoothstep_Inverse(float start, float end, float t);
WEMDEF float wem_smoothDamp(float from, float to, float *velocity, float maxSpeed, float smoothTime, float timeDelta);

#ifdef WEM_IMPLEMENTATION

#include "macros.h"
#include <math.h>

float wem_smoothstep(float start, float end, float t) {
    t = CLAMP(t, 0, 1);
    return (t * t * (3.0f - 2.0f * t)) * (end - start) + start;
}
float wem_smootherstep(float start, float end, float t) {
    t = CLAMP(t, 0, 1);
    return (t * t * t * (t * (6.0f * t - 15.0f) + 10.0f)) * (end - start) + start;
}
float wem_smoothstep_Inverse(float start, float end, float t) {
    return (0.5f - sinf(asinf(1.0f - 2.0f * t) / 3.0f)) * (end - start) + start;
}
float wem_smoothDamp(float from, float to, float *velocity, float maxSpeed, float smoothTime, float timeDelta) {
    float change = to - from;
    float maxChange = maxSpeed * smoothTime;
    if (change > maxChange) {
        change = maxSpeed;
    }
    from += change * timeDelta;
    return from;
}

#endif
#endif