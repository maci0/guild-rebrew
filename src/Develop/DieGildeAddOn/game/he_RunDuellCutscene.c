#include <string.h>

#pragma pack(push, 2)
/* SIZE 0xe */
typedef struct {
    int a;
    int b;
    int c;
    short d;
} Stamp_54fd60;
#pragma pack(pop)

/* SIZE 0x8 */
typedef struct {
    unsigned short slot;
    unsigned char type;
    char pad3;
    int id;
} Entity_54fd60;

/* SIZE 0xb8 */
typedef struct {
    char pad0[0x52];
    Stamp_54fd60 stamp;
    char pad60[0x10];
    int state;
    char pad74[4];
    unsigned char flags;
    char pad79[0xb];
    int event;
    char pad88[0x24];
    int actor;
    int target;
    int mode;
} Order_54fd60;

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntityIdField[];

Entity_54fd60* __cdecl gm_LookupEntityRecordById(int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
int __cdecl cm_SendSetHE(int, Order_54fd60*);
void __cdecl gm_AddTime(Stamp_54fd60*, int, int, int);
void __cdecl he_FreeAction(Order_54fd60*);
int __cdecl cm_EnqueueStagedPacket(void*);
int __cdecl cm_GetCommandStatus(int);

/* ADDRESS: GOLDTL 0x0054fd60 */
void __cdecl he_RunDuellCutscene(Order_54fd60* o)
{
    char msg[0x114];
    Entity_54fd60* a;
    Entity_54fd60* b;

    if (o->event != -1 && cm_GetCommandStatus(o->event) == 0) {
        return;
    }
    o->event = -1;
    switch (o->state) {
    case 2:
        if ((o->flags & 2) == 0) {
            return;
        }
        a = gm_LookupEntityRecordById(o->actor);
        b = gm_LookupEntityRecordById(o->target);
        if (a != 0) {
            if (b != 0) {
                memset(msg, 0, sizeof(msg));
                *(int*) (msg + 0x34) = a->id;
                *(int*) (msg + 0x1c) = gm_GameTimeHour;
                msg[8] = 4;
                msg[0x26] = 0xa2;
                *(int*) (msg + 0x14) = -1;
                msg[0x30] = 2;
                *(int*) (msg + 0xc) = *(int*) (gm_EntityIdField + (unsigned short) gm_LocalPlayerSlot * 0x21c);
                *(int*) (msg + 0x38) = b->id;
                *(int*) (msg + 0x18) = (*(int*) &gm_GameTime);
                msg[0x7c] = 0;
                *(int*) (msg + 0x20) = gm_GameTimeSliceDword;
                *(short*) (msg + 0x24) = gm_GameTimeTailWord;
                gm_AddTime((Stamp_54fd60*) (msg + 0x18), 0, 0x1e, 0);
                cm_EnqueueStagedPacket(msg);
            }
            cm_RequestChangeBits(a->id, 0x1c8, 4, 0, 0x400);
        }
        if (b != 0) {
            cm_RequestChangeBits(b->id, 0x1c8, 4, 0, 0x400);
        }
        o->stamp = (*(Stamp_54fd60*) &gm_GameTime);
        gm_AddTime(&o->stamp, 0, 2, 0);
        o->event = cm_SendSetHE(-1, o);
        return;
    case 1:
        if ((o->flags & 2) == 0) {
            return;
        }
        a = gm_LookupEntityRecordById(o->actor);
        b = gm_LookupEntityRecordById(o->target);
        if (a != 0) {
            cm_RequestChangeBits(a->id, 0x1c8, 4, 0, 0x400);
        }
        if (b != 0) {
            cm_RequestChangeBits(b->id, 0x1c8, 4, 0, 0x400);
        }
        o->stamp = (*(Stamp_54fd60*) &gm_GameTime);
        gm_AddTime(&o->stamp, 0, 2, 0);
        o->event = cm_SendSetHE(-1, o);
        return;
    case -1:
    case -2:
        if ((o->flags & 2) != 0) {
            a = gm_LookupEntityRecordById(o->actor);
            b = gm_LookupEntityRecordById(o->target);
            if (a != 0) {
                cm_RequestChangeBits(a->id, 0x1c8, 4, 0, 0x400);
            }
            if (b != 0) {
                cm_RequestChangeBits(b->id, 0x1c8, 4, 0, 0x400);
            }
            o->stamp = (*(Stamp_54fd60*) &gm_GameTime);
            gm_AddTime(&o->stamp, 0, 2, 0);
            o->event = cm_SendSetHE(-1, o);
        }
        he_FreeAction(o);
        return;
    }
}
