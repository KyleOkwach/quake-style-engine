#include "game.h"

float f_theta = 0.0f; // Initialize rotation angle

SDL_AppResult game_init(void *appstate) {
    AppState *state = (AppState*)appstate;  // Cast appstate to AppState pointer
    if (!state) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "AppState is NULL in game_init");
        return SDL_APP_FAILURE;  // Return failure if appstate is NULL
    }

    // Testing...
    // ...

    // Initialize the camera
    Camera camera;
    Vec3 camera_position = {0.5f, 0.5f, 3.0f}; // Position the camera slightly above the center
    Vec3 camera_direction = {0.0f, 0.0f, 1.0f}; // Point the camera towards the positive Z direction
    Vec3 camera_up = {0.0f, 1.0f, 0.0f}; // Define the up direction for the camera
    float near_plane = 0.1f; // Near clipping plane
    float far_plane = 100.0f; // Far clipping plane
    float fov = 60.0f; // Field of view in degrees
    camera_init(
        &camera,
        camera_position,
        camera_direction,
        camera_up,
        near_plane,
        far_plane,
        fov,
        (float)state->resolution_width / (float)state->resolution_height, // Aspect ratio
        state->resolution_width, state->resolution_height);

    Mesh mesh;
    Tri* tris = SDL_malloc(sizeof(Tri) * 12); // 12 triangles for a cube
    SDL_memcpy(tris, (Tri[]){
        // South
        { .p = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}} },
        { .p = {{1, 0, 0}, {1, 1, 0}, {0, 1, 0}} },
        // East
        { .p = {{1, 0, 0}, {1, 0, 1}, {1, 1, 0}} },
        { .p = {{1, 0, 1}, {1, 1, 1}, {1, 1, 0}} },
        // North
        { .p = {{1, 0, 1}, {0, 0, 1}, {1, 1, 1}} },
        { .p = {{0, 0, 1}, {0, 1, 1}, {1, 1, 1}} },
        // West
        { .p = {{0, 0, 1}, {0, 0, 0}, {0, 1, 1}} },
        { .p = {{0, 0, 0}, {0, 1, 0}, {0, 1, 1}} },
        // Top
        { .p = {{0, 1, 0}, {1, 1, 0}, {0, 1, 1}} },
        { .p = {{1, 1, 0}, {1, 1, 1}, {0, 1, 1}} },
        // Bottom
        { .p = {{0, 0, 0}, {1, 0, 0}, {0, 0, 1}} },
        { .p = {{1, 0, 0}, {1, 0, 1}, {0, 0, 1}} }
    }, sizeof(Tri) * 12);

    mesh.tris = tris;
    mesh.size = 12;
    mesh.capacity = 12;

    Entity player = create_entity();
    Entity cube = create_entity();
    add_camera(player, &camera, COMPONENT_DEBUG); // Add the camera to the entity
    add_mesh(cube, &mesh, COMPONENT_DEBUG);

    return SDL_APP_CONTINUE;  // Indicate that the game initialization was successful
}

void game_update(void *appstate) {
    AppState *state = (AppState*)appstate;  // Cast appstate to AppState pointer
    game_render();  // Call the render function to draw the game scene

    // Update the game state here
    state->current_tick = SDL_GetTicks();  // Get the current tick count in milliseconds
    state->delta_time = (state->current_tick - state->last_tick) / 1000.0f;  // Calculate delta time in seconds
    state->last_tick = state->current_tick;  // Update last tick to current tick
}

void game_render(void) {
    // Render the game scene here
    // This function will be called every frame to render the game
    
    // Find the first camera (assuming player entity ID 0 has the camera)
    Camera* main_camera = get_camera(0);
    if (!main_camera) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Warning: No camera found for rendering");
        return;
    }
    f_theta += 0.01f; // Increment the rotation angle for animation
    // Render all entities that have meshes
    for (Entity e = 0; e < MAX_ENTITIES; ++e) {
        Mesh* entity_mesh = get_mesh(e);
        if (entity_mesh) {
            rot_mesh_render_wireframe(entity_mesh, main_camera, 0xFFFFFFFF, f_theta); // Render the mesh in wireframe mode
        }
    }
}

void game_quit(void) {
    // Clean up game resources here
    SDL_Log("Cleaning up game resources...");
    for (Entity e = 0; e < MAX_ENTITIES; ++e) {
        if (has_mesh[e]) {
            SDL_free(meshes[e].tris); // Free the triangles allocated for the mesh
            has_mesh[e] = false; // Mark the mesh as no longer having a mesh component
        }
    }
    SDL_Log("Game resources cleaned up.");
}