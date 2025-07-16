#ifndef wem_macros_h
#define wem_macros_h

#define POW2(X)     (X * X)
#define POW3(X)     (X * X * X)
#define PI          3.14159265359
#define RAD2DEG     (180.0f / PI)
#define DEG2RAD     (PI / 180.0f)
#define CLAMP(X, Min, Max) (X < Min ? Min : X > Max ? Max : X)

#endif