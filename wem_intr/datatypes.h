#ifndef WEM_INTRINSICS_DATATYPES_H
#define WEM_INTRINSICS_DATATYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef float Vec[4];

typedef struct Vec2 { float x, y; }         __attribute__((aligned(16))) Vec2;
typedef struct Vec3 { float x, y, z; }      __attribute__((aligned(16))) Vec3;
typedef struct Vec4 { float x, y, z, w; }   __attribute__((aligned(16))) Vec4;

typedef union Vector2 { Vec p; Vec2 v; }    Vector2;
typedef union Vector3 { Vec p; Vec3 v; }    Vector3;
typedef union Vector4 { Vec p; Vec4 v; }    Vector4;

#define VECTOR2(X, Y)           (Vector2){{X, Y}}
#define VECTOR3(X, Y, Z)        (Vector3){{X, Y, Z}}
#define VECTOR4(X, Y, Z, W)     (Vector4){{X, Y, Z, W}}

#endif