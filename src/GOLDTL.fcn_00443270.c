#include "Develop/Units/d3/d3_object.h"
#include "Develop/Units/d3/d3_d3d.h"

#ifdef REBREW_GOLD
#define d3_OWNER_OFFSET 0x10
#define d3_TABLE_OFFSET 0x14
#define d3_COUNT_OFFSET 0x1e0
#define d3_RESOURCE_OFFSET 0x64
#define d3_FLAG_OFFSET 0x68
#define d3_FLAG_BIT 0x80
#else
#define d3_OWNER_OFFSET 0x318
#define d3_TABLE_OFFSET 0x31c
#define d3_COUNT_OFFSET 0x1e4
#define d3_RESOURCE_OFFSET 0x50
#define d3_FLAG_OFFSET 0x54
#define d3_FLAG_BIT 0x40
#endif

/* Inferred name, source home and context/texture access views. */
/* ADDRESS: GOLDTL 0x00443270 */
/* ADDRESS: GOLD 0x00447800 */
void __cdecl fcn_00443270(char* object)
{
    char* context;
    char* owner;
    unsigned char** table;
    unsigned char* texture;
    void* resource;
    int count;
    int i;

    context = (char*) ((D3_OBJECT*) object)->kontext;
    if (context != 0) {
        owner = *(char**) (context + d3_OWNER_OFFSET);
        if (owner != 0) {
            count = *(int*) (owner + d3_COUNT_OFFSET);
            table = *(unsigned char***) (context + d3_TABLE_OFFSET);
            for (i = 0; i < count; i++) {
                texture = table[i];
                if (texture != 0) {
                    resource = *(void**) (texture + d3_RESOURCE_OFFSET);
                    if (resource != 0 && !(texture[d3_FLAG_OFFSET] & d3_FLAG_BIT)) {
#ifdef REBREW_GOLD
                        d3d_PrecacheTexture(resource);
#else
                        ((int (__stdcall*)(void*)) (*(void***) resource)[9])(resource);
#endif
                        table[i][d3_FLAG_OFFSET] |= d3_FLAG_BIT;
                    }
                }
            }
        }
    }
}
