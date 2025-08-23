#ifndef wem_vec3_h
#define wem_vec3_h

#ifndef WEMDEF
    #ifdef WEM_EXTERN
    #define WEMDEF extern
    #else
    #define WEMDEF static
    #define WEM_IMPLEMENTATION
    #endif
#endif

#ifdef WEM_IMPLEMENTATION

#include "macros.h"
#include "datatypes.h"

#include <math.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ALLOCATION

WEMDEF vec3 wem_vec3(float x, float y, float z) {
    vec3 out = {x, y, z};
    return out;
}
WEMDEF vec3 wem_vec3_1f(float f) {
    vec3 out = {f, f, f};
    return out;
}
WEMDEF vec3 wem_vec3_zero() {
    vec3 out = {0, 0, 0};
    return out;
}

WEMDEF vec3 *wem_vec3_allocNew(float x, float y, float z) {
    vec3 *out = (vec3*)malloc(sizeof(vec3));
    out->x = x; out->y = y;
    return out;
}
WEMDEF vec3 *wem_vec3_alloc(vec3 vec) {
    vec3 *out = (vec3*)malloc(sizeof(vec3));
    *out = vec;
    return out;
}
WEMDEF void wem_vec3_setVec(vec3 *h, vec3 vec) {
    *h = vec;
}
WEMDEF void wem_vec3_free(vec3 **h) {
    free(*h);
    *h = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CONVERSION

WEMDEF vec2 wem_vec3_toVec2(vec3 v) {
    vec2 out = {v.x, v.y};
    return out;
}
WEMDEF vec4 wem_vec3_toVec4(vec3 v) {
    vec4 out = {v.x, v.y, v.z, 1};
    return out;
}
WEMDEF vec2 wem_vec3_homogenous(vec3 v) {
    vec2 out = {v.x / v.z, v.y / v.z};
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADDITION

WEMDEF vec3 wem_vec3_add(vec3 v1, vec3 v2) {
    v1.x += v2.x; v1.y += v2.y; v1.z += v2.z;
    return v1;
}
WEMDEF vec3 wem_vec3_add3f(vec3 v, float x, float y, float z) {
    v.x += x; v.y += y; v.z += z;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SUBTRACTION

WEMDEF vec3 wem_vec3_sub(vec3 v1, vec3 v2) {
    v1.x -= v2.x; v1.y -= v2.y; v1.z -= v2.z;
    return v1;
}
WEMDEF vec3 wem_vec3_sub3f(vec3 v, float x, float y, float z) {
    v.x -= x; v.y -= y; v.z -= z;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MULTIPLICATION

WEMDEF vec3 wem_vec3_mul(vec3 v1, vec3 v2) {
    v1.x *= v2.x; v1.y *= v2.y; v1.z *= v2.z;
    return v1;
}
WEMDEF vec3 wem_vec3_mul3f(vec3 v, float x, float y, float z) {
    v.x *= x; v.y *= y; v.z *= z;
    return v;
}
// WEMDEF vec3 wem_vec3_mulMat4(vec3 v, mat4 m) {
//     vec3 out    = {0};
//     float *outf = (float*)&out;
//     float *vf   = (float*)&v;
//     for (int y = 0; y < 4; y++) {
//         for (int x = 0; x < 4; x++) {
//             outf[y] += vf[x] * m.v[4 * x + y];  
//         }
//     }
//     out = *(vec3*)outf;
//     return out;
// }
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DIVISION

WEMDEF vec3 wem_vec3_div(vec3 v1, vec3 v2) {
    v1.x /= v2.x; v1.y /= v2.y; v1.z /= v2.z;
    return v1;
}
WEMDEF vec3 wem_vec3_div3f(vec3 v, float x, float y, float z) {
    v.x /= x; v.y /= y; v.z /= z;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SCALE

WEMDEF vec3 wem_vec3_scale(vec3 v, float scale) {
    v.x *= scale; v.y *= scale; v.z *= scale;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

WEMDEF vec3 wem_vec3_inv(vec3 v) {
    v.x = -v.x; v.y = -v.y; v.z = -v.z;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

WEMDEF float wem_vec3_sqrMagnitude(vec3 v) {
    return POW2(v.x) + POW2(v.y) + POW2(v.z);
}
WEMDEF float wem_vec3_magnitude(vec3 v) {
    return sqrt(wem_vec3_sqrMagnitude(v));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

WEMDEF vec3 wem_vec3_norm(vec3 v) {
    float l = wem_vec3_magnitude(v);
    v.x /= l; v.y /= l; v.z /= l;
    return v;
}
WEMDEF vec3 wem_vec3_norm3f(float x, float y, float z) {
    float l = sqrt(POW2(x) + POW2(y) + POW2(z));
    vec3 out = {x / l, y / l, z / l};
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

WEMDEF float wem_vec3_dot(vec3 v1, vec3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
WEMDEF float wem_vec3_dotN(vec3 v1, vec3 v2) {
    return wem_vec3_dot(wem_vec3_norm(v1), wem_vec3_norm(v2));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS

WEMDEF vec3 wem_vec3_cross(vec3 v1, vec3 v2) {
    vec3 out = {v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x
                };
    return out;
}
WEMDEF vec3 wem_vec3_crossN(vec3 v1, vec3 v2) {
    // v1 = wem_vec3_norm(v1); v2 = wem_vec3_norm(v2);
    // vec3 out = {v1.y * v2.z - v1.z * v2.y,
    //             v1.z * v2.x - v1.x * v2.z,
    //             v1.x * v2.y - v1.y * v2.x
    //             };
    // return out;
    return wem_vec3_norm(wem_vec3_cross(v1, v2));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

WEMDEF vec3 wem_vec3_lerp(vec3 v1, vec3 v2, float t) {
    vec3 out = wem_vec3_add(wem_vec3_scale(v1, 1.0f - t), wem_vec3_scale(v2, t));
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE

WEMDEF float wem_vec3_angleInRad(vec3 v1, vec3 v2) {
    float dot = wem_vec3_dotN(v1, v2);
    return acos(dot);
} 
WEMDEF float wem_vec3_angleInDeg(vec3 v1, vec3 v2) {
    return wem_vec3_angleInRad(v1, v2) * RAD2DEG; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL

WEMDEF int wem_vec3_matches(vec3 v1, vec3 v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}
WEMDEF int wem_vec3_inRange(vec3 v1, vec3 v2, float range) {
    vec3 dir = wem_vec3_sub(v2, v1);
    return wem_vec3_sqrMagnitude(dir) <= POW2(range);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_vec3_print(vec3 v) {
    printf("vec3(%f, %f, %f)\n", v.x, v.y, v.z);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  OPERATORS

#ifdef __cplusplus
WEMDEF vec3 operator+(vec3 v1, vec3 v2) { return wem_vec3_add(v1, v2); }
WEMDEF void operator+=(vec3 &v1, vec3 v2) { v1 = wem_vec3_add(v1, v2); }
WEMDEF vec3 operator+(vec3 v, float f) { return wem_vec3_add3f(v, f, f, f); }
WEMDEF void operator+=(vec3 &v, float f) { v = wem_vec3_add3f(v, f, f, f); }

WEMDEF vec3 operator-(vec3 v1, vec3 v2) { return wem_vec3_sub(v1, v2); }
WEMDEF void operator-=(vec3 &v1, vec3 v2) { v1 = wem_vec3_sub(v1, v2); }
WEMDEF vec3 operator-(vec3 v, float f) { return wem_vec3_sub3f(v, f, f, f); }
WEMDEF void operator-=(vec3 &v, float f) { v = wem_vec3_sub3f(v, f, f, f); }

WEMDEF vec3 operator*(vec3 v1, vec3 v2) { return wem_vec3_mul(v1, v2); }
WEMDEF void operator*=(vec3 &v1, vec3 v2) { v1 = wem_vec3_mul(v1, v2); }
WEMDEF vec3 operator*(vec3 v, float f) { return wem_vec3_scale(v, f); }
WEMDEF void operator*=(vec3 &v, float f) { v = wem_vec3_scale(v, f); }

WEMDEF vec3 operator/(vec3 v1, vec3 v2) { return wem_vec3_div(v1, v2); }
WEMDEF void operator/=(vec3 &v1, vec3 v2) { v1 = wem_vec3_div(v1, v2); }

WEMDEF vec3 operator-(vec3 v) { return wem_vec3_inv(v); }
#endif

#endif
#endif