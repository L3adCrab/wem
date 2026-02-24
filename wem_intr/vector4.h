#ifndef WEM_INTRINSICS_VECTOR_4_H
#define WEM_INTRINSICS_VECTOR_4_H

#include "datatypes.h"

#define WEMDEF extern

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC

WEMDEF Vector4 wem_Vector4_add(const Vector4 *v1, const Vector4 *v2);
WEMDEF Vector4 wem_Vector4_sub(const Vector4 *v1, const Vector4 *v2);
WEMDEF Vector4 wem_Vector4_mul(const Vector4 *v1, const Vector4 *v2);
WEMDEF Vector4 wem_Vector4_div(const Vector4 *v1, const Vector4 *v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW

WEMDEF Vector4 wem_Vector4_add4f(const Vector4 *v, float x, float y, float z, float w);
WEMDEF Vector4 wem_Vector4_sub4f(const Vector4 *v, float x, float y, float z, float w);
WEMDEF Vector4 wem_Vector4_mul4f(const Vector4 *v, float x, float y, float z, float w);
WEMDEF Vector4 wem_Vector4_div4f(const Vector4 *v, float x, float y, float z, float w);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF

WEMDEF Vector4 wem_Vector4_add1f(const Vector4 *v, float val);
WEMDEF Vector4 wem_Vector4_sub1f(const Vector4 *v, float val);
WEMDEF Vector4 wem_Vector4_mul1f(const Vector4 *v, float val);
WEMDEF Vector4 wem_Vector4_div1f(const Vector4 *v, float val);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

WEMDEF float wem_Vector4_sqrMagnitude(const Vector4 *v);
WEMDEF float wem_Vector4_magnitude(const Vector4 *v);
WEMDEF Vector4 wem_Vector4_clampMagnitude(const Vector4 *v, float maxMagnitude);
////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

WEMDEF Vector4 wem_Vector4_norm(const Vector4 *v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  POW2

WEMDEF Vector4 wem_Vector4_pow2(const Vector4 *v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

WEMDEF float wem_Vector4_dot(const Vector4 *v1, const Vector4 *v2);
WEMDEF float wem_Vector4_dotN(const Vector4 *v1, const Vector4 *v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

WEMDEF Vector4 wem_Vector4_inv(const Vector4 *v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS

WEMDEF Vector4 wem_Vector4_cross(const Vector4 *v1, const Vector4 *v2);
WEMDEF Vector4 wem_Vector4_crossN(const Vector4 *v1, const Vector4 *v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

Vector4 wem_Vector4_lerp(const Vector4 *from, const Vector4 *to, float t);
Vector4 wem_Vector4_smoothstep(const Vector4 *from, const Vector4 *to, float t);
Vector4 wem_Vector4_smootherstep(const Vector4 *from, const Vector4 *to, float t);
Vector4 wem_Vector4_smoothstep_inverse(const Vector4 *from, const Vector4 *to, float t);
Vector4 wem_Vector4_smoothDamp(const Vector4 *from, const Vector4 *to, Vector4 *velocity, float maxSpeed, float smoothTime, float timeDelta);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE

WEMDEF float wem_Vector4_angleInRad(const Vector4 *v1, const Vector4 *v2);
WEMDEF float wem_Vector4_angleInDeg(const Vector4 *v1, const Vector4 *v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL

WEMDEF bool wem_Vector4_matches(const Vector4 *v1, const Vector4 *v2);
WEMDEF bool wem_Vector4_inRange(const Vector4 *v1, const Vector4 *v2, float range);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_Vector4_print(const Vector4 v);

#ifdef WEM_INTR_IMPLEMENTATION

#include <math.h>
#include <immintrin.h>

#include "Vector.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector4 wem_Vector4_add(const Vector4 *v1, const Vector4 *v2) {
    Vector4 out = {{0}};
    wem_Vec_add(out.p, v1->p, v2->p);
    return out;
}
Vector4 wem_Vector4_sub(const Vector4 *v1, const Vector4 *v2) {
    Vector4 out = {{0}};
    wem_Vec_sub(out.p, v1->p, v2->p);
    return out;
}
Vector4 wem_Vector4_mul(const Vector4 *v1, const Vector4 *v2) {
    Vector4 out = {{0}};
    wem_Vec_mul(out.p, v1->p, v2->p);
    return out;
}
Vector4 wem_Vector4_div(const Vector4 *v1, const Vector4 *v2) {
    Vector4 out = {{0}};
    wem_Vec_div(out.p, v1->p, v2->p);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW

Vector4 wem_Vector4_add4f(const Vector4 *v, float x, float y, float z, float w) {
    Vector4 out = {{0}};
    wem_Vec_add4f(out.p, v->p, x, y, z, w);
    return out;
}
Vector4 wem_Vector4_sub4f(const Vector4 *v, float x, float y, float z, float w) {
    Vector4 out = {{0}};
    wem_Vec_sub4f(out.p, v->p, x, y, z, w);
    return out;
}
Vector4 wem_Vector4_mul4f(const Vector4 *v, float x, float y, float z, float w) {
    Vector4 out = {{0}};
    wem_Vec_mul4f(out.p, v->p, x, y, z, w);
    return out;
}
Vector4 wem_Vector4_div4f(const Vector4 *v, float x, float y, float z, float w) {
    Vector4 out = {{0}};
    wem_Vec_div4f(out.p, v->p, x, y, z, w);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector4 wem_Vector4_add1f(const Vector4 *v, float val) {
    Vector4 out = {{0}};
    wem_Vec_add1f(out.p, v->p, val);
    return out;
}
Vector4 wem_Vector4_sub1f(const Vector4 *v, float val) {
    Vector4 out = {{0}};
    wem_Vec_sub1f(out.p, v->p, val);
    return out;
}
Vector4 wem_Vector4_mul1f(const Vector4 *v, float val) {
    Vector4 out = {{0}};
    wem_Vec_mul1f(out.p, v->p, val);
    return out;
}
Vector4 wem_Vector4_div1f(const Vector4 *v, float val) {
    Vector4 out = {{0}};
    wem_Vec_div1f(out.p, v->p, val);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vector4_sqrMagnitude(const Vector4 *v) {
    return wem_Vec_sqrMagnitude(v->p);
}
float wem_Vector4_magnitude(const Vector4 *v) {
    return wem_Vec_magnitude(v->p);
}
Vector4 wem_Vector4_clampMagnitude(const Vector4 *v, float maxMagnitude) {
    Vector4 out = {{0}};
    wem_Vec_clampMagnitude(out.p, v->p, maxMagnitude);
    return out;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector4 wem_Vector4_norm(const Vector4 *v) {
    Vector4 out = {{0}};
    wem_Vec_div1f(out.p, v->p, wem_Vector4_magnitude(v));
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  POW2
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector4 wem_Vector4_pow2(const Vector4 *v) {
    Vector4 out = {{0}};
    wem_Vec_mul(out.p, v->p, v->p);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vector4_dot(const Vector4 *v1, const Vector4 *v2) {
    Vec out;
    wem_Vec_mul(out, v1->p, v2->p);
    return out[0] + out[1] + out[2] + out[3];
}
float wem_Vector4_dotN(const Vector4 *v1, const Vector4 *v2) {
    Vector4 v1N, v2N;
    v1N = wem_Vector4_norm(v1); v2N = wem_Vector4_norm(v2);
    return wem_Vector4_dot(&v1N, &v2N);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector4 wem_Vector4_inv(const Vector4 *v) {
    Vector4 out = {{0}};
    wem_Vec_inv(out.p, v->p);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector4 wem_Vector4_cross(const Vector4 *v1, const Vector4 *v2) {
    Vector4 out;
    wem_Vec_cross(out.p, v1->p, v2->p);
    return out;
}
Vector4 wem_Vector4_crossN(const Vector4 *v1, const Vector4 *v2) {
    Vector4 out = wem_Vector4_cross(v1, v2);
    return wem_Vector4_norm(&out);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

Vector4 wem_Vector4_lerp(const Vector4 *from, const Vector4 *to, float t) {
    Vector4 out = {{0}};
    wem_Vec_lerp(out.p, from->p, to->p, t);
    return out;
}
Vector4 wem_Vector4_smoothstep(const Vector4 *from, const Vector4 *to, float t) {
    Vector4 out = {{0}};
    wem_Vec_smoothstep(out.p, from->p, to->p, t);
    return out;
}
Vector4 wem_Vector4_smootherstep(const Vector4 *from, const Vector4 *to, float t) {
    Vector4 out = {{0}};
    wem_Vec_smootherstep(out.p, from->p, to->p, t);
    return out;
}
Vector4 wem_Vector4_smoothstep_inverse(const Vector4 *from, const Vector4 *to, float t) {
    Vector4 out = {{0}};
    wem_Vec_smoothstep_inverse(out.p, from->p, to->p, t);
    return out;
}
Vector4 wem_Vector4_smoothDamp(const Vector4 *from, const Vector4 *to, Vector4 *velocity, float maxSpeed, float smoothTime, float timeDelta) {
    Vector4 out = {{0}};
    wem_Vec_smoothDamp(out.p, from->p, to->p, velocity->p, maxSpeed, smoothTime, timeDelta);
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vector4_angleInRad(const Vector4 *v1, const Vector4 *v2) {
    float dot = wem_Vector4_dotN(v1, v2);
    return acosf(dot);
}
float wem_Vector4_angleInDeg(const Vector4 *v1, const Vector4 *v2) {
    return wem_Vector4_angleInRad(v1, v2) * RAD2DEG; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool wem_Vector4_matches(const Vector4 *v1, const Vector4 *v2) {
    return wem_Vec_matches(v1->p, v2->p);
}
bool wem_Vector4_inRange(const Vector4 *v1, const Vector4 *v2, float range) {
    return wem_Vec_inRange(v1->p, v2->p, range);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vector4_print(const Vector4 v) {
    printf("(%f %f %f %f)", v.p[0], v.p[1], v.p[2], v.p[3]);
}

#endif
#endif