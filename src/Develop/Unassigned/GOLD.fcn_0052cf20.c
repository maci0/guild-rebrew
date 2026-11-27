extern volatile int g_6b7fac;
void __cdecl fcn_00476020(int);
unsigned char __cdecl d3_GetObjectScreenRect(char*, int*);
void __cdecl d2_RenderWrappedText(int, int, int, int, int, char*, int);
void __cdecl fcn_00468ea0(int, int, int, int);
#include "Develop/DieGildeAddOn/game/ch_motion.h"
typedef struct {
    int textId;
    unsigned int time;
    char* actor;
    char text[0x100];
} MessageSlot;

/* ADDRESS: GOLD 0x0052cf20 */
void __cdecl d2_RenderFloatingMessages(void)
{
    MessageSlot* slots = (MessageSlot*) 0x761fc0;
    int i;
    char* entity;
    int rect[4];
    int x;
    int y;

    for (i = 0; i < 0x40; i++) {
        if (slots[i].actor && (unsigned int) g_6b7fac > slots[i].time + 300u)
            slots[i].actor = 0;
    }
    fcn_00476020(0x54);
    for (i = 0; i < 0x40; i++) {
        if (!slots[i].actor)
            continue;
        entity = *(char**) (slots[i].actor + 0x34);
        if (*(int*) (entity + 0x208) != g_67a370)
            continue;
        if (*(int*) (entity + 0x218) != 1) {
            if (!d3_GetObjectScreenRect(entity, rect))
                continue;
        } else {
            entity = *(char**) (slots[i].actor + 0x22c);
            if (!entity || *(int*) (entity + 0x218) == 1 || !d3_GetObjectScreenRect(entity, rect))
                continue;
        }
        y = rect[1] - 0x40;
        x = (rect[2] - rect[0]) / 2 + rect[0] - 0x50;
        if (slots[i].text[0])
            d2_RenderWrappedText(x, y, 0xa0, 0x60, *(int*) 0x6ed924, slots[i].text, 0x28);
        else
            d2_RenderWrappedText(x, y, 0xa0, 0x60, *(int*) 0x6ed924, ((char**) 0x143a1c0)[slots[i].textId], 0x28);
        fcn_00468ea0(x, y, *(int*) 0x6ed968, *(int*) 0x6ed96c);
    }
}
