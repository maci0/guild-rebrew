#include "Develop/client_types.h"

typedef struct {
    int kind;
    char pad4[0x10];
} Lane;
extern Lane g_778d4c[4];
extern Slot_778da0 g_778da0[16];
extern char* d2_Controls;

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

void* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
int __cdecl gm_GetStorageSlotCapacity(char* a1, int a2);
int __cdecl gm_GetMsgField(char* msg, char* pkt);
u16* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl d2_GetControlValue(int id);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00597bb0 */
int __cdecl d2_UpdateProduktionSlotGrid(char* ep)
{
    int tbl[68] = {
        2,0,0,0, 2,0,0,0, 2,0,0,0, 3,0,0,0,
        4,0,0,0, 3,2,0,0, 4,2,0,0, 4,3,0,0,
        4,4,0,0, 4,3,2,0, 4,3,3,0, 4,4,3,0,
        4,4,4,0, 4,4,3,2, 4,4,3,3, 4,4,4,3,
        4,4,4,4
    };
    u16* q;
    int b;
    int id;
    int i, j, slot, idx;

    for (i = 0; i < 4; i++) {
        b = *(u8*)(ep + 0x1c);
        g_778d4c[i].kind = tbl[i + b * 4];
    }

    q = (u16*)fcn_00502cd0(*(int*)(ep + 0x14), 1, 5);
    if (q != 0) {
        do {
            idx = 0;
            id = *q;
            for (; idx < 16; idx++) {
                if (g_778da0[idx].x0 == id) {
                    break;
                }
            }
            if (idx >= 16) {
                for (slot = 0; slot < 16; slot++) {
                    if (g_778da0[slot].x0 == 0) {
                        break;
                    }
                }
                if (slot < 16) {
                    g_778da0[slot].x0 = id;
                    g_778da0[slot].x2c = 0;
                    g_778da0[slot].x30 = 0;
                    g_778da0[slot].x34 = 0;
                }
            } else {
                g_778da0[idx].x30 =
                    gm_GetMsgField(ep, (char*)q);
            }
            q = gm_NextEntityQueryMatch();
        } while (q != 0);
    }

    for (j = 0; j < 16; j++) {
        q = (u16*)fcn_00502cd0(*(int*)(ep + 0x14), 1, 0,
                                g_778da0[j].x0);
        if (q != 0) {
            g_778da0[j].x30 =
                gm_GetMsgField(ep, (char*)q);
            g_778da0[j].x34 =
                gm_GetStorageSlotCapacity((char*)ep, *(u16*)q);
        }
    }

    b = 0;
    for (j = 0; b == 0 && j < 16; j++) {
        id = g_778da0[j].x10;
        if (id != -1) {
            if (((D2_CONTROL_TL*) ((int) d2_Controls))[id].kind == 0x41) {
                if (d2_GetControlValue(id))
                    b = 1;
            }
        }
    }
    return b;
}
