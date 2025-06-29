#include "math.h"

// -----------------------------------------------------
// ----------------- Vect3d Operations------------------
// -----------------------------------------------------

void vec3_add(Vec3 *result, const Vec3 *a, const Vec3 *b) {
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
}
void vec3_subtract(Vec3 *result, const Vec3 *a, const Vec3 *b) {
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
}
void vec3_scale(Vec3 *result, const Vec3 *v, float scalar) {
    result->x = v->x * scalar;
    result->y = v->y * scalar;
    result->z = v->z * scalar;
}
void vec3_cross(Vec3 *result, const Vec3 *a, const Vec3 *b) {
    result->x = a->y * b->z - a->z * b->y;
    result->y = a->z * b->x - a->x * b->z;
    result->z = a->x * b->y - a->y * b->x;
}
void vec3_dot(float *result, const Vec3 *a, const Vec3 *b) {
    *result = a->x * b->x + a->y * b->y + a->z * b->z;
}
float vec3_length(const Vec3 *v) {
    return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}
void vec3_normalize(Vec3 *v) {
    float length = vec3_length(v);
    if (length > 0.0f) {
        v->x /= length;
        v->y /= length;
        v->z /= length;
    }
}


// -----------------------------------------------------
// ----------------- Mat4x4 Operations------------------
// -----------------------------------------------------

void mat4_identity(Mat4 *m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m->m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}
void mat4_translate(Mat4 *m, float x, float y, float z) {
    mat4_identity(m);
    m->m[3][0] = x;
    m->m[3][1] = y;
    m->m[3][2] = z;
}
void mat4_rotate(Mat4 *m, float angle, float x, float y, float z) {
    mat4_identity(m);
    float rad = angle * (M_PI / 180.0f);
    float c = cosf(rad);
    float s = sinf(rad);
    float len = sqrtf(x * x + y * y + z * z);
    if (len > 0.0f) {
        x /= len; y /= len; z /= len;
    }
    
    m->m[0][0] = c + (1 - c) * x * x;
    m->m[0][1] = (1 - c) * x * y - s * z;
    m->m[0][2] = (1 - c) * x * z + s * y;
    
    m->m[1][0] = (1 - c) * y * x + s * z;
    m->m[1][1] = c + (1 - c) * y * y;
    m->m[1][2] = (1 - c) * y * z - s * x;
    
    m->m[2][0] = (1 - c) * z * x - s * y;
    m->m[2][1] = (1 - c) * z * y + s * x;
    m->m[2][2] = c + (1 - c) * z * z;
}
void mat4_scale(Mat4 *m, float x, float y, float z) {
    mat4_identity(m);
    m->m[0][0] = x;
    m->m[1][1] = y;
    m->m[2][2] = z;
}
void transpose(Mat4 *m) {
    Mat4 temp = *m;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m->m[i][j] = temp.m[j][i];
        }
    }
}
void mat4_inverse(Mat4 *m) {
    // This function is a placeholder. Implementing matrix inversion is complex and requires additional logic.
    // For now, we will just set it to identity.
    mat4_identity(m);
}
void mat4_multiply(Mat4 *result, const Mat4 *a, const Mat4 *b) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result->m[i][j] = a->m[i][0] * b->m[0][j] +
                              a->m[i][1] * b->m[1][j] +
                              a->m[i][2] * b->m[2][j] +
                              a->m[i][3] * b->m[3][j];
        }
    }
}
void mat4_multiply_vec3(Vec3 *result, const Mat4 *m, const Vec3 *v) {
    result->x = m->m[0][0] * v->x + m->m[1][0] * v->y + m->m[2][0] * v->z + m->m[3][0];
    result->y = m->m[0][1] * v->x + m->m[1][1] * v->y + m->m[2][1] * v->z + m->m[3][1];
    result->z = m->m[0][2] * v->x + m->m[1][2] * v->y + m->m[2][2] * v->z + m->m[3][2];
    float w = m->m[0][3] * v->x + m->m[1][3] * v->y + m->m[2][3] * v->z + m->m[3][3];

    if (w != 0.0f) {
        result->x /= w;
        result->y /= w;
        result->z /= w;
    }
}