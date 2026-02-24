#ifndef WEM_INTINSIC_VEC_H
#define WEM_INTINSIC_VEC_H

#include "datatypes.h"

#define WEMDEF extern

WEMDEF void wem_Vec_cpy(Vec out, const Vec v);

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC

WEMDEF void wem_Vec_add(Vec out, const Vec v1, const Vec v2);
WEMDEF void wem_Vec_sub(Vec out, const Vec v1, const Vec v2);
WEMDEF void wem_Vec_mul(Vec out, const Vec v1, const Vec v2);
WEMDEF void wem_Vec_div(Vec out, const Vec v1, const Vec v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW

WEMDEF void wem_Vec_add4f(Vec out, const Vec v, float x, float y, float z, float w);
WEMDEF void wem_Vec_sub4f(Vec out, const Vec v, float x, float y, float z, float w);
WEMDEF void wem_Vec_mul4f(Vec out, const Vec v, float x, float y, float z, float w);
WEMDEF void wem_Vec_div4f(Vec out, const Vec v, float x, float y, float z, float w);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF

WEMDEF void wem_Vec_add1f(Vec out, const Vec v, float val);
WEMDEF void wem_Vec_sub1f(Vec out, const Vec v, float val);
WEMDEF void wem_Vec_mul1f(Vec out, const Vec v, float val);
WEMDEF void wem_Vec_div1f(Vec out, const Vec v, float val);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE

WEMDEF float wem_Vec_sqrMagnitude(const Vec v);
WEMDEF float wem_Vec_magnitude(const Vec v);
WEMDEF void wem_Vec_clampMagnitude(Vec out, const Vec v, float maxMagnitude);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION

WEMDEF void wem_Vec_norm(Vec out, const Vec v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  POW2

WEMDEF void wem_Vec_pow2(Vec out, const Vec v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT

WEMDEF float wem_Vec_dot(const Vec v1, const Vec v2);
WEMDEF float wem_Vec_dotN(const Vec v1, const Vec v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE

WEMDEF void wem_Vec_inv(Vec out, const Vec v);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS

WEMDEF void wem_Vec_cross(Vec out, const Vec v1, const Vec v2);
WEMDEF void wem_Vec_crossN(Vec out, Vec v1, Vec v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION

WEMDEF void wem_Vec_lerp(Vec out, const Vec from, const Vec to, float t);
WEMDEF void wem_Vec_smoothstep(Vec out, const Vec from, const Vec to, float t);
WEMDEF void wem_Vec_smootherstep(Vec out, const Vec from, const Vec to, float t);
WEMDEF void wem_Vec_smoothstep_inverse(Vec out, const Vec from, const Vec to, float t);
WEMDEF void wem_Vec_smoothDamp(Vec out, const Vec from, const Vec to, Vec velocity, float maxSpeed, float smoothTime, float timeDelta);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE

WEMDEF float wem_Vec_angleInRad(const Vec v1, const Vec v2);
WEMDEF float wem_Vec_angleInDeg(const Vec v1, const Vec v2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL

WEMDEF bool wem_Vec_matches(const Vec v1, const Vec v2);
WEMDEF bool wem_Vec_inRange(const Vec v1, const Vec v2, float range);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_Vec_print(const Vec v);

#ifdef WEM_INTR_IMPLEMENTATION

#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <immintrin.h>
#include <pmmintrin.h>

#include "macros.h"

void wem_Vec_cpy(Vec out, const Vec v) {
    memcpy(out, v, 16);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec_add(Vec out, const Vec v1, const Vec v2) {
    __m128 a, b, acc;
    a = _mm_load_ps(v1);
    b = _mm_load_ps(v2);
    acc = _mm_add_ps(a, b);     //  v * v
    _mm_store_ps(out, acc);
}
void wem_Vec_sub(Vec out, const Vec v1, const Vec v2) {
    __m128 a, b, acc;
    a = _mm_load_ps(v1);
    b = _mm_load_ps(v2);
    acc = _mm_sub_ps(a, b);     //  v - v
    _mm_store_ps(out, acc);
}
void wem_Vec_mul(Vec out, const Vec v1, const Vec v2) {
    __m128 a, b, acc;
    a = _mm_load_ps(v1);
    b = _mm_load_ps(v2);
    acc = _mm_mul_ps(a, b);     //  v * v
    _mm_store_ps(out, acc);
}
void wem_Vec_div(Vec out, const Vec v1, const Vec v2) {
    __m128 a, b, acc;
    a = _mm_load_ps(v1);
    b = _mm_load_ps(v2);
    acc = _mm_div_ps(a, b);     //  v / v
    _mm_store_ps(out, acc);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec_add4f(Vec out, const Vec v, float x, float y, float z, float w) {
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set_ps(x, y, z, w);
    acc = _mm_add_ps(a, b);     //  v + (x y z w)
    _mm_store_ps(out, acc);
}
void wem_Vec_sub4f(Vec out, const Vec v, float x, float y, float z, float w) {
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set_ps(x, y, z, w);
    acc = _mm_sub_ps(a, b);     //  v - (x y z w)
    _mm_store_ps(out, acc);
}
void wem_Vec_mul4f(Vec out, const Vec v, float x, float y, float z, float w) {
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set_ps(x, y, z, w);
    acc = _mm_mul_ps(a, b);     //  v * (x y z w)
    _mm_store_ps(out, acc);
}
void wem_Vec_div4f(Vec out, const Vec v, float x, float y, float z, float w) {
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set_ps(x, y, z, w);
    acc = _mm_div_ps(a, b);     //  v / (x y z w)
    _mm_store_ps(out, acc);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec_add1f(Vec out, const Vec v, float val) {
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set1_ps(val);
    acc = _mm_add_ps(a, b);     //  v + f
    _mm_store_ps(out, acc);
}
void wem_Vec_sub1f(Vec out, const Vec v, float val) {
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set1_ps(val);
    acc = _mm_sub_ps(a, b);     //  v - f
    _mm_store_ps(out, acc);
}
void wem_Vec_mul1f(Vec out, const Vec v, float val) {
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set1_ps(val);
    acc = _mm_mul_ps(a, b);     //  v * f
    _mm_store_ps(out, acc);
}
void wem_Vec_div1f(Vec out, const Vec v, float val) {
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set1_ps(val);
    acc = _mm_div_ps(a, b);     //  v / f
    _mm_store_ps(out, acc);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vec_sqrMagnitude(const Vec v) {
    __m128 a, acc;
    a = _mm_load_ps(v);
    acc = _mm_mul_ps(a, a);
    return acc[0] + acc[1] + acc[2] + acc[3];
}
float wem_Vec_magnitude(const Vec v) {
    __m128 a, acc;
    a = _mm_load_ps(v);
    acc = _mm_mul_ps(a, a);
    return sqrtf(acc[0] + acc[1] + acc[2] + acc[3]);
}
void wem_Vec_clampMagnitude(Vec out, const Vec v, float maxMagnitude) {
    float sqrmag = wem_Vec_sqrMagnitude(v);
    if (sqrmag > maxMagnitude) {
        __m128 a, b, c, acc;
        float mag = sqrtf(sqrmag);

        a = _mm_load_ps(v);
        b = _mm_set1_ps(mag);
        c = _mm_set1_ps(maxMagnitude);

        acc = _mm_div_ps(a, b);         // v /= mag
        acc = _mm_mul_ps(acc, c);       // v *= maxMag
        _mm_store_ps(out, acc);
        return;
    }
    wem_Vec_cpy(out, v);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec_norm(Vec out, const Vec v) {
    wem_Vec_div1f(out, v, wem_Vec_magnitude(v));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  POW2
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec_pow2(Vec out, const Vec v) {
    wem_Vec_mul(out, v, v);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DOT
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vec_dot(const Vec v1, const Vec v2) {
    Vec out;
    wem_Vec_mul(out, v1, v2);
    return out[0] + out[1] + out[2];
}
float wem_Vec_dotN(const Vec v1, const Vec v2) {
    Vec v1N, v2N;
    wem_Vec_norm(v1N, v1); wem_Vec_norm(v2N, v2);
    return wem_Vec_dot(v1N, v2N);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INVERSE
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec_inv(Vec out, const Vec v) {
    wem_Vec_mul1f(out, v, -1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CROSS
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec_cross(Vec out, const Vec v1, const Vec v2) {
    out[0] = v1[1] * v2[2] - v1[2] * v2[1];
    out[1] = v1[2] * v2[0] - v1[0] * v2[2];
    out[2] = v1[0] * v2[1] - v1[1] * v2[0];
    out[3] = 1;   
}
void wem_Vec_crossN(Vec out, Vec v1, Vec v2) {
    Vec cross;
    wem_Vec_cross(cross, v1, v2);
    wem_Vec_norm(out, cross);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  INTERPOLATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec_lerp(Vec out, const Vec from, const Vec to, float t) {
    __m128 a, b, acc, o_t, _t;

    a = _mm_load_ps(from);
    b = _mm_load_ps(to);

    o_t = _mm_set1_ps(1.0f - t);
    _t  = _mm_set1_ps(t);

    a = _mm_mul_ps(a, o_t);         //  from * (1.0f - t)
    b = _mm_mul_ps(a, _t);          //  to * t
    acc = _mm_add_ps(a, b);         //  from * (1.0f - t) + to * t
    _mm_store_ps(out, acc);
}
void wem_Vec_smoothstep(Vec out, const Vec from, const Vec to, float t) {
    t = CLAMP(t, 0, 1);
    float ttC = (t * t * (3.0f - 2.0f * t));
    
    __m128 a, b, acc, _ttC;

    a = _mm_load_ps(from);          //  start
    b = _mm_load_ps(to);            //  end
    _ttC = _mm_set1_ps(ttC);        //  (t * t * (3.0f - 2.0f * t));

    acc = _mm_sub_ps(b, a);         //  end - start
    acc = _mm_mul_ps(acc, _ttC);    //  ttC * (end - start)
    acc = _mm_add_ps(acc, a);       //  (ttC * (end - start)) + start
    _mm_store_ps(out, acc);
}
void wem_Vec_smootherstep(Vec out, const Vec from, const Vec to, float t) {
    t = CLAMP(t, 0, 1);
    float ttC = (t * t * t * (t * (6.0f * t - 15.0f) + 10.0f));
    
    __m128 a, b, acc, _ttC;

    a = _mm_load_ps(from);          //  start
    b = _mm_load_ps(to);            //  end
    _ttC = _mm_set1_ps(ttC);        //  (t * t * t * (t * (6.0f * t - 15.0f) + 10.0f))

    acc = _mm_sub_ps(b, a);         //  end - start
    acc = _mm_mul_ps(acc, _ttC);    //  ttC * (end - start)
    acc = _mm_add_ps(acc, a);       //  (ttC * (end - start)) + start
    _mm_store_ps(out, acc);
}
void wem_Vec_smoothstep_inverse(Vec out, const Vec from, const Vec to, float t) {
    t = CLAMP(t, 0, 1);
    float ttC = (0.5f - sinf(asinf(1.0f - 2.0f * t) / 3.0f));
    
    __m128 a, b, acc, _ttC;

    a = _mm_load_ps(from);          //  start
    b = _mm_load_ps(to);            //  end
    _ttC = _mm_set1_ps(ttC);        //  (0.5f - sinf(asinf(1.0f - 2.0f * t) / 3.0f))

    acc = _mm_sub_ps(b, a);         //  end - start
    acc = _mm_mul_ps(acc, _ttC);    //  ttC * (end - start)
    acc = _mm_add_ps(acc, a);       //  (ttC * (end - start)) + start
    _mm_store_ps(out, acc);
}
void wem_Vec_smoothDamp(Vec out, const Vec from, const Vec to, Vec velocity, float maxSpeed, float smoothTime, float timeDelta) {
    Vec change, ogTo, _to;
    wem_Vec_sub(change, from, to);
    wem_Vec_cpy(ogTo, to);

    float omega = 2.0f / smoothTime;
    float x     = omega * timeDelta;
    float exp   = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);

    float maxChange     = maxSpeed * smoothTime;
    float maxChangeSqr  = maxChange * maxChange;
    float sqrMag        = wem_Vec_sqrMagnitude(change);
    if (sqrMag > maxChangeSqr) {
        float mag = sqrtf(sqrMag);
        wem_Vec_div1f(change, change, mag);
        wem_Vec_mul1f(change, change, maxChange);
    }

    wem_Vec_sub(_to, from, change);

    Vec tmp;
    wem_Vec_mul1f(tmp, change, omega);
    wem_Vec_add(tmp, tmp, velocity);
    wem_Vec_mul1f(tmp, tmp, timeDelta);

    Vec velTmp;
    wem_Vec_cpy(velTmp, velocity);
    wem_Vec_mul1f(velocity, tmp, omega);
    wem_Vec_sub(velocity, velTmp, velocity);
    wem_Vec_mul1f(velocity, velocity, exp);

    wem_Vec_add(out, change, tmp);
    wem_Vec_mul1f(out, out, exp);
    wem_Vec_add(out, out, _to);

    Vec ogSubCurrent, outSubOg;
    wem_Vec_sub(ogSubCurrent, ogTo, from);
    wem_Vec_sub(outSubOg, out, ogTo);

    if (wem_Vec_dot(ogSubCurrent, outSubOg) > 0) {
        wem_Vec_cpy(out, ogTo);

        wem_Vec_sub(velocity, out, ogTo);
        wem_Vec_div1f(velocity, velocity, timeDelta);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ANGLE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vec_angleInRad(const Vec v1, const Vec v2) {
    float dot = wem_Vec_dotN(v1, v2);
    return acosf(dot);
}
float wem_Vec_angleInDeg(const Vec v1, const Vec v2) {
    return wem_Vec_angleInRad(v1, v2) * RAD2DEG; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  UTIL
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool wem_Vec_matches(const Vec v1, const Vec v2) {
    __m128 a, b, acc;
    a = _mm_load_ps(v1);
    b = _mm_load_ps(v2);
    acc = _mm_cmpeq_ps(a, b);
    return  _mm_movemask_ps(acc) == 0xf;    // test first 4 bits are 1
}
bool wem_Vec_inRange(const Vec v1, const Vec v2, float range) {
    Vec dir;
    wem_Vec_sub(dir, v1, v2);
    return wem_Vec_sqrMagnitude(dir) <= POW2(range);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec_print(const Vec v) {
    printf("%f %f %f %f", v[0], v[1], v[2], v[3]);
}

#endif
#endif