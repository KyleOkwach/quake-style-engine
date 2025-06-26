#pragma once

#include <math.h>
#include <stdint.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Mathematical types and structures used in the engine
typedef struct {
    float x, y; // 2D vector with x and y components
} Vec2;

typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    float x, y, z, w; // 4D vector with x, y, z, and w components
} Vec4;

typedef struct {
    Vec3 p[3]; // Array of 3 vec3 points representing a triangle
} Tri;

typedef struct {
    float m[4][4]; // 4x4 matrix represented as an array of arrays
} Mat4;

typedef struct {
    float m[3][3]; // 3x3 matrix represented as an array of arrays
} Mat3;

typedef struct {
    float m[2][2]; // 2x2 matrix represented as an array of arrays
} Mat2;

// Mathematical operations
// void mat4_identity(Mat4 *m);
// void mat4_translate(Mat4 *m, float x, float y, float z);
// void mat4_rotate(Mat4 *m, float angle, float x, float y, float z);
// void mat4_scale(Mat4 *m, float x, float y, float z);
// void mat4_transpose(Mat4 *m);
// void mat4_inverse(Mat4 *m);
// void mat4_multiply(Mat4 *result, const Mat4 *a, const Mat4 *b);
void mat4_multiply_vec3(Vec3 *result, const Mat4 *m, const Vec3 *v);