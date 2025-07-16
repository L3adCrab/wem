#ifndef wem_bezier_h
#define wem_bezier_h

#ifndef WEMDEF
    #ifdef WEM_EXTERN
    #define WEMDEF extern
    #else
    #define WEMDEF static
    #endif
#endif

#include "macros.h"
#include "datatypes.h"
#include "vec3.h"

#include <math.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  LINEAR

WEMDEF bezier_linear wem_bezier_linear(vec3 beg, vec3 end) {
    return {beg, end};
}
WEMDEF vec3 wem_bezier_linearEvaluate(bezier_linear b, float t) {
    t = CLAMP(t, 0, 1);
    //  (p0 * (1-t)) + (p1 * t)
    return wem_vec3_add(wem_vec3_scale(b.p0, 1.0f - t), wem_vec3_scale(b.p1, t));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  QUADRATIC

WEMDEF bezier_quad wem_bezier_quad(vec3 beg, vec3 handle, vec3 end) {
    return {beg, handle, end};
}
WEMDEF vec3 wem_bezier_quadEvaluate(bezier_quad b, float t) {
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

WEMDEF bezier_cubic wem_bezier_cubic(vec3 beg, vec3 handle1, vec3 handle2, vec3 end) {
    return {beg, handle1, handle2, end, wem_bezier_quad(beg, handle1, handle2), wem_bezier_quad(handle1, handle2, end)};
}
WEMDEF void wem_bezier_cubicUpdate(bezier_cubic *b) {
    b->b0 = wem_bezier_quad(b->p0, b->p1, b->p2);
    b->b1 = wem_bezier_quad(b->p1, b->p2, b->p3);
}
WEMDEF vec3 wem_bezier_cubicEvaluate(bezier_cubic b, float t) {
    t = CLAMP(t, 0, 1);
    //  bQ(b0, t)(1-t) + bQ(b1, t)t
    return wem_vec3_add(wem_vec3_scale(wem_bezier_quadEvaluate(b.b0, t), 1.0f - t), wem_vec3_scale(wem_bezier_quadEvaluate(b.b1, t), t));
}


#endif