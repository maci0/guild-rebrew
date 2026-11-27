#include <string.h>
extern unsigned int g_fb9084;
extern void* g_fb9074;
void* __cdecl m_alloc(unsigned int, const char*);
void __cdecl m_FreeTracked(void*);
void __cdecl d3_ClearObjectOverlayCoords(char*);

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

typedef struct {
    char pad00[0x68];
    unsigned char f68;
    char pad69[3];
    unsigned char alpha;
    unsigned char pad6d;
    unsigned char flags;
    char pad6f[0x11];
} D3_MATERIAL;

typedef union {
    unsigned int u32;
    struct {
        unsigned char b;
        unsigned char g;
        unsigned char r;
        unsigned char a;
    } bgra;
} COLOR32;

/* ADDRESS: GOLD 0x0043dbc0 */
void __cdecl d3_InflateObject(char* object)
{
    INFLATED_BANK* bank;
    INFLATED_FACE* face;
    char* source;
    D3_MATERIAL* material;
    int* mapping;
    int group;
    unsigned char fresh_faces;
    int count;
    int i;
    int j;
    int material_index;
    int next_material;
    COLOR32 color;
    int fill;
    int len;

    if (object == 0 || *(void**)(object + 0x1ec) == 0) {
        return;
    }
    object[0x210] |= 4;
    d3_ClearObjectOverlayCoords(object);
    for (group = 0; group <= 3; group++) {
        bank = (INFLATED_BANK*)(*(char**)(object + 0x1ec) + 0xf4 + group * 0x198);
        source = bank->source;
        if (source == 0) {
            continue;
        }
        fresh_faces = 0;
        if (bank->faces == 0 && (count = *(int*)(source + 0x4c)) > 0) {
            bank->face_count = count;
            bank->faces = (INFLATED_FACE*)m_alloc(count * 0x28, "d3:InflateObject(allpolys)");
            fresh_faces = 1;
        }
        if (bank->vertices == 0 && (count = *(int*)(source + 0x44)) > 0) {
            bank->vertex_count = count;
            bank->vertices = (INFLATED_VERTEX*)m_alloc((count + 8) * 0x50, "d3:InflateObject(allpoints)");
        } else if (!fresh_faces) {
            continue;
        }
        color.u32 = 0xffffffffU;
        if (*(int*)(source + 0x44) > 0) {
            for (i = 0; i < bank->vertex_count + 8; i++) {
                bank->vertices[i].point = *(char**)(source + 0x40) + i * 0x18;
                bank->vertices[i].diffuse = color.u32;
                bank->vertices[i].specular = color.u32;
            }
        }
        mapping = (int*)m_alloc(g_fb9084 * 4, "d3:!InflateObject(mat)");
        fill = -1;
        len = g_fb9084 * 4;
        __asm {
            mov edi, mapping
            mov eax, fill
            mov ebx, len
            mov ah, al
            shl eax, 0x10
            mov ecx, eax
            shr ecx, 0x10
            add eax, ecx
            lea ecx, [edi+edi*2]
            and ecx, 3
            sub ebx, ecx
            jle short FillMapTail
            rep stosb
            mov ecx, ebx
            and ebx, 3
            shr ecx, 2
            rep stosd
        FillMapTail:
            add ecx, ebx
            rep stosb
        }
        next_material = 0;
        face = bank->faces;
        for (i = 0; i < bank->face_count; i++, face++) {
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
            if (*(int*)(face->source + 0x24) >= 0) {
                material_index = mapping[*(int*)(face->source + 0x24)];
                if (material_index < 0) {
                    material_index = (D3_MATERIAL*)bank->materials[next_material++] - (D3_MATERIAL*)g_fb9074;
                    mapping[*(int*)(face->source + 0x24)] = material_index;
                }
                material = (D3_MATERIAL*)g_fb9074 + material_index;
                face->material = (char*)material;
                if (material->alpha < 0xff || (material->flags & 3)) {
                    color.bgra.a = material->alpha;
                    if (material->flags & 1) {
                        color.bgra.b = material->alpha;
                        color.bgra.g = material->alpha;
                        color.bgra.r = material->alpha;
                    } else {
                        color.bgra.b = 0xff;
                        color.bgra.g = 0xff;
                        color.bgra.r = 0xff;
                    }
                    for (j = 0; j < 3; j++) {
                        face->vertex[j]->diffuse = color.u32;
                        face->vertex[j]->specular = color.u32;
                    }
                }
                face->flags = (face->flags & 0xf7) | ((material->f68 & 1) << 3);
                for (j = 0; j < 3; j++) {
                    face->vertex[j]->mode = material->f68 & 1;
                }
            } else {
                face->material = 0;
            }
        }
        m_FreeTracked(mapping);
    }
}
