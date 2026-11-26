#include "client_types.h"
#pragma pack(push, 2)
/* SIZE 0xe */
#include "Develop/DieGildeAddOn/game/entity_record.h"





#pragma pack(pop)


extern pos14_7f4c00 gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_7f4ca0[];
extern int gm_CityEntity;
extern char g_6a5998[];

void __cdecl he_FreeAction(char*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl gm_ResolveEntityById(char**, int, int, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(int, char*);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_GetElapsedMinutes(pos14_7f4c00*, pos14_7f4c00*);
void __cdecl fcn_00549c50(int, char*, char*, int);
int __cdecl gm_RandomMod(int);
void __cdecl cm_SendLogAction(char*);
void __cdecl fcn_004c6900(int*);
void __cdecl cm_SendTraceEnd(char*);

/* ADDRESS: GOLDTL 0x0054a210 */
void __cdecl fcn_0054a210(char* a0)
{
    char* o;
    char* sel;
    char* rec;
    int ev;
    int none;
    int loc[3];

    o = a0;
    none = -1;
    if (*(int*) (o + 0x70) == none || *(int*) (o + 0x70) == -2) {
        he_FreeAction(o);
        return;
    }
    if (*(unsigned char*) (o + 0x78) & 4) {
        return;
    }
    ev = *(int*) (o + 0x84);
    if (ev != none && cm_GetCommandStatus(ev) == 0) {
        return;
    }
    *(int*) (o + 0x84) = none;
    gm_ResolveEntityById(&a0, 0, 0, *(int*) (o + 0xac));
    if (a0 == 0) {
        gm_AddTime((pos14_7f4c00*) (o + 0x52), 0, 5, 0);
        fcn_004c5620(none, o);
        return;
    }
    sel = fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 6, 0, 0x12d);
    if (sel == 0) {
        gm_AddTime((pos14_7f4c00*) (o + 0x52), 0, 5, 0);
        fcn_004c5620(none, o);
        return;
    }
    if (*(unsigned short*) (a0 + 0x27) != 0xffff) {
        rec = ((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[*(unsigned short*) (a0 + 0x27)]);
        if (rec != 0 && rec != (char*) gm_CityEntity && *(char*)&((ENTITY_RECORD_VIEW*)rec)->health != 0 && *(char*)&((ENTITY_RECORD_VIEW*)rec)->entity_type != 0xf) {
            if (*(int*) (o + 0xc0) == 1) {
                fcn_00549c50(0x6e657720, a0, sel, -1);
                *(int*) (o + 0xc0) = *(int*) (o + 0xc0) - 1;
                *(pos14_7f4c00*) (o + 0x52) = gm_GameTime;



                gm_AddTime((pos14_7f4c00*) (o + 0x52), 1, 0, 0);
                *(pos14_7f4c00*) (o + 0xb0) = gm_GameTime;
                gm_AddTime((pos14_7f4c00*) (o + 0xb0), 0x18, 0, 0);
                *(int*) (o + 0xb6) = 0;
                *(short*) (o + 0xb4) = gm_RandomMod(4) + 0x13;
                fcn_004c5620(0, o);
                return;



            }
            else {
                if (gm_GetElapsedMinutes(&gm_GameTime, (pos14_7f4c00*) (o + 0xb0)) > 0) {
                    gm_AddTime((pos14_7f4c00*) (o + 0x52), 1, 0, 0);
                    fcn_004c5620(0, o);
                    return;
                }
                fcn_00549c50(0x65786563, a0, sel, -1);
                *(pos14_7f4c00*) (o + 0x52) = gm_GameTime;



                gm_AddTime((pos14_7f4c00*) (o + 0x52), 1, 0, 0);
                *(pos14_7f4c00*) (o + 0xb0) = gm_GameTime;
                gm_AddTime((pos14_7f4c00*) (o + 0xb0), 0x18, 0, 0);
                *(int*) (o + 0xb6) = 0;
                *(short*) (o + 0xb4) = gm_RandomMod(4) + 0x13;
                fcn_004c5620(0, o);
                return;



            }
        }
    }
    if (*(int*) (o + 0xc0) == 0) {
        loc[0] = 0x636c6572;
        loc[1] = none;
        loc[2] = *(int*) (a0 + 1);
        cm_SendLogAction(g_6a5998);
        fcn_004c6900(loc);
        cm_SendTraceEnd(g_6a5998);
        *(int*) (o + 0xc0) = *(int*) (o + 0xc0) + 1;
    }
    *(pos14_7f4c00*) (o + 0x52) = gm_GameTime;



    gm_AddTime((pos14_7f4c00*) (o + 0x52), 1, 0, 0);
    *(pos14_7f4c00*) (o + 0xb0) = gm_GameTime;



    gm_AddTime((pos14_7f4c00*) (o + 0xb0), 0x18, 0, 0);
    *(int*) (o + 0xb6) = 0;
    *(short*) (o + 0xb4) = gm_RandomMod(4) + 0x13;
    fcn_004c5620(0, o);
}
