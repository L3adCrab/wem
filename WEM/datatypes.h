#ifndef wem_datatypes_h
#define wem_datatypes_h

typedef struct vec2 { float x, y; } vec2;
typedef struct vec3 { float x, y, z; } vec3;
typedef struct vec4 { float x, y, z, w; } vec4;

typedef struct mat4 { float v[16]; } mat4;

typedef struct quat { float i, j, k, w; } quat;

typedef struct bezier_linear { vec3 p0, p1; } bezier_linear;
typedef struct bezier_quad { vec3 p0, p1, p2; } bezier_quad;
typedef struct bezier_cubic { vec3 p0, p1, p2, p3; bezier_quad b0, b1; } bezier_cubic;

#endif