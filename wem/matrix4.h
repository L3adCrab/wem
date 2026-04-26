#ifndef WEM_MATRIX_4_H
#define WEM_MATRIX_4_H

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
//  ALLOCATION

WEMDEF void wem_Mat4_zero(Mat4 out);
WEMDEF void wem_Mat4_identity(Mat4 out);
WEMDEF void wem_Mat4_cpy(Mat4 out, const Mat4 m);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADDITION

WEMDEF void wem_Mat4_add(Mat4 out, const Mat4 m1, const Mat4 m2);
WEMDEF void wem_Mat4_add1f(Mat4 out, const Mat4 m, char row, char column, float val);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SUBTRACTION

WEMDEF void wem_Mat4_sub(Mat4 out, const Mat4 m1, const Mat4 m2);
WEMDEF void wem_Mat4_sub1f(Mat4 out, const Mat4 m, char row, char column, float val);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MULTIPLICATION

WEMDEF void wem_Mat4_scalarMul(Mat4 out, const Mat4 m, float val);
WEMDEF void wem_Mat4_mul(Mat4 out, const Mat4 m1, const Mat4 m2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  TRANSPOSITION

WEMDEF void wem_Mat4_transpose(Mat4 out, const Mat4 m);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  TRANSLATION

WEMDEF void wem_Mat4_translation(Mat4 out, const Vec3 position, const Vec3 scale);
WEMDEF void wem_Mat4_setTranslation(Mat4 out, const Mat4 m, const Vec3 position);
WEMDEF void wem_Mat4_translate(Mat4 out, const Mat4 m, const Vec3 position);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SCALAR

WEMDEF void wem_Mat4_scalar(Mat4 out, const Vec3 scale);
WEMDEF void wem_Mat4_setScale(Mat4 out, const Mat4 m, const Vec3 scale);
WEMDEF void wem_Mat4_scale(Mat4 out, const Mat4 m, const Vec3 scale);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VIEW

WEMDEF void wem_Mat4_lookAt(Mat4 out, const Vec3 position, const Vec3 target, const Vec3 camUp);
WEMDEF void wem_Mat4_view(Mat4 out, const Vec3 position, const Vec3 forward, const Vec3 camUp);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  PROJECTION

WEMDEF void wem_Mat4_ortho(Mat4 out, float zoom, float aspectRatio, float near, float far);
WEMDEF void wem_Mat4_perspective(Mat4 out, float fovDeg, float aspectRatio, float near, float far);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_Mat4_print(Mat4 m);

#ifdef WEM_IMPLEMENTATION

#include <immintrin.h>
#include "vector3.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ALLOCATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Mat4_zero(Mat4 out) {
    memset(out, 0, sizeof(Mat4));
}
void wem_Mat4_identity(Mat4 out) {
    wem_Mat4_zero(out);
    out[0] = 1; out[5] = 1; out[10] = 1; out[15] = 1;
}
void wem_Mat4_cpy(Mat4 out, const Mat4 m) {
    memcpy(out, m, sizeof(Mat4));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADDITION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Mat4_add(Mat4 out, const Mat4 m1, const Mat4 m2) {
    #if defined(__OPTIMIZE__) && defined(__AVX__)
    __m256 a, b, acc;
    
    a = _mm256_load_ps(m2);
    b = _mm256_load_ps(m2);
    acc = _mm256_add_ps(a, b);
    _mm256_store_ps(out, acc);

    a = _mm256_load_ps(m1 + 8);
    b = _mm256_load_ps(m2 + 8);
    acc = _mm256_add_ps(a, b);
    _mm256_store_ps(out + 8, acc);

    #elif defined(__OPTIMIZE__) && defined(__SSE3__)
    __m128 a, b, acc;
    a = _mm_load_ps(m1);
    b = _mm_load_ps(m2);
    acc = _mm_add_ps(a, b);
    _mm_store_ps(out, acc);

    a = _mm_load_ps(m1 + 4);
    b = _mm_load_ps(m2 + 4);
    acc = _mm_add_ps(a, b);
    _mm_store_ps(out + 4, acc);

    a = _mm_load_ps(m1 + 8);
    b = _mm_load_ps(m2 + 8);
    acc = _mm_add_ps(a, b);
    _mm_store_ps(out + 8, acc);

    a = _mm_load_ps(m1 + 12);
    b = _mm_load_ps(m2 + 12);
    acc = _mm_add_ps(a, b);
    _mm_store_ps(out + 12, acc);
    #else
    for (size_t i = 0; i < 16; i++)
    {
        out[i] = m1[i] + m2[i];
    }
    #endif
}
void wem_Mat4_add1f(Mat4 out, const Mat4 m, char row, char column, float val) {
    memcpy(out, m, sizeof(Mat4));
    out[4 * column + row] += val;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SUBTRACTION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Mat4_sub(Mat4 out, const Mat4 m1, const Mat4 m2) {
    #if defined(__OPTIMIZE__) && defined(__AVX__)
    __m256 a, b, acc;
    
    a = _mm256_load_ps(m1);
    b = _mm256_load_ps(m2);
    acc = _mm256_sub_ps(a, b);
    _mm256_store_ps(out, acc);

    a = _mm256_load_ps(m1 + 8);
    b = _mm256_load_ps(m2 + 8);
    acc = _mm256_sub_ps(a, b);
    _mm256_store_ps(out + 8, acc);

    #elif defined(__OPTIMIZE__) && defined(__SSE3__)
    __m128 a, b, acc;
    a = _mm_load_ps(m1);
    b = _mm_load_ps(m2);
    acc = _mm_sub_ps(a, b);
    _mm_store_ps(out, acc);

    a = _mm_load_ps(m1 + 4);
    b = _mm_load_ps(m2 + 4);
    acc = _mm_sub_ps(a, b);
    _mm_store_ps(out + 4, acc);

    a = _mm_load_ps(m1 + 8);
    b = _mm_load_ps(m2 + 8);
    acc = _mm_sub_ps(a, b);
    _mm_store_ps(out + 8, acc);

    a = _mm_load_ps(m1 + 12);
    b = _mm_load_ps(m2 + 12);
    acc = _mm_sub_ps(a, b);
    _mm_store_ps(out + 12, acc);
    #else
    for (size_t i = 0; i < 16; i++)
    {
        out[i] = m1[i] - m2[i];
    }
    #endif
}
void wem_Mat4_sub1f(Mat4 out, const Mat4 m, char row, char column, float val) {
    memcpy(out, m, sizeof(Mat4));
    out[4 * column + row] -= val;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MULTIPLICATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Mat4_scalarMul(Mat4 out, const Mat4 m, float val) {
    #if defined(__OPTIMIZE__) && defined(__AVX__)
    __m256 a, b, acc;
    a = _mm256_load_ps(m);
    b = _mm256_set1_ps(val);
    acc = _mm256_mul_ps(a, b);
    _mm256_store_ps(out, acc);

    a = _mm256_load_ps(m + 8);
    acc = _mm256_mul_ps(a, b);
    _mm256_store_ps(out + 8, acc);
    #elif defined(__OPTIMIZE__) && defined(__SSE3__)
    __m128 a, b, acc;
    a = _mm_load_ps(m);
    b = _mm_set1_ps(val);
    acc = _mm_mul_ps(a, b);
    _mm_store_ps(out, acc);

    a = _mm_load_ps(m + 4);
    acc = _mm_mul_ps(a, b);
    _mm_store_ps(out + 4, acc);

    a = _mm_load_ps(m + 8);
    acc = _mm_mul_ps(a, b);
    _mm_store_ps(out + 8, acc);

    a = _mm_load_ps(m + 12);
    acc = _mm_mul_ps(a, b);
    _mm_store_ps(out + 12, acc);
    #else
    for (size_t i = 0; i < 16; i++)
    {
        out[i] = m[i] * val;
    }
    #endif
}
void wem_Mat4_mul(Mat4 out, const Mat4 m1, const Mat4 m2) {
    #if defined(__OPTIMIZE__) && defined(__AVX__)
    __m128 row1, row2, row3, row4;
    row1 = _mm_load_ps(m2 + 0);
    row2 = _mm_load_ps(m2 + 4);
    row3 = _mm_load_ps(m2 + 8);
    row4 = _mm_load_ps(m2 + 12);
    
    __m256 AD, EH, IL, MP;
    AD = _mm256_set_m128(row1, row1);
    EH = _mm256_set_m128(row2, row2);
    IL = _mm256_set_m128(row3, row3);
    MP = _mm256_set_m128(row4, row4);
   
    __m256 a1, a2, a3, a4, acc;
    for (uint32_t i = 0; i < 2; i++)
    {
        a1 = _mm256_setr_m128(_mm_set_ps1(m1[8 * i + 0]), _mm_set_ps1(m1[8 * i + 4]));
        a2 = _mm256_setr_m128(_mm_set_ps1(m1[8 * i + 1]), _mm_set_ps1(m1[8 * i + 5]));
        a3 = _mm256_setr_m128(_mm_set_ps1(m1[8 * i + 2]), _mm_set_ps1(m1[8 * i + 6]));
        a4 = _mm256_setr_m128(_mm_set_ps1(m1[8 * i + 3]), _mm_set_ps1(m1[8 * i + 7]));
        
        acc = _mm256_add_ps(
            _mm256_add_ps (
                _mm256_mul_ps(a1, AD),
                _mm256_mul_ps(a2, EH)
            ),
            _mm256_add_ps(
                _mm256_mul_ps(a3, IL),
                _mm256_mul_ps(a4, MP)
            )
        );
        _mm256_store_ps(out + 8 * i, acc);
    }
    #elif defined(__OPTIMIZE__) && defined(__SSE3__)
    __m128 row1, row2, row3, row4, acc;
    __m128 col1, col2, col3, col4;
    row1 = _mm_load_ps(m2 + 0);
    row2 = _mm_load_ps(m2 + 4);
    row3 = _mm_load_ps(m2 + 8);
    row4 = _mm_load_ps(m2 + 12);

    for (uint32_t i = 0; i < 4; i++)
    {
        col1 = _mm_set1_ps(m1[4 * i]);
        col2 = _mm_set1_ps(m1[4 * i + 1]);
        col3 = _mm_set1_ps(m1[4 * i + 2]);
        col4 = _mm_set1_ps(m1[4 * i + 3]);
        acc = _mm_add_ps(
            _mm_add_ps(
                _mm_mul_ps(col1, row1),
                _mm_mul_ps(col2, row2)),
            _mm_add_ps(
                _mm_mul_ps(col3, row3),
                _mm_mul_ps(col4, row4))
        );
        _mm_store_ps(out + 4 * i, acc);
    }
    #else
    Mat4 tmp = {0};
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            for (size_t k = 0; k < 4; k++)
            {
                tmp[4 * j + i] += m1[4 * j + k] * m2[4 * k + i];
            }
        }
    }
    memcpy(out, tmp, sizeof(Mat4));
    #endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  TRANSPOSITION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Mat4_transpose(Mat4 out, const Mat4 m) {
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 row1, row2, row3, row4;
    row1 = _mm_load_ps(m + 0);
    row2 = _mm_load_ps(m + 4);
    row3 = _mm_load_ps(m + 8);
    row4 = _mm_load_ps(m + 12);
    
    //  _MM_TRANSPOSE4_PS
    __m128 tmp1, tmp2, tmp3, tmp4;
    tmp1 = _mm_unpacklo_ps(row1, row2);
    tmp3 = _mm_unpacklo_ps(row3, row4);
    tmp2 = _mm_unpackhi_ps(row1, row2);
    tmp4 = _mm_unpackhi_ps(row3, row4);

    row1 = _mm_movelh_ps(tmp1, tmp3);
    row2 = _mm_movehl_ps(tmp3, tmp1);
    row3 = _mm_movelh_ps(tmp2, tmp4);
    row4 = _mm_movehl_ps(tmp4, tmp2);

    _mm_store_ps(out + 0, row1);
    _mm_store_ps(out + 4, row2);
    _mm_store_ps(out + 8, row3);
    _mm_store_ps(out + 12, row4);
    #else
    Mat4 tmp;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {   
            tmp[4 * j + i] = m[4 * i + j];
        }
    }
    memcpy(out, tmp, sizeof(Mat4));
    #endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  TRANSLATION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Mat4_translation(Mat4 out, const Vec3 position, const Vec3 scale) {
    wem_Mat4_zero(out);
    out[0] = scale[0]; out[5] = scale[1]; out[10] = scale[2]; out[15] = 1;
    memcpy(out + 12, position, sizeof(float) * 3);
}
void wem_Mat4_setTranslation(Mat4 out, const Mat4 m, const Vec3 position) {
    memcpy(out, m, sizeof(Mat4));
    memcpy(out + 12, position, sizeof(float) * 3);
}
void wem_Mat4_translate(Mat4 out, const Mat4 m, const Vec3 position) {
    memcpy(out, m, sizeof(Mat4));
    #if defined(__OPTIMIZE__) && (defined(__AVX__) || defined(__SSE3__))
    __m128 a, b;
    a = _mm_load_ps(m + 12);
    b = _mm_load_ps(position);
    _mm_store_ps(out + 12, _mm_add_ps(a, b));
    #else
    out[12] += position[0];
    out[13] += position[1];
    out[14] += position[2];
    #endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SCALAR
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Mat4_scalar(Mat4 out, const Vec3 scale) {
    wem_Mat4_identity(out);
    out[0] = scale[0]; out[5] = scale[1]; out[10] = scale[2];
}
void wem_Mat4_setScale(Mat4 out, const Mat4 m, const Vec3 scale) {
    memcpy(out, m, sizeof(Mat4));
    out[0]  = scale[0];
    out[5]  = scale[1];
    out[10] = scale[2];
}
void wem_Mat4_scale(Mat4 out, const Mat4 m, const Vec3 scale) {
    memcpy(out, m, sizeof(Mat4));
    out[0]  *= scale[0];
    out[5]  *= scale[1];
    out[10] *= scale[2];
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  VIEW
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Mat4_lookAt(Mat4 out, const Vec3 position, const Vec3 target, const Vec3 camUp){
    Vec3 fwd, right, up;
    wem_Vec3_sub(fwd, target, position);
    wem_Vec3_norm(fwd, fwd);
    wem_Vec3_cross(right, camUp, fwd);
    wem_Vec3_cross(up, fwd, right);
    wem_Vec3_inv(fwd, fwd);
    float tx = wem_Vec3_dot(position, right);
    float ty = wem_Vec3_dot(position, up);
    float tz = wem_Vec3_dot(position, fwd);
    Mat4 outMat = {
        right[0], up[0], fwd[0], 0,
        right[1], up[1], fwd[1], 0,
        right[2], up[2], fwd[2], 0,
        -tx, -ty, -tz, 1
    };
    memcpy(out, outMat, sizeof(Mat4));
}
void wem_Mat4_view(Mat4 out, const Vec3 position, const Vec3 forward, const Vec3 camUp){
    Vec3 fwd, right, up;
    wem_Vec3_norm(fwd, forward);
    wem_Vec3_cross(right, camUp, fwd);
    wem_Vec3_cross(up, fwd, right);
    wem_Vec3_inv(fwd, fwd);
    float tx = wem_Vec3_dot(position, right);
    float ty = wem_Vec3_dot(position, up);
    float tz = wem_Vec3_dot(position, fwd);
    Mat4 outMat = {
        right[0], up[0], fwd[0], 0,
        right[1], up[1], fwd[1], 0,
        right[2], up[2], fwd[2], 0,
        -tx, -ty, -tz, 1
    };
    memcpy(out, outMat, sizeof(Mat4));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  PROJECTION
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Mat4_ortho(Mat4 out, float zoom, float aspectRatio, float near, float far) {
    Mat4 outMat = {
        2.0f / (aspectRatio * 2) * zoom, 0, 0, 0,
        0, zoom, 0, 0,
        0, 0, -2.0f / (far - near), 0,
        0, 0, -(far + near) / (far - near), 1
    };
    memcpy(out, outMat, sizeof(Mat4));
}
void wem_Mat4_perspective(Mat4 out, float fovDeg, float aspectRatio, float near, float far) {
    float fov = DEG2RAD * fovDeg;
    Mat4 outMat = {
        1.0f / (aspectRatio * tanf(fov / 2)), 0, 0, 0,
        0, 1.0f / tanf(fov / 2), 0, 0,
        0, 0, -(far + near) / (far - near), -1,
        0, 0, -(2 * far * near) / (far - near), 0
    };
    memcpy(out, outMat, sizeof(Mat4));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wem_Mat4_print(Mat4 m) {
    printf("Mat4\n");
    for (size_t i = 0; i < 4; i++)
    {
        printf("%f %f %f %f\n", m[i * 4 + 0], m[i * 4 + 1], m[i * 4 + 2], m[i * 4 + 3]);
    }
}


#endif
#endif