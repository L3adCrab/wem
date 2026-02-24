#ifndef WEM_INTRINSICS_VECTOR_2_H
#define WEM_INTRINSICS_VECTOR_2_H

#include "datatypes.h"

#define WEMDEF extern

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC

WEMDEF Vector2 wem_Vector2_add(const Vector2 *v1, const Vector2 *v2);
WEMDEF Vector2 wem_Vector2_sub(const Vector2 *v1, const Vector2 *v2);
WEMDEF Vector2 wem_Vector2_mul(const Vector2 *v1, const Vector2 *v2);
WEMDEF Vector2 wem_Vector2_div(const Vector2 *v1, const Vector2 *v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW

WEMDEF Vector2 wem_Vector2_add4f(const Vector2 *v, float x, float y);
WEMDEF Vector2 wem_Vector2_sub4f(const Vector2 *v, float x, float y);
WEMDEF Vector2 wem_Vector2_mul4f(const Vector2 *v, float x, float y);
WEMDEF Vector2 wem_Vector2_div4f(const Vector2 *v, float x, float y);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF

WEMDEF Vector2 wem_Vector2_add1f(const Vector2 *v, float val);
WEMDEF Vector2 wem_Vector2_sub1f(const Vector2 *v, float val);
WEMDEF Vector2 wem_Vector2_mul1f(const Vector2 *v, float val);
WEMDEF Vector2 wem_Vector2_div1f(const Vector2 *v, float val);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

WEMDEF float wem_Vector2_sqrMagnitude(const Vector2 *v);
WEMDEF float wem_Vector2_magnitude(const Vector2 *v);
WEMDEF Vector2 wem_Vector2_clampMagnitude(const Vector2 *v, float maxMagnitude);
////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

WEMDEF Vector2 wem_Vector2_norm(const Vector2 *v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  POW2

WEMDEF Vector2 wem_Vector2_pow2(const Vector2 *v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

WEMDEF float wem_Vector2_dot(const Vector2 *v1, const Vector2 *v2);
WEMDEF float wem_Vector2_dotN(const Vector2 *v1, const Vector2 *v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

WEMDEF Vector2 wem_Vector2_inv(const Vector2 *v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS

WEMDEF Vector2 wem_Vector2_cross(const Vector2 *v1, const Vector2 *v2);
WEMDEF Vector2 wem_Vector2_crossN(const Vector2 *v1, const Vector2 *v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

Vector2 wem_Vector2_lerp(const Vector2 *from, const Vector2 *to, float t);
Vector2 wem_Vector2_smoothstep(const Vector2 *from, const Vector2 *to, float t);
Vector2 wem_Vector2_smootherstep(const Vector2 *from, const Vector2 *to, float t);
Vector2 wem_Vector2_smoothstep_inverse(const Vector2 *from, const Vector2 *to, float t);
Vector2 wem_Vector2_smoothDamp(const Vector2 *from, const Vector2 *to, Vector2 *velocity, float maxSpeed, float smoothTime, float timeDelta);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE

WEMDEF float wem_Vector2_angleInRad(const Vector2 *v1, const Vector2 *v2);
WEMDEF float wem_Vector2_angleInDeg(const Vector2 *v1, const Vector2 *v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL

WEMDEF bool wem_Vector2_matches(const Vector2 *v1, const Vector2 *v2);
WEMDEF bool wem_Vector2_inRange(const Vector2 *v1, const Vector2 *v2, float range);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_Vector2_print(const Vector2 v);

#ifdef WEM_INTR_IMPLEMENTATION

#include <stdio.h>
#include <math.h>
#include <immintrin.h>

#include "Vector.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector2 wem_Vector2_add(const Vector2 *v1, const Vector2 *v2) {
    Vector2 out = {{0}};
    wem_Vec_add(out.p, v1->p, v2->p);
    return out;
}
Vector2 wem_Vector2_sub(const Vector2 *v1, const Vector2 *v2) {
    Vector2 out = {{0}};
    wem_Vec_sub(out.p, v1->p, v2->p);
    return out;
}
Vector2 wem_Vector2_mul(const Vector2 *v1, const Vector2 *v2) {
    Vector2 out = {{0}};
    wem_Vec_mul(out.p, v1->p, v2->p);
    return out;
}
Vector2 wem_Vector2_div(const Vector2 *v1, const Vector2 *v2) {
    Vector2 out = {{0}};
    wem_Vec_div(out.p, v1->p, v2->p);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW

Vector2 wem_Vector2_add4f(const Vector2 *v, float x, float y) {
    Vector2 out = {{0}};
    wem_Vec_add4f(out.p, v->p, x, y, 0, 0);
    return out;
}
Vector2 wem_Vector2_sub4f(const Vector2 *v, float x, float y) {
    Vector2 out = {{0}};
    wem_Vec_sub4f(out.p, v->p, x, y, 0, 0);
    return out;
}
Vector2 wem_Vector2_mul4f(const Vector2 *v, float x, float y) {
    Vector2 out = {{0}};
    wem_Vec_mul4f(out.p, v->p, x, y, 0, 0);
    return out;
}
Vector2 wem_Vector2_div4f(const Vector2 *v, float x, float y) {
    Vector2 out = {{0}};
    wem_Vec_div4f(out.p, v->p, x, y, 0, 0);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector2 wem_Vector2_add1f(const Vector2 *v, float val) {
    Vector2 out = {{0}};
    wem_Vec_add1f(out.p, v->p, val);
    return out;
}
Vector2 wem_Vector2_sub1f(const Vector2 *v, float val) {
    Vector2 out = {{0}};
    wem_Vec_sub1f(out.p, v->p, val);
    return out;
}
Vector2 wem_Vector2_mul1f(const Vector2 *v, float val) {
    Vector2 out = {{0}};
    wem_Vec_mul1f(out.p, v->p, val);
    return out;
}
Vector2 wem_Vector2_div1f(const Vector2 *v, float val) {
    Vector2 out = {{0}};
    wem_Vec_div1f(out.p, v->p, val);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vector2_sqrMagnitude(const Vector2 *v) {
    return POW2(v->p[0]) + POW2(v->p[1]);
}
float wem_Vector2_magnitude(const Vector2 *v) {
    __m128 a, acc;
    a = _mm_load_ps(v->p);
    acc = _mm_mul_ps(a, a);
    return sqrtf(acc[0] + acc[1]);
}
Vector2 wem_Vector2_clampMagnitude(const Vector2 *v, float maxMagnitude) {
    Vector2 out = {{0}};
    wem_Vec_clampMagnitude(out.p, v->p, maxMagnitude);
    return out;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector2 wem_Vector2_norm(const Vector2 *v) {
    Vector2 out = {{0}};
    wem_Vec_div1f(out.p, v->p, wem_Vector2_magnitude(v));
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  POW2
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector2 wem_Vector2_pow2(const Vector2 *v) {
    Vector2 out = {{0}};
    wem_Vec_mul(out.p, v->p, v->p);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vector2_dot(const Vector2 *v1, const Vector2 *v2) {
    Vec out;
    wem_Vec_mul(out, v1->p, v2->p);
    return out[0] + out[1];
}
float wem_Vector2_dotN(const Vector2 *v1, const Vector2 *v2) {
    Vector2 v1N, v2N;
    v1N = wem_Vector2_norm(v1); v2N = wem_Vector2_norm(v2);
    return wem_Vector2_dot(&v1N, &v2N);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector2 wem_Vector2_inv(const Vector2 *v) {
    Vector2 out = {{0}};
    wem_Vec_inv(out.p, v->p);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector2 wem_Vector2_cross(const Vector2 *v1, const Vector2 *v2) {
    return (Vector2){{v1->p[1] - v2->p[1], v1->p[0] - v2->p[0]}};
}
Vector2 wem_Vector2_crossN(const Vector2 *v1, const Vector2 *v2) {
    Vector2 out = wem_Vector2_cross(v1, v2);
    return wem_Vector2_norm(&out);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector2 wem_Vector2_lerp(const Vector2 *from, const Vector2 *to, float t) {
    Vector2 out = {{0}};
    wem_Vec_lerp(out.p, from->p, to->p, t);
    return out;
}
Vector2 wem_Vector2_smoothstep(const Vector2 *from, const Vector2 *to, float t) {
    Vector2 out = {{0}};
    wem_Vec_smoothstep(out.p, from->p, to->p, t);
    return out;
}
Vector2 wem_Vector2_smootherstep(const Vector2 *from, const Vector2 *to, float t) {
    Vector2 out = {{0}};
    wem_Vec_smootherstep(out.p, from->p, to->p, t);
    return out;
}
Vector2 wem_Vector2_smoothstep_inverse(const Vector2 *from, const Vector2 *to, float t) {
    Vector2 out = {{0}};
    wem_Vec_smoothstep_inverse(out.p, from->p, to->p, t);
    return out;
}
Vector2 wem_Vector2_smoothDamp(const Vector2 *from, const Vector2 *to, Vector2 *velocity, float maxSpeed, float smoothTime, float timeDelta) {
    Vector2 out = {{0}};
    wem_Vec_smoothDamp(out.p, from->p, to->p, velocity->p, maxSpeed, smoothTime, timeDelta);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vector2_angleInRad(const Vector2 *v1, const Vector2 *v2) {
    float dot = wem_Vector2_dotN(v1, v2);
    return acosf(dot);
}
float wem_Vector2_angleInDeg(const Vector2 *v1, const Vector2 *v2) {
    return wem_Vector2_angleInRad(v1, v2) * RAD2DEG; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool wem_Vector2_matches(const Vector2 *v1, const Vector2 *v2) {
    return wem_Vec_matches(v1->p, v2->p);
}
bool wem_Vector2_inRange(const Vector2 *v1, const Vector2 *v2, float range) {
    return wem_Vec_inRange(v1->p, v2->p, range);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vector2_print(const Vector2 v) {
    printf("(%f %f)", v.p[0], v.p[1]);
}

#endif
#endif