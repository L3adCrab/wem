#ifndef wem_vec4_h
#define wem_vec4_h

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

WEMDEF vec4 wem_vec4(float x, float y, float z, float w) {
    vec4 out = {x, y, z, w};
    return out;
}
WEMDEF vec4 wem_vec4_1f(float f) {
    vec4 out = {f, f, f, f};
    return out;
}
WEMDEF vec4 wem_vec4_zero() {
    vec4 out = {0, 0, 0, 0};
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CONVERSION

WEMDEF vec2 wem_vec4_toVec2(vec4 v) {
    vec2 out = {v.x, v.y};
    return out;
}
WEMDEF vec3 wem_vec4_toVec3(vec4 v) {
    vec3 out = {v.x, v.y, v.z};
    return out;
}
WEMDEF vec3 wem_vec4_homogenous(vec4 v) {
    vec3 out = {v.x / v.w, v.y / v.w, v.z / v.w};
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADDITION

WEMDEF vec4 wem_vec4_add(vec4 v1, vec4 v2) {
    v1.x += v2.x; v1.y += v2.y; v1.z += v2.z; v1.w += v2.w;
    return v1;
}
WEMDEF vec4 wem_vec4_add4f(vec4 v, float x, float y, float z, float w) {
    v.x += x; v.y += y; v.z += z; v.w += w;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SUBTRACTION

WEMDEF vec4 wem_vec4_sub(vec4 v1, vec4 v2) {
    v1.x -= v2.x; v1.y -= v2.y; v1.z -= v2.z; v1.w -= v2.w;
    return v1;
}
WEMDEF vec4 wem_vec4_sub4f(vec4 v, float x, float y, float z, float w) {
    v.x -= x; v.y -= y; v.z -= z; v.w -= w;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MULTIPLICATION

WEMDEF vec4 wem_vec4_mul(vec4 v1, vec4 v2) {
    v1.x *= v2.x; v1.y *= v2.y; v1.z *= v2.z; v1.w *= v2.w;
    return v1;
}
WEMDEF vec4 wem_vec4_mul4f(vec4 v, float x, float y, float z, float w) {
    v.x *= x; v.y *= y; v.z *= z; v.w *= w;
    return v;
}
WEMDEF vec4 wem_vec4_mulMat4(vec4 v, mat4 m) {
    vec4 out = {
            v.x * m.v[0] + v.y * m.v[4] + v.z * m.v[8] + v.w * m.v[12],
            v.x * m.v[1] + v.y * m.v[5] + v.z * m.v[9] + v.w * m.v[13],
            v.x * m.v[2] + v.y * m.v[6] + v.z * m.v[10] + v.w * m.v[14],
            v.x * m.v[3] + v.y * m.v[7] + v.z * m.v[11] + v.w * m.v[15]
        };
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DIVISION

WEMDEF vec4 wem_vec4_div(vec4 v1, vec4 v2) {
    v1.x /= v2.x; v1.y /= v2.y; v1.z /= v2.z; v1.w /= v2.w;
    return v1;
}
WEMDEF vec4 wem_vec4_div4f(vec4 v, float x, float y, float z, float w) {
    v.x /= x; v.y /= y; v.z /= z; v.w /= w;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SCALE

WEMDEF vec4 wem_vec4_scale(vec4 v, float scale) {
    v.x *= scale; v.y *= scale; v.z *= scale; v.w *= scale;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

WEMDEF vec4 wem_vec4_inv(vec4 v) {
    v.x = -v.x; v.y = -v.y; v.z = -v.z; v.w = -v.w;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

WEMDEF float wem_vec4_sqrMagnitude(vec4 v) {
    return POW2(v.x) + POW2(v.y) + POW2(v.z) + POW2(v.w);
}
WEMDEF float wem_vec4_magnitude(vec4 v) {
    return sqrt(wem_vec4_sqrMagnitude(v));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

WEMDEF vec4 wem_vec4_norm(vec4 v) {
    float l = wem_vec4_magnitude(v);
    v.x /= l; v.y /= l; v.z /= l; v.w /= l;
    return v;
}
WEMDEF vec4 wem_vec4_norm4f(float x, float y, float z, float w) {
    float l = sqrt(POW2(x) + POW2(y) + POW2(z) + POW2(w));
    vec4 out = {x / l, y / l, z / l, w / l};
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

WEMDEF float wem_vec4_dot(vec4 v1, vec4 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}
WEMDEF float wem_vec4_dotN(vec4 v1, vec4 v2) {
    return wem_vec4_dot(wem_vec4_norm(v1), wem_vec4_norm(v2));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS

WEMDEF vec4 wem_vec4_cross(vec4 v1, vec4 v2) {
    vec4 out = {v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x,
                1};
    return out;
}
WEMDEF vec4 wem_vec4_crossN(vec4 v1, vec4 v2) {
    v1 = wem_vec4_norm(v1); v2 = wem_vec4_norm(v2);
    vec4 out = {v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x,
                1};
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

WEMDEF vec4 wem_vec4_lerp(vec4 v1, vec4 v2, float t) {
    vec4 out = wem_vec4_add(wem_vec4_scale(v1, 1.0f - t), wem_vec4_scale(v2, t));
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE

float wem_vec4_angleInRad(vec4 v1, vec4 v2) {
    float dot = wem_vec4_dotN(v1, v2);
    return acos(dot);
}
float wem_vec4_angleInDeg(vec4 v1, vec4 v2) {
    return wem_vec4_angleInRad(v1, v2) * RAD2DEG; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL

WEMDEF int wem_vec4_matches(vec4 v1, vec4 v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}
WEMDEF int wem_vec4_inRange(vec4 v1, vec4 v2, float range) {
    vec4 dir = wem_vec4_sub(v2, v1);
    return wem_vec4_sqrMagnitude(dir) <= POW2(range);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_vec4_print(vec4 v) {
    printf("vec4(%f, %f, %f, %f)\n", v.x, v.y, v.z, v.w);
}

#endif