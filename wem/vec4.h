#ifndef wem_vec4_h
#define wem_vec4_h

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
//  ALLOCATION

WEMDEF vec4 wem_vec4(float x, float y, float z, float w);
WEMDEF vec4 wem_vec4_1f(float f);
WEMDEF vec4 wem_vec4_zero();

WEMDEF vec4 *wem_vec4_allocNew(float x, float y, float z, float w);
WEMDEF vec4 *wem_vec4_alloc(vec4 vec);
WEMDEF void wem_vec4_setVec(vec4 *h, vec4 vec);
WEMDEF void wem_vec4_free(vec4 **h);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CONVERSION

WEMDEF vec2 wem_vec4_toVec2(vec4 v);
WEMDEF vec3 wem_vec4_toVec3(vec4 v);
WEMDEF vec3 wem_vec4_homogenous(vec4 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADDITION

WEMDEF vec4 wem_vec4_add(vec4 v1, vec4 v2);
WEMDEF vec4 wem_vec4_add4f(vec4 v, float x, float y, float z, float w);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SUBTRACTION

WEMDEF vec4 wem_vec4_sub(vec4 v1, vec4 v2);
WEMDEF vec4 wem_vec4_sub4f(vec4 v, float x, float y, float z, float w);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MULTIPLICATION

WEMDEF vec4 wem_vec4_mul(vec4 v1, vec4 v2);
WEMDEF vec4 wem_vec4_mul4f(vec4 v, float x, float y, float z, float w);
WEMDEF vec4 wem_vec4_mulMat4(vec4 v, mat4 m);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DIVISION

WEMDEF vec4 wem_vec4_div(vec4 v1, vec4 v2);
WEMDEF vec4 wem_vec4_div4f(vec4 v, float x, float y, float z, float w);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SCALE

WEMDEF vec4 wem_vec4_scale(vec4 v, float scale);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

WEMDEF vec4 wem_vec4_inv(vec4 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

WEMDEF float wem_vec4_sqrMagnitude(vec4 v);
WEMDEF float wem_vec4_magnitude(vec4 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

WEMDEF vec4 wem_vec4_norm(vec4 v);
WEMDEF vec4 wem_vec4_norm4f(float x, float y, float z, float w);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

WEMDEF float wem_vec4_dot(vec4 v1, vec4 v2);
WEMDEF float wem_vec4_dotN(vec4 v1, vec4 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS

WEMDEF vec4 wem_vec4_cross(vec4 v1, vec4 v2);
WEMDEF vec4 wem_vec4_crossN(vec4 v1, vec4 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

WEMDEF vec4 wem_vec4_lerp(vec4 v1, vec4 v2, float t);
WEMDEF vec4 wem_vec4_smoothstep(vec4 v1, vec4 v2, float t);
WEMDEF vec4 wem_vec4_smootherstep(vec4 v1, vec4 v2, float t);
WEMDEF vec4 wem_vec4_smoothstep_inverse(vec4 v1, vec4 v2, float t);
WEMDEF vec4 wem_vec4_smoothDamp(vec4 from, vec4 to, vec4 *velocity, float maxSpeed, float smoothTime, float timeDelta);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE

float wem_vec4_angleInRad(vec4 v1, vec4 v2);
float wem_vec4_angleInDeg(vec4 v1, vec4 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL

WEMDEF int wem_vec4_matches(vec4 v1, vec4 v2);
WEMDEF int wem_vec4_inRange(vec4 v1, vec4 v2, float range);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_vec4_print(vec4 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  OPERATORS

#ifdef __cplusplus
WEMDEF vec4 operator+(vec4 v1, vec4 v2);
WEMDEF void operator+=(vec4 &v1, vec4 v2);
WEMDEF vec4 operator+(vec4 v, float f);
WEMDEF void operator+=(vec4 &v, float f);

WEMDEF vec4 operator-(vec4 v1, vec4 v2);
WEMDEF void operator-=(vec4 &v1, vec4 v2);
WEMDEF vec4 operator-(vec4 v, float f);
WEMDEF void operator-=(vec4 &v, float f);

WEMDEF vec4 operator*(vec4 v1, vec4 v2);
WEMDEF void operator*=(vec4 &v1, vec4 v2);
WEMDEF vec4 operator*(vec4 v, float f);
WEMDEF void operator*=(vec4 &v, float f);

WEMDEF vec4 operator*(vec4 v, mat4 m);
WEMDEF void operator*(vec4 &v, mat4 m);

WEMDEF vec4 operator/(vec4 v1, vec4 v2);
WEMDEF void operator/=(vec4 &v1, vec4 v2);

WEMDEF vec4 operator-(vec4 v);
#endif

#ifdef WEM_IMPLEMENTATION

#include "macros.h"
#include "mathf.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ALLOCATION

vec4 wem_vec4(float x, float y, float z, float w) {
    vec4 out = {x, y, z, w};
    return out;
}
vec4 wem_vec4_1f(float f) {
    vec4 out = {f, f, f, f};
    return out;
}
vec4 wem_vec4_zero() {
    vec4 out = {0, 0, 0, 0};
    return out;
}

vec4 *wem_vec4_allocNew(float x, float y, float z, float w) {
    vec4 *out = (vec4*)malloc(sizeof(vec4));
    out->x = x; out->y = y; out->z = z; out->w = w;
    return out;
}
vec4 *wem_vec4_alloc(vec4 vec) {
    vec4 *out = (vec4*)malloc(sizeof(vec4));
    *out = vec;
    return out;
}
void wem_vec4_setVec(vec4 *h, vec4 vec) {
    *h = vec;
}
void wem_vec4_free(vec4 **h) {
    free(*h);
    *h = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CONVERSION

vec2 wem_vec4_toVec2(vec4 v) {
    vec2 out = {v.x, v.y};
    return out;
}
vec3 wem_vec4_toVec3(vec4 v) {
    vec3 out = {v.x, v.y, v.z};
    return out;
}
vec3 wem_vec4_homogenous(vec4 v) {
    vec3 out = {v.x / v.w, v.y / v.w, v.z / v.w};
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADDITION

vec4 wem_vec4_add(vec4 v1, vec4 v2) {
    v1.x += v2.x; v1.y += v2.y; v1.z += v2.z; v1.w += v2.w;
    return v1;
}
vec4 wem_vec4_add4f(vec4 v, float x, float y, float z, float w) {
    v.x += x; v.y += y; v.z += z; v.w += w;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SUBTRACTION

vec4 wem_vec4_sub(vec4 v1, vec4 v2) {
    v1.x -= v2.x; v1.y -= v2.y; v1.z -= v2.z; v1.w -= v2.w;
    return v1;
}
vec4 wem_vec4_sub4f(vec4 v, float x, float y, float z, float w) {
    v.x -= x; v.y -= y; v.z -= z; v.w -= w;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MULTIPLICATION

vec4 wem_vec4_mul(vec4 v1, vec4 v2) {
    v1.x *= v2.x; v1.y *= v2.y; v1.z *= v2.z; v1.w *= v2.w;
    return v1;
}
vec4 wem_vec4_mul4f(vec4 v, float x, float y, float z, float w) {
    v.x *= x; v.y *= y; v.z *= z; v.w *= w;
    return v;
}
vec4 wem_vec4_mulMat4(vec4 v, mat4 m) {
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

vec4 wem_vec4_div(vec4 v1, vec4 v2) {
    v1.x /= v2.x; v1.y /= v2.y; v1.z /= v2.z; v1.w /= v2.w;
    return v1;
}
vec4 wem_vec4_div4f(vec4 v, float x, float y, float z, float w) {
    v.x /= x; v.y /= y; v.z /= z; v.w /= w;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SCALE

vec4 wem_vec4_scale(vec4 v, float scale) {
    v.x *= scale; v.y *= scale; v.z *= scale; v.w *= scale;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

vec4 wem_vec4_inv(vec4 v) {
    v.x = -v.x; v.y = -v.y; v.z = -v.z; v.w = -v.w;
    return v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

float wem_vec4_sqrMagnitude(vec4 v) {
    return POW2(v.x) + POW2(v.y) + POW2(v.z) + POW2(v.w);
}
float wem_vec4_magnitude(vec4 v) {
    return sqrt(wem_vec4_sqrMagnitude(v));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

vec4 wem_vec4_norm(vec4 v) {
    float l = wem_vec4_magnitude(v);
    v.x /= l; v.y /= l; v.z /= l; v.w /= l;
    return v;
}
vec4 wem_vec4_norm4f(float x, float y, float z, float w) {
    float l = sqrt(POW2(x) + POW2(y) + POW2(z) + POW2(w));
    vec4 out = {x / l, y / l, z / l, w / l};
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

float wem_vec4_dot(vec4 v1, vec4 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}
float wem_vec4_dotN(vec4 v1, vec4 v2) {
    return wem_vec4_dot(wem_vec4_norm(v1), wem_vec4_norm(v2));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS

vec4 wem_vec4_cross(vec4 v1, vec4 v2) {
    vec4 out = {v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x,
                1};
    return out;
}
vec4 wem_vec4_crossN(vec4 v1, vec4 v2) {
    v1 = wem_vec4_norm(v1); v2 = wem_vec4_norm(v2);
    vec4 out = {v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x,
                1};
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

vec4 wem_vec4_lerp(vec4 v1, vec4 v2, float t) {
    vec4 out = wem_vec4_add(wem_vec4_scale(v1, 1.0f - t), wem_vec4_scale(v2, t));
    return out;
}
vec4 wem_vec4_smoothstep(vec4 v1, vec4 v2, float t) {
    t = CLAMP(t, 0, 1);
    float x = wem_smoothstep(v1.x, v2.x, t);
    float y = wem_smoothstep(v1.y, v2.y, t);
    float z = wem_smoothstep(v1.z, v2.z, t);
    float w = wem_smoothstep(v1.w, v2.w, t);
    return (vec4){x, y, z, w};
}
vec4 wem_vec4_smootherstep(vec4 v1, vec4 v2, float t) {
    t = CLAMP(t, 0, 1);
    float x = wem_smootherstep(v1.x, v2.x, t);
    float y = wem_smootherstep(v1.y, v2.y, t);
    float z = wem_smootherstep(v1.z, v2.z, t);
    float w = wem_smootherstep(v1.w, v2.w, t);
    return (vec4){x, y, z, w};
}
vec4 wem_vec4_smoothstep_inverse(vec4 v1, vec4 v2, float t) {
    t = CLAMP(t, 0, 1);
    float x = wem_smoothstep_Inverse(v1.x, v2.x, t);
    float y = wem_smoothstep_Inverse(v1.y, v2.y, t);
    float z = wem_smoothstep_Inverse(v1.z, v2.z, t);
    float w = wem_smoothstep_Inverse(v1.w, v2.w, t);
    return (vec4){x, y, z, w};
}
vec4 wem_vec4_smoothDamp(vec4 from, vec4 to, vec4 *velocity, float maxSpeed, float smoothTime, float timeDelta) {
    vec4 out = wem_vec4_zero();

    float omega = 2.0f / smoothTime;
    float x     = omega * timeDelta;
    float exp   = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);
    
    vec4 change = wem_vec4_sub(from, to);
    vec4 ogTo   = to;

    float maxChange     = maxSpeed * smoothTime;
    float maxChangeSqr  = maxChange * maxChange;
    float sqrMag        = wem_vec4_sqrMagnitude(change);
    if (sqrMag > maxChangeSqr) {
        float mag = sqrtf(sqrMag);
        change.x = change.x / mag * maxChange;
        change.y = change.y / mag * maxChange;
        change.z = change.z / mag * maxChange;
        change.w = change.w / mag * maxChange;
    }

    to = wem_vec4_sub(from, change);

    vec4 temp = (vec4){
        (velocity->x + omega * change.x) * timeDelta,
        (velocity->y + omega * change.y) * timeDelta,
        (velocity->z + omega * change.z) * timeDelta,
        (velocity->w + omega * change.w) * timeDelta
    };

    velocity->x = (velocity->x - omega * temp.x) * exp;
    velocity->y = (velocity->y - omega * temp.y) * exp;
    velocity->z = (velocity->z - omega * temp.z) * exp;
    velocity->w = (velocity->w - omega * temp.w) * exp;

    out.x = to.x + (change.x + temp.x) * exp;
    out.y = to.y + (change.y + temp.y) * exp;
    out.z = to.z + (change.z + temp.z) * exp;
    out.w = to.w + (change.w + temp.w) * exp;

    vec4 ogMinusCurrent = wem_vec4_sub(ogTo, from);
    vec4 outMinusOg     = wem_vec4_sub(out, ogTo);

    if (wem_vec4_dot(ogMinusCurrent, outMinusOg) > 0) {
        out = ogTo;
        velocity->x = (out.x - ogTo.x) / timeDelta;
        velocity->y = (out.y - ogTo.y) / timeDelta;
        velocity->z = (out.z - ogTo.z) / timeDelta;
        velocity->w = (out.w - ogTo.w) / timeDelta;
    }

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

int wem_vec4_matches(vec4 v1, vec4 v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}
int wem_vec4_inRange(vec4 v1, vec4 v2, float range) {
    vec4 dir = wem_vec4_sub(v2, v1);
    return wem_vec4_sqrMagnitude(dir) <= POW2(range);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

void wem_vec4_print(vec4 v) {
    printf("vec4(%f, %f, %f, %f)\n", v.x, v.y, v.z, v.w);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  OPERATORS

#ifdef __cplusplus
vec4 operator+(vec4 v1, vec4 v2) { return wem_vec4_add(v1, v2); }
void operator+=(vec4 &v1, vec4 v2) { v1 = wem_vec4_add(v1, v2); }
vec4 operator+(vec4 v, float f) { return wem_vec4_add4f(v, f, f, f, f); }
void operator+=(vec4 &v, float f) { v = wem_vec4_add4f(v, f, f, f, f); }

vec4 operator-(vec4 v1, vec4 v2) { return wem_vec4_sub(v1, v2); }
void operator-=(vec4 &v1, vec4 v2) { v1 = wem_vec4_sub(v1, v2); }
vec4 operator-(vec4 v, float f) { return wem_vec4_sub4f(v, f, f, f, f); }
void operator-=(vec4 &v, float f) { v = wem_vec4_sub4f(v, f, f, f, f); }

vec4 operator*(vec4 v1, vec4 v2) { return wem_vec4_mul(v1, v2); }
void operator*=(vec4 &v1, vec4 v2) { v1 = wem_vec4_mul(v1, v2); }
vec4 operator*(vec4 v, float f) { return wem_vec4_scale(v, f); }
void operator*=(vec4 &v, float f) { v = wem_vec4_scale(v, f); }

vec4 operator*(vec4 v, mat4 m) { return wem_vec4_mulMat4(v, m); }
void operator*(vec4 &v, mat4 m) { v = wem_vec4_mulMat4(v, m); }

vec4 operator/(vec4 v1, vec4 v2) { return wem_vec4_div(v1, v2); }
void operator/=(vec4 &v1, vec4 v2) { v1 = wem_vec4_div(v1, v2); }

vec4 operator-(vec4 v) { return wem_vec4_inv(v); }
#endif

#endif
#endif