#include "mesh.h"

void mesh_render(Mesh* mesh, Camera *camera) {
    // This function will render the mesh using the camera's projection matrix
    for (int t; t < mesh->size; t++) {
        Tri tri_projected;
        for (int p = 0; p < 3; p++) {
            // Project each vertex of the triangle using the camera's projection matrix
            mat4_multiply_vec3(&tri_projected.p[p], &camera->projection_matrix, &mesh->tris[t].p[p]);
        }
        // Draw the projected triangle using the rasterization function
        draw_triangle(tri_projected.p[0].x, tri_projected.p[0].y,
                      tri_projected.p[1].x, tri_projected.p[1].y,
                      tri_projected.p[2].x, tri_projected.p[2].y, 0xFFFFFFFF); // White color
    }
}