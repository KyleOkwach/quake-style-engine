#include "camera.h"

void camera_init(
    Camera *camera,
    Vec3 position,
    Vec3 direction,
    Vec3 up,
    float near_plane,
    float far_plane,
    float fov,
    float aspect_ratio,
    int width,
    int height
) {
    camera->position = position;
    camera->direction = direction;
    camera->up = up;
    camera->width = width;
    camera->height = height;

    Mat4 projection_matrix = {0};
    float fov_rad = 1.0f / tanf(fov * 0.5f / 180.0f * M_PI);

    // Set up projection matrix properly
    projection_matrix.m[0][0] = fov_rad / aspect_ratio;
    projection_matrix.m[1][1] = fov_rad;
    projection_matrix.m[2][2] = (far_plane + near_plane) / (far_plane - near_plane);
    projection_matrix.m[3][2] = (-2.0f * far_plane * near_plane) / (far_plane - near_plane);
    projection_matrix.m[2][3] = 1.0f;
    projection_matrix.m[3][3] = 0.0f;

    camera->projection_matrix = projection_matrix;
}