#pragma once

#include "../ecs.h"
#include "../utils/math.h"
#include "../utils/rasterize.h"
#include "transform.h"

// Flags
#define MESH_FLAG_NONE 0
#define MESH_FLAG_WIREFRAME 1
#define MESH_FLAG_SOLID 2
#define MESH_FLAG_LIT 3
#define MESH_FLAG_FLAT_SHADED 4
#define MESH_FLAG_TEXTURED 8
#define MESH_FLAG_BACKFACE_CULL 16

#define BACKFACE_CULL_ANGLE_THRESHOLD (M_PI/2.0f + 0.09f)
#define BACKFACE_CULL_DOT_THRESHOLD -0.1f

void render_model(Mesh *mesh, Camera *camera, uint32_t color, int flags);

// Debug functions
void rot_mesh_render(Mesh* mesh, Camera *camera, uint32_t color, float f_theta, int flags);