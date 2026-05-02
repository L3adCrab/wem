#ifndef WEM_BEZIER_H
#define WEM_BEZIER_H

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

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  LINEAR

WEMDEF void wem_BezierLinear_set(BezierLinear out, const Vec4 beg, const Vec4 end);
WEMDEF void wem_BezierLinear_get(Vec4 outBeg, Vec4 outEnd, const BezierLinear bezier);
WEMDEF void wem_BezierLinear_evaluate(Vec4 out, const BezierLinear bezier, float t);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  QUADRATIC

WEMDEF void wem_BezierQuad_set(BezierQuad out, const Vec4 beg, const Vec4 handle, const Vec4 end);
WEMDEF void wem_BezierQuad_get(Vec4 outBeg, Vec4 outHandle, Vec4 outEnd, const BezierQuad bezier);
WEMDEF void wem_BezierQuad_evaluate(Vec4 out, const BezierQuad bezier, float t);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CUBIC

WEMDEF void wem_BezierCubic_set(BezierCubic out, const Vec4 beg, const Vec4 handle1, const Vec4 handle2, const Vec4 end);
WEMDEF void wem_BezierCubic_get(Vec4 outBeg, Vec4 outHandle1, Vec4 outHandle2, Vec4 outEnd, const BezierCubic bezier);
WEMDEF void wem_BezierCubic_evaluate(Vec4 out, const BezierCubic bezier, float t);

#ifdef WEM_IMPLEMENTATION 

#include <memory.h>
#include <immintrin.h>

