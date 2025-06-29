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
Transform3d transform3ds[MAX_ENTITIES];
bool has_transform3d[MAX_ENTITIES];
void add_transform3d(Entity entity_id, Transform3d* transform3d, int flags) {
    ADD_COMPONENT(transform3ds, has_transform3d, entity_id, transform3d, flags);
}
void remove_transform3d(Entity entity_id, int flags) {
    REMOVE_COMPONENT(transform3ds, has_transform3d, entity_id, flags);
}
Transform3d* get_transform3d(Entity entity_id) {
    return GET_COMPONENT(transform3ds, has_transform3d, entity_id);
}

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

LightSource light_sources[MAX_ENTITIES];
bool has_light_source[MAX_ENTITIES];
void add_light_source(Entity entity_id, LightSource* light_source, int flags) {
    ADD_COMPONENT(light_sources, has_light_source, entity_id, light_source, flags);
}
void remove_light_source(Entity entity_id, int flags) {
    REMOVE_COMPONENT(light_sources, has_light_source, entity_id, flags);
}
LightSource* get_light_source(Entity entity_id) {
    return GET_COMPONENT(light_sources, has_light_source, entity_id);
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