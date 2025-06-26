#include "ecs.h"

static Entity next_entity = 0;  // Static variable to keep track of the next available entity ID

Mesh meshes[MAX_ENTITIES] = {0};
bool has_mesh[MAX_ENTITIES] = {0};
Camera cameras[MAX_ENTITIES] = {0};
bool has_camera[MAX_ENTITIES] = {0};

Entity create_entity(void) {
    if (next_entity >= MAX_ENTITIES) {
        return 0;  // Return 0 if the maximum number of entities has been reached
    }  
    return next_entity++;  // Assign the current ID and increment for the next entity
}

void add_mesh(Entity entity_id, Mesh *mesh) {
    if (entity_id >= MAX_ENTITIES) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Entity ID %u is out of bounds. Maximum allowed is %d.", entity_id, MAX_ENTITIES - 1);
        return;  // Return if the entity ID is out of bounds
    }
    
    meshes[entity_id] = *mesh;  // Copy the mesh data into the entity's mesh component
    has_mesh[entity_id] = true;  // Mark that this entity has a mesh component
}

void add_camera(Entity entity_id, Camera *camera) {
    if (entity_id >= MAX_ENTITIES) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Entity ID %u is out of bounds. Maximum allowed is %d.", entity_id, MAX_ENTITIES - 1);
        return;  // Return if the entity ID is out of bounds
    }

    cameras[entity_id] = *camera;  // Copy the camera data into the entity's camera component
    has_camera[entity_id] = true;  // Mark that this entity has a camera component
}