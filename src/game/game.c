#include "game.h"

float f_theta = 0.0f; // Initialize rotation angle

SDL_AppResult game_init(void *appstate) {
    AppState *state = (AppState*)appstate;  // Cast appstate to AppState pointer
    if (!state) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "AppState is NULL in game_init");
        return SDL_APP_FAILURE;  // Return failure if appstate is NULL
    }

    Entity player = create_entity();
    Transform3d player_transform;
    player_transform.position.x = 0.0f;
    player_transform.position.x = 0.0f;
    player_transform.position.x = -3.0f;

    // Initialize the camera
    Camera camera;
    Vec3 camera_position = {0.0f, 0.0f, -3.0f}; // Position the camera slightly above the center
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
        state->resolution_width, state->resolution_height
    );

    Mesh mesh;
    model_from_obj("./assets/models/ranger.obj", &mesh);

    add_transform3d(player, &player_transform, 0);
    add_camera(player, &camera, 0); // Add the camera to the entity

    Entity test_model = create_entity();
    add_mesh(test_model, &mesh, 0);

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
            // mesh_render(entity_mesh, main_camera, 0xFFFFFFFF, MESH_FLAG_WIREFRAME | MESH_FLAG_BACKFACE_CULL);
            rot_mesh_render(entity_mesh, main_camera, 0xFFFFFFFF, f_theta, MESH_FLAG_WIREFRAME | MESH_FLAG_SOLID | MESH_FLAG_BACKFACE_CULL);
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