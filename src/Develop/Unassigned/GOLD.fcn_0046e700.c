#include <string.h>
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/Units/m_alloc/m_alloc.h"
extern GuiEnt** g_006ed964;
extern void* g_006ed9dc;
void __cdecl fcn_0047ce20(int);
void __cdecl fcn_00472df0(int);
void __cdecl fcn_0046cab0(int);
void __cdecl fcn_00478fb0(int);
void __cdecl fcn_00468fa0(int, int, int, int, void*);
void __cdecl fcn_00468ea0(int, int, int, int);

/* ADDRESS: GOLD 0x0046e700 */
void __cdecl fcn_0046e700(int index)
{
    GuiEnt* element;
    GuiWin* parent;
    char* object;
    int offset;
    int i;
    offset = index * 0x2ec;
    element = (GuiEnt*) ((char*) g_00f8f080 + offset);
    if (*(int*) ((char*) element + 4) == 0) return;
    switch (element->kind) {
    case 0x43:
        if (element->bild_offset) m_FreeTracked((void*) element->bild_offset);
        break;
    case 4:
        fcn_0047ce20(element->bild_offset);
        break;
    case 0x40:
        fcn_00472df0(element->bild_offset);
        break;
    case 0x41:
        object = (char*) 0xfa6020 + element->bild_offset * 0x160;
        if (g_006ed9dc == object) g_006ed9dc = 0;
        if (*(int*) (object + 0x13c) != -1) fcn_0046cab0(*(int*) (object + 0x13c));
        memset(object, 0, 0x160);
        break;
    case 0x45:
        fcn_00478fb0(*(int*) ((char*) element + 0x98));
        break;
    case 9:
        if (element->parent) *(int*) ((char*) element->parent + 0x3b4) = 0;
        break;
    case 0x47:
        if (element->buf) {
            m_FreeTracked(element->buf);
            element->buf = 0;
        }
        break;
    }
    if (element->kind < 0x40) fcn_0046cab0(element->f08);
    parent = element->parent;
    if (parent) {
        i = 0;
        while (i < parent->count) {
            ++i;
            if (parent->list[i - 1] == index) break;
        }
        --i;
        if (i != parent->count) {
            memcpy(parent->list + i, parent->list + i + 1, (parent->count - i) * 4);
        }
        --parent->count;
    }
    object = (char*) element->f40;
    if (object && *(int*) (object + 0x198)) {
        fcn_00468fa0(element->x, element->y, element->w, element->f16, object);
    } else {
        fcn_00468ea0(element->x, element->y, element->w, element->f16);
    }
    for (i = 0; i < 0x2ff; i++) {
        if (g_006ed964[i] == element) {
            if (i == 0x2ff) g_006ed964[0x2ff] = 0;
            else memcpy(g_006ed964 + i, g_006ed964 + i + 1, 0xbf8 - i * 4);
            break;
        }
    }
    if (index == *(int*) 0x6ed94c) *(int*) 0x6ed94c = index - 1;
    memset((char*) g_00f8f080 + offset, 0, 0x2ec);
    ((GuiEnt*) ((char*) g_00f8f080 + offset))->id = index;
}
