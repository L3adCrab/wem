#ifndef wem_mat4_h
#define wem_mat4_h

#ifndef WEMDEF
    #ifdef WEM_EXTERN
    #define WEMDEF extern
    #else
    #define WEMDEF static
    #endif
#endif

#include "macros.h"
#include "datatypes.h"
#include "vec3.h"

#include <math.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ALLOCATION

WEMDEF mat4 wem_mat4_zero() {
    mat4 out = {0};
    return out;
}
WEMDEF mat4 wem_mat4_identity() {
    mat4 out = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
        };
    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADDITION

WEMDEF mat4 wem_mat4_add(mat4 m1, mat4 m2) {
    for (int i = 0; i < 16; i++) {
        m1.v[i] += m2.v[i];
    }
    return m1;
}
WEMDEF mat4 wem_mat4_add1f(mat4 m, char row, char column, float val) {
    m.v[4 * column + row] += val;
    return m;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SUBTRACTION

WEMDEF mat4 wem_mat4_sub(mat4 m1, mat4 m2) {
    for (int i = 0; i < 16; i++) {
        m1.v[i] -= m2.v[i];
    }
    return m1;
}
WEMDEF mat4 wem_mat4_sub1f(mat4 m, char row, char column, float val) {
    m.v[4 * column + row] -= val;
    return m;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  MULTIPLICATION

WEMDEF mat4 wem_mat4_scalarMul(mat4 m, float scale) {
    for (int i = 0; i < 16; i++) {
        m.v[i] *= scale;
    }
    return m;
}
WEMDEF mat4 wem_mat4_mul(mat4 m1, mat4 m2) {
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

WEMDEF mat4 wem_mat4_transpose(mat4 m) {
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

WEMDEF mat4 wem_mat4_translation(vec3 position) {
    mat4 out = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        position.x, position.y, position.z, 1
        };
    return out;
}
WEMDEF mat4 wem_mat4_setTranslation(mat4 m, vec3 position) {
    m.v[12] = position.x;
    m.v[13] = position.y;
    m.v[14] = position.z;
    return m;
}
WEMDEF mat4 wem_mat4_translate(mat4 m, vec3 position) {
    m.v[12] += position.x;
    m.v[13] += position.y;
    m.v[14] += position.z;
    return m; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  SCALAR

WEMDEF mat4 wem_mat4_scalar(vec3 scale) {
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
WEMDEF mat4 wem_mat4_setScale(mat4 m, vec3 scale) {
    m.v[0]  = scale.x;
    m.v[5]  = scale.y;
    m.v[10] = scale.z;
    return m;
}
WEMDEF mat4 wem_mat4_scale(mat4 m, vec3 scale) {
    m.v[0]  *= scale.x;
    m.v[5]  *= scale.y;
    m.v[10] *= scale.z;
    return m;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ROTATION

WEMDEF mat4 wem_mat4_roatationEuler(vec3 rotInDeg) {
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
WEMDEF mat4 wem_mat4_setRotationEuler(mat4 m, vec3 rotInDeg) {
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
WEMDEF mat4 wem_mat4_rotateEuler(mat4 m, vec3 rotInDeg) {
    return wem_mat4_mul(wem_mat4_roatationEuler(rotInDeg), m);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  TRANSFORMATION

WEMDEF mat4 wem_mat4_modelEuler(vec3 posisition, vec3 scale, vec3 rotInDeg) {
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

WEMDEF mat4 wem_mat4_lookAt(vec3 position, vec3 target, vec3 camUp) {
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
WEMDEF mat4 wem_mat4_view(vec3 position, vec3 forward, vec3 camUp) {
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

WEMDEF mat4 wem_mat4_ortho(float zoom, float aspectRatio, float near, float far) {
    mat4 out = {
            2.0f / (aspectRatio * 2) * zoom, 0, 0, 0,
            0, zoom, 0, 0,
            0, 0, -2.0f / (far - near), 0,
            0, 0, -(far + near) / (far - near), 0
        };
    return out;
}
WEMDEF mat4 wem_mat4_perspective(float fovDeg, float aspectRatio, float near, float far) {
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

WEMDEF void wem_mat4_print(mat4 m) {
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
#endif