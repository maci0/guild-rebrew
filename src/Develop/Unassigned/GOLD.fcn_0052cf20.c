extern int g_006333cc;
void __cdecl fcn_00476020(int);
unsigned char __cdecl fcn_004486e0(char*, int*);
void __cdecl fcn_0046f190(int, int, int, int, int, char*, int);
void __cdecl fcn_00468ea0(int, int, int, int);

typedef struct {
    int textId;
    unsigned int time;
    char* actor;
    char text[0x100];
} MessageSlot;

/* ADDRESS: GOLD 0x0052cf20 */
void __cdecl fcn_0052cf20(void)
{
    MessageSlot* p;
    char* object;
    char* entity;
    char* text;
    int rect[4];
    int x;
    int y;

    for (p = (MessageSlot*) 0x761fc0; p < (MessageSlot*) 0x7662c0; p++) {
        if (p->actor && (unsigned int) g_006333cc > p->time + 300u)
            p->actor = 0;
    }
    fcn_00476020(0x54);
    for (p = (MessageSlot*) 0x761fc0; p < (MessageSlot*) 0x7662c0; p++) {
        object = p->actor;
        if (!object)
            continue;
        entity = *(char**) (object + 0x34);
        if (*(int*) (entity + 0x208) != *(int*) 0x5fb5b0)
            continue;
        if (*(int*) (entity + 0x218) == 1) {
            entity = *(char**) (object + 0x22c);
            if (!entity || *(int*) (entity + 0x218) == 1)
                continue;
        }
        if (!fcn_004486e0(entity, rect))
            continue;
        x = (rect[2] - rect[0]) / 2 + rect[0] - 0x50;
        y = rect[1] - 0x40;
        text = p->text;
        if (!text[0])
            text = ((char**) 0x143a1c0)[p->textId];
        fcn_0046f190(x, y, 0xa0, 0x60, *(int*) 0x6ed924, text, 0x28);
        fcn_00468ea0(x, y, *(int*) 0x6ed968, *(int*) 0x6ed96c);
    }
}
