#include <string.h>

extern char g_770b80[];
int __cdecl gm_RandomMod(unsigned short);
void __cdecl fcn_004fb620(void*);

typedef struct {
    int id;
    char name[0x30];
    int value[4];
} ENTRY_4fb390;

/* ADDRESS: GOLD 0x004fb390 */
ENTRY_4fb390* __cdecl fcn_004fb390(unsigned int player)
{
    char* slot;
    ENTRY_4fb390* table;
    ENTRY_4fb390* current;
    ENTRY_4fb390* result;
    unsigned char kind;
    int i;
    int value;

    table = 0;
    i = 0;
    slot = g_770b80 + player * 0x21c;
    kind = *(unsigned char*) (slot + 0x164);
    if (!kind && (float) *(unsigned short*) (slot + 0xa)
        < *(float*) (slot + 0x20)) {
        if (slot[9])
            return (ENTRY_4fb390*) 0x6118d0;
        return (ENTRY_4fb390*) 0x611888;
    }
    if (slot[0x1f4] && *(int*) (slot + 0x18c) != -1) {
        value = *(int*) (slot + 0x18c);
        *(int*) 0x6f1bb0 = (*(int*) 0x6f1bb0 + 1) % 8;
        result = (ENTRY_4fb390*) 0x91ac40 + *(int*) 0x6f1bb0;
        strcpy(result->name, slot + 0x1f4);
        value -= 0x639;
        result->value[0] = value;
        result->value[1] = value;
        result->value[2] = value;
        result->value[3] = value;
        return result;
    }
    if (slot[2] == 0x11)
        return (ENTRY_4fb390*) 0x617378 + (unsigned short) gm_RandomMod(3);
    if (kind) {
        if (slot[9] == 0)
            table = (ENTRY_4fb390*) 0x612bb8;
        else if (slot[9] == 1)
            table = (ENTRY_4fb390*) 0x6144f8;
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
    kind = *(unsigned char*) (slot + 0x165);
    if (kind) {
        if (slot[9] == 0)
            table = (ENTRY_4fb390*) 0x611918;
        else if (slot[9] == 1)
            table = (ENTRY_4fb390*) 0x612268;
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
    if (slot[9] == 0)
        table = (ENTRY_4fb390*) 0x611918;
    else if (slot[9] == 1)
        table = (ENTRY_4fb390*) 0x612268;
    return table;
}
