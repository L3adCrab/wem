#ifndef wem_vec2_h
#define wem_vec2_h

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

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ALLOCATION

WEMDEF vec2 wem_vec2(float x, float y);
WEMDEF vec2 wem_vec2_1f(float f);
WEMDEF vec2 wem_vec2_zero();

WEMDEF vec2 *wem_vec2_allocNew(float x, float y);
WEMDEF vec2 *wem_vec2_alloc(vec2 vec);
WEMDEF void wem_vec2_setVec(vec2 *h, vec2 vec);
WEMDEF void wem_vec2_free(vec2 **h);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CONVERSION

WEMDEF vec3 wem_vec2_toVec3(vec2 v);
WEMDEF vec4 wem_vec2_toVec4(vec2 v);
//////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADDITION

WEMDEF vec2 wem_vec2_add(vec2 v1, vec2 v2);
WEMDEF vec2 wem_vec2_add2f(vec2 v, float x, float y);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SUBTRACTION

WEMDEF vec2 wem_vec2_sub(vec2 v1, vec2 v2);
WEMDEF vec2 wem_vec2_sub2f(vec2 v, float x, float y);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MULTIPLICATION

WEMDEF vec2 wem_vec2_mul(vec2 v1, vec2 v2);
WEMDEF vec2 wem_vec2_mul2f(vec2 v, float x, float y);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DIVISION

WEMDEF vec2 wem_vec2_div(vec2 v1, vec2 v2);
WEMDEF vec2 wem_vec2_div2f(vec2 v, float x, float y);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SCALE

WEMDEF vec2 wem_vec2_scale(vec2 v, float scale);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

