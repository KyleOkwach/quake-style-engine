#pragma once

#include "../math.h"
#include "../ecs.h"
#include "rasterize.h"
#include "transform.h"

// Flags
#define MESH_FLAG_NONE 0
#define MESH_FLAG_WIREFRAME 1
#define MESH_FLAG_SOLID 2
#define MESH_FLAG_FLAT_SHADED 4
#define MESH_FLAG_TEXTURED 8
#define MESH_FLAG_BACKFACE_CULL 16

void mesh_render(Mesh *mesh, Camera *camera, uint32_t color, int flags);

// Debug functions
void rot_mesh_render(Mesh* mesh, Camera *camera, uint32_t color, float f_theta, int flags);