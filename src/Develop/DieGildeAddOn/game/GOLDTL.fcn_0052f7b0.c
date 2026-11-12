typedef unsigned char u8;
#include <string.h>
#include "game_data.h"
typedef struct SelectProto { unsigned char kind; unsigned char rest[0x24c]; } SelectProto;
extern int g_67d370;
extern int g_6a25b4;
extern int g_6a25b8;
extern int g_6a25e0;
extern int g_6a25e4;
extern int g_6a25ec;
extern int g_6a2524;
extern char* g_7e2aa0;
extern int* g_7e2a9c;
extern char* g_7746c0;
extern int g_7746d8;
extern int g_7746dc;
extern int g_7746f0;
extern char g_7746f4;
extern char g_6b5c60[];

void* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl fcn_00472640(int, int);
int __cdecl gm_GetBuildingTypeCategory(int);
int __cdecl fcn_00506380(int, unsigned char*, unsigned short*, int);
int __cdecl fcn_0057ec20(int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl fcn_005cd440(char*, int, int, void*);
int __cdecl fcn_005ba910(int, int);
void __cdecl fcn_00525ef0(void);
void __cdecl fcn_0059aa10(char*, int);
void __cdecl fcn_005c3f10(char*);
void __cdecl fcn_005c49e0(char*);
int __cdecl fcn_0052f7a0(void);
void __cdecl fcn_0052ea30(void);
void __cdecl fcn_0052f710(void);
void __cdecl fcn_0052e450(unsigned short*);
void __cdecl fcn_0052e7b0(char*);
void __cdecl fcn_0052e5a0(void);
void __cdecl fcn_0052e250(unsigned short*);
void __cdecl fcn_0052df40(unsigned char*);

/* Dispatch selection actions, then refresh changed panel state. */
/* ADDRESS: GOLDTL 0x0052f7b0 */
void __cdecl fcn_0052f7b0(void)
{
    int query[20];
    char* selected;
    char* record;
    unsigned short* item;
    int focus;
    int count;
    int kind;
    int flags;
    int disabled;

    if (g_6a25b4 != -1 || g_774964 == 0)
        return;
    disabled = 1;
    if (g_7e2aa0 != 0 && fcn_00502cd0(*(int*)(g_7e2aa0 + 0x5d), 2, 6, 0, 0x2a) == 0
        && fcn_00502cd0(*(int*)(g_7e2aa0 + 0x5d), 2, 6, 0, 0x116) == 0)
        disabled = 0;
    fcn_00472640(g_6a25e4, disabled);
    selected = g_7e2aa0;
    flags = g_7e46ac & 0x2000;
    if (flags && g_100f1dc != -1) {
        if (g_6a25ec != -1 && g_67d370 == g_6a25ec) {
            if (g_7746c4 != 0) {
                g_7746dc = fcn_00506380(g_774970, (u8*)g_7746c4, 0, 0);
            } else if (g_7746c8 != 0) {
                if (g_7746cc != 0) {
                    item = (unsigned short*)fcn_00502cd0(*(int*)(g_7746c8 + 0x5d),
                        1, 0, *(unsigned short*)(g_7746c8 + 0x29));
                    g_7746dc = fcn_00506380(g_774970, 0, item, 0);
                } else {
                    g_7746dc = fcn_00506380(g_774970, g_7746c8, 0, 0);
                }
            } else {
                if (selected == 0)
                    goto refresh;
                g_7746dc = fcn_00506380(g_774970, (u8*)selected, 0, 0);
            }
            if (g_7746c4 != 0 && (g_7746dc & 0x10)) {
                fcn_0059aa10(g_7746c4, *(unsigned short*)(g_7746c4 + 0x29));
            } else if (g_7746c8 != 0 && g_7746cc == 0) {
                fcn_005c3f10((char*)g_7746c8);
            } else if (g_7746c8 != 0 && (g_7746dc & 0x10)) {
                fcn_0059aa10((char*)g_7746c8, *(unsigned short*)g_7746cc);
            } else if (g_7e2aa0 != 0) {
                kind = gm_GetBuildingTypeCategory(*(u8*)g_7e2aa0);
                g_7746dc = fcn_00506380(g_774970, (u8*)g_7e2aa0, 0, 0);
                if ((kind == 3 || kind == 5) && (g_7746dc & 0x10))
                    fcn_005c49e0(g_7e2aa0);
                else
                    fcn_005c3f10(g_7e2aa0);
            }
        } else if (g_6a25e4 != -1 && g_67d370 == g_6a25e4) {
            if (selected != 0 && *(u8*)selected != 0x47) {
                kind = gm_GetBuildingTypeCategory(*(u8*)selected);
                if (kind == 1 || kind == 2 || kind == 4 || kind == 7 || kind == 8 ||
                    ((SelectProto*)lpGebaeudePROT)[*(u8*)selected].kind == 0x10 ||
                    ((SelectProto*)lpGebaeudePROT)[*(u8*)selected].kind == 0x1e) {
                    if (fcn_0057ec20(0x400) == 1) {
                        g_7746d8 = fcn_00506380(g_774970, (u8*)selected, 0, 0);
                        fcn_0057e880(0x12, (int)selected, 0, 0);
                        fcn_005ba910((int)selected, 1);
                        fcn_0057e880(0x12, (int)selected, 1, 0);
                        g_7e2aa0 = selected;
                        fcn_00525ef0();
                    }
                }
            }
        } else if (g_6a25e0 != -1 && g_67d370 == g_6a25e0) {
            if (fcn_0057ec20(0x80) == 1) {
                memset(query, 0, sizeof(query));
                query[1] = 0;
                query[5] = 4;
                fcn_0057e880(0xf, 0, 0, 0);
                fcn_005cd440((char*)query, (int)g_6b5c60, (int)g_6b5c60,
                    (void*)fcn_0052f7a0);
                fcn_0057e880(0xf, 0, 1, 0);
            }
        }
    }
refresh:
    fcn_0052ea30();
    if (g_7e2aa0 == *(char**)0x774780 &&
        g_7746c8 == *(u8**)0x77477c &&
        g_7746c4 == *(char**)0x774778 &&
        g_7746cc == *(char**)0x774784 &&
        g_7e2a9c == *(int**)0x774788 &&
        g_7ea360 == *(int*)0x77478c &&
        (unsigned char)g_7746f4 == *(int*)0x774790 &&
        g_7746f0 == *(int*)0x774794 && g_6a2524 == 0)
        return;
    g_6a2524 = 0;
    fcn_0052f710();
    item = (unsigned short*)g_7e2a9c;
    focus = g_7ea360;
    count = g_7746f0;
    if (item != 0 && *(u8*)(lpObjektePROT + *item * 0x41) == 0x1d &&
        count == 0 && focus == 0) {
        fcn_0052e450(item);
        goto reload;
    }
    if (g_7746c0 == 0 && g_7746f4 == 0 && count == 0) {
        if (g_7746cc != 0 || focus != 0)
            goto snapshot;
        fcn_0052e5a0();
        goto reload;
    }
    if (count != 0 && (focus != *(int*)0x77478c || count != *(int*)0x774794)) {
        if (count > 1) {
            fcn_0052e7b0(0);
        } else {
            fcn_0052e7b0((char*)focus);
            *(int*)0x77478c = g_7ea360;
            fcn_0052ea30();
        }
        goto reload;
    }
    goto snapshot;
reload:
    item = (unsigned short*)g_7e2a9c;
    focus = g_7ea360;
    count = g_7746f0;
snapshot:
    record = g_7746cc;
    *(int*)0x774790 = (unsigned char)g_7746f4;
    *(int*)0x774794 = count;
    if (g_7746c0 == 0 && g_7746c8 == 0 && g_7746c4 == 0) {
        *(unsigned short**)0x774788 = item;
        selected = g_7e2aa0;
        *(u8**)0x77477c = 0;
        *(char**)0x774778 = 0;
        *(char**)0x774648 = 0;
        *(char**)0x774784 = record;
        *(int*)0x77478c = focus;
        *(char**)0x774780 = selected;
        return;
    }
    selected = g_7e2aa0;
    *(u8**)0x77477c = g_7746c8;
    *(char**)0x774778 = g_7746c4;
    *(char**)0x774784 = record;
    *(int*)0x77478c = focus;
    *(unsigned short**)0x774788 = item;
    *(char**)0x774780 = selected;
    if ((item != 0 || record != 0) && g_6a25b8 == -1) {
        *(char**)0x774648 = g_7746c0;
        if (item != 0) {
            fcn_0052e250(item);
            fcn_0052ea30();
            return;
        }
        if (record != 0) {
            fcn_0052e250((unsigned short*)record);
            fcn_0052ea30();
        }
        return;
    }
    if (g_7e2aa0 == 0 && g_7746c8 == 0) {
        *(char**)0x774648 = 0;
        return;
    }
    *(char**)0x774648 = g_7746c0;
    selected = g_7e2aa0 != 0 ? g_7e2aa0 : (char*)g_7746c8;
    fcn_0052df40((u8*)selected);
    fcn_0052ea30();
}
