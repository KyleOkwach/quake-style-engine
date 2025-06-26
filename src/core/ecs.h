#pragma once

#include "math.h"
#include "../backend/common.h"

#define MAX_ENTITIES 1024

typedef uint32_t Entity;  // Define EntityID as a 32-bit unsigned integer

Entity create_entity(void);

// Component Structs
typedef struct {
    Tri* tris;    // Pointer to array of triangles
    size_t size;            // Current number of triangles
    size_t capacity;        // Current capacity of the array
} Mesh;

typedef struct {
    Vec3 position;  // Camera position in 3D space
    Vec3 direction; // Direction the camera is facing
    Vec3 up;        // Up vector for the camera orientation
    Mat4 projection_matrix; // Projection matrix for the camera
} Camera;


// Entity Management
extern Mesh meshes[MAX_ENTITIES];  // Array of Mesh components for each entity
extern bool has_mesh[MAX_ENTITIES];  // Array to track if an entity has a Mesh component
void add_mesh(Entity entity_id, Mesh* mesh);
// void remove_mesh(Entity entity_id);
// Mesh* get_mesh(Entity entity_id);

// Camera Management
extern Camera cameras[MAX_ENTITIES];  // Array of Camera components for each entity
extern bool has_camera[MAX_ENTITIES];  // Array to track if an entity has a Camera component
void add_camera(Entity entity_id, Camera* camera);