#pragma once

#include <math.h>
#include "../math.h"
#include "../ecs.h"

void camera_init(Camera *camera, Vec3 position, Vec3 direction, Vec3 up, float near_plane, float far_plane, float fov, float aspect_ratio);