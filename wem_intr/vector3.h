#ifndef WEM_INTRINSICS_VECTOR_3_H
#define WEM_INTRINSICS_VECTOR_3_H

#include "datatypes.h"

#define WEMDEF extern

WEMDEF void wem_Vec3_set(Vec3 out, float x, float y, float z);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC

WEMDEF void wem_Vec3_add(Vec3 out, const Vec3 v1, const Vec3 v2);
WEMDEF void wem_Vec3_sub(Vec3 out, const Vec3 v1, const Vec3 v2);
WEMDEF void wem_Vec3_mul(Vec3 out, const Vec3 v1, const Vec3 v2);
WEMDEF void wem_Vec3_div(Vec3 out, const Vec3 v1, const Vec3 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW

WEMDEF void wem_Vec3_add3f(Vec3 out, const Vec3 v, float x, float y, float z);
WEMDEF void wem_Vec3_sub3f(Vec3 out, const Vec3 v, float x, float y, float z);
WEMDEF void wem_Vec3_mul3f(Vec3 out, const Vec3 v, float x, float y, float z);
WEMDEF void wem_Vec3_div3f(Vec3 out, const Vec3 v, float x, float y, float z);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF

WEMDEF void wem_Vec3_add1f(Vec3 out, const Vec3 v, float val);
WEMDEF void wem_Vec3_sub1f(Vec3 out, const Vec3 v, float val);
WEMDEF void wem_Vec3_mul1f(Vec3 out, const Vec3 v, float val);
WEMDEF void wem_Vec3_div1f(Vec3 out, const Vec3 v, float val);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

WEMDEF float wem_Vec3_sqrMagnitude(const Vec3 v);
WEMDEF float wem_Vec3_magnitude(const Vec3 v);
WEMDEF void wem_Vec3_clampMagnitude(Vec3 out, const Vec3 v, float maxMagnitude);
////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

WEMDEF void wem_Vec3_norm(Vec3 out, const Vec3 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  POW2

WEMDEF void wem_Vec3_pow2(Vec3 out, const Vec3 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

WEMDEF float wem_Vec3_dot(const Vec3 v1, const Vec3 v2);
WEMDEF float wem_Vec3_dotN(const Vec3 v1, const Vec3 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

WEMDEF void wem_Vec3_inv(Vec3 out, const Vec3 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS

WEMDEF void wem_Vec3_cross(Vec3 out, const Vec3 v1, const Vec3 v2);
WEMDEF void wem_Vec3_crossN(Vec3 out, const Vec3 v1, const Vec3 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

WEMDEF void wem_Vec3_lerp(Vec3 out, const Vec3 from, const Vec3 to, float t);
WEMDEF void wem_Vec3_smoothstep(Vec3 out, const Vec3 from, const Vec3 to, float t);
WEMDEF void wem_Vec3_smootherstep(Vec3 out, const Vec3 from, const Vec3 to, float t);
WEMDEF void wem_Vec3_smoothstep_inverse(Vec3 out, const Vec3 from, const Vec3 to, float t);
WEMDEF void wem_Vec3_smoothDamp(Vec3 out, const Vec3 from, const Vec3 to, Vec3 velocity, float maxSpeed, float smoothTime, float timeDelta);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE

WEMDEF float wem_Vec3_angleInRad(const Vec3 v1, const Vec3 v2);
WEMDEF float wem_Vec3_angleInDeg(const Vec3 v1, const Vec3 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL

WEMDEF bool wem_Vec3_matches(const Vec3 v1, const Vec3 v2);
WEMDEF bool wem_Vec3_inRange(const Vec3 v1, const Vec3 v2, float range);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_Vec3_print(const Vec3 v);

#ifdef WEM_INTR_IMPLEMENTATION

#include <math.h>
#include <immintrin.h>

#include "vector.h"

void wem_Vec3_set(Vec3 out, float x, float y, float z) {
    out[0] = x; out[1] = y, out[2] = z, out[3] = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec3_add(Vec3 out, const Vec3 v1, const Vec3 v2) {
    wem_Vec_add(out, v1, v2);
}
void wem_Vec3_sub(Vec3 out, const Vec3 v1, const Vec3 v2) {
    wem_Vec_sub(out, v1, v2);
}
void wem_Vec3_mul(Vec3 out, const Vec3 v1, const Vec3 v2) {
    wem_Vec_mul(out, v1, v2);
}
void wem_Vec3_div(Vec3 out, const Vec3 v1, const Vec3 v2) {
    wem_Vec_div(out, v1, v2);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW

void wem_Vec3_add3f(Vec3 out, const Vec3 v, float x, float y, float z) {
    wem_Vec_add4f(out, v, x, y, z, 0);
}
void wem_Vec3_sub3f(Vec3 out, const Vec3 v, float x, float y, float z) {
    wem_Vec_sub4f(out, v, x, y, z, 0);
}
void wem_Vec3_mul3f(Vec3 out, const Vec3 v, float x, float y, float z) {
    wem_Vec_mul4f(out, v, x, y, z, 0);
}
void wem_Vec3_div3f(Vec3 out, const Vec3 v, float x, float y, float z) {
    wem_Vec_div4f(out, v, x, y, z, 1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec3_add1f(Vec3 out, const Vec3 v, float val) {
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set_ps(0, val, val, val);
    acc = _mm_add_ps(a, b);     //  v + f
    _mm_store_ps(out, acc);
}
void wem_Vec3_sub1f(Vec3 out, const Vec3 v, float val) {
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set_ps(0, val, val, val);
    acc = _mm_sub_ps(a, b);     //  v + f
    _mm_store_ps(out, acc);
}
void wem_Vec3_mul1f(Vec3 out, const Vec3 v, float val) {
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set_ps(0, val, val, val);
    acc = _mm_mul_ps(a, b);     //  v + f
    _mm_store_ps(out, acc);
}
void wem_Vec3_div1f(Vec3 out, const Vec3 v, float val) {
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set_ps(0, val, val, val);
    acc = _mm_div_ps(a, b);     //  v + f
    _mm_store_ps(out, acc);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vec3_sqrMagnitude(const Vec3 v) {
    return wem_Vec_sqrMagnitude(v);
}
float wem_Vec3_magnitude(const Vec3 v) {
    return wem_Vec_magnitude(v);
}
void wem_Vec3_clampMagnitude(Vec3 out, const Vec3 v, float maxMagnitude) {
    wem_Vec_clampMagnitude(out, v, maxMagnitude);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec3_norm(Vec3 out, const Vec3 v) {
    __m128 a, vP, acc;
    a = _mm_load_ps(v);
    vP = _mm_mul_ps(a, a);
    float mag = sqrtf(vP[0] + vP[1] + vP[2]);
    acc = _mm_div_ps(a, _mm_set_ps1(mag));
    _mm_store_ps(out, acc);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  POW2
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec3_pow2(Vec3 out, const Vec3 v) {
    wem_Vec_mul(out, v, v);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vec3_dot(const Vec3 v1, const Vec3 v2) {
    Vec out;
    wem_Vec_mul(out, v1, v2);
    return out[0] + out[1] + out[2];
}
float wem_Vec3_dotN(const Vec3 v1, const Vec3 v2) {
    Vec3 v1N, v2N;
    wem_Vec3_norm(v1N, v1); wem_Vec3_norm(v2N, v2);
    return wem_Vec3_dot(v1N, v2N);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec3_inv(Vec3 out, const Vec3 v) {
    wem_Vec_inv(out, v);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec3_cross(Vec3 out, const Vec3 v1, const Vec3 v2) {
    wem_Vec_cross(out, v1, v2);
}
void wem_Vec3_crossN(Vec3 out, const Vec3 v1, const Vec3 v2) {
    wem_Vec3_cross(out, v1, v2);
    return wem_Vec3_norm(out, out);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec3_lerp(Vec3 out, const Vec3 from, const Vec3 to, float t) {
    wem_Vec_lerp(out, from, to, t);
}
void wem_Vec3_smoothstep(Vec3 out, const Vec3 from, const Vec3 to, float t) {
    wem_Vec_smoothstep(out, from, to, t);
}
void wem_Vec3_smootherstep(Vec3 out, const Vec3 from, const Vec3 to, float t) {
    wem_Vec_smootherstep(out, from, to, t);
}
void wem_Vec3_smoothstep_inverse(Vec3 out, const Vec3 from, const Vec3 to, float t) {
    wem_Vec_smoothstep_inverse(out, from, to, t);
}
void wem_Vec3_smoothDamp(Vec3 out, const Vec3 from, const Vec3 to, Vec3 velocity, float maxSpeed, float smoothTime, float timeDelta) {
    wem_Vec_smoothDamp(out, from, to, velocity, maxSpeed, smoothTime, timeDelta);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vec3_angleInRad(const Vec3 v1, const Vec3 v2) {
    float dot = wem_Vec3_dotN(v1, v2);
    return acosf(dot);
}
float wem_Vec3_angleInDeg(const Vec3 v1, const Vec3 v2) {
    return wem_Vec3_angleInRad(v1, v2) * RAD2DEG; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool wem_Vec3_matches(const Vec3 v1, const Vec3 v2) {
    return wem_Vec_matches(v1, v2);
}
bool wem_Vec3_inRange(const Vec3 v1, const Vec3 v2, float range) {
    return wem_Vec_inRange(v1, v2, range);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec3_print(const Vec3 v) {
    printf("(%f %f %f %f)", v[0], v[1], v[2], v[3]);
}

#endif
#endif