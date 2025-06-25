#pragma once

#include <stdint.h>

typedef struct {
    int x;
    int y;
} vec2;

typedef struct {
    int x;
    int y;
    int z;
} vec3;

typedef struct {
    int x;
    int y;
    int z;
    int w;
} vec4;

typedef struct {
    int m[4][4];
} mat4;