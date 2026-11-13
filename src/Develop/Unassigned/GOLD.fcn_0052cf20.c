extern int g_6b7fac;
void __cdecl fcn_00476020(int);
unsigned char __cdecl fcn_004486e0(char*, int*);
void __cdecl fcn_0046f190(int, int, int, int, int, char*, int);
void __cdecl fcn_00468ea0(int, int, int, int);
#include "Develop/DieGildeAddOn/game/ch_motion.h"
typedef struct {
    int textId;
    unsigned int time;
    char* actor;
    char text[0x100];
} MessageSlot;

/* ADDRESS: GOLD 0x0052cf20 */
void __cdecl fcn_0052cf20(void)
{
    char** p;
    char* object;
    char* entity;
    int rect[4];
    int x;
    int y;

    for (p = (char**) 0x761fc8; (int) p < 0x7662c8; p += 0x43) {
        if (*p && (unsigned int) g_6b7fac > ((unsigned int*) p)[-1] + 300u)
            *p = 0;
    }
    fcn_00476020(0x54);
    for (p = (char**) 0x761fc8; (int) p < 0x7662c8; p += 0x43) {
        object = *p;
        if (!object)
            continue;
        entity = *(char**) (object + 0x34);
        if (*(int*) (entity + 0x208) != g_67a370)
            continue;
        if (*(int*) (entity + 0x218) != 1) {
            if (!fcn_004486e0(entity, rect))
                continue;
        } else {
            entity = *(char**) (object + 0x22c);
            if (!entity || *(int*) (entity + 0x218) == 1 || !fcn_004486e0(entity, rect))
                continue;
        }
        y = rect[1] - 0x40;
        x = (rect[2] - rect[0]) / 2 + rect[0] - 0x50;
        if (((char*) p)[4])
            fcn_0046f190(x, y, 0xa0, 0x60, *(int*) 0x6ed924, (char*) (p + 1), 0x28);
        else
            fcn_0046f190(x, y, 0xa0, 0x60, *(int*) 0x6ed924, ((char**) 0x143a1c0)[((int*) p)[-2]], 0x28);
        fcn_00468ea0(x, y, *(int*) 0x6ed968, *(int*) 0x6ed96c);
    }
}
