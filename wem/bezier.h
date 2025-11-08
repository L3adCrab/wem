#ifndef wem_bezier_h
#define wem_bezier_h

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

#include "macros.h"
#include "datatypes.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  LINEAR

WEMDEF bezier_linear wem_bezier_linear(vec3 beg, vec3 end);
WEMDEF vec3 wem_bezier_linearEvaluate(bezier_linear b, float t);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  QUADRATIC

WEMDEF bezier_quad wem_bezier_quad(vec3 beg, vec3 handle, vec3 end);
WEMDEF vec3 wem_bezier_quadEvaluate(bezier_quad b, float t);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CUBIC

WEMDEF bezier_cubic wem_bezier_cubic(vec3 beg, vec3 handle1, vec3 handle2, vec3 end);
WEMDEF void wem_bezier_cubicUpdate(bezier_cubic *b);
WEMDEF vec3 wem_bezier_cubicEvaluate(bezier_cubic b, float t);


#ifdef WEM_IMPLEMENTATION

#include "vec3.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  LINEAR

bezier_linear wem_bezier_linear(vec3 beg, vec3 end) {
    bezier_linear out = {beg, end};
    return out;
}
vec3 wem_bezier_linearEvaluate(bezier_linear b, float t) {
    t = CLAMP(t, 0, 1);
    //  (p0 * (1-t)) + (p1 * t)
    return wem_vec3_add(wem_vec3_scale(b.p0, 1.0f - t), wem_vec3_scale(b.p1, t));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  QUADRATIC

bezier_quad wem_bezier_quad(vec3 beg, vec3 handle, vec3 end) {
    bezier_quad out = {beg, handle, end};
    return out;
}
vec3 wem_bezier_quadEvaluate(bezier_quad b, float t) {
    t = CLAMP(t, 0, 1);
    //  (p0 * (1-t) + p1 * t)(1-t) + (p1 * (1-t) + p2 * t)t
    //  (p0 * (1-t) + p1 * t)(1-t)
    vec3 part1 = wem_vec3_scale(wem_vec3_add(wem_vec3_scale(b.p0, 1.0f - t), wem_vec3_scale(b.p1, t)), 1.0f - t);
    //  (p1 * (1-t) + p2 * t)t
    vec3 part2 = wem_vec3_scale(wem_vec3_add(wem_vec3_scale(b.p1, 1.0 - t),wem_vec3_scale(b.p2, t)), t);
    return wem_vec3_add(part1, part2);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CUBIC

bezier_cubic wem_bezier_cubic(vec3 beg, vec3 handle1, vec3 handle2, vec3 end) {
    bezier_cubic out = {beg, handle1, handle2, end, wem_bezier_quad(beg, handle1, handle2), wem_bezier_quad(handle1, handle2, end)};
    return out;
}
void wem_bezier_cubicUpdate(bezier_cubic *b) {
    b->b0 = wem_bezier_quad(b->p0, b->p1, b->p2);
    b->b1 = wem_bezier_quad(b->p1, b->p2, b->p3);
}
vec3 wem_bezier_cubicEvaluate(bezier_cubic b, float t) {
    t = CLAMP(t, 0, 1);
    //  bQ(b0, t)(1-t) + bQ(b1, t)t
    return wem_vec3_add(wem_vec3_scale(wem_bezier_quadEvaluate(b.b0, t), 1.0f - t), wem_vec3_scale(wem_bezier_quadEvaluate(b.b1, t), t));
}

#endif
#endif