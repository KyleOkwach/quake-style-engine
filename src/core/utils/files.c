#include "files.h"

bool model_from_obj(char *filename, Mesh *mesh) {
    FILE *fptr;
    char line[256];  // Line buffer

    fptr = fopen(filename, "r");
    if (!fptr) {
        return false;  // File didn't open successfully
    }

    Vec3 *verts = NULL;
    size_t vert_count = 0;

    Tri *tris = NULL;
    size_t tri_count = 0;

    // Read each line
    while(fgets(line, sizeof(line), fptr)) {
        if (line[0] == 'v' && line[1] == ' ') {  // Vertex line ("v x y z")
            Vec3 v;
            if (sscanf(line + 2, "%f %f %f", &v.x, &v.y, &v.z) != 3) {
                fprintf(stderr, "Error parsing vertex: %s", line);
                continue;
            }

            // Append to verts
            vert_count++;
            verts = realloc(verts, sizeof(Vec3) * vert_count);
            if (!verts) {
                fprintf(stderr, "Memory allocation failed for vertices!\n");
                fclose(fptr);
                return false;
            }
            verts[vert_count - 1] = v;  // Append vert to end of verts array
        }else if (line[0] == 'f' && line[1] == ' ') {  // Face
            int v_indices[3] = {0}, vt_indices[3] = {0}, vn_indices[3] = {0};
            char *token = strtok(line + 2, " \t\n");  // Split face line into an array of tokens i.e { v1/vt1/vn1, v2/vt2/vn2, v3/vt3/vn3 }

            // Parse up to 3 vertices (triangulate quads later if needed)
            for (int i = 0; i < 3 && token != NULL; i++) {
                // Extract v, vt, vn indices (ignoring missing values)
                sscanf(token, "%d/%d/%d", &v_indices[i], &vt_indices[i], &vn_indices[i]);
                token = strtok(NULL, " \t\n");
            }

            // Validate vertex indices
            if (v_indices[0] == 0 || v_indices[1] == 0 || v_indices[2] == 0) {
                fprintf(stderr, "Invalid face indices: %s", line);
                continue;
            }

            // Add triangle (using only vertex positions for now)
            tri_count++;
            tris = realloc(tris, sizeof(Tri) * tri_count);
            tris[tri_count - 1] = (Tri){
                .p = {
                    verts[v_indices[0] - 1],
                    verts[v_indices[1] - 1],
                    verts[v_indices[2] - 1]
                }
            };
        }
    }

    fclose(fptr);

    mesh->tris = tris;
    mesh->size = tri_count;
    mesh->capacity = tri_count;

    free(verts);
    return true;
}