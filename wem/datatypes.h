#ifndef WEM_DATATYPES_H
#define WEM_DATATYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef float __attribute__((aligned(16))) Vec[4];

//  X Y z w
typedef Vec Vec2;
//  X Y Z w
typedef Vec Vec3;
//  X Y Z W
typedef Vec Vec4;

#define VEC2(X, Y)          (Vec){X, Y, 0, 0}
#define VEC3(X, Y, Z)       (Vec){X, Y, Z, 0}
#define VEC4(X, Y, Z, W)    (Vec){X, Y, Z, W}

/*
m0_ m4_ m8_ m12
m1_ m5_ m9_ m13
m2_ m6_ m10 m14
m3_ m7_ m11 m15
*/
typedef float 
#ifdef __AVX__
__attribute__((aligned(32))) Mat4[16];
#else
__attribute__((aligned(16))) Mat4[16];
#endif

typedef float __attribute__((aligned(16))) BezierLinear[8];
typedef float __attribute__((aligned(16))) BezierQuad[12];
typedef float __attribute__((aligned(16))) BezierCubic[16];

typedef float __attribute__((aligned(16))) Quat[4];

#endif