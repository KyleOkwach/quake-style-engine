#include "transform.h"

void rotate_z(Vec3 *vi,Vec3 v, float angle) {
    Mat4 rotation = {0};
    rotation.m[0][0] = cosf(angle);
    rotation.m[0][1] = -sinf(angle);
    rotation.m[1][0] = sinf(angle);
    rotation.m[1][1] = cosf(angle);
    rotation.m[2][2] = 1.0f;
    rotation.m[3][3] = 1.0f;
    mat4_multiply_vec3(vi, &rotation, &v);
}

void rotate_x(Vec3 *vi, Vec3 v, float angle) {
    Mat4 rotation = {0};
    rotation.m[0][0] = 1.0f;
    rotation.m[1][1] = cosf(angle);
    rotation.m[1][2] = -sinf(angle);
    rotation.m[2][1] = sinf(angle);
    rotation.m[2][2] = cosf(angle);
    rotation.m[3][3] = 1.0f;
    mat4_multiply_vec3(vi, &rotation, &v);
}

void rotate_y(Vec3 *vi, Vec3 v, float angle) {
    Mat4 rotation = {0};
    rotation.m[0][0] = cosf(angle);
    rotation.m[0][2] = sinf(angle);
    rotation.m[1][1] = 1.0f;
    rotation.m[2][0] = -sinf(angle);
    rotation.m[2][2] = cosf(angle);
    rotation.m[3][3] = 1.0f;
    mat4_multiply_vec3(vi, &rotation, &v);
}