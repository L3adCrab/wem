#ifndef WEM_INTRINSICS_MACROS_H
#define WEM_INTRINSICS_MACROS_H

#define MIN(X, Y)           (X <= Y ? X : Y)
#define MAX(X, Y)           (X >= Y ? X : Y)

#define POW2(X)             (X * X)
#define POW3(X)             (X * X * X)

#define PI                  3.14159265359
#define RAD2DEG             (180.0f / PI)
#define DEG2RAD             (PI / 180.0f)

#define CLAMP(X, Min, Max)      (X < Min ? Min : X > Max ? Max : X)
#define INRANGE(X, Min, Max)    (X < Min ? 0 : X > Max ? 0 : 1)

#define WEM_AS(X, AS)       (*(AS*)((float*)&X))

#endif