WEMDEF vec2 wem_vec2_inv(vec2 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

WEMDEF float wem_vec2_sqrMagnitude(vec2 v);
WEMDEF float wem_vec2_magnitude(vec2 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

WEMDEF vec2 wem_vec2_norm(vec2 v);
WEMDEF vec2 wem_vec2_norm2f(float x, float y);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

WEMDEF float wem_vec2_dot(vec2 v1, vec2 v2);
WEMDEF float wem_vec2_dotN(vec2 v1, vec2 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  PERPENDICULAR

WEMDEF vec2 wem_vec2_perp(vec2 v);
WEMDEF vec2 wem_vec2_perpN(vec2 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

WEMDEF vec2 wem_vec2_lerp(vec2 v1, vec2 v2, float t);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE

float wem_vec2_angleInRad(vec2 v1, vec2 v2);
float wem_vec2_angleInDeg(vec2 v1, vec2 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL

WEMDEF int wem_vec2_matches(vec2 v1, vec2 v2);
WEMDEF int wem_vec2_inRange(vec2 v1, vec2 v2, float range);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_vec2_print(vec2 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  OPERATORS

#ifdef __cplusplus
WEMDEF vec2 operator+(vec2 v1, vec2 v2);
WEMDEF void operator+=(vec2 &v1, vec2 v2);
WEMDEF vec2 operator+(vec2 v, float f);
WEMDEF void operator+=(vec2 &v, float f);

WEMDEF vec2 operator-(vec2 v1, vec2 v2);
WEMDEF void operator-=(vec2 &v1, vec2 v2);
WEMDEF vec2 operator-(vec2 v, float f);
WEMDEF void operator-=(vec2 &v, float f);

WEMDEF vec2 operator*(vec2 v1, vec2 v2);
WEMDEF void operator*=(vec2 &v1, vec2 v2);
WEMDEF vec2 operator*(vec2 v, float f);
WEMDEF void operator*=(vec2 &v, float f);

WEMDEF vec2 operator/(vec2 v1, vec2 v2);
WEMDEF void operator/=(vec2 &v1, vec2 v2);

WEMDEF vec2 operator-(vec2 v);
#endif

#ifdef WEM_IMPLEMENTATION
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ALLOCATION

vec2 wem_vec2(float x, float y) {
    vec2 out = {x, y};
    return out;
}
vec2 wem_vec2_1f(float f) {
    vec2 out = {f, f};
    return out;
}
vec2 wem_vec2_zero() {
    vec2 out = {0, 0};
    return out;
}

vec2 *wem_vec2_allocNew(float x, float y) {
    vec2 *out = (vec2*)malloc(sizeof(vec2));
    out->x = x; out->y = y;
    return out;
}
vec2 *wem_vec2_alloc(vec2 vec) {
    vec2 *out = (vec2*)malloc(sizeof(vec2));
    *out = vec;
    return out;
}
void wem_vec2_setVec(vec2 *h, vec2 vec) {
    *h = vec;
}
void wem_vec2_free(vec2 **h) {
    free(*h);
    *h = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CONVERSION

vec3 wem_vec2_toVec3(vec2 v) {
    vec3 out = {v.x, v.y, 0};
    return out;
}
vec4 wem_vec2_toVec4(vec2 v) {
    vec4 out = {v.x, v.y, 0, 1};
    return out;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADDITION

vec2 wem_vec2_add(vec2 v1, vec2 v2) {
    v1.x += v2.x; v1.y += v2.y;
    return v1;
}
vec2 wem_vec2_add2f(vec2 v, float x, float y) {
    v.x += x; v.y += y;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SUBTRACTION

vec2 wem_vec2_sub(vec2 v1, vec2 v2) {
    v1.x -= v2.x; v1.y -= v2.y;
    return v1;
}
vec2 wem_vec2_sub2f(vec2 v, float x, float y) {
    v.x -= x; v.y -= y;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MULTIPLICATION

vec2 wem_vec2_mul(vec2 v1, vec2 v2) {
    v1.x *= v2.x; v1.y *= v2.y;
    return v1;
}
vec2 wem_vec2_mul2f(vec2 v, float x, float y) {
    v.x *= x; v.y *= y;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DIVISION

vec2 wem_vec2_div(vec2 v1, vec2 v2) {
    v1.x /= v2.x; v1.y /= v2.y;
    return v1;
}
vec2 wem_vec2_div2f(vec2 v, float x, float y) {
    v.x /= x; v.y /= y;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SCALE

vec2 wem_vec2_scale(vec2 v, float scale) {
    v.x *= scale; v.y *= scale;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

vec2 wem_vec2_inv(vec2 v) {
    v.x = -v.x; v.y = -v.y;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

float wem_vec2_sqrMagnitude(vec2 v) {
    return POW2(v.x) + POW2(v.y);
}
float wem_vec2_magnitude(vec2 v) {
    return sqrt(wem_vec2_sqrMagnitude(v));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

vec2 wem_vec2_norm(vec2 v) {
    float l = wem_vec2_magnitude(v);
    v.x /= l; v.y /= l;
    return v;
}
vec2 wem_vec2_norm2f(float x, float y) {
    float l = sqrt(POW2(x) + POW2(y));
    vec2 out = {x / l, y / l};
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

float wem_vec2_dot(vec2 v1, vec2 v2) {
    return v1.x * v2.x + v1.y * v2.y;
}
float wem_vec2_dotN(vec2 v1, vec2 v2) {
    return wem_vec2_dot(wem_vec2_norm(v1), wem_vec2_norm(v2));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  PERPENDICULAR

vec2 wem_vec2_perp(vec2 v) {
    vec2 out = {v.y, v.x};
    return out;
}
vec2 wem_vec2_perpN(vec2 v) {
    return wem_vec2_norm(wem_vec2_perp(v));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

vec2 wem_vec2_lerp(vec2 v1, vec2 v2, float t) {
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

int wem_vec2_matches(vec2 v1, vec2 v2) {
    return v1.x == v2.x && v1.y == v2.y;
}
int wem_vec2_inRange(vec2 v1, vec2 v2, float range) {
    vec2 dir = wem_vec2_sub(v2, v1);
    return wem_vec2_sqrMagnitude(dir) <= POW2(range);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

void wem_vec2_print(vec2 v) {
    printf("vec2(%f, %f)\n", v.x, v.y);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  OPERATORS

#ifdef __cplusplus
vec2 operator+(vec2 v1, vec2 v2) { return wem_vec2_add(v1, v2); }
void operator+=(vec2 &v1, vec2 v2) { v1 = wem_vec2_add(v1, v2); }
vec2 operator+(vec2 v, float f) { return wem_vec2_add2f(v, f, f); }
void operator+=(vec2 &v, float f) { v = wem_vec2_add2f(v, f, f); }

vec2 operator-(vec2 v1, vec2 v2) { return wem_vec2_sub(v1, v2); }
void operator-=(vec2 &v1, vec2 v2) { v1 = wem_vec2_sub(v1, v2); }
vec2 operator-(vec2 v, float f) { return wem_vec2_sub2f(v, f, f); }
void operator-=(vec2 &v, float f) { v = wem_vec2_sub2f(v, f, f); }

vec2 operator*(vec2 v1, vec2 v2) { return wem_vec2_mul(v1, v2); }
void operator*=(vec2 &v1, vec2 v2) { v1 = wem_vec2_mul(v1, v2); }
vec2 operator*(vec2 v, float f) { return wem_vec2_scale(v, f); }
void operator*=(vec2 &v, float f) { v = wem_vec2_scale(v, f); }

vec2 operator/(vec2 v1, vec2 v2) { return wem_vec2_div(v1, v2); }
void operator/=(vec2 &v1, vec2 v2) { v1 = wem_vec2_div(v1, v2); }

vec2 operator-(vec2 v) { return wem_vec2_inv(v); }
#endif

#endif
#endif