#include "vector4.h"
#include "macros.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  LINEAR
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_BezierLinear_set(BezierLinear out, const Vec4 beg, const Vec4 end) {
    memcpy(out + 0, beg, sizeof(Vec4));
    memcpy(out + 4, end, sizeof(Vec4));
}
void wem_BezierLinear_get(Vec4 outBeg, Vec4 outEnd, const BezierLinear bezier) {
    if (outBeg) memcpy(outBeg, bezier + 0, sizeof(Vec4));
    if (outEnd) memcpy(outEnd, bezier + 4, sizeof(Vec4));
}
void wem_BezierLinear_evaluate(Vec4 out, const BezierLinear bezier, float t) {
    t = CLAMP01(t);
    float o_t = 1.0f - t;
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    
    __m128 _beg, _end, acc;
    _beg = _mm_load_ps(bezier);
    _end = _mm_load_ps(bezier + 4);
    
    //  (beg * (1-t)) + (end * t)
    acc = _mm_add_ps(
        _mm_mul_ps(_beg, _mm_set_ps1(o_t)),
        _mm_mul_ps(_end, _mm_set_ps1(t))
    );
    _mm_store_ps(out, acc);
    #else
    Vec4 beg, end;
    wem_Vec4_mul1f(beg, bezier, o_t);       //  (beg * (1-t))
    wem_Vec4_mul1f(end, bezier + 4, t);     //  (end * t)
    wem_Vec4_add(out, beg, end);            //  (beg * (1-t)) + (end * t)
    #endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  QUADRATIC
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_BezierQuad_set(BezierQuad out, const Vec4 beg, const Vec4 handle, const Vec4 end) {
    memcpy(out + 0, beg, sizeof(Vec4));
    memcpy(out + 4, handle, sizeof(Vec4));
    memcpy(out + 8, end, sizeof(Vec4));
}
void wem_BezierQuad_get(Vec4 outBeg, Vec4 outHandle, Vec4 outEnd, const BezierQuad bezier) {
    if (outBeg)     memcpy(outBeg,      bezier + 0, sizeof(Vec4));
    if (outHandle)  memcpy(outHandle,   bezier + 4, sizeof(Vec4));
    if (outEnd)     memcpy(outEnd,      bezier + 8, sizeof(Vec4));
}
void wem_BezierQuad_evaluate(Vec4 out, const BezierQuad bezier, float t) {
    t = CLAMP01(t);
    float o_t = 1.0f - t;
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    
    __m128 _beg, _han, _end, acc;
    __m128 h1, h2;
    _beg = _mm_load_ps(bezier + 0);
    _han = _mm_load_ps(bezier + 4);
    _end = _mm_load_ps(bezier + 8);
    
    __m128 _t       = _mm_set_ps1(t);
    __m128 oneMinT  = _mm_set_ps1(o_t);
    
    //  (beg * (1-t) + han * t)(1-t) + (han * (1-t) + end * t)t
    //  (beg * (1-t) + han * t)(1-t)
    h1 = _mm_mul_ps(
        _mm_add_ps(                     // (beg * (1-t) + han * t)
            _mm_mul_ps(_beg, oneMinT),  // beg * (1-t)
            _mm_mul_ps(_han, _t)        // han * t
        ),
        oneMinT       
    );
    //  (han * (1-t) + end * t)t
    h2 = _mm_mul_ps(
        _mm_add_ps(                     // (han * (1-t) + end * t)
            _mm_mul_ps(_han, oneMinT),  // han * (1-t)
            _mm_mul_ps(_end, _t)        // end * t
        ),
        _t
    );
    acc = _mm_add_ps(h1, h2);
    _mm_store_ps(out, acc);
    #else
    Vec4 h1, h2;
    Vec4 tmp;
    //  (beg * (1-t) + han * t)(1-t) + (han * (1-t) + end * t)t
    //  (beg * (1-t) + han * t)(1-t)
    wem_Vec4_mul1f(h1, bezier, o_t);        //  beg * (1-t) 
    wem_Vec4_mul1f(tmp, bezier + 4, t);     //  han * t
    wem_Vec4_add(h1, h1, tmp);              //  (beg * (1-t) + han * t)
    wem_Vec4_mul1f(h1, h1, o_t);            //  (beg * (1-t) + han * t)(1-t)

    //  (han * (1-t) + end * t)t    
    wem_Vec4_mul1f(h2, bezier + 4, o_t);    //  han * (1-t)
    wem_Vec4_mul1f(tmp, bezier + 8, t);     //  end * t
    wem_Vec4_add(h2, h2, tmp);              //  (han * (1-t) + end * t)
    wem_Vec4_mul1f(h2, h2, t);              //  (han * (1-t) + end * t)t

    //  (beg * (1-t) + han * t)(1-t) + (han * (1-t) + end * t)t
    wem_Vec4_add(out, h1, h2);
    #endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CUBIC
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_BezierCubic_set(BezierCubic out, const Vec4 beg, const Vec4 handle1, const Vec4 handle2, const Vec4 end) {
    memcpy(out + 0, beg,     sizeof(Vec4));
    memcpy(out + 4, handle1, sizeof(Vec4));
    memcpy(out + 8, handle2, sizeof(Vec4));
    memcpy(out + 12, end,    sizeof(Vec4));
}
void wem_BezierCubic_get(Vec4 outBeg, Vec4 outHandle1, Vec4 outHandle2, Vec4 outEnd, const BezierCubic bezier) {
    if (outBeg)     memcpy(outBeg,      bezier + 0, sizeof(Vec4));
    if (outHandle1) memcpy(outHandle1,  bezier + 4, sizeof(Vec4));
    if (outHandle2) memcpy(outHandle2,  bezier + 8, sizeof(Vec4));
    if (outEnd)     memcpy(outEnd,      bezier + 12, sizeof(Vec4));
}
void wem_BezierCubic_evaluate(Vec4 out, const BezierCubic bezier, float t) {
    t = CLAMP01(t);
    float o_t = 1.0f - t;
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))

    __m128 _beg, _han1, _han2, _end, bq1, bq2, acc;
    __m128 h1, h2;
    _beg = _mm_load_ps(bezier + 0);
    _han1 = _mm_load_ps(bezier + 4);
    _han2 = _mm_load_ps(bezier + 8);
    _end = _mm_load_ps(bezier + 12);
    
    __m128 _t       = _mm_set_ps1(t);
    __m128 oneMinT  = _mm_set_ps1(o_t);
    
    //  (beg * (1-t) + han1 * t)(1-t) + (han1 * (1-t) + han2 * t)t
    //  (beg * (1-t) + han1 * t)(1-t)
    h1 = _mm_mul_ps(
        _mm_add_ps(                     // (beg * (1-t) + han1 * t)
            _mm_mul_ps(_beg, oneMinT),  // beg * (1-t)
            _mm_mul_ps(_han1, _t)       // han1 * t
        ),
        oneMinT       
    );
    //  (han1 * (1-t) + han2 * t)t
    h2 = _mm_mul_ps(
        _mm_add_ps(                     // (han1 * (1-t) + han2 * t)
            _mm_mul_ps(_han1, oneMinT), // han1 * (1-t)
            _mm_mul_ps(_han2, _t)       // han2 * t
        ),
        _t
    );
    bq1 = _mm_add_ps(h1, h2);           // quad bezier of beg, handle1 and handle2

    //  (han1 * (1-t) + han2 * t)(1-t) + (han2 * (1-t) + end * t)t
    //  (han1 * (1-t) + han2 * t)(1-t)
    h1 = _mm_mul_ps(
        _mm_add_ps(                     // (han1 * (1-t) + han2 * t) 
            _mm_mul_ps(_han1, oneMinT), // han1 * (1-t)
            _mm_mul_ps(_han2, _t)       // han2 * t
        ),
        oneMinT       
    );
    //  (han2 * (1-t) + end * t)t
    h2 = _mm_mul_ps(
        _mm_add_ps(                     // (han2 * (1-t) + end * t) 
            _mm_mul_ps(_han2, oneMinT), // han1 * (1-t)
            _mm_mul_ps(_end, _t)        // end * t
        ),
        _t
    );
    bq2 = _mm_add_ps(h1, h2);           // quad bezier of handle1, handle2 and end

    acc = _mm_add_ps(
        _mm_mul_ps(bq1, oneMinT),       // bezierQuad(beg, handle1, handle2) * (1.0f - t)
        _mm_mul_ps(bq2, _t)             // bezierQuad(handle1, handle2, end) * t
    );
    _mm_store_ps(out, acc);
    #else
    //  bQ(b0, t)(1-t) + bQ(b1, t)t
    Vec4 b1, b2;
    wem_BezierQuad_evaluate(b1, bezier, t);     //  bQ(b0, t)
    wem_Vec4_mul1f(b1, b1, o_t);                //  bQ(b0, t)(1-t) 
    
    wem_BezierQuad_evaluate(b2, bezier + 4, t); //  bQ(b1, t)
    wem_Vec4_mul1f(b2, b2, t);                  //  bQ(b1, t)t

    wem_Vec4_add(out, b1, b2);                  //  bQ(b0, t)(1-t) + bQ(b1, t)t
    #endif
}

#endif
#endif