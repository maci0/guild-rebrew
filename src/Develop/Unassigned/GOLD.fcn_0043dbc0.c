#include <string.h>
void* __cdecl m_alloc(unsigned int, const char*);
void __cdecl m_FreeTracked(void*);
void __cdecl fcn_0045cdf0(char*);

typedef struct {
    char prefix[0x40];
    unsigned int diffuse;
    unsigned int specular;
    char* point;
    unsigned char flags;
    unsigned char mode;
    char tail[2];
} INFLATED_VERTEX;

typedef struct {
    INFLATED_VERTEX* vertex[3];
    int unknown0c;
    char* source;
    char* material;
    int field18;
    int field1c;
    int field20;
    unsigned char field24;
    unsigned char field25;
    unsigned char flags;
    unsigned char field27;
} INFLATED_FACE;

typedef struct {
    INFLATED_VERTEX* vertices;
    INFLATED_FACE* faces;
    int vertex_count;
    int face_count;
    char* source;
    char** materials;
} INFLATED_BANK;

/* ADDRESS: GOLD 0x0043dbc0 */
void __cdecl fcn_0043dbc0(char* object)
{
    INFLATED_BANK* bank;
    INFLATED_FACE* face;
    char* source;
    char* material;
    int* mapping;
    int group;
    int fresh_faces;
    int count;
    int i;
    int j;
    int material_slot;
    int material_index;
    int next_material;
    unsigned int alpha;
    unsigned int color;

    if (object == 0 || *(void**)(object + 0x1ec) == 0) {
        return;
    }
    object[0x210] |= 4;
    fcn_0045cdf0(object);
    for (group = 0; group < 4; group++) {
        bank = (INFLATED_BANK*)(*(char**)(object + 0x1ec) + 0xf4 + group * 0x198);
        source = bank->source;
        if (source == 0) {
            continue;
        }
        fresh_faces = 0;
        count = *(int*)(source + 0x4c);
        if (bank->faces == 0 && count > 0) {
            bank->face_count = count;
            bank->faces = (INFLATED_FACE*)m_alloc(count * 0x28, "d3:InflateObject(allpolys)");
            fresh_faces = 1;
        }
        count = *(int*)(source + 0x44);
        if (bank->vertices == 0 && count > 0) {
            bank->vertex_count = count;
            bank->vertices = (INFLATED_VERTEX*)m_alloc((count + 8) * 0x50, "d3:InflateObject(allpoints)");
        } else if (!fresh_faces) {
            continue;
        }
        if (*(int*)(source + 0x44) > 0) {
            for (i = 0; i < bank->vertex_count + 8; i++) {
                bank->vertices[i].point = *(char**)(source + 0x40) + i * 0x18;
                bank->vertices[i].diffuse = (unsigned int)-1;
                bank->vertices[i].specular = (unsigned int)-1;
            }
        }
        mapping = (int*)m_alloc(*(unsigned int*)0xfb9084 * 4, "d3:!InflateObject(mat)");
        memset(mapping, 0xff, *(unsigned int*)0xfb9084 * 4);
        next_material = 0;
        for (i = 0; i < bank->face_count; i++) {
            face = &bank->faces[i];
            face->field20 = 0;
            face->flags &= 0xfe;
            face->field1c = 0;
            face->field18 = 0;
            face->source = *(char**)(source + 0x48) + i * 0x38;
            for (j = 0; j < 3; j++) {
                face->vertex[j] = &bank->vertices[((int*)(face->source + 0x18))[j]];
                face->vertex[j]->flags |= 0x80;
            }
            face->field24 = 0;
            material_slot = *(int*)(face->source + 0x24);
            if (material_slot < 0) {
                face->material = 0;
                continue;
            }
            material_index = mapping[material_slot];
            if (material_index <= -1) {
                material_index = (bank->materials[next_material] - *(char**)0xfb9074) >> 7;
                next_material++;
                mapping[material_slot] = material_index;
            }
            material = *(char**)0xfb9074 + material_index * 0x80;
            face->material = material;
            alpha = *(unsigned char*)(material + 0x6c);
            if (alpha != 0xff || (material[0x6e] & 3)) {
                color = (alpha << 24) | ((material[0x6e] & 1) ? alpha * 0x010101U : 0x00ffffffU);
                for (j = 0; j < 3; j++) {
                    face->vertex[j]->diffuse = color;
                    face->vertex[j]->specular = color;
                }
            }
            face->flags = (face->flags & 0xf7) | ((material[0x68] & 1) << 3);
            for (j = 0; j < 3; j++) {
                face->vertex[j]->mode = material[0x68] & 1;
            }
        }
        m_FreeTracked(mapping);
    }
}
