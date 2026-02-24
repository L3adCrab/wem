#ifndef WEM_INTRINSICS_VECTOR_3_H
#define WEM_INTRINSICS_VECTOR_3_H

#include "datatypes.h"

#define WEMDEF extern

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC

WEMDEF Vector3 wem_Vector3_add(const Vector3 *v1, const Vector3 *v2);
WEMDEF Vector3 wem_Vector3_sub(const Vector3 *v1, const Vector3 *v2);
WEMDEF Vector3 wem_Vector3_mul(const Vector3 *v1, const Vector3 *v2);
WEMDEF Vector3 wem_Vector3_div(const Vector3 *v1, const Vector3 *v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW

WEMDEF Vector3 wem_Vector3_add4f(const Vector3 *v, float x, float y, float z);
WEMDEF Vector3 wem_Vector3_sub4f(const Vector3 *v, float x, float y, float z);
WEMDEF Vector3 wem_Vector3_mul4f(const Vector3 *v, float x, float y, float z);
WEMDEF Vector3 wem_Vector3_div4f(const Vector3 *v, float x, float y, float z);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF

WEMDEF Vector3 wem_Vector3_add1f(const Vector3 *v, float val);
WEMDEF Vector3 wem_Vector3_sub1f(const Vector3 *v, float val);
WEMDEF Vector3 wem_Vector3_mul1f(const Vector3 *v, float val);
WEMDEF Vector3 wem_Vector3_div1f(const Vector3 *v, float val);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

WEMDEF float wem_Vector3_sqrMagnitude(const Vector3 *v);
WEMDEF float wem_Vector3_magnitude(const Vector3 *v);
WEMDEF Vector3 wem_Vector3_clampMagnitude(const Vector3 *v, float maxMagnitude);
////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

WEMDEF Vector3 wem_Vector3_norm(const Vector3 *v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  POW2

WEMDEF Vector3 wem_Vector3_pow2(const Vector3 *v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

WEMDEF float wem_Vector3_dot(const Vector3 *v1, const Vector3 *v2);
WEMDEF float wem_Vector3_dotN(const Vector3 *v1, const Vector3 *v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

WEMDEF Vector3 wem_Vector3_inv(const Vector3 *v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS

WEMDEF Vector3 wem_Vector3_cross(const Vector3 *v1, const Vector3 *v2);
WEMDEF Vector3 wem_Vector3_crossN(const Vector3 *v1, const Vector3 *v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

Vector3 wem_Vector3_lerp(const Vector3 *from, const Vector3 *to, float t);
Vector3 wem_Vector3_smoothstep(const Vector3 *from, const Vector3 *to, float t);
Vector3 wem_Vector3_smootherstep(const Vector3 *from, const Vector3 *to, float t);
Vector3 wem_Vector3_smoothstep_inverse(const Vector3 *from, const Vector3 *to, float t);
Vector3 wem_Vector3_smoothDamp(const Vector3 *from, const Vector3 *to, Vector3 *velocity, float maxSpeed, float smoothTime, float timeDelta);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE

WEMDEF float wem_Vector3_angleInRad(const Vector3 *v1, const Vector3 *v2);
WEMDEF float wem_Vector3_angleInDeg(const Vector3 *v1, const Vector3 *v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL

WEMDEF bool wem_Vector3_matches(const Vector3 *v1, const Vector3 *v2);
WEMDEF bool wem_Vector3_inRange(const Vector3 *v1, const Vector3 *v2, float range);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_Vector3_print(const Vector3 v);

#ifdef WEM_INTR_IMPLEMENTATION

#include <stdio.h>
#include <math.h>
#include <immintrin.h>

#include "Vector.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector3 wem_Vector3_add(const Vector3 *v1, const Vector3 *v2) {
    Vector3 out = {{0}};
    wem_Vec_add(out.p, v1->p, v2->p);
    return out;
}
Vector3 wem_Vector3_sub(const Vector3 *v1, const Vector3 *v2) {
    Vector3 out = {{0}};
    wem_Vec_sub(out.p, v1->p, v2->p);
    return out;
}
Vector3 wem_Vector3_mul(const Vector3 *v1, const Vector3 *v2) {
    Vector3 out = {{0}};
    wem_Vec_mul(out.p, v1->p, v2->p);
    return out;
}
Vector3 wem_Vector3_div(const Vector3 *v1, const Vector3 *v2) {
    Vector3 out = {{0}};
    wem_Vec_div(out.p, v1->p, v2->p);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW

Vector3 wem_Vector3_add4f(const Vector3 *v, float x, float y, float z) {
    Vector3 out = {{0}};
    wem_Vec_add4f(out.p, v->p, x, y, z, 0);
    return out;
}
Vector3 wem_Vector3_sub4f(const Vector3 *v, float x, float y, float z) {
    Vector3 out = {{0}};
    wem_Vec_sub4f(out.p, v->p, x, y, z, 0);
    return out;
}
Vector3 wem_Vector3_mul4f(const Vector3 *v, float x, float y, float z) {
    Vector3 out = {{0}};
    wem_Vec_mul4f(out.p, v->p, x, y, z, 0);
    return out;
}
Vector3 wem_Vector3_div4f(const Vector3 *v, float x, float y, float z) {
    Vector3 out = {{0}};
    wem_Vec_div4f(out.p, v->p, x, y, z, 0);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector3 wem_Vector3_add1f(const Vector3 *v, float val) {
    Vector3 out = {{0}};
    wem_Vec_add1f(out.p, v->p, val);
    return out;
}
Vector3 wem_Vector3_sub1f(const Vector3 *v, float val) {
    Vector3 out = {{0}};
    wem_Vec_sub1f(out.p, v->p, val);
    return out;
}
Vector3 wem_Vector3_mul1f(const Vector3 *v, float val) {
    Vector3 out = {{0}};
    wem_Vec_mul1f(out.p, v->p, val);
    return out;
}
Vector3 wem_Vector3_div1f(const Vector3 *v, float val) {
    Vector3 out = {{0}};
    wem_Vec_div1f(out.p, v->p, val);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vector3_sqrMagnitude(const Vector3 *v) {
    __m128 a, acc;
    a = _mm_load_ps(v->p);
    acc = _mm_mul_ps(a, a);
    return acc[0] + acc[1] + acc[2];
}
float wem_Vector3_magnitude(const Vector3 *v) {
    __m128 a, acc;
    a = _mm_load_ps(v->p);
    acc = _mm_mul_ps(a, a);
    return sqrtf(acc[0] + acc[1] + acc[2]);
}
Vector3 wem_Vector3_clampMagnitude(const Vector3 *v, float maxMagnitude) {
    Vector3 out = {{0}};
    wem_Vec_clampMagnitude(out.p, v->p, maxMagnitude);
    return out;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector3 wem_Vector3_norm(const Vector3 *v) {
    Vector3 out = {{0}};
    wem_Vec_div1f(out.p, v->p, wem_Vector3_magnitude(v));
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  POW2
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector3 wem_Vector3_pow2(const Vector3 *v) {
    Vector3 out = {{0}};
    wem_Vec_mul(out.p, v->p, v->p);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vector3_dot(const Vector3 *v1, const Vector3 *v2) {
    Vec out;
    wem_Vec_mul(out, v1->p, v2->p);
    return out[0] + out[1] + out[2];
}
float wem_Vector3_dotN(const Vector3 *v1, const Vector3 *v2) {
    Vector3 v1N, v2N;
    v1N = wem_Vector3_norm(v1); v2N = wem_Vector3_norm(v2);
    return wem_Vector3_dot(&v1N, &v2N);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector3 wem_Vector3_inv(const Vector3 *v) {
    Vector3 out = {{0}};
    wem_Vec_inv(out.p, v->p);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector3 wem_Vector3_cross(const Vector3 *v1, const Vector3 *v2) {
    Vector3 out;
    wem_Vec_cross(out.p, v1->p, v2->p);
    out.p[3] = 0;
    return out;
}
Vector3 wem_Vector3_crossN(const Vector3 *v1, const Vector3 *v2) {
    Vector3 out = wem_Vector3_cross(v1, v2);
    return wem_Vector3_norm(&out);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector3 wem_Vector3_lerp(const Vector3 *from, const Vector3 *to, float t) {
    Vector3 out = {{0}};
    wem_Vec_lerp(out.p, from->p, to->p, t);
    return out;
}
Vector3 wem_Vector3_smoothstep(const Vector3 *from, const Vector3 *to, float t) {
    Vector3 out = {{0}};
    wem_Vec_smoothstep(out.p, from->p, to->p, t);
    return out;
}
Vector3 wem_Vector3_smootherstep(const Vector3 *from, const Vector3 *to, float t) {
    Vector3 out = {{0}};
    wem_Vec_smootherstep(out.p, from->p, to->p, t);
    return out;
}
Vector3 wem_Vector3_smoothstep_inverse(const Vector3 *from, const Vector3 *to, float t) {
    Vector3 out = {{0}};
    wem_Vec_smoothstep_inverse(out.p, from->p, to->p, t);
    return out;
}
Vector3 wem_Vector3_smoothDamp(const Vector3 *from, const Vector3 *to, Vector3 *velocity, float maxSpeed, float smoothTime, float timeDelta) {
    Vector3 out = {{0}};
    wem_Vec_smoothDamp(out.p, from->p, to->p, velocity->p, maxSpeed, smoothTime, timeDelta);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vector3_angleInRad(const Vector3 *v1, const Vector3 *v2) {
    float dot = wem_Vector3_dotN(v1, v2);
    return acosf(dot);
}
float wem_Vector3_angleInDeg(const Vector3 *v1, const Vector3 *v2) {
    return wem_Vector3_angleInRad(v1, v2) * RAD2DEG; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool wem_Vector3_matches(const Vector3 *v1, const Vector3 *v2) {
    return wem_Vec_matches(v1->p, v2->p);
}
bool wem_Vector3_inRange(const Vector3 *v1, const Vector3 *v2, float range) {
    return wem_Vec_inRange(v1->p, v2->p, range);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vector3_print(const Vector3 v) {
    printf("(%f %f %f)", v.p[0], v.p[1], v.p[2]);
}

#endif
#endif