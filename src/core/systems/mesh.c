#include "mesh.h"

static int tri_backface_cull(const Tri* tri, const Camera* camera) {
    Vec3 line1, line2, normal;
    vec3_subtract(&line1, &tri->p[1], &tri->p[0]);
    vec3_subtract(&line2, &tri->p[2], &tri->p[0]);
    vec3_cross(&normal, &line1, &line2);
    vec3_normalize(&normal);

    // Calculate triangle center for more accurate culling
    Vec3 triangle_center = {
        (tri->p[0].x + tri->p[1].x + tri->p[2].x) / 3.0f,
        (tri->p[0].y + tri->p[1].y + tri->p[2].y) / 3.0f,
        (tri->p[0].z + tri->p[1].z + tri->p[2].z) / 3.0f
    };

    // Calculate view vector FROM triangle center TO camera
    Vec3 view_vector;
    vec3_subtract(&view_vector, &camera->position, &triangle_center);
    vec3_normalize(&view_vector);

    // Calculate dot product between surface normal and view vector
    float dot_product;
    vec3_dot(&dot_product, &normal, &view_vector);
    
    // If dot product is negative, triangle faces away from camera (backface)
    return (dot_product < 0.0f);
}

void mesh_render(Mesh* mesh, Camera *camera, uint32_t color, int flags) {
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

        if (tri_backface_cull(&tri_translated, camera) && flags & MESH_FLAG_BACKFACE_CULL) {
            // Backface culling: skip rendering this triangle if the normal is facing away from the camera
            continue;
        }

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


void rot_mesh_render(Mesh* mesh, Camera *camera, uint32_t color, float f_theta, int flags) {
    if (!mesh || !camera || !mesh->tris || mesh->size == 0) {
        SDL_Log("Error: Invalid mesh or camera");
        return;
    }

    for (int t = 0; t < mesh->size; t++) {
        Tri tri_projected, tri_translated, tri_rotated_z, tri_rotated_zx;

        for (int p = 0; p < 3; p++) {
            rotate_z(&tri_rotated_z.p[p], mesh->tris[t].p[p], f_theta);
            rotate_x(&tri_rotated_zx.p[p], tri_rotated_z.p[p], f_theta);
        }

        tri_translated = tri_rotated_zx;
        tri_translated.p[0].z += camera->position.z; // Translate triangle to camera position
        tri_translated.p[1].z += camera->position.z;
        tri_translated.p[2].z += camera->position.z;

        if (tri_backface_cull(&tri_translated, camera) && flags & MESH_FLAG_BACKFACE_CULL) {
            // Backface culling: skip rendering this triangle if the normal is facing away from the camera
            continue;
        }

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