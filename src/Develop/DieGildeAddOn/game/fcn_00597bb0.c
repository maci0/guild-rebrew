#include "client_types.h"

typedef struct {
    int kind;
    char pad4[0x10];
} Lane;
extern Lane g_778d4c[4];
extern Slot_778da0 g_778da0[16];
extern char* g_1015ea0;

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

void* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
int __cdecl fcn_0050dfd0(char* a1, int a2);
int __cdecl gm_GetMsgField(char* msg, char* pkt);
u16* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_00471f80(int id);

/* ADDRESS: GOLDTL 0x00597bb0 */
int __cdecl fcn_00597bb0(char* ep)
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
    Slot_778da0* rec;

    for (i = 0; i < 4; i++) {
        b = *(u8*)(ep + 0x1c);
        g_778d4c[i].kind = tbl[i + b * 4];
    }

    q = (u16*)fcn_00502cd0(*(int*)(ep + 0x14), 1, 5);
    if (q != 0) {
        do {
            id = *q;
            idx = -1;
            for (j = 0; j < 16; j++) {
                if (g_778da0[j].x0 == id) {
                    idx = j;
                    break;
                }
            }
            if (idx >= 0) {
                g_778da0[idx].x30 =
                    gm_GetMsgField(ep, (char*)q);
            } else {
                slot = -1;
                for (j = 0; j < 16; j++) {
                    if (g_778da0[j].x0 == 0) {
                        slot = j;
                        break;
                    }
                }
                if (slot >= 0 && slot < 16) {
                    g_778da0[slot].x0 = id;
                    g_778da0[slot].x2c = 0;
                    g_778da0[slot].x30 = 0;
                    g_778da0[slot].x34 = 0;
                }
            }
            q = gm_NextEntityQueryMatch();
        } while (q != 0);
    }

    for (rec = g_778da0; rec < g_778da0 + 16; rec++) {
        q = (u16*)fcn_00502cd0(*(int*)(ep + 0x14), 1, 0,
                                rec->x0);
        if (q != 0) {
            rec->x30 =
                gm_GetMsgField(ep, (char*)q);
            rec->x34 =
                fcn_0050dfd0((char*)ep, *(u16*)q);
        }
    }

    b = 0;
    for (rec = g_778da0; rec < g_778da0 + 16 && b == 0; rec++) {
        id = rec->x10;
        if (id != -1) {
            if (*(int*)((int) g_1015ea0 + 756 * id + 0x20) == 0x41) {
                if (fcn_00471f80(id))
                    b = 1;
            }
        }
    }
    return b;
}
