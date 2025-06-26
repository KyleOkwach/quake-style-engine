/*
* ECS (Entity Component System) implementation
* This file provides the implementation of the ECS system, including entity creation and component management.
*/
#include "ecs.h"

// --------------------------------------
// -----------Entity creation------------
// --------------------------------------
// This function creates a new entity by returning the next available entity ID
static Entity next_entity = 0;  // Static variable to keep track of the next available entity ID
Entity create_entity(void) {
    if (next_entity >= MAX_ENTITIES) {
        return 0;  // Return 0 if the maximum number of entities has been reached
    }  
    return next_entity++;  // Assign the current ID and increment for the next entity
}


// --------------------------------------
// ---------Component management---------
// --------------------------------------
// This section manages the components associated with entities in the ECS system
Mesh meshes[MAX_ENTITIES];
bool has_mesh[MAX_ENTITIES];
void add_mesh(Entity entity_id, Mesh* mesh, int flags) {
    ADD_COMPONENT(meshes, has_mesh, entity_id, mesh, flags);
}
void remove_mesh(Entity entity_id, int flags) {
    REMOVE_COMPONENT(meshes, has_mesh, entity_id, flags);
}
Mesh* get_mesh(Entity entity_id) {
    return GET_COMPONENT(meshes, has_mesh, entity_id);
}

Camera cameras[MAX_ENTITIES];
bool has_camera[MAX_ENTITIES];
void add_camera(Entity entity_id, Camera* camera, int flags) {
    ADD_COMPONENT(cameras, has_camera, entity_id, camera, flags);
}
void remove_camera(Entity entity_id, int flags) {
    REMOVE_COMPONENT(cameras, has_camera, entity_id, flags);
}
Camera* get_camera(Entity entity_id) {
    return GET_COMPONENT(cameras, has_camera, entity_id);
}

Position3d positions[MAX_ENTITIES];
bool has_position[MAX_ENTITIES];
void add_position(Entity entity_id, Position3d* position, int flags) {
    ADD_COMPONENT(positions, has_position, entity_id, position, flags);
}
void remove_position(Entity entity_id, int flags) {
    REMOVE_COMPONENT(positions, has_position, entity_id, flags);
}
Position3d* get_position(Entity entity_id) {
    return GET_COMPONENT(positions, has_position, entity_id);
}

Movement3d movements[MAX_ENTITIES];
bool has_movement[MAX_ENTITIES];
void add_movement(Entity entity_id, Movement3d* movement, int flags) {
    ADD_COMPONENT(movements, has_movement, entity_id, movement, flags);
}
void remove_movement(Entity entity_id, int flags) {
    REMOVE_COMPONENT(movements, has_movement, entity_id, flags);
}
Movement3d* get_movement(Entity entity_id) {
    return GET_COMPONENT(movements, has_movement, entity_id);
}