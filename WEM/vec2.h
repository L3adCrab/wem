#ifndef wem_vec2_h
#define wem_vec2_h

#ifndef WEMDEF
    #ifdef WEM_EXTERN
    #define WEMDEF extern
    #else
    #define WEMDEF static
    #endif
#endif

#include "macros.h"
#include "datatypes.h"

#include <math.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ALLOCATION

WEMDEF vec2 wem_vec2(float x, float y) {
    vec2 out = {x, y};
    return out;
}
WEMDEF vec2 wem_vec2_1f(float f) {
    vec2 out = {f, f};
    return out;
}
WEMDEF vec2 wem_vec2_zero() {
    vec2 out = {0, 0};
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CONVERSION

WEMDEF vec3 wem_vec2_toVec3(vec2 v) {
    vec3 out = {v.x, v.y, 0};
    return out;
}
WEMDEF vec4 wem_vec2_toVec4(vec2 v) {
    vec4 out = {v.x, v.y, 0, 1};
    return out;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADDITION

WEMDEF vec2 wem_vec2_add(vec2 v1, vec2 v2) {
    v1.x += v2.x; v1.y += v2.y;
    return v1;
}
WEMDEF vec2 wem_vec2_add2f(vec2 v, float x, float y) {
    v.x += x; v.y += y;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SUBTRACTION

WEMDEF vec2 wem_vec2_sub(vec2 v1, vec2 v2) {
    v1.x -= v2.x; v1.y -= v2.y;
    return v1;
}
WEMDEF vec2 wem_vec2_sub2f(vec2 v, float x, float y) {
    v.x -= x; v.y -= y;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MULTIPLICATION

WEMDEF vec2 wem_vec2_mul(vec2 v1, vec2 v2) {
    v1.x *= v2.x; v1.y *= v2.y;
    return v1;
}
WEMDEF vec2 wem_vec2_mul2f(vec2 v, float x, float y) {
    v.x *= x; v.y *= y;
    return v;
}
// WEMDEF vec2 wem_vec2_mulMat4(vec2 v, mat4 m) {
//     vec2 out    = {0};
//     float *outf = (float*)&out;
//     float *vf   = (float*)&v;
//     for (int y = 0; y < 4; y++) {
//         for (int x = 0; x < 4; x++) {
//             outf[y] += vf[x] * m.v[4 * x + y];  
//         }
//     }
//     out = *(vec2*)outf;
//     return out;
// }
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DIVISION

WEMDEF vec2 wem_vec2_div(vec2 v1, vec2 v2) {
    v1.x /= v2.x; v1.y /= v2.y;
    return v1;
}
WEMDEF vec2 wem_vec2_div2f(vec2 v, float x, float y) {
    v.x /= x; v.y /= y;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SCALE

WEMDEF vec2 wem_vec2_scale(vec2 v, float scale) {
    v.x *= scale; v.y *= scale;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

WEMDEF vec2 wem_vec2_inv(vec2 v) {
    v.x = -v.x; v.y = -v.y;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

WEMDEF float wem_vec2_sqrMagnitude(vec2 v) {
    return POW2(v.x) + POW2(v.y);
}
WEMDEF float wem_vec2_magnitude(vec2 v) {
    return sqrt(wem_vec2_sqrMagnitude(v));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

WEMDEF vec2 wem_vec2_norm(vec2 v) {
    float l = wem_vec2_magnitude(v);
    v.x /= l; v.y /= l;
    return v;
}
WEMDEF vec2 wem_vec2_norm2f(float x, float y) {
    float l = sqrt(POW2(x) + POW2(y));
    vec2 out = {x / l, y / l};
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

WEMDEF float wem_vec2_dot(vec2 v1, vec2 v2) {
    return v1.x * v2.x + v1.y * v2.y;
}
WEMDEF float wem_vec2_dotN(vec2 v1, vec2 v2) {
    return wem_vec2_dot(wem_vec2_norm(v1), wem_vec2_norm(v2));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  PERPENDICULAR

WEMDEF vec2 wem_vec2_perp(vec2 v) {
    vec2 out = {v.y, v.x};
    return out;
}
WEMDEF vec2 wem_vec2_perpN(vec2 v) {
    return wem_vec2_norm(wem_vec2_perp(v));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

WEMDEF vec2 wem_vec2_lerp(vec2 v1, vec2 v2, float t) {
    vec2 out = wem_vec2_add(wem_vec2_scale(v1, 1.0f - t), wem_vec2_scale(v2, t));
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE

float wem_vec2_angleInRad(vec2 v1, vec2 v2) {
    float dot = wem_vec2_dotN(v1, v2);
    return acos(dot);
}
float wem_vec2_angleInDeg(vec2 v1, vec2 v2) {
    return wem_vec2_angleInRad(v1, v2) * RAD2DEG; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL

WEMDEF int wem_vec2_matches(vec2 v1, vec2 v2) {
    return v1.x == v2.x && v1.y == v2.y;
}
WEMDEF int wem_vec2_inRange(vec2 v1, vec2 v2, float range) {
    vec2 dir = wem_vec2_sub(v2, v1);
    return wem_vec2_sqrMagnitude(dir) <= POW2(range);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_vec2_print(vec2 v) {
    printf("vec2(%f, %f)\n", v.x, v.y);
}

#endif