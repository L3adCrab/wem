#ifndef WEM_INTRINSICS_VECTOR_4_H
#define WEM_INTRINSICS_VECTOR_4_H

#include "datatypes.h"

#define WEMDEF extern

WEMDEF void wem_Vec4_set(Vec4 out, float x, float y, float z, float w);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC

WEMDEF void wem_Vec4_add(Vec4 out, const Vec4 v1, const Vec4 v2);
WEMDEF void wem_Vec4_sub(Vec4 out, const Vec4 v1, const Vec4 v2);
WEMDEF void wem_Vec4_mul(Vec4 out, const Vec4 v1, const Vec4 v2);
WEMDEF void wem_Vec4_div(Vec4 out, const Vec4 v1, const Vec4 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW

WEMDEF void wem_Vec4_add4f(Vec4 out, const Vec4 v, float x, float y, float z, float w);
WEMDEF void wem_Vec4_sub4f(Vec4 out, const Vec4 v, float x, float y, float z, float w);
WEMDEF void wem_Vec4_mul4f(Vec4 out, const Vec4 v, float x, float y, float z, float w);
WEMDEF void wem_Vec4_div4f(Vec4 out, const Vec4 v, float x, float y, float z, float w);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF

WEMDEF void wem_Vec4_add1f(Vec4 out, const Vec4 v, float val);
WEMDEF void wem_Vec4_sub1f(Vec4 out, const Vec4 v, float val);
WEMDEF void wem_Vec4_mul1f(Vec4 out, const Vec4 v, float val);
WEMDEF void wem_Vec4_div1f(Vec4 out, const Vec4 v, float val);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC * MAT4

WEMDEF void wem_Vec4_mulMat4(Vec4 out, const Vec4 v, const Mat4 m);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

WEMDEF float wem_Vec4_sqrMagnitude(const Vec4 v);
WEMDEF float wem_Vec4_magnitude(const Vec4 v);
WEMDEF void wem_Vec4_clampMagnitude(Vec4 out, const Vec4 v, float maxMagnitude);
////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

WEMDEF void wem_Vec4_norm(Vec4 out, const Vec4 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  POW2

WEMDEF void wem_Vec4_pow2(Vec4 out, const Vec4 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

WEMDEF float wem_Vec4_dot(const Vec4 v1, const Vec4 v2);
WEMDEF float wem_Vec4_dotN(const Vec4 v1, const Vec4 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

WEMDEF void wem_Vec4_inv(Vec4 out, const Vec4 v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS

WEMDEF void wem_Vec4_cross(Vec4 out, const Vec4 v1, const Vec4 v2);
WEMDEF void wem_Vec4_crossN(Vec4 out, const Vec4 v1, const Vec4 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

WEMDEF void wem_Vec4_lerp(Vec4 out, const Vec4 from, const Vec4 to, float t);
WEMDEF void wem_Vec4_smoothstep(Vec4 out, const Vec4 from, const Vec4 to, float t);
WEMDEF void wem_Vec4_smootherstep(Vec4 out, const Vec4 from, const Vec4 to, float t);
WEMDEF void wem_Vec4_smoothstep_inverse(Vec4 out, const Vec4 from, const Vec4 to, float t);
WEMDEF void wem_Vec4_smoothDamp(Vec4 out, const Vec4 from, const Vec4 to, Vec4 velocity, float maxSpeed, float smoothTime, float timeDelta);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE

WEMDEF float wem_Vec4_angleInRad(const Vec4 v1, const Vec4 v2);
WEMDEF float wem_Vec4_angleInDeg(const Vec4 v1, const Vec4 v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL

WEMDEF bool wem_Vec4_matches(const Vec4 v1, const Vec4 v2);
WEMDEF bool wem_Vec4_inRange(const Vec4 v1, const Vec4 v2, float range);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_Vec4_print(const Vec4 v);

#ifdef WEM_INTR_IMPLEMENTATION

#include <math.h>
#include <immintrin.h>

#include "Vector.h"

void wem_Vec4_set(Vec4 out, float x, float y, float z, float w) {
    out[0] = x; out[1] = y, out[2] = z, out[3] = w;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec4_add(Vec4 out, const Vec4 v1, const Vec4 v2) {
    wem_Vec_add(out, v1, v2);
}
void wem_Vec4_sub(Vec4 out, const Vec4 v1, const Vec4 v2) {
    wem_Vec_sub(out, v1, v2);
}
void wem_Vec4_mul(Vec4 out, const Vec4 v1, const Vec4 v2) {
    wem_Vec_mul(out, v1, v2);
}
void wem_Vec4_div(Vec4 out, const Vec4 v1, const Vec4 v2) {
    wem_Vec_div(out, v1, v2);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW

void wem_Vec4_add4f(Vec4 out, const Vec4 v, float x, float y, float z, float w) {
    wem_Vec_add4f(out, v, x, y, z, w);
}
void wem_Vec4_sub4f(Vec4 out, const Vec4 v, float x, float y, float z, float w) {
    wem_Vec_sub4f(out, v, x, y, z, w);
}
void wem_Vec4_mul4f(Vec4 out, const Vec4 v, float x, float y, float z, float w) {
    wem_Vec_mul4f(out, v, x, y, z, w);
}
void wem_Vec4_div4f(Vec4 out, const Vec4 v, float x, float y, float z, float w) {
    wem_Vec_div4f(out, v, x, y, z, w);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec4_add1f(Vec4 out, const Vec4 v, float val) {
    wem_Vec_add1f(out, v, val);
}
void wem_Vec4_sub1f(Vec4 out, const Vec4 v, float val) {
    wem_Vec_sub1f(out, v, val);
}
void wem_Vec4_mul1f(Vec4 out, const Vec4 v, float val) {
    wem_Vec_mul1f(out, v, val);
}
void wem_Vec4_div1f(Vec4 out, const Vec4 v, float val) {
    wem_Vec_div1f(out, v, val);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC * MAT4
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec4_mulMat4(Vec4 out, const Vec4 v, const Mat4 m) {
    wem_Vec_mulMat4(out, v, m);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vec4_sqrMagnitude(const Vec4 v) {
    return wem_Vec_sqrMagnitude(v);
}
float wem_Vec4_magnitude(const Vec4 v) {
    return wem_Vec_magnitude(v);
}
void wem_Vec4_clampMagnitude(Vec4 out, const Vec4 v, float maxMagnitude) {
    wem_Vec_clampMagnitude(out, v, maxMagnitude);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec4_norm(Vec4 out, const Vec4 v) {
    wem_Vec_div1f(out, v, wem_Vec4_magnitude(v));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  POW2
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec4_pow2(Vec4 out, const Vec4 v) {
    wem_Vec_mul(out, v, v);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vec4_dot(const Vec4 v1, const Vec4 v2) {
    Vec out;
    wem_Vec_mul(out, v1, v2);
    return out[0] + out[1] + out[2] + out[3];
}
float wem_Vec4_dotN(const Vec4 v1, const Vec4 v2) {
    Vec4 v1N, v2N;
    wem_Vec4_norm(v1N, v1); wem_Vec4_norm(v2N, v2);
    return wem_Vec4_dot(v1N, v2N);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec4_inv(Vec4 out, const Vec4 v) {
    wem_Vec_inv(out, v);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec4_cross(Vec4 out, const Vec4 v1, const Vec4 v2) {
    wem_Vec_cross(out, v1, v2);
}
void wem_Vec4_crossN(Vec4 out, const Vec4 v1, const Vec4 v2) {
    wem_Vec4_cross(out, v1, v2);
    return wem_Vec4_norm(out, out);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec4_lerp(Vec4 out, const Vec4 from, const Vec4 to, float t) {
    wem_Vec_lerp(out, from, to, t);
}
void wem_Vec4_smoothstep(Vec4 out, const Vec4 from, const Vec4 to, float t) {
    wem_Vec_smoothstep(out, from, to, t);
}
void wem_Vec4_smootherstep(Vec4 out, const Vec4 from, const Vec4 to, float t) {
    wem_Vec_smootherstep(out, from, to, t);
}
void wem_Vec4_smoothstep_inverse(Vec4 out, const Vec4 from, const Vec4 to, float t) {
    wem_Vec_smoothstep_inverse(out, from, to, t);
}
void wem_Vec4_smoothDamp(Vec4 out, const Vec4 from, const Vec4 to, Vec4 velocity, float maxSpeed, float smoothTime, float timeDelta) {
    wem_Vec_smoothDamp(out, from, to, velocity, maxSpeed, smoothTime, timeDelta);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vec4_angleInRad(const Vec4 v1, const Vec4 v2) {
    float dot = wem_Vec4_dotN(v1, v2);
    return acosf(dot);
}
float wem_Vec4_angleInDeg(const Vec4 v1, const Vec4 v2) {
    return wem_Vec4_angleInRad(v1, v2) * RAD2DEG; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool wem_Vec4_matches(const Vec4 v1, const Vec4 v2) {
    return wem_Vec_matches(v1, v2);
}
bool wem_Vec4_inRange(const Vec4 v1, const Vec4 v2, float range) {
    return wem_Vec_inRange(v1, v2, range);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec4_print(const Vec4 v) {
    printf("(%f %f %f %f)", v[0], v[1], v[2], v[3]);
}

#endif
#endif