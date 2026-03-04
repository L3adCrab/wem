#ifndef WEM_INTRINSICS_BEZIER_H
#define WEM_INTRINSICS_BEZIER_H

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

#include "datatypes.h"

#define WEMDEF extern

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

#ifdef WEM_INTR_IMPLEMENTATION 

#include <memory.h>
#include <immintrin.h>

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
    t = CLAMP(t, 0, 1);
    
    __m128 _beg, _end, acc;
    _beg = _mm_load_ps(bezier);
    _end = _mm_load_ps(bezier + 4);
    
    //  (beg * (1-t)) + (end * t)
    acc = _mm_add_ps(
        _mm_mul_ps(_beg, _mm_set_ps1(1.0f - t)),
        _mm_mul_ps(_end, _mm_set_ps1(t))
    );
    _mm_store_ps(out, acc);
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
    t = CLAMP(t, 0, 1);
    
    __m128 _beg, _han, _end, acc;
    __m128 h1, h2;
    _beg = _mm_load_ps(bezier + 0);
    _han = _mm_load_ps(bezier + 4);
    _end = _mm_load_ps(bezier + 8);
    
    __m128 _t       = _mm_set_ps1(t);
    __m128 oneMinT  = _mm_set_ps1(1.0f - t);
    
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
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CUBIC
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_BezierCubic_set(BezierCubic out, const Vec4 beg, const Vec4 handle1, const Vec4 handle2, const Vec4 end) {
    memcpy(out + 0, beg,     sizeof(vec4));
    memcpy(out + 4, handle1, sizeof(vec4));
    memcpy(out + 8, handle2, sizeof(vec4));
    memcpy(out + 12, end,    sizeof(vec4));
}
void wem_BezierCubic_get(Vec4 outBeg, Vec4 outHandle1, Vec4 outHandle2, Vec4 outEnd, const BezierCubic bezier) {
    if (outBeg)     memcpy(outBeg,      bezier + 0, sizeof(Vec4));
    if (outHandle1) memcpy(outHandle1,  bezier + 4, sizeof(Vec4));
    if (outHandle2) memcpy(outHandle2,  bezier + 8, sizeof(Vec4));
    if (outEnd)     memcpy(outEnd,      bezier + 12, sizeof(Vec4));
}
void wem_BezierCubic_evaluate(Vec4 out, const BezierCubic bezier, float t) {
    t = CLAMP(t, 0, 1);

    __m128 _beg, _han1, _han2, _end, bq1, bq2, acc;
    __m128 h1, h2;
    _beg = _mm_load_ps(bezier + 0);
    _han1 = _mm_load_ps(bezier + 4);
    _han2 = _mm_load_ps(bezier + 8);
    _end = _mm_load_ps(bezier + 12);
    
    __m128 _t       = _mm_set_ps1(t);
    __m128 oneMinT  = _mm_set_ps1(1.0f - t);
    
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
}

#endif
#endif