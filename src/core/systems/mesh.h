#pragma once

#include "../math.h"
#include "../ecs.h"
#include "rasterize.h"

void mesh_render_wireframe(Mesh *mesh, Camera *camera, uint32_t color);

// Debug functions
void rot_mesh_render_wireframe(Mesh* mesh, Camera *camera, uint32_t color, float f_theta);