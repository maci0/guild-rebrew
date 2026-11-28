typedef unsigned char u8;
typedef unsigned short u16;
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char str_empty[];
extern char g_6a80c0[];

int __cdecl cm_GetCommandStatus(int);
char* __cdecl gm_SearchTable67(int);
int __cdecl gm_QueryEntities(int, int, int, int);
int __cdecl gm_AddTime(char*, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, char*,
                          char*);
int __cdecl init_EnsureObjektSceneContext(int);
void __cdecl d3_SelectSceneContext(int, int);
void* __cdecl evt_LoadGfxScript(char*);
void __cdecl evt_CallScriptFunction(void*, int, int);
void __cdecl he_FreeAction(char*);
void __cdecl he_AwardEvent0a0Bonus(char*);
int __cdecl cm_SendSetHE(int, char*);

/* ADDRESS: GOLDTL 0x0057cbc0 */
/* ADDRESS: GOLDDE 0x005629f0 */
void __cdecl he_UpdateEvent0a0(char* p)
{
    char buf[0x400];
    char* s;
    char* wnd;
    char* e;
    char* tbl;
    int w;
    int r;
    int gfx;

    if (*(int*) (p + 0x84) != -1 && cm_GetCommandStatus(*(int*) (p + 0x84)) == 0)
        return;
    if (*(int*) (p + 0x70) == -1 || *(int*) (p + 0x70) == -2) {
        he_FreeAction(p);
        return;
    }
    if (*(int*) (p + 0x70) == 0) {
        wnd = 0;
        s = gm_SearchTable67(*(int*) (p + 0x10));
        if (s != 0)
            wnd = (char*) gm_QueryEntities(*(int*) (s + 0x5d), 1, 0, 0x27f);
        gm_AddTime(p + 0x52, 2, 0, 0);
        if (wnd != 0) {
            w = *(unsigned short*) (s + 0x27);
            tbl = ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[w]);
            io_FormatTextBuffer(buf, 0x4205, s);
            he_MessageBoxQuickjump(*(int*) (tbl + 4), *(int*) (tbl + 4), buf, 0, 0x5fc,
                         *(int*) (s + 1), *(int*) (wnd + 2), str_empty,
                         str_empty);
            gfx = d3_CurrentContextIndex;
            r = init_EnsureObjektSceneContext((int) wnd);
            d3_SelectSceneContext(r, 1);
            e = (char*) evt_LoadGfxScript(g_6a80c0);
            if (e != 0) {
                *(int*) (e + 0x104) = *(int*) (wnd + 2);
                *(int*) (e + 0xc8c) = 1;
                evt_CallScriptFunction(e, 1, *(int*) (p + 0xac));
            }
            d3_SelectSceneContext(gfx, 1);
        }
        *(int*) (p + 0x58) = 0;
        *(int*) (p + 0x70) = 1;
        return;
    }
    if (*(int*) (p + 0x70) == 1 && (*(u8*) (p + 0x78) & 4) == 0) {
        he_AwardEvent0a0Bonus(p);
        *(int*) (p + 0x84) = cm_SendSetHE(-1, p);
    }
}
