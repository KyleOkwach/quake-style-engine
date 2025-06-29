#pragma once

// Flag definitions for component management
#define COMPONENT_FLAG_NONE 0  // No flags set for component operations
#define COMPONENT_FLAG_DEBUG 1  // Debug flag for logging component operations
#define COMPONENT_FLAG_PERSISTENT 2  // Persistent flag for components that should not be removed on entity destruction

// Macro definitions for adding, removing, and getting components
// These macros handle the addition, removal, and retrieval of components for entities in the ECS system
#define ADD_COMPONENT(array, has_array, entity_id, value_ptr, flags) \
    do { \
        if ((entity_id) >= MAX_ENTITIES) { \
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Entity ID %u is out of bounds. Maximum allowed is %d.", (entity_id), MAX_ENTITIES - 1); \
            break; \
        } \
        (array)[entity_id] = *(value_ptr); \
        (has_array)[entity_id] = true; \
        if (flags & COMPONENT_FLAG_DEBUG) { \
            SDL_Log("Added component to entity %u", (entity_id)); \
        } \
    } while (0)

#define REMOVE_COMPONENT(array, has_array, entity_id, flags) \
    do { \
        if ((entity_id) >= MAX_ENTITIES) { \
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Entity ID %u is out of bounds. Maximum allowed is %d.", (entity_id), MAX_ENTITIES - 1); \
            break; \
        } \
        (has_array)[entity_id] = false; \
        if (flags & COMPONENT_FLAG_DEBUG) { \
            SDL_Log("Removed component from entity %u", (entity_id)); \
        } \
    } while (0)

#define GET_COMPONENT(array, has_array, entity_id) \
    ((entity_id) < MAX_ENTITIES && (has_array)[entity_id] ? &(array)[entity_id] : NULL)

#define HAS_COMPONENT(has_array, entity_id) \
    ((entity_id) < MAX_ENTITIES && (has_array)[entity_id])

// ----------------------------------------------------------------------------------------

#include "utils/math.h"
#include "../backend/common.h"

#define MAX_ENTITIES 1024

typedef uint32_t Entity;  // Define EntityID as a 32-bit unsigned integer

Entity create_entity(void);

// Component Structs
typedef struct {
    Vec3 position;
    Vec3 rotation;  // Euler angles in radians (pitch, yaw, roll)
    Vec3 scale;     // Scale factors for each axis
} Transform3d;

typedef struct {
    Tri* tris;  // Pointer to an array of triangles representing the mesh
    size_t size;  // Current number of triangles in the mesh
    size_t capacity; // Maximum number of triangles the mesh can hold
} Mesh;

typedef struct {
    Vec3 direction;
    int intensity;
} LightSource;

typedef struct {
    Vec3 position;  // Camera position in 3D space
    Vec3 direction; // Direction the camera is facing
    Vec3 up;        // Up vector for the camera orientation
    Mat4 projection_matrix; // Projection matrix for the camera
    int width;  // Width of the camera's viewport
    int height; // Height of the camera's viewport
} Camera;

typedef struct {
    Vec3 position;  // Position in 3D space
    Vec3 velocity;  // Velocity vector for movement
    Vec3 acceleration; // Acceleration vector for movement
    float speed;    // Speed of the entity
    float rotation; // Rotation angle in radians
    float pitch;    // Pitch angle in radians
    float yaw;      // Yaw angle in radians
} Movement3d;

// ----------------------------------------------------------------------------------------
// Component Storage Structure
typedef struct {
    Transform3d* transform3ds;  // Array of Transform3d components
    bool* has_transform3d;  // Array to track if an entity has a Transform3d

    Mesh* meshes;  // Array of Mesh components
    bool* has_mesh;  // Array to track if an entity has a Mesh component

    LightSource* light_sources;  // Array of LightSource components
    bool* has_light_source;  // Array to track if an entity has a LightSource

    Camera* cameras;  // Array of Camera components
    bool* has_camera;  // Array to track if an entity has a Camera component
    
    Movement3d* movements;  // Array of Movement3d components
    bool* has_movement;  // Array to track if an entity has a Movement3d component
} ComponentStorage;

// ----------------------------------------------------------------------------------------

// Transform3d Management
extern Transform3d transform3ds[MAX_ENTITIES];  // Array of Transform3d components for each
extern bool has_transform3d[MAX_ENTITIES];  // Array to track if an entity has a Transform3d component
void add_transform3d(Entity entity_id, Transform3d* transform3d, int flags);
void remove_transform3d(Entity entity_id, int flags);
Transform3d* get_transform3d(Entity entity_id);

// Mesh Management
extern Mesh meshes[MAX_ENTITIES];  // Array of Mesh components for each entity
extern bool has_mesh[MAX_ENTITIES];  // Array to track if an entity has a Mesh component
void add_mesh(Entity entity_id, Mesh* mesh, int flags);
void remove_mesh(Entity entity_id, int flags);
Mesh* get_mesh(Entity entity_id);

// Light source management
extern LightSource light_sources[MAX_ENTITIES];
extern bool has_light_source[MAX_ENTITIES];  // Array of light source components for each entity
void add_light_source(Entity entity_id, LightSource* light_source, int flags);  // Array to track if an entity has a Light Source component
void remove_light_source(Entity entity_id, int flags);
LightSource* get_light_source(Entity entity_id);

// Camera Management
extern Camera cameras[MAX_ENTITIES];  // Array of Camera components for each entity
extern bool has_camera[MAX_ENTITIES];  // Array to track if an entity has a Camera component
void add_camera(Entity entity_id, Camera* camera, int flags);
void remove_camera(Entity entity_id, int flags);
Camera* get_camera(Entity entity_id);

// Movement3d Management
extern Movement3d movements[MAX_ENTITIES];  // Array of Movement3d components for each
extern bool has_movement[MAX_ENTITIES];  // Array to track if an entity has a Movement3d component
void add_movement(Entity entity_id, Movement3d* movement, int flags);
void remove_movement(Entity entity_id, int flags);
Movement3d* get_movement(Entity entity_id);