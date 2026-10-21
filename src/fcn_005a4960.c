typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

void* __cdecl fcn_00470820(short a, short b, char* c);
void __cdecl fcn_00471b60(int a);
void __cdecl fcn_004727a0(int a, int b);
void __cdecl fcn_00519190(void* id, ...);
void __cdecl fcn_00473a90(int a, int b);
int __cdecl fcn_005373e0(void* a, int b);
void __cdecl fcn_0046f280(int w);
int __cdecl fcn_0046b2b0(int id);
int __cdecl fcn_0050d5d0(int id, char* owner, char** out);
int __cdecl fcn_0046f740(int a, int b, int c, int d);
int __cdecl fcn_0046f100(int a, int b, int c, int d, int e, int f);
void __cdecl fcn_00471e30(int a);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x005a4960 */
void __cdecl fcn_005a4960(void)
{
    int slot[9][3];
    char* dlg;
    int idx;
    int i;
    int ebx = 0;
    int esi = 1;

    for (i = 0; i < 9; i++) {
        slot[i][0] = -1;
        slot[i][1] = -1;
        slot[i][2] = 0;
    }

    dlg = fcn_00470820(0x6aabcc, 0, 0);
    fcn_00471b60((int)dlg);
    fcn_004727a0((int)dlg, 0);

    idx = 972 * *(int*)0x772514;
    *(int*)(0x10162e8 + idx) = 0xe;
    *(int*)(0x10162ec + idx) = 0x18;
    *(int*)(0x10162f0 + idx) = 0x18;
    *(int*)(0x10162f4 + idx) = 0xe;
    fcn_004727a0((int)dlg, 1);

    fcn_00519190((void*)0x18d9);
    fcn_00473a90(0, 0);

    while (fcn_005373e0((void*)0x5a4960, 0x677c7)) {
        if (esi != 0) {
            for (i = 0; i < 9; i++) {
                if (slot[i][0] != -1) {
                    fcn_0046f280(slot[i][0]);
                    fcn_0046b2b0(slot[i][1]);
                    slot[i][0] = -1;
                    slot[i][1] = -1;
                    slot[i][2] = 0;
                }
            }

            idx = fcn_0050d5d0(0, 0, (char**)slot);
            for (i = 0; i < idx; i++) {
                fcn_004727a0((int)dlg, 2);
                slot[i][1] = fcn_0046f740(0, 0, 0x75a,
                                           *(int*)0x772514);
                slot[i][2] = fcn_0046f100(0, 0, 0, 0x110,
                                           *(int*)0x772514, 0);
                idx = 972 * slot[i][2];
                *(int*)(0x10161cc + idx) = 0x56;
                *(int*)(0x1015f58 + idx) = 0x10;
                fcn_00519190((void*)0x18e0,
                             (void*)*(int*)(slot[i][0] + 0xb4));
                fcn_00519190((void*)0x18e1,
                             (void*)(slot[i][0] + 0xc4));
                fcn_00519190((void*)0x18e2,
                             (void*)*(int*)(slot[i][0] + 0xc0));
                ebx += *(int*)(slot[i][0] + 0x18) + 4;
            }
            ebx = 0;
        }
        esi = 0;

        if (*(int*)0x14ce8e0 != 0)
            *(int*)0x774654 = 1;
    }

    fcn_00471e30((int)dlg);
    fcn_00532ef0();
}
