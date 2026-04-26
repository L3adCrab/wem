#ifndef WEM_VEC_H
#define WEM_VEC_H

#ifdef WEMDLL
    #ifdef _WIN32
        #ifdef DLLBUILD
            #define WEMDEF __declspec(dllexport)
        #else
            #define WEMDEF __declspec(dllimport)
        #endif
    #else
        #define WEMDEF
    #endif
#else
    #define WEMDEF extern
#endif

#include "datatypes.h"

WEMDEF void wem_Vec_set(Vec out, float x, float y, float z, float w);
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
//  VEC * MAT4

WEMDEF void wem_Vec_mulMat4(Vec out, const Vec v, const Mat4 m);
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

#ifdef WEM_IMPLEMENTATION

#include <stdio.h>
#include <math.h>
#include <immintrin.h>

#include "macros.h"

void wem_Vec_set(Vec out, float x, float y, float z, float w) {
    out[0] = x; out[1] = y, out[2] = z, out[3] = w;
}
void wem_Vec_cpy(Vec out, const Vec v) {
    memcpy(out, v, sizeof(Vec));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ VEC
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec_add(Vec out, const Vec v1, const Vec v2) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v1);
    b = _mm_load_ps(v2);
    acc = _mm_add_ps(a, b);     //  v * v
    _mm_store_ps(out, acc);
    #else
    out[0] = v1[0] + v2[0];
    out[1] = v1[1] + v2[1];
    out[2] = v1[2] + v2[2];
    out[3] = v1[3] + v2[3];
    #endif
}
void wem_Vec_sub(Vec out, const Vec v1, const Vec v2) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v1);
    b = _mm_load_ps(v2);
    acc = _mm_sub_ps(a, b);     //  v - v
    _mm_store_ps(out, acc);
    #else
    out[0] = v1[0] - v2[0];
    out[1] = v1[1] - v2[1];
    out[2] = v1[2] - v2[2];
    out[3] = v1[3] - v2[3];
    #endif
}
void wem_Vec_mul(Vec out, const Vec v1, const Vec v2) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v1);
    b = _mm_load_ps(v2);
    acc = _mm_mul_ps(a, b);     //  v * v
    _mm_store_ps(out, acc);
    #else
    out[0] = v1[0] * v2[0];
    out[1] = v1[1] * v2[1];
    out[2] = v1[2] * v2[2];
    out[3] = v1[3] * v2[3];
    #endif
}
void wem_Vec_div(Vec out, const Vec v1, const Vec v2) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v1);
    b = _mm_load_ps(v2);
    acc = _mm_div_ps(a, b);     //  v / v
    _mm_store_ps(out, acc);
    #else
    out[0] = v1[0] / v2[0];
    out[1] = v1[1] / v2[1];
    out[2] = v1[2] / v2[2];
    out[3] = v1[3] / v2[3];
    #endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ XYZW
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec_add4f(Vec out, const Vec v, float x, float y, float z, float w) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set_ps(w, z, y, x);
    acc = _mm_add_ps(a, b);     //  v + (x y z w)
    _mm_store_ps(out, acc);
    #else
    out[0] = v[0] + x;
    out[1] = v[1] + y;
    out[2] = v[2] + z;
    out[3] = v[3] + w;
    #endif
}
void wem_Vec_sub4f(Vec out, const Vec v, float x, float y, float z, float w) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set_ps(w, z, y, x);
    acc = _mm_sub_ps(a, b);     //  v - (x y z w)
    _mm_store_ps(out, acc);
    #else
    out[0] = v[0] - x;
    out[1] = v[1] - y;
    out[2] = v[2] - z;
    out[3] = v[3] - w;
    #endif
}
void wem_Vec_mul4f(Vec out, const Vec v, float x, float y, float z, float w) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set_ps(w, z, y, x);
    acc = _mm_mul_ps(a, b);     //  v * (x y z w)
    _mm_store_ps(out, acc);
    #else
    out[0] = v[0] * x;
    out[1] = v[1] * y;
    out[2] = v[2] * z;
    out[3] = v[3] * w;
    #endif
}
void wem_Vec_div4f(Vec out, const Vec v, float x, float y, float z, float w) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set_ps(w, z, y, x);
    acc = _mm_div_ps(a, b);     //  v / (x y z w)
    _mm_store_ps(out, acc);
    #else
    out[0] = v[0] / x;
    out[1] = v[1] / y;
    out[2] = v[2] / z;
    out[3] = v[3] / w;
    #endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC +-*/ FFFF
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec_add1f(Vec out, const Vec v, float val) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set1_ps(val);
    acc = _mm_add_ps(a, b);     //  v + f
    _mm_store_ps(out, acc);
    #else
    out[0] = v[0] + val;
    out[1] = v[1] + val;
    out[2] = v[2] + val;
    out[3] = v[3] + val;
    #endif
}
void wem_Vec_sub1f(Vec out, const Vec v, float val) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set1_ps(val);
    acc = _mm_sub_ps(a, b);     //  v - f
    _mm_store_ps(out, acc);
    #else
    out[0] = v[0] - val;
    out[1] = v[1] - val;
    out[2] = v[2] - val;
    out[3] = v[3] - val;
    #endif
}
void wem_Vec_mul1f(Vec out, const Vec v, float val) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set1_ps(val);
    acc = _mm_mul_ps(a, b);     //  v * f
    _mm_store_ps(out, acc);
    #else
    out[0] = v[0] * val;
    out[1] = v[1] * val;
    out[2] = v[2] * val;
    out[3] = v[3] * val;
    #endif
}
void wem_Vec_div1f(Vec out, const Vec v, float val) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v);
    b = _mm_set1_ps(val);
    acc = _mm_div_ps(a, b);     //  v / f
    _mm_store_ps(out, acc);
    #else
    out[0] = v[0] / val;
    out[1] = v[1] / val;
    out[2] = v[2] / val;
    out[3] = v[3] / val;
    #endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VEC * MAT4
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec_mulMat4(Vec out, const Vec v, const Mat4 m) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 x, y, z, w, acc;
    __m128 row1, row2, row3, row4;

    x = _mm_set_ps1(v[0]);
    y = _mm_set_ps1(v[1]);
    z = _mm_set_ps1(v[2]);
    w = _mm_set_ps1(v[3]);

    row1 = _mm_load_ps(m);
    row2 = _mm_load_ps(m + 4);
    row3 = _mm_load_ps(m + 8);
    row4 = _mm_load_ps(m + 12);
    
    acc = _mm_add_ps(
        _mm_add_ps(
            _mm_mul_ps(x, row1),
            _mm_mul_ps(y, row2)
        ),
        _mm_add_ps(
            _mm_mul_ps(z, row3),
            _mm_mul_ps(w, row4)
        )
    );
    _mm_store_ps(out, acc);
    #else
    Vec tmp = {0};
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            tmp[j] += m[4 * j + i] * v[i];
        }
    }
    memcpy(out, tmp, sizeof(Vec));
    #endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MAGNITUDE
