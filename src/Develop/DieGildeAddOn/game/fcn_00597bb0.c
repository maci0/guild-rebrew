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

    b = ep[0x1c];
    for (i = 0; i < 3; i++)
        *(int*)(0x778d4c + 20 * i) = tbl[i + b * 4];

    q = (u16*)fcn_00502cd0(*(int*)(ep + 0x14), 1, 5);
    if (q != 0) {
        do {
            id = *q;
            idx = -1;
            for (j = 0; j < 16; j++) {
                if (*(int*)(0x778da0 + 56 * j) == id) {
                    idx = j;
                    break;
                }
            }
            if (idx >= 0) {
                *(int*)(0x778dd0 + 56 * idx) =
                    gm_GetMsgField(ep, (char*)q);
            } else {
                slot = -1;
                for (j = 0; j < 16; j++) {
                    if (*(int*)(0x778da0 + 56 * j) == 0) {
                        slot = j;
                        break;
                    }
                }
                if (slot >= 0 && slot < 16) {
                    *(int*)(0x778da0 + 56 * slot) = id;
                    *(int*)(0x778da0 + 56 * slot + 0x2c) = 0;
                    *(int*)(0x778da0 + 56 * slot + 0x30) = 0;
                    *(int*)(0x778da0 + 56 * slot + 0x34) = 0;
                }
            }
            q = gm_NextEntityQueryMatch();
        } while (q != 0);
    }

    for (i = 0; i < 16; i++) {
        q = (u16*)fcn_00502cd0(*(int*)(ep + 0x14), 1, 0,
                                *(int*)(0x778da0 + 56 * i));
        if (q != 0) {
            *(int*)(0x778dd0 + 56 * i) =
                gm_GetMsgField(ep, (char*)q);
            *(int*)(0x778dd0 + 56 * i + 4) =
                fcn_0050dfd0((char*)ep, *(u16*)q);
        }
    }

    for (i = 0; i < 16; i++) {
        id = *(int*)(0x778db0 + 56 * i);
        if (id != -1) {
            if (*(int*)(*(int*)0x1015ea0 + 756 * id + 0x20) == 0x41) {
                if (fcn_00471f80(id))
                    return 1;
            }
        }
    }
    return 0;
}
