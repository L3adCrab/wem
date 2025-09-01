#ifndef wem_mat4_h
#define wem_mat4_h

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

#ifndef WEMDEF
    #ifdef WEM_STATIC
    #define WEMDEF static
    #define WEM_IMPLEMENTATION
    #else
    #define WEMDEF extern
    #endif
#endif

#include "macros.h"
#include "datatypes.h"
#include "vec3.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ALLOCATION

WEMDEF mat4 wem_mat4_zero();
WEMDEF mat4 wem_mat4_identity();

WEMDEF mat4 *wem_mat4_alloc(mat4 mat);
WEMDEF void wem_mat4_setMat(mat4 *h, mat4 mat);
WEMDEF void wem_mat4_free(mat4 **h);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADDITION

WEMDEF mat4 wem_mat4_add(mat4 m1, mat4 m2);
WEMDEF mat4 wem_mat4_add1f(mat4 m, char row, char column, float val);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SUBTRACTION

WEMDEF mat4 wem_mat4_sub(mat4 m1, mat4 m2);
WEMDEF mat4 wem_mat4_sub1f(mat4 m, char row, char column, float val);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MULTIPLICATION

WEMDEF mat4 wem_mat4_scalarMul(mat4 m, float scale);
WEMDEF mat4 wem_mat4_mul(mat4 m1, mat4 m2);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  TRANSPOSITION

WEMDEF mat4 wem_mat4_transpose(mat4 m);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  TRANSLATION

WEMDEF mat4 wem_mat4_translation(vec3 position);
WEMDEF mat4 wem_mat4_setTranslation(mat4 m, vec3 position);
WEMDEF mat4 wem_mat4_translate(mat4 m, vec3 position);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SCALAR

WEMDEF mat4 wem_mat4_scalar(vec3 scale);
//  Sets 0th, 5th, and 10th value of matrix to x, y and z of scale respectively.
//  Shouldn't be used with rotated matrix.
WEMDEF mat4 wem_mat4_setScale(mat4 m, vec3 scale);
WEMDEF mat4 wem_mat4_scale(mat4 m, vec3 scale);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ROTATION

WEMDEF mat4 wem_mat4_roatationEuler(vec3 rotInDeg);
WEMDEF mat4 wem_mat4_setRotationEuler(mat4 m, vec3 rotInDeg);
WEMDEF mat4 wem_mat4_rotateEuler(mat4 m, vec3 rotInDeg);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  TRANSFORMATION

WEMDEF mat4 wem_mat4_modelEuler(vec3 posisition, vec3 scale, vec3 rotInDeg);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CAMERA

WEMDEF mat4 wem_mat4_lookAt(vec3 position, vec3 target, vec3 camUp);
WEMDEF mat4 wem_mat4_view(vec3 position, vec3 forward, vec3 camUp);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  PROJECTION

WEMDEF mat4 wem_mat4_ortho(float zoom, float aspectRatio, float near, float far);
WEMDEF mat4 wem_mat4_perspective(float fovDeg, float aspectRatio, float near, float far);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

WEMDEF void wem_mat4_print(mat4 m);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  OPERATORS

#ifdef __cplusplus
WEMDEF mat4 operator+(mat4 m1, mat4 m2);
WEMDEF void operator+=(mat4 &m1, mat4 m2);

WEMDEF mat4 operator-(mat4 m1, mat4 m2);
WEMDEF void operator-=(mat4 &m1, mat4 m2);

WEMDEF mat4 operator*(mat4 m, float f);
WEMDEF void operator*=(mat4 &m, float f);
WEMDEF mat4 operator*(mat4 m1, mat4 m2);
WEMDEF void operator*=(mat4 &m1, mat4 m2);
#endif

#ifdef WEM_IMPLEMENTATION
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ALLOCATION

mat4 wem_mat4_zero() {
    mat4 out = {0};
    return out;
}
mat4 wem_mat4_identity() {
    mat4 out = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    return out;
}

