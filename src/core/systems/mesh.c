#include "mesh.h"

void mesh_render_wireframe(Mesh* mesh, Camera *camera, uint32_t color) {
    if (!mesh || !camera || !mesh->tris || mesh->size == 0) {
        SDL_Log("Error: Invalid mesh or camera");
        return;
    }

    for (int t = 0; t < mesh->size; t++) {
        Tri tri_projected, tri_translated;

        tri_translated = mesh->tris[t];
        tri_translated.p[0].z += camera->position.z; // Translate triangle to camera position
        tri_translated.p[1].z += camera->position.z;
        tri_translated.p[2].z += camera->position.z;

        for (int p = 0; p < 3; p++) {
            mat4_multiply_vec3(&tri_projected.p[p], &camera->projection_matrix, &tri_translated.p[p]);
        }

        // Scale into view - this is necessary to fit the projected triangle into the viewport
        // Adjust the coordinates to fit the viewport, assuming the viewport is centered at (1, 1)
        for (int p = 0; p < 3; p++) {
            tri_projected.p[p].x += 1.0f; tri_projected.p[p].y += 1.0f;
        }

        for (int p = 0; p < 3; p++) {
            tri_projected.p[p].x *= 0.5f * camera->width;  // Scale to viewport width
            tri_projected.p[p].y *= 0.5f * camera->height; // Scale to viewport height
        }

        draw_triangle(
            (int)tri_projected.p[0].x, (int)tri_projected.p[0].y,
            (int)tri_projected.p[1].x, (int)tri_projected.p[1].y,
            (int)tri_projected.p[2].x, (int)tri_projected.p[2].y,
            color
        );
    }
}


void rot_mesh_render_wireframe(Mesh* mesh, Camera *camera, uint32_t color, float f_theta) {
    if (!mesh || !camera || !mesh->tris || mesh->size == 0) {
        SDL_Log("Error: Invalid mesh or camera");
        return;
    }

    Mat4 mat_rot_z = {0}, mat_rot_x = {0};

    mat_rot_z.m[0][0] = cosf(f_theta);
    mat_rot_z.m[0][1] = -sinf(f_theta);
    mat_rot_z.m[1][0] = sinf(f_theta);
    mat_rot_z.m[1][1] = cosf(f_theta);
    mat_rot_z.m[2][2] = 1.0f;
    mat_rot_z.m[3][3] = 1.0f;

    mat_rot_x.m[0][0] = 1.0f;
    mat_rot_x.m[1][1] = cosf(f_theta * 0.5f);
    mat_rot_x.m[1][2] = -sinf(f_theta * 0.5f);
    mat_rot_x.m[2][1] = sinf(f_theta * 0.5f);
    mat_rot_x.m[2][2] = cosf(f_theta * 0.5f);
    mat_rot_x.m[3][3] = 1.0f;

    for (int t = 0; t < mesh->size; t++) {
        Tri tri_projected, tri_translated, tri_rotated_z, tri_rotated_zx;

        mat4_multiply_vec3(&tri_rotated_z.p[0], &mat_rot_z, &mesh->tris[t].p[0]);
        mat4_multiply_vec3(&tri_rotated_z.p[1], &mat_rot_z, &mesh->tris[t].p[1]);
        mat4_multiply_vec3(&tri_rotated_z.p[2], &mat_rot_z, &mesh->tris[t].p[2]);

        mat4_multiply_vec3(&tri_rotated_zx.p[0], &mat_rot_x, &tri_rotated_z.p[0]);
        mat4_multiply_vec3(&tri_rotated_zx.p[1], &mat_rot_x, &tri_rotated_z.p[1]);
        mat4_multiply_vec3(&tri_rotated_zx.p[2], &mat_rot_x, &tri_rotated_z.p[2]);

        tri_translated = tri_rotated_zx;
        tri_translated.p[0].z += camera->position.z; // Translate triangle to camera position
        tri_translated.p[1].z += camera->position.z;
        tri_translated.p[2].z += camera->position.z;

        for (int p = 0; p < 3; p++) {
            mat4_multiply_vec3(&tri_projected.p[p], &camera->projection_matrix, &tri_translated.p[p]);
        }

        // Scale into view - this is necessary to fit the projected triangle into the viewport
        // Adjust the coordinates to fit the viewport, assuming the viewport is centered at (1, 1)
        for (int p = 0; p < 3; p++) {
            tri_projected.p[p].x += 1.0f; tri_projected.p[p].y += 1.0f;
        }

        for (int p = 0; p < 3; p++) {
            tri_projected.p[p].x *= 0.5f * camera->width;  // Scale to viewport width
            tri_projected.p[p].y *= 0.5f * camera->height; // Scale to viewport height
        }

        draw_triangle(
            (int)tri_projected.p[0].x, (int)tri_projected.p[0].y,
            (int)tri_projected.p[1].x, (int)tri_projected.p[1].y,
            (int)tri_projected.p[2].x, (int)tri_projected.p[2].y,
            color
        );
    }
}