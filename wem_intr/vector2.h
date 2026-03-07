#ifndef WEM_INTRINSICS_VECTOR_2_H
#define WEM_INTRINSICS_VECTOR_2_H

#include "datatypes.h"

#define WEMDEF extern

WEMDEF void wem_Vec2_set(Vec2 out, float x, float y);
WEMDEF void wem_Vec2_cpy(Vec2 out, const Vec2 v);
WEMDEF void wem_Vec2_set2F(Vec2 out, float *f2);
WEMDEF void wem_Vec2_to2F(float *f2, const Vec2 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC

WEMDEF void wem_Vec2_add(Vec2 out, const Vec2 v1, const Vec2 v2);
WEMDEF void wem_Vec2_sub(Vec2 out, const Vec2 v1, const Vec2 v2);
WEMDEF void wem_Vec2_mul(Vec2 out, const Vec2 v1, const Vec2 v2);
WEMDEF void wem_Vec2_div(Vec2 out, const Vec2 v1, const Vec2 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW

WEMDEF void wem_Vec2_add2f(Vec2 out, const Vec2 v, float x, float y);
WEMDEF void wem_Vec2_sub2f(Vec2 out, const Vec2 v, float x, float y);
WEMDEF void wem_Vec2_mul2f(Vec2 out, const Vec2 v, float x, float y);
WEMDEF void wem_Vec2_div2f(Vec2 out, const Vec2 v, float x, float y);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF

WEMDEF void wem_Vec2_add1f(Vec2 out, const Vec2 v, float val);
WEMDEF void wem_Vec2_sub1f(Vec2 out, const Vec2 v, float val);
WEMDEF void wem_Vec2_mul1f(Vec2 out, const Vec2 v, float val);
WEMDEF void wem_Vec2_div1f(Vec2 out, const Vec2 v, float val);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

WEMDEF float wem_Vec2_sqrMagnitude(const Vec2 v);
WEMDEF float wem_Vec2_magnitude(const Vec2 v);
WEMDEF void wem_Vec2_clampMagnitude(Vec2 out, const Vec2 v, float maxMagnitude);
////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

WEMDEF void wem_Vec2_norm(Vec2 out, const Vec2 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  POW2

WEMDEF void wem_Vec2_pow2(Vec2 out, const Vec2 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

WEMDEF float wem_Vec2_dot(const Vec2 v1, const Vec2 v2);
WEMDEF float wem_Vec2_dotN(const Vec2 v1, const Vec2 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

WEMDEF void wem_Vec2_inv(Vec2 out, const Vec2 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  PERPENDICULAR

WEMDEF void wem_Vec2_perp(Vec2 out, const Vec2 v);
WEMDEF void wem_Vec2_perpN(Vec2 out, const Vec2 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

WEMDEF void wem_Vec2_lerp(Vec2 out, const Vec2 from, const Vec2 to, float t);
WEMDEF void wem_Vec2_smoothstep(Vec2 out, const Vec2 from, const Vec2 to, float t);
WEMDEF void wem_Vec2_smootherstep(Vec2 out, const Vec2 from, const Vec2 to, float t);
WEMDEF void wem_Vec2_smoothstep_inverse(Vec2 out, const Vec2 from, const Vec2 to, float t);
WEMDEF void wem_Vec2_smoothDamp(Vec2 out, const Vec2 from, const Vec2 to, Vec2 velocity, float maxSpeed, float smoothTime, float timeDelta);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE

WEMDEF float wem_Vec2_angleInRad(const Vec2 v1, const Vec2 v2);
WEMDEF float wem_Vec2_angleInDeg(const Vec2 v1, const Vec2 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL

WEMDEF bool wem_Vec2_matches(const Vec2 v1, const Vec2 v2);
WEMDEF bool wem_Vec2_inRange(const Vec2 v1, const Vec2 v2, float range);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_Vec2_print(const Vec2 v);

#ifdef WEM_INTR_IMPLEMENTATION

#include <math.h>
#include <immintrin.h>

#include "vector.h"

void wem_Vec2_set(Vec2 out, float x, float y) {
    out[0] = x; out[1] = y;
}
void wem_Vec2_cpy(Vec2 out, const Vec2 v) {
    memcpy(out, v, sizeof(Vec2));
}
void wem_Vec2_set2F(Vec2 out, float *f2) {
    memcpy(out, f2, sizeof(float) * 2);
}
void wem_Vec2_to2F(float *f2, const Vec2 v) {
    memcpy(f2, v, sizeof(float) * 2);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec2_add(Vec2 out, const Vec2 v1, const Vec2 v2) {
    wem_Vec_add(out, v1, v2);
}
void wem_Vec2_sub(Vec2 out, const Vec2 v1, const Vec2 v2) {
    wem_Vec_sub(out, v1, v2);
}
void wem_Vec2_mul(Vec2 out, const Vec2 v1, const Vec2 v2) {
    wem_Vec_mul(out, v1, v2);
}
void wem_Vec2_div(Vec2 out, const Vec2 v1, const Vec2 v2) {
    wem_Vec_div(out, v1, v2);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW

void wem_Vec2_add2f(Vec2 out, const Vec2 v, float x, float y) {
    wem_Vec_add4f(out, v, x, y, 0, 0);
}
void wem_Vec2_sub2f(Vec2 out, const Vec2 v, float x, float y) {
    wem_Vec_sub4f(out, v, x, y, 0, 0);
}
void wem_Vec2_mul2f(Vec2 out, const Vec2 v, float x, float y) {
    wem_Vec_mul4f(out, v, x, y, 0, 0);
}
void wem_Vec2_div2f(Vec2 out, const Vec2 v, float x, float y) {
    wem_Vec_div4f(out, v, x, y, 1, 1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec2_add1f(Vec2 out, const Vec2 v, float val) {
    wem_Vec_add1f(out, v, val);
}
void wem_Vec2_sub1f(Vec2 out, const Vec2 v, float val) {
    wem_Vec_sub1f(out, v, val);
}
void wem_Vec2_mul1f(Vec2 out, const Vec2 v, float val) {
    wem_Vec_mul1f(out, v, val);
}
void wem_Vec2_div1f(Vec2 out, const Vec2 v, float val) {
    wem_Vec_div1f(out, v, val);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vec2_sqrMagnitude(const Vec2 v) {
    return POW2(v[0]) + POW2(v[1]);
}
float wem_Vec2_magnitude(const Vec2 v) {
    return sqrtf(POW2(v[0]) + POW2(v[1]));
}
void wem_Vec2_clampMagnitude(Vec2 out, const Vec2 v, float maxMagnitude) {
    float mag = sqrtf(POW2(v[0]) + POW2(v[1]));
    __m128 a, d, m, acc;
    a = _mm_load_ps(v);
    d = _mm_set_ps1(mag > maxMagnitude ? mag : 1);
    m = _mm_set_ps1(mag > maxMagnitude ? maxMagnitude : 1);
    acc = _mm_div_ps(a, d);
    acc = _mm_mul_ps(acc, m);
    _mm_store_ps(out, acc); 
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec2_norm(Vec2 out, const Vec2 v) {
    float mag = sqrtf(POW2(v[0]) + POW2(v[1]));
    __m128 acc = _mm_div_ps(_mm_load_ps(v), _mm_set_ps1(mag));
    _mm_store_ps(out, acc);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  POW2
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec2_pow2(Vec2 out, const Vec2 v) {
    wem_Vec_mul(out, v, v);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vec2_dot(const Vec2 v1, const Vec2 v2) {
    Vec out;
    wem_Vec_mul(out, v1, v2);
    return out[0] + out[1];
}
float wem_Vec2_dotN(const Vec2 v1, const Vec2 v2) {
    Vec2 v1N, v2N;
    wem_Vec2_norm(v1N, v1); wem_Vec2_norm(v2N, v2);
    return wem_Vec2_dot(v1N, v2N);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec2_inv(Vec2 out, const Vec2 v) {
    wem_Vec_inv(out, v);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  PERPENDICULAR
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec2_perp(Vec2 out, const Vec2 v) {
    out[0] = v[1]; out[1] = v[0];
}
void wem_Vec2_perpN(Vec2 out, const Vec2 v) {
    out[0] = v[1]; out[1] = v[0];
    wem_Vec2_norm(out, out);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec2_lerp(Vec2 out, const Vec2 from, const Vec2 to, float t) {
    wem_Vec_lerp(out, from, to, t);
}
void wem_Vec2_smoothstep(Vec2 out, const Vec2 from, const Vec2 to, float t) {
    wem_Vec_smoothstep(out, from, to, t);
}
void wem_Vec2_smootherstep(Vec2 out, const Vec2 from, const Vec2 to, float t) {
    wem_Vec_smootherstep(out, from, to, t);
}
void wem_Vec2_smoothstep_inverse(Vec2 out, const Vec2 from, const Vec2 to, float t) {
    wem_Vec_smoothstep_inverse(out, from, to, t);
}
void wem_Vec2_smoothDamp(Vec2 out, const Vec2 from, const Vec2 to, Vec2 velocity, float maxSpeed, float smoothTime, float timeDelta) {
    wem_Vec_smoothDamp(out, from, to, velocity, maxSpeed, smoothTime, timeDelta);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vec2_angleInRad(const Vec2 v1, const Vec2 v2) {
    float dot = wem_Vec2_dotN(v1, v2);
    return acosf(dot);
}
float wem_Vec2_angleInDeg(const Vec2 v1, const Vec2 v2) {
    return wem_Vec2_angleInRad(v1, v2) * RAD2DEG; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool wem_Vec2_matches(const Vec2 v1, const Vec2 v2) {
    return wem_Vec_matches(v1, v2);
}
bool wem_Vec2_inRange(const Vec2 v1, const Vec2 v2, float range) {
    return wem_Vec_inRange(v1, v2, range);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec2_print(const Vec2 v) {
    printf("(%f %f %f %f)", v[0], v[1], v[2], v[3]);
}

#endif
#endif