/////////////////////////////////////////////////////////////////////////////////////////////////////

float wem_Vec_sqrMagnitude(const Vec v) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, acc;
    a = _mm_load_ps(v);
    acc = _mm_mul_ps(a, a);
    return acc[0] + acc[1] + acc[2] + acc[3];
    #else
    return POW2(v[0]) + POW2(v[1]) + POW2(v[2]) + POW2(v[3]);
    #endif
}
float wem_Vec_magnitude(const Vec v) {
    return sqrtf(wem_Vec_sqrMagnitude(v));
}
void wem_Vec_clampMagnitude(Vec out, const Vec v, float maxMagnitude) {
    float sqrmag = wem_Vec_sqrMagnitude(v);
    if (sqrmag > POW2(maxMagnitude)) {
        wem_Vec_div1f(out, v, sqrtf(sqrmag));
        wem_Vec_mul1f(out, out, maxMagnitude);
        return;
    }
    wem_Vec_cpy(out, v);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  NORMALIZATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Vec_norm(Vec out, const Vec v) {
    float mag = wem_Vec_magnitude(v);
    wem_Vec_div1f(out, v, mag);
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
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v1);
    b = _mm_load_ps(v2);
    acc = _mm_mul_ps(a, b);     //  v * v

    acc = _mm_hadd_ps(acc, acc);
    acc = _mm_hadd_ps(acc, acc);
    return acc[0];
    #else
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3]; 
    #endif
}
float wem_Vec_dotN(const Vec v1, const Vec v2) {
    Vec v1N, v2N;
    wem_Vec_norm(v1N, v1);
    wem_Vec_norm(v2N, v2);
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
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v1);
    b = _mm_load_ps(v2);

    __m128 ah1 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
    __m128 ah2 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 1, 0, 2));

    __m128 bh1 = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 1, 0, 2));
    __m128 bh2 = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));

    __m128 h1 = _mm_mul_ps(ah1, bh1);
    __m128 h2 = _mm_mul_ps(ah2, bh2);

    acc = _mm_sub_ps(h1, h2);
    _mm_store_ps(out, acc);
    out[3] = 1;
    #else
    out[0] = v1[1] * v2[2] - v1[2] * v2[1];
    out[1] = v1[2] * v2[0] - v1[0] * v2[2];
    out[2] = v1[0] * v2[1] - v1[1] * v2[0];
    out[3] = 1;
    #endif
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
    t = CLAMP01(t);
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc, o_t, _t;

    a = _mm_load_ps(from);
    b = _mm_load_ps(to);

    o_t = _mm_set1_ps(1.0f - t);
    _t  = _mm_set1_ps(t);

    a = _mm_mul_ps(a, o_t);         //  from * (1.0f - t)
    b = _mm_mul_ps(a, _t);          //  to * t
    acc = _mm_add_ps(a, b);         //  from * (1.0f - t) + to * t
    _mm_store_ps(out, acc);
    #else
    //  from * (1.0f - t) + to * t
    float o_t = 1.0f - t;
    out[0] = from[0] * o_t + to[0] * t;
    out[1] = from[1] * o_t + to[1] * t;
    out[2] = from[2] * o_t + to[2] * t;
    out[3] = from[3] * o_t + to[3] * t;
    #endif
}
void wem_Vec_smoothstep(Vec out, const Vec from, const Vec to, float t) {
    t = CLAMP01(t);
    float ttC = (t * t * (3.0f - 2.0f * t));
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc, _ttC;

    a = _mm_load_ps(from);          //  start
    b = _mm_load_ps(to);            //  end
    _ttC = _mm_set1_ps(ttC);        //  (t * t * (3.0f - 2.0f * t));

    acc = _mm_sub_ps(b, a);         //  end - start
    acc = _mm_mul_ps(acc, _ttC);    //  ttC * (end - start)
    acc = _mm_add_ps(acc, a);       //  (ttC * (end - start)) + start
    _mm_store_ps(out, acc);
    #else
    //  (ttC * (end - start)) + start
    out[0] = ttC * (to[0] - from[0]) + from[0];
    out[1] = ttC * (to[1] - from[1]) + from[1];
    out[2] = ttC * (to[2] - from[2]) + from[2];
    out[3] = ttC * (to[3] - from[3]) + from[3];
    #endif
}
void wem_Vec_smootherstep(Vec out, const Vec from, const Vec to, float t) {
    t = CLAMP(t, 0, 1);
    float ttC = (t * t * t * (t * (6.0f * t - 15.0f) + 10.0f));
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    
    __m128 a, b, acc, _ttC;

    a = _mm_load_ps(from);          //  start
    b = _mm_load_ps(to);            //  end
    _ttC = _mm_set1_ps(ttC);        //  (t * t * t * (t * (6.0f * t - 15.0f) + 10.0f))

    acc = _mm_sub_ps(b, a);         //  end - start
    acc = _mm_mul_ps(acc, _ttC);    //  ttC * (end - start)
    acc = _mm_add_ps(acc, a);       //  (ttC * (end - start)) + start
    _mm_store_ps(out, acc);
    #else
    //  (ttC * (end - start)) + start
    out[0] = ttC * (to[0] - from[0]) + from[0];
    out[1] = ttC * (to[1] - from[1]) + from[1];
    out[2] = ttC * (to[2] - from[2]) + from[2];
    out[3] = ttC * (to[3] - from[3]) + from[3];
    #endif
}
void wem_Vec_smoothstep_inverse(Vec out, const Vec from, const Vec to, float t) {
    t = CLAMP(t, 0, 1);
    float ttC = (0.5f - sinf(asinf(1.0f - 2.0f * t) / 3.0f));
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    
    __m128 a, b, acc, _ttC;

    a = _mm_load_ps(from);          //  start
    b = _mm_load_ps(to);            //  end
    _ttC = _mm_set1_ps(ttC);        //  (0.5f - sinf(asinf(1.0f - 2.0f * t) / 3.0f))

    acc = _mm_sub_ps(b, a);         //  end - start
    acc = _mm_mul_ps(acc, _ttC);    //  ttC * (end - start)
    acc = _mm_add_ps(acc, a);       //  (ttC * (end - start)) + start
    _mm_store_ps(out, acc);
    #else
    //  (ttC * (end - start)) + start
    out[0] = ttC * (to[0] - from[0]) + from[0];
    out[1] = ttC * (to[1] - from[1]) + from[1];
    out[2] = ttC * (to[2] - from[2]) + from[2];
    out[3] = ttC * (to[3] - from[3]) + from[3];
    #endif
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
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b, acc;
    a = _mm_load_ps(v1);
    b = _mm_load_ps(v2);
    acc = _mm_cmpeq_ps(a, b);
    return  _mm_movemask_ps(acc) == 0xf;    // test first 4 bits are 1
    #else
    return v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2] && v1[3] == v2[3];
    #endif
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
    printf("%f %f %f %f\n", v[0], v[1], v[2], v[3]);
}

#endif
#endif