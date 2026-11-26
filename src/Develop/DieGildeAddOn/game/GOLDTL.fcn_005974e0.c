#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
unsigned short* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_0050dfd0(char*, int);
int __cdecl gm_GetMsgField(char*, char*);
void* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl gm_FindSlotById(int, int);
int __cdecl CountDisplayCounters(void);
void __cdecl cm_BeginPacketFieldDelta(void*, int);
void __cdecl cm_AppendCommandSyncField(int, int, int, void*);
void __cdecl cm_SendSetAttribute(void);
int __cdecl d2_GetControlValue(int);

/* Build the message slot table for one packet: widen the four 0x14-byte
   attribute rows selected by the packet's type byte, merge the queried
   message records into the 0x38-byte slot rows, then resolve each slot
   reference to its field values. */
/* ADDRESS: GOLDTL 0x005974e0 */
int __cdecl fcn_005974e0(int a0, char* a1)
{
    unsigned int layoutValues[68];
    unsigned int* v13;

    unsigned short* v5;
    unsigned short* v9;
    unsigned int* v6;
    int* v7;
    int v8;
    int v10;
    int v12;
    unsigned short v2;
    char* v3;

    v3 = a1;
    layoutValues[0] = 2;
    layoutValues[1] = 0;
    layoutValues[2] = 0;
    layoutValues[3] = 0;
    layoutValues[4] = 2;
    layoutValues[5] = 0;
    layoutValues[6] = 0;
    layoutValues[7] = 0;
    layoutValues[8] = 2;
    layoutValues[9] = 0;
    layoutValues[10] = 0;
    layoutValues[0xb] = 0;
    layoutValues[0xc] = 3;
    layoutValues[0xd] = 0;
    layoutValues[0xe] = 0;
    layoutValues[0xf] = 0;
    layoutValues[0x10] = 4;
    layoutValues[0x11] = 0;
    layoutValues[0x12] = 0;
    layoutValues[0x13] = 0;
    layoutValues[0x14] = 3;
    layoutValues[0x15] = 2;
    layoutValues[0x16] = 0;
    layoutValues[0x17] = 0;
    layoutValues[0x18] = 4;
    layoutValues[0x19] = 2;
    layoutValues[0x1a] = 0;
    layoutValues[0x1b] = 0;
    layoutValues[0x1c] = 4;
    layoutValues[0x1d] = 3;
    layoutValues[0x1e] = 0;
    layoutValues[0x1f] = 0;
    layoutValues[0x20] = 4;
    layoutValues[0x21] = 4;
    layoutValues[0x22] = 0;
    layoutValues[0x23] = 0;
    layoutValues[0x24] = 4;
    layoutValues[0x25] = 3;
    layoutValues[0x26] = 2;
    layoutValues[0x27] = 0;
    layoutValues[0x28] = 4;
    layoutValues[0x29] = 3;
    layoutValues[0x2a] = 3;
    layoutValues[0x2b] = 0;
    layoutValues[0x2c] = 4;
    layoutValues[0x2d] = 4;
    layoutValues[0x2e] = 3;
    layoutValues[0x2f] = 0;
    layoutValues[0x30] = 4;
    layoutValues[0x31] = 4;
    layoutValues[0x32] = 4;
    layoutValues[0x33] = 0;
    layoutValues[0x34] = 4;
    layoutValues[0x35] = 4;
    layoutValues[0x36] = 3;
    layoutValues[0x37] = 2;
    layoutValues[0x38] = 4;
    layoutValues[0x39] = 4;
    layoutValues[0x3a] = 3;
    layoutValues[0x3b] = 3;
    layoutValues[0x3c] = 4;
    layoutValues[0x3d] = 4;
    layoutValues[0x3e] = 4;
    layoutValues[0x3f] = 3;
    layoutValues[0x40] = 4;
    layoutValues[0x41] = 4;
    layoutValues[0x42] = 4;
    layoutValues[0x43] = 4;
    v10 = 0;
    v13 = (unsigned int*) 0x778d4c;
    do {
        v8 = v10 + *(unsigned char*) (v3 + 0x1c) * 4;
        v10 += 1;
        *v13 = layoutValues[v8];
        v13 += 5;
    } while ((int) v13 < 0x778d9c);

    v5 = fcn_00502cd0(*(unsigned int*) (v3 + 0x14), 1, 5);
    while (v5) {
        v10 = 0;
        v6 = (unsigned int*) 0x778da0;
        do {
            if (*v6 == (unsigned int) *v5) {
                if (v10 < 0x10) {
                    *(unsigned int*) (v10 * 0x38 + 0x778dd0) =
                        gm_GetMsgField(v3, (char*) v5);
                    goto next_match;
                }
                break;
            }
            v6 = &v6[0xe];
            v10 += 1;
        } while ((int) v6 < 0x779120);
        v10 = 0;
        v7 = (int*) 0x778da0;
        do {
            if (!*v7) {
                if (v10 < 0x10) {
                    if (*(unsigned short*) v3 != 0x1db && *(unsigned short*) v3 != 0x1dc) {
                        goto store_slot;
                    }
                    v8 = (int) gm_FindSlotById(*(unsigned int*) ((char*) a0 + 0x65),
                                               (unsigned int) *v5);
                    if (!v8 || *(int*) (v8 + 4)) {
                        goto store_slot;
                    }
                }
                break;
            }
            v7 = &v7[0xe];
            v10 += 1;
        } while ((int) v7 < 0x779120);
        goto next_match;
    store_slot:
        v10 *= 0x38;
        v2 = *v5;
        *(unsigned int*) (v10 + 0x778dcc) = 0;
        *(unsigned int*) (v10 + 0x778da0) = (unsigned int) v2;
        *(unsigned int*) (v10 + 0x778dd0) = 0;
        *(unsigned int*) (v10 + 0x778dd4) = 0;
    next_match:
        v5 = (unsigned short*) gm_NextEntityQueryMatch();
    }

    v13 = (unsigned int*) 0x778dd0;
    do {
        v9 = fcn_00502cd0(*(unsigned int*) (v3 + 0x14), 1, 0, v13[-0xc]);
        if (v9) {
            if (*(unsigned short*) v3 != 0x1db && *(unsigned short*) v3 != 0x1dc) {
                v10 = fcn_0050dfd0(v3, *v9);
                v13[-1] = (unsigned int) (v10 * *(int*) (v9 + 0xe)) >> 2;
                *v13 = gm_GetMsgField(v3, (char*) v9);
                v2 = *v9;
                v13[1] = fcn_0050dfd0(v3, v2);
            } else {
                v10 = (int) gm_FindSlotById(*(unsigned int*) ((char*) a0 + 0x65), *v9);
                if (v10 && *(int*) (v10 + 4)) {
                    *v13 = gm_GetMsgField(v3, (char*) v9);
                    v2 = *v9;
                    v13[1] = fcn_0050dfd0(v3, v2);
                }
            }
        } else {
            v13[-0xc] = 0;
        }
        v13 = &v13[0xe];
    } while ((int) v13 < 0x779150);

    if ((*(unsigned int*) 0x7746d8 & 0x200) && *(int*) 0x14ce8d8 &&
        !CountDisplayCounters()) {
        v7 = (int*) 0x778dc0;
        do {
            if (*v7 != -1 && *v7 == d2_CurrentElementId) {
                v10 = (int) fcn_00502cd0(*(unsigned int*) (v3 + 0x14), 1, 0,
                                         v7[-8]);
                if (!v10) {
                    break;
                }
                if (4 <= *(unsigned int*) (v10 + 0x1c)) {
                    v12 = 0;
                } else {
                    v12 = *(unsigned int*) (v10 + 0x1c) + 1;
                }
                cm_BeginPacketFieldDelta((void*) v10, *(unsigned int*) (v10 + 2));
                cm_AppendCommandSyncField(4, 1, (v10 - *(int*) 0xaed32c) + 0x1c, &v12);
                cm_SendSetAttribute();
                *(int*) (v10 + 0x1c) = v12;
            }
            v7 = &v7[0xe];
        } while ((int) v7 < 0x779140);
    }

    v10 = 0;
    v7 = (int*) 0x778db0;
    do {
        if (0x779130 <= (int) v7) {
            return v10;
        }
        v8 = *v7;
        if (v8 != -1 &&
            *(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[v8].kind)) == 0x41 &&
            d2_GetControlValue(v8)) {
            v10 = 1;
        }
        v7 = &v7[0xe];
    } while (!v10);
    return v10;
}
