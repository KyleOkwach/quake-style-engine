#include "math.h"

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