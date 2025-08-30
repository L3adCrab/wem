#ifndef wem_vec3_h
#define wem_vec3_h

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

#include <math.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ALLOCATION

WEMDEF vec3 wem_vec3(float x, float y, float z);
WEMDEF vec3 wem_vec3_1f(float f);
WEMDEF vec3 wem_vec3_zero();

WEMDEF vec3 *wem_vec3_allocNew(float x, float y, float z);
WEMDEF vec3 *wem_vec3_alloc(vec3 vec);
WEMDEF void wem_vec3_setVec(vec3 *h, vec3 vec);
WEMDEF void wem_vec3_free(vec3 **h);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CONVERSION

WEMDEF vec2 wem_vec3_toVec2(vec3 v);
WEMDEF vec4 wem_vec3_toVec4(vec3 v);
WEMDEF vec2 wem_vec3_homogenous(vec3 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADDITION

WEMDEF vec3 wem_vec3_add(vec3 v1, vec3 v2);
WEMDEF vec3 wem_vec3_add3f(vec3 v, float x, float y, float z);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SUBTRACTION

WEMDEF vec3 wem_vec3_sub(vec3 v1, vec3 v2);
WEMDEF vec3 wem_vec3_sub3f(vec3 v, float x, float y, float z);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MULTIPLICATION

WEMDEF vec3 wem_vec3_mul(vec3 v1, vec3 v2);
WEMDEF vec3 wem_vec3_mul3f(vec3 v, float x, float y, float z);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DIVISION

WEMDEF vec3 wem_vec3_div(vec3 v1, vec3 v2);
WEMDEF vec3 wem_vec3_div3f(vec3 v, float x, float y, float z);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SCALE

WEMDEF vec3 wem_vec3_scale(vec3 v, float scale);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

WEMDEF vec3 wem_vec3_inv(vec3 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

WEMDEF float wem_vec3_sqrMagnitude(vec3 v);
WEMDEF float wem_vec3_magnitude(vec3 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

WEMDEF vec3 wem_vec3_norm(vec3 v);
WEMDEF vec3 wem_vec3_norm3f(float x, float y, float z);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

WEMDEF float wem_vec3_dot(vec3 v1, vec3 v2);
WEMDEF float wem_vec3_dotN(vec3 v1, vec3 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS

WEMDEF vec3 wem_vec3_cross(vec3 v1, vec3 v2);
WEMDEF vec3 wem_vec3_crossN(vec3 v1, vec3 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

WEMDEF vec3 wem_vec3_lerp(vec3 v1, vec3 v2, float t);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE

WEMDEF float wem_vec3_angleInRad(vec3 v1, vec3 v2);
WEMDEF float wem_vec3_angleInDeg(vec3 v1, vec3 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL

WEMDEF int wem_vec3_matches(vec3 v1, vec3 v2);
WEMDEF int wem_vec3_inRange(vec3 v1, vec3 v2, float range);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_vec3_print(vec3 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  OPERATORS

#ifdef __cplusplus
WEMDEF vec3 operator+(vec3 v1, vec3 v2);
WEMDEF void operator+=(vec3 &v1, vec3 v2);
WEMDEF vec3 operator+(vec3 v, float f);
WEMDEF void operator+=(vec3 &v, float f);

WEMDEF vec3 operator-(vec3 v1, vec3 v2);
WEMDEF void operator-=(vec3 &v1, vec3 v2);
WEMDEF vec3 operator-(vec3 v, float f);
WEMDEF void operator-=(vec3 &v, float f);

WEMDEF vec3 operator*(vec3 v1, vec3 v2);
WEMDEF void operator*=(vec3 &v1, vec3 v2);
WEMDEF vec3 operator*(vec3 v, float f);
WEMDEF void operator*=(vec3 &v, float f);

WEMDEF vec3 operator/(vec3 v1, vec3 v2);
WEMDEF void operator/=(vec3 &v1, vec3 v2);

WEMDEF vec3 operator-(vec3 v);
#endif

#ifdef WEM_IMPLEMENTATION
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ALLOCATION

vec3 wem_vec3(float x, float y, float z) {
    vec3 out = {x, y, z};
    return out;
}
vec3 wem_vec3_1f(float f) {
    vec3 out = {f, f, f};
    return out;
}
vec3 wem_vec3_zero() {
    vec3 out = {0, 0, 0};
    return out;
}

vec3 *wem_vec3_allocNew(float x, float y, float z) {
    vec3 *out = (vec3*)malloc(sizeof(vec3));
    out->x = x; out->y = y;
    return out;
}
vec3 *wem_vec3_alloc(vec3 vec) {
    vec3 *out = (vec3*)malloc(sizeof(vec3));
    *out = vec;
    return out;
}
void wem_vec3_setVec(vec3 *h, vec3 vec) {
    *h = vec;
}
void wem_vec3_free(vec3 **h) {
    free(*h);
    *h = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CONVERSION

vec2 wem_vec3_toVec2(vec3 v) {
    vec2 out = {v.x, v.y};
    return out;
}
vec4 wem_vec3_toVec4(vec3 v) {
    vec4 out = {v.x, v.y, v.z, 1};
    return out;
}
vec2 wem_vec3_homogenous(vec3 v) {
    vec2 out = {v.x / v.z, v.y / v.z};
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADDITION

vec3 wem_vec3_add(vec3 v1, vec3 v2) {
    v1.x += v2.x; v1.y += v2.y; v1.z += v2.z;
    return v1;
}
vec3 wem_vec3_add3f(vec3 v, float x, float y, float z) {
    v.x += x; v.y += y; v.z += z;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SUBTRACTION

vec3 wem_vec3_sub(vec3 v1, vec3 v2) {
    v1.x -= v2.x; v1.y -= v2.y; v1.z -= v2.z;
    return v1;
}
vec3 wem_vec3_sub3f(vec3 v, float x, float y, float z) {
    v.x -= x; v.y -= y; v.z -= z;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MULTIPLICATION

vec3 wem_vec3_mul(vec3 v1, vec3 v2) {
    v1.x *= v2.x; v1.y *= v2.y; v1.z *= v2.z;
    return v1;
}
vec3 wem_vec3_mul3f(vec3 v, float x, float y, float z) {
    v.x *= x; v.y *= y; v.z *= z;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DIVISION

vec3 wem_vec3_div(vec3 v1, vec3 v2) {
    v1.x /= v2.x; v1.y /= v2.y; v1.z /= v2.z;
    return v1;
}
vec3 wem_vec3_div3f(vec3 v, float x, float y, float z) {
    v.x /= x; v.y /= y; v.z /= z;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SCALE

vec3 wem_vec3_scale(vec3 v, float scale) {
    v.x *= scale; v.y *= scale; v.z *= scale;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

vec3 wem_vec3_inv(vec3 v) {
    v.x = -v.x; v.y = -v.y; v.z = -v.z;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

float wem_vec3_sqrMagnitude(vec3 v) {
    return POW2(v.x) + POW2(v.y) + POW2(v.z);
}
float wem_vec3_magnitude(vec3 v) {
    return sqrt(wem_vec3_sqrMagnitude(v));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

vec3 wem_vec3_norm(vec3 v) {
    float l = wem_vec3_magnitude(v);
    v.x /= l; v.y /= l; v.z /= l;
    return v;
}
vec3 wem_vec3_norm3f(float x, float y, float z) {
    float l = sqrt(POW2(x) + POW2(y) + POW2(z));
    vec3 out = {x / l, y / l, z / l};
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

float wem_vec3_dot(vec3 v1, vec3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
float wem_vec3_dotN(vec3 v1, vec3 v2) {
    return wem_vec3_dot(wem_vec3_norm(v1), wem_vec3_norm(v2));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS

vec3 wem_vec3_cross(vec3 v1, vec3 v2) {
    vec3 out = {v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x
                };
    return out;
}
vec3 wem_vec3_crossN(vec3 v1, vec3 v2) {
    return wem_vec3_norm(wem_vec3_cross(v1, v2));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

vec3 wem_vec3_lerp(vec3 v1, vec3 v2, float t) {
    vec3 out = wem_vec3_add(wem_vec3_scale(v1, 1.0f - t), wem_vec3_scale(v2, t));
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE

float wem_vec3_angleInRad(vec3 v1, vec3 v2) {
    float dot = wem_vec3_dotN(v1, v2);
    return acos(dot);
} 
float wem_vec3_angleInDeg(vec3 v1, vec3 v2) {
    return wem_vec3_angleInRad(v1, v2) * RAD2DEG; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL

int wem_vec3_matches(vec3 v1, vec3 v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}
int wem_vec3_inRange(vec3 v1, vec3 v2, float range) {
    vec3 dir = wem_vec3_sub(v2, v1);
    return wem_vec3_sqrMagnitude(dir) <= POW2(range);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

void wem_vec3_print(vec3 v) {
    printf("vec3(%f, %f, %f)\n", v.x, v.y, v.z);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  OPERATORS

#ifdef __cplusplus
vec3 operator+(vec3 v1, vec3 v2) { return wem_vec3_add(v1, v2); }
void operator+=(vec3 &v1, vec3 v2) { v1 = wem_vec3_add(v1, v2); }
vec3 operator+(vec3 v, float f) { return wem_vec3_add3f(v, f, f, f); }
void operator+=(vec3 &v, float f) { v = wem_vec3_add3f(v, f, f, f); }

vec3 operator-(vec3 v1, vec3 v2) { return wem_vec3_sub(v1, v2); }
void operator-=(vec3 &v1, vec3 v2) { v1 = wem_vec3_sub(v1, v2); }
vec3 operator-(vec3 v, float f) { return wem_vec3_sub3f(v, f, f, f); }
void operator-=(vec3 &v, float f) { v = wem_vec3_sub3f(v, f, f, f); }

vec3 operator*(vec3 v1, vec3 v2) { return wem_vec3_mul(v1, v2); }
void operator*=(vec3 &v1, vec3 v2) { v1 = wem_vec3_mul(v1, v2); }
vec3 operator*(vec3 v, float f) { return wem_vec3_scale(v, f); }
void operator*=(vec3 &v, float f) { v = wem_vec3_scale(v, f); }

vec3 operator/(vec3 v1, vec3 v2) { return wem_vec3_div(v1, v2); }
void operator/=(vec3 &v1, vec3 v2) { v1 = wem_vec3_div(v1, v2); }

vec3 operator-(vec3 v) { return wem_vec3_inv(v); }
#endif

#endif
#endif