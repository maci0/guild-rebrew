#include <string.h>

extern char g_770b80[];
extern unsigned char g_entity_type_bytes[];
extern char g_7f4caa[];
extern char g_7f4cc0[];
int __cdecl gm_RandomMod(unsigned short);
void __cdecl fcn_004fb620(void*);

typedef struct {
    int id;
    char name[0x30];
    int value[4];
} CHARACTER_PORTRAIT_SPEC;

/* ADDRESS: GOLD 0x004fb390 */
CHARACTER_PORTRAIT_SPEC* __cdecl gm_LookupPortraitSpec(unsigned int player)
{
    CHARACTER_PORTRAIT_SPEC* table;
    CHARACTER_PORTRAIT_SPEC* current;
    CHARACTER_PORTRAIT_SPEC* result;
    unsigned char kind;
    int i;
    int value;
    unsigned int off;

    table = 0;
    i = 0;
    off = player * 0x21c;
    kind = g_entity_type_bytes[off];
    if (!kind && (float) *(unsigned short*) (g_7f4caa + off)
        < *(float*) (g_7f4cc0 + off)) {
        if (g_770b80[off + 9])
            return (CHARACTER_PORTRAIT_SPEC*) 0x6118d0;
        return (CHARACTER_PORTRAIT_SPEC*) 0x611888;
    }
    if (g_770b80[off + 0x1f4] && *(int*) (g_770b80 + off + 0x18c) != -1) {
        value = *(int*) (g_770b80 + off + 0x18c);
        *(int*) 0x6f1bb0 = (*(int*) 0x6f1bb0 + 1) % 8;
        result = (CHARACTER_PORTRAIT_SPEC*) 0x91ac40 + *(int*) 0x6f1bb0;
        strcpy(result->name, g_770b80 + off + 0x1f4);
        value -= 0x639;
        result->value[0] = value;
        result->value[1] = value;
        result->value[2] = value;
        result->value[3] = value;
        return result;
    }
    if (g_770b80[off + 2] == 0x11)
        return (CHARACTER_PORTRAIT_SPEC*) 0x617378 + (unsigned short) gm_RandomMod(3);
    if (kind) {
        if (g_770b80[off + 9] == 0)
            table = (CHARACTER_PORTRAIT_SPEC*) 0x612bb8;
        else if (g_770b80[off + 9] == 1)
            table = (CHARACTER_PORTRAIT_SPEC*) 0x6144f8;
        current = table;
        do {
            if (!current->id)
                break;
            if (current->id == kind) {
                result = table + i;
                fcn_004fb620(result);
                return result;
            }
            i++;
            current++;
        } while (i < 0x5f);
        return table + i;
    }
    kind = *(unsigned char*) (g_770b80 + off + 0x165);
    if (kind) {
        if (g_770b80[off + 9] == 0)
            table = (CHARACTER_PORTRAIT_SPEC*) 0x611918;
        else if (g_770b80[off + 9] == 1)
            table = (CHARACTER_PORTRAIT_SPEC*) 0x612268;
        current = table;
        do {
            if (!current->id) {
                if (i < 0x23)
                    return table + i;
                break;
            }
            if (current->id == kind) {
                result = table + i;
                fcn_004fb620(result);
                return result;
            }
            i++;
            current++;
        } while (i < 0x23);
    }
    if (g_770b80[off + 9] == 0)
        table = (CHARACTER_PORTRAIT_SPEC*) 0x611918;
    else if (g_770b80[off + 9] == 1)
        table = (CHARACTER_PORTRAIT_SPEC*) 0x612268;
    return table;
}
