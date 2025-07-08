#include "files.h"
#include <string.h>

int model_from_obj(char *filename, Mesh *mesh) {
    FILE *fptr;
    char line[256];  // Line buffer

    if (!mesh) {
        fprintf(stderr, "Error: mesh pointer is NULL\n");
        return 1;
    }

    // Initialize mesh
    mesh->tris = NULL;
    mesh->size = 0;
    mesh->capacity = 0;

    errno_t err = fopen_s(&fptr, filename, "r");  // Safer than fopen
    if (err != 0) {
        fprintf(stderr, "Error %d opening file %s\n", err, filename);
        return 1;  // File didn't open successfully
    }

    Vec3 *verts = NULL;
    size_t vert_count = 0;

    Tri *tris = NULL;
    size_t tri_count = 0;

    // Read each line
    while(fgets(line, sizeof(line), fptr)) {
        if (line[0] == 'v' && line[1] == ' ') {  // Vertex line ("v x y z")
            Vec3 v;
            if (sscanf_s(line + 2, "%f %f %f", &v.x, &v.y, &v.z) != 3) {
                fprintf(stderr, "Error parsing vertex: %s", line);
                continue;
            }

            // Append to verts
            vert_count++;
            verts = realloc(verts, sizeof(Vec3) * vert_count);
            if (!verts) {
                fprintf(stderr, "Memory allocation failed for vertices!\n");
                fclose(fptr);
                return 1;
            }
            verts[vert_count - 1] = v;  // Append vert to end of verts array
        }else if (line[0] == 'f' && line[1] == ' ') {  // Face
            int v_indices[3] = {0}, vt_indices[3] = {0}, vn_indices[3] = {0};
            char *token;
            char *ctx;  // Context pointer
            int len = strlen(line);
            
            token = strtok_s(line + 2, " \t\n", &ctx);  // Split face line into an array of tokens i.e { v1/vt1/vn1, v2/vt2/vn2, v3/vt3/vn3 }

            // Parse up to 3 vertices (triangulate quads later if needed)
            for (int i = 0; i < 3 && token != NULL; i++) {
                // Extract v, vt, vn indices (ignoring missing values)
                sscanf_s(token, "%d/%d/%d", &v_indices[i], &vt_indices[i], &vn_indices[i]);
                token = strtok_s(NULL, " \t\n", &ctx);
            }

            // Validate vertex indices
            if (v_indices[0] == 0 || v_indices[1] == 0 || v_indices[2] == 0) {
                fprintf(stderr, "Invalid face indices: %s", line);
                continue;
            }

            // Add triangle (using only vertex positions for now)
            tri_count++;
            Tri *new_tris = realloc(tris, sizeof(Tri) * tri_count);
            if (!new_tris) {
                fprintf(stderr, "Memory allocation failed for triangles!\n");
                free(tris);
                free(verts);
                fclose(fptr);
                return 1;
            }
            tris = new_tris;
            tris[tri_count - 1] = (Tri){
                .p = {
                    verts[v_indices[0] - 1],
                    verts[v_indices[1] - 1],
                    verts[v_indices[2] - 1]
                }
            };  // Append tri to the end ofthe tris array
        }
    }

    fclose(fptr);

    mesh->tris = tris;
    mesh->size = tri_count;
    mesh->capacity = tri_count;

    free(verts);
    return 0;
}
