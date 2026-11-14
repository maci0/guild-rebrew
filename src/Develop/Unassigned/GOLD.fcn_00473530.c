#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl fcn_0047cb60(int, unsigned int);
int __cdecl fcn_0046ea00(const char*, int);
int __cdecl fcn_004759e0(int, int*, int*);
#include <string.h>

/* ADDRESS: GOLD 0x00473530 */
void __cdecl fcn_00473530(int id, char* text)
{
    GuiEnt* entry;
    char* left;
    char* right;
    int offset;
    int unused;
    int width;
    int data;

    offset = id * 0x2ec;
    entry = (GuiEnt*) ((char*) g_00f8f080 + offset);
    if (entry->kind == 9) {
        data = (int) entry->data;
        left = (char*) fcn_0047cb60(data, 0);
        right = (char*) fcn_0047cb60(data, 1);
        id = fcn_0046ea00(text, *(int*) 0x5fe73c)
            + *(unsigned short*) (right + 6) + 4
            + *(unsigned short*) (left + 6);
        strncpy((char*) entry + 0x7c, text, 0x3f);
        ((GuiEnt*) ((char*) g_00f8f080 + offset))->w = (short) id;
        return;
    }
    if (!fcn_004759e0(id, &id, &unused))
        id = 0x18;
    strncpy((char*) g_00f8f080 + offset + 0x7c, text, 0x3f);
    entry = (GuiEnt*) ((char*) g_00f8f080 + offset);
    if (*(int*) ((char*) entry + 0x5c) == 0) {
        width = fcn_0046ea00(text, entry->font) + 6 + id;
        ((GuiEnt*) ((char*) g_00f8f080 + offset))->w = (short) width;
    } else {
        entry->w = (short) id;
    }
}
