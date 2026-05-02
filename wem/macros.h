#ifndef WEM_MACROS_H
#define WEM_MACROS_H

#define MIN(X, Y)           (X <= Y ? X : Y)
#define MAX(X, Y)           (X >= Y ? X : Y)

#define POW2(X)             (X * X)
#define POW3(X)             (X * X * X)

#define PI                  3.14159265359
#define RAD2DEG             (180.0f / PI)
#define DEG2RAD             (PI / 180.0f)
#define RAD(D)              (D * (PI / 180.0))

#define CLAMP(X, Min, Max)      (X < Min ? Min : X > Max ? Max : X)

#define CLAMP01(X)              (X < 0 ? 0 : X > 1 ? 1 : X)
#define CLAMP01_NF(X)           (X * (X < 0) * (X > 1) + (X > 1))

#define INRANGE(X, Min, Max)    (X < Min ? 0 : X > Max ? 0 : 1)

#define WEM_AS(X, AS)           (*(AS*)((float*)&X))

#define SET2V(V, X, Y)          (V[0] = X, V[1] = Y)
#define SET3V(V, X, Y, Z)       (V[0] = X, V[1] = Y, V[2] = Z)
#define SET4V(V, X, Y, Z, W)    (V[0] = X, V[1] = Y, V[2] = Z, V[3] = W)

#endif