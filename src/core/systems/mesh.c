#include "mesh.h"

static void calculate_triangle_normal(Vec3* normal, const Tri* tri) {
    Vec3 line1, line2;
    vec3_subtract(&line1, &tri->p[1], &tri->p[0]); // edge from p0 to p1
    vec3_subtract(&line2, &tri->p[2], &tri->p[0]); // edge from p0 to p2
    vec3_cross(normal, &line1, &line2);
}

static void calculate_lighting(Vec3 light_source) {
    
}

static int tri_backface_cull(const Tri* tri, const Camera* camera) {
    Vec3 normal;
    calculate_triangle_normal(&normal, tri);
    
    // Check for zero-length normal (degenerate triangle)
    float normal_length = vec3_length(&normal);
    if (normal_length < 0.0001f) {
        return 1; // Cull degenerate triangles
    }
    vec3_normalize(&normal);

    // Calculate triangle center for more stable culling
    Vec3 triangle_center = {
        (tri->p[0].x + tri->p[1].x + tri->p[2].x) / 3.0f,
        (tri->p[0].y + tri->p[1].y + tri->p[2].y) / 3.0f,
        (tri->p[0].z + tri->p[1].z + tri->p[2].z) / 3.0f
    };

    // Calculate view vector from triangle center to camera
    Vec3 view_vector;
    vec3_subtract(&view_vector, &camera->position, &triangle_center);
    vec3_normalize(&view_vector);

    float dot_product;
    vec3_dot(&dot_product, &normal, &view_vector);
    return (dot_product > BACKFACE_CULL_DOT_THRESHOLD);

    // Angle-based culling - More accurate but slower
    // float angle = acosf(fmaxf(fminf(dot_product, 1.0f), -1.0f)); // Clamped to avoid domain errors
    
    // Cull if angle between normal and view vector is less than 95 degrees
    // (90° would be exactly perpendicular)
    // return (angle < BACKFACE_CULL_ANGLE_THRESHOLD);
}

void add_triangle(Tri **tris, int *count, Tri *new_tri) {
    *tris = SDL_realloc(*tris, sizeof(Tri) * (*count + 1));
    if (*tris) {
        (*tris)[*count] = *new_tri;  // Add new tri
        (*count)++;  // Increase tri count
    }
}

void render_model(Mesh* mesh, Camera *camera, uint32_t color, int flags) {
    if (!mesh || !camera || !mesh->tris || mesh->size == 0) {
        SDL_Log("Error: Invalid mesh or camera");
        return;
    }

    for (int t = 0; t < mesh->size; t++) {
        // Iterate through each triangle in the mesh
        // Project the triangle onto the camera's view plane
        Tri tri_projected, tri_translated;

        tri_translated = mesh->tris[t];
        // Move the cube away from the camera (into the scene)
        tri_translated.p[0].z += 3.0f; 
        tri_translated.p[1].z += 3.0f;
        tri_translated.p[2].z += 3.0f;

        if (flags & MESH_FLAG_BACKFACE_CULL) {
            if (tri_backface_cull(&tri_translated, camera)) {
                continue; // Skip this triangle
            }
        }

        for (int p = 0; p < 3; p++) {
            mat4_multiply_vec3(&tri_projected.p[p], &camera->projection_matrix, &tri_translated.p[p]);

            // Adjust the coordinates to fit the viewport
            tri_projected.p[p].x += 1.0f; tri_projected.p[p].y += 1.0f;

            // Scale to viewport dimensions
            tri_projected.p[p].x *= 0.5f * camera->width;
            tri_projected.p[p].y *= 0.5f * camera->height;
        }

        // Rasterize the tris
        if (flags & MESH_FLAG_SOLID) {
            draw_polygon(
                (int)tri_projected.p[0].x, (int)tri_projected.p[0].y,
                (int)tri_projected.p[1].x, (int)tri_projected.p[1].y,
                (int)tri_projected.p[2].x, (int)tri_projected.p[2].y,
                color,
                1
            );
        }

        if (flags & MESH_FLAG_WIREFRAME) {
            draw_triangle(
                (int)tri_projected.p[0].x, (int)tri_projected.p[0].y,
                (int)tri_projected.p[1].x, (int)tri_projected.p[1].y,
                (int)tri_projected.p[2].x, (int)tri_projected.p[2].y,
                0x000000FF
            );
        }
    }
}

void rot_mesh_render(Mesh* mesh, Camera *camera, uint32_t color, float f_theta, int flags) {
    if (!mesh || !camera || !mesh->tris || mesh->size == 0) {
        SDL_Log("Error: Invalid mesh or camera");
        return;
    }

    for (int t = 0; t < mesh->size; t++) {
        // Iterate through each triangle in the mesh
        Tri tri_projected, tri_translated, tri_rotated_z, tri_rotated_zx;

        for (int p = 0; p < 3; p++) {
            rotate_z(&tri_rotated_z.p[p], mesh->tris[t].p[p], f_theta);
            rotate_x(&tri_rotated_zx.p[p], tri_rotated_z.p[p], f_theta);
        }

        tri_translated = tri_rotated_zx;
        // Move the cube away from the camera (into the scene)
        tri_translated.p[0].z += 1.0f; 
        tri_translated.p[1].z += 1.0f;
        tri_translated.p[2].z += 1.0f;

        // Do backface culling after all transformations but before projection
        if (flags & MESH_FLAG_BACKFACE_CULL) {
            if (tri_backface_cull(&tri_translated, camera)) {
                continue; // Skip this triangle
            }
        }

        // Sample lighting
        Vec3 light_direction = {0.0f, 0.0f, 3.0f};
        vec3_normalize(&light_direction);

        Vec3 normal;
        calculate_triangle_normal(&normal, &tri_translated);

        float dp;
        vec3_dot(&dp, &normal, &light_direction);

        for (int p = 0; p < 3; p++) {
            mat4_multiply_vec3(&tri_projected.p[p], &camera->projection_matrix, &tri_translated.p[p]);

            // Adjust the coordinates to fit the viewport
            tri_projected.p[p].x += 1.0f; tri_projected.p[p].y += 1.0f;

            // Scale to viewport dimensions
            tri_projected.p[p].x *= 0.5f * camera->width;
            tri_projected.p[p].y *= 0.5f * camera->height;
        }

        // Rasterize the tris
        if (flags & MESH_FLAG_SOLID) {
            draw_polygon(
                (int)tri_projected.p[0].x, (int)tri_projected.p[0].y,
                (int)tri_projected.p[1].x, (int)tri_projected.p[1].y,
                (int)tri_projected.p[2].x, (int)tri_projected.p[2].y,
                color,
                dp
            );
        }

        if (flags & MESH_FLAG_WIREFRAME) {
            draw_triangle(
                (int)tri_projected.p[0].x, (int)tri_projected.p[0].y,
                (int)tri_projected.p[1].x, (int)tri_projected.p[1].y,
                (int)tri_projected.p[2].x, (int)tri_projected.p[2].y,
                0x000000FF
            );
        }
    }
}