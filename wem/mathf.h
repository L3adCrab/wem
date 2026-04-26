#ifndef WEM_MATHF_H
#define WEM_MATHF_H

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

WEMDEF float wem_smoothstep(float start, float end, float t);
WEMDEF float wem_smootherstep(float start, float end, float t);
WEMDEF float wem_smoothstep_Inverse(float start, float end, float t);

#ifdef WEM_IMPLEMENTATION 

#include <math.h>

#include "macros.h"

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

#endif
#endif