mat4 *wem_mat4_alloc(mat4 mat) {
    mat4 *out = (mat4*)malloc(sizeof(mat4));
    *out = mat;
    return out;
}
void wem_mat4_setMat(mat4 *h, mat4 mat) {
    *h = mat;
}
void wem_mat4_free(mat4 **h) {
    free(*h);
    *h = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADDITION

mat4 wem_mat4_add(mat4 m1, mat4 m2) {
    for (int i = 0; i < 16; i++) {
        m1.v[i] += m2.v[i];
    }
    return m1;
}
mat4 wem_mat4_add1f(mat4 m, char row, char column, float val) {
    m.v[4 * column + row] += val;
    return m;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SUBTRACTION

mat4 wem_mat4_sub(mat4 m1, mat4 m2) {
    for (int i = 0; i < 16; i++) {
        m1.v[i] -= m2.v[i];
    }
    return m1;
}
mat4 wem_mat4_sub1f(mat4 m, char row, char column, float val) {
    m.v[4 * column + row] -= val;
    return m;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MULTIPLICATION

mat4 wem_mat4_scalarMul(mat4 m, float scale) {
    for (int i = 0; i < 16; i++) {
        m.v[i] *= scale;
    }
    return m;
}
mat4 wem_mat4_mul(mat4 m1, mat4 m2) {
    mat4 out = {0};
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            for (int i = 0; i < 4; i++)
            {
                out.v[4 * x + y] += m1.v[4 * x + i] * m2.v[4 * i + y];
            }
        }
    }
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  TRANSPOSITION

mat4 wem_mat4_transpose(mat4 m) {
    mat4 out;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            out.v[4 * x + y] = m.v[4 * y + x];   
        }
    }
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  TRANSLATION

mat4 wem_mat4_translation(vec3 position) {
    mat4 out = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        position.x, position.y, position.z, 1
        };
    return out;
}
mat4 wem_mat4_setTranslation(mat4 m, vec3 position) {
    m.v[12] = position.x;
    m.v[13] = position.y;
    m.v[14] = position.z;
    return m;
}
mat4 wem_mat4_translate(mat4 m, vec3 position) {
    m.v[12] += position.x;
    m.v[13] += position.y;
    m.v[14] += position.z;
    return m; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SCALAR

mat4 wem_mat4_scalar(vec3 scale) {
    mat4 out = {
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1
        };
    return out;
}
//  Sets 0th, 5th, and 10th value of matrix to x, y and z of scale respectively.
//  Shouldn't be used with rotated matrix.
mat4 wem_mat4_setScale(mat4 m, vec3 scale) {
    m.v[0]  = scale.x;
    m.v[5]  = scale.y;
    m.v[10] = scale.z;
    return m;
}
mat4 wem_mat4_scale(mat4 m, vec3 scale) {
    m.v[0]  *= scale.x;
    m.v[5]  *= scale.y;
    m.v[10] *= scale.z;
    return m;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ROTATION

mat4 wem_mat4_roatationEuler(vec3 rotInDeg) {
    float x = DEG2RAD * rotInDeg.x, y = DEG2RAD * rotInDeg.y, z = DEG2RAD * rotInDeg.z;
    float sinX = sinf(x), sinY = sinf(y), sinZ = sinf(z);
    float cosX = cosf(x), cosY = cosf(y), cosZ = cosf(z);
    float sinXxsinY = -sinX * -sinY;
    float sinXxcosY = -sinX * cosY;
    mat4 out = {
            cosZ * cosY + -sinZ * sinXxsinY,        cosZ * cosY + cosZ * sinXxsinY,     cosY * -sinY,   0,
            -sinZ * cosX,                           cosZ * cosX,                        sinX,           0,
            cosZ * sinY + -sinZ * sinXxcosY,        sinZ * sinY + cosZ * sinXxcosY,  cosX * cosY,    0,
            0, 0, 0, 1
        };
    return out;
}
mat4 wem_mat4_setRotationEuler(mat4 m, vec3 rotInDeg) {
    float x = DEG2RAD * rotInDeg.x, y = DEG2RAD * rotInDeg.y, z = DEG2RAD * rotInDeg.z;
    float sinX = sinf(x), sinY = sinf(y), sinZ = sinf(z);
    float cosX = cosf(x), cosY = cosf(y), cosZ = cosf(z);
    float sinXxsinY = -sinX * -sinY;
    float sinXxcosY = -sinX * cosY;
    m.v[0] = cosZ * cosY + -sinZ * sinXxsinY;   m.v[4] = -sinZ * cosX,  m.v[8] = cosZ * sinY + -sinZ * sinXxcosY;
    m.v[1] = cosZ * cosY + cosZ * sinXxsinY;    m.v[5] = cosZ * cosX;   m.v[9] = sinZ * sinY + cosZ * sinXxcosY;
    m.v[2] = cosY * -sinY;                      m.v[6] = sinX;          m.v[10] = cosX * cosY;
    return m;
}
mat4 wem_mat4_rotateEuler(mat4 m, vec3 rotInDeg) {
    return wem_mat4_mul(wem_mat4_roatationEuler(rotInDeg), m);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  TRANSFORMATION

mat4 wem_mat4_modelEuler(vec3 posisition, vec3 scale, vec3 rotInDeg) {
    float x = DEG2RAD * rotInDeg.x, y = DEG2RAD * rotInDeg.y, z = DEG2RAD * rotInDeg.z;
    float sinX = sinf(x), sinY = sinf(y), sinZ = sinf(z);
    float cosX = cosf(x), cosY = cosf(y), cosZ = cosf(z);
    float sinXxsinY = -sinX * -sinY;
    float sinXxcosY = -sinX * cosY;
    mat4 out = {
            scale.x * (cosZ * cosY + -sinZ * sinXxsinY),    cosZ * cosY + cosZ * sinXxsinY,     cosY * -sinY,           0,
            -sinZ * cosX,                                   scale.y * cosZ * cosX,              sinX,                   0,
            cosZ * sinY + -sinZ * sinXxcosY,                sinZ * sinY + cosZ * sinXxcosY,     scale.z * cosX * cosY,  0,
            posisition.x, posisition.y, posisition.z, 1
        };
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  CAMERA

mat4 wem_mat4_lookAt(vec3 position, vec3 target, vec3 camUp) {
    vec3 forward    = wem_vec3_norm(wem_vec3_sub(target, position));
    vec3 right      = wem_vec3_cross(forward, camUp);
    vec3 up         = wem_vec3_cross(right, forward);
    forward         = wem_vec3_inv(forward);
    float tx = wem_vec3_dot(position, right);
    float ty = wem_vec3_dot(position, up);
    float tz = wem_vec3_dot(position, forward);
    mat4 out = {
        right.x, up.x, forward.x, 0,
        right.y, up.y, forward.y, 0,
        right.z, up.z, forward.z, 0,
        -tx, -ty, -tz, 1
        };
    return out;
}
mat4 wem_mat4_view(vec3 position, vec3 forward, vec3 camUp) {
    vec3 right      = wem_vec3_cross(forward, camUp);
    vec3 up         = wem_vec3_cross(right, forward);
    forward         = wem_vec3_inv(forward);
    float tx = wem_vec3_dot(position, right);
    float ty = wem_vec3_dot(position, up);
    float tz = wem_vec3_dot(position, forward);
    mat4 out = {
        right.x, up.x, forward.x, 0,
        right.y, up.y, forward.y, 0,
        right.z, up.z, forward.z, 0,
        -tx, -ty, -tz, 1
        };
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  PROJECTION

mat4 wem_mat4_ortho(float zoom, float aspectRatio, float near, float far) {
    mat4 out = {
            2.0f / (aspectRatio * 2) * zoom, 0, 0, 0,
            0, zoom, 0, 0,
            0, 0, -2.0f / (far - near), 0,
            0, 0, -(far + near) / (far - near), 1
        };
    return out;
}
mat4 wem_mat4_perspective(float fovDeg, float aspectRatio, float near, float far) {
    float fov = DEG2RAD * fovDeg;
    mat4 out = {
            1.0f / (aspectRatio * tanf(fov / 2)), 0, 0, 0,
            0, 1.0f / tanf(fov / 2), 0, 0,
            0, 0, -(far + near) / (far - near), -1,
            0, 0, -(2 * far * near) / (far - near), 0
        };
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  DEBUG

void wem_mat4_print(mat4 m) {
    printf("mat4 {\n");
    for (int y = 0; y < 4; y++) {
        printf(" ");
        for (int x = 0; x < 4; x++) {
            printf("%f ", m.v[4 * x + y]);
        }
        printf("\n");
    }
    printf("}\n");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  OPERATORS

#ifdef __cplusplus
mat4 operator+(mat4 m1, mat4 m2) { return wem_mat4_add(m1, m2); }
void operator+=(mat4 &m1, mat4 m2) { m1 = wem_mat4_add(m1, m2); }

mat4 operator-(mat4 m1, mat4 m2) { return wem_mat4_sub(m1, m2); }
void operator-=(mat4 &m1, mat4 m2) { m1 = wem_mat4_sub(m1, m2); }

mat4 operator*(mat4 m, float f) { return wem_mat4_scalarMul(m, f); }
void operator*=(mat4 &m, float f) { m = wem_mat4_scalarMul(m, f); }
mat4 operator*(mat4 m1, mat4 m2) { return wem_mat4_mul(m1, m2); }
void operator*=(mat4 &m1, mat4 m2) { m1 = wem_mat4_mul(m1, m2); }
#endif

#endif
#endif