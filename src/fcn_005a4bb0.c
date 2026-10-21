typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

void* __cdecl fcn_00470820(short a, short b, char* c);
void __cdecl fcn_00471b60(int a);
void __cdecl fcn_004727a0(int a, int b);
int __cdecl fcn_00519190(void* id, ...);
int __cdecl gm_QueryEntitySum(int a, int b);
int __cdecl fcn_00472250(int a, int b, int c);
void __cdecl d2_SetElementValue(int a, int b, int c, int d);
int __cdecl gm_AccumulateTyped2(void* p);
int __cdecl fcn_0050b710(int a, int b, ...);
int __cdecl fcn_0050b750(int a);
void __cdecl fcn_00473a90(int a, int b);
int __cdecl fcn_005373e0(void* a, int b);
int __cdecl fcn_00471f80(int a, int b);
int __cdecl fcn_004c5150(int a, int b, int c, int d);
void __cdecl fcn_004c4510(void* a, int b);
void __cdecl fcn_004c4570(int a, int b, int c, void* d);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00471e30(int a);

/* ADDRESS: GOLDTL 0x005a4bb0 */
void __cdecl fcn_005a4bb0(char* o)
{
    char* dlg;
    int ebx;
    int ebp;
    int hidx;
    int cidx;
    int tmp;

    dlg = fcn_00470820(0x6aabfc, 0, 0);
    fcn_00471b60((int)dlg);
    fcn_004727a0((int)dlg, 1);
    fcn_00519190((void*)0x18e5);

    ebx = gm_QueryEntitySum(*(int*)(o + 0x5d), *(u8*)0x773d75);
    fcn_004727a0((int)dlg, 2);

    cidx = 756 * *(u8*)0x773d75;
    hidx = *(u16*)(0x8680b4 + cidx);
    ebp = fcn_00519190((void*)0x18e6, (void*)(2 * hidx + 0x9a8));
    tmp = fcn_00472250((int)dlg, 2, ebp);
    ebp++;
    fcn_00472250((int)dlg, 2, ebp);

    d2_SetElementValue((int)o, 5, 0x28, *(int*)(o + 0x65));
    gm_AccumulateTyped2((void*)(0x7f4ca0 + 540 * *(u16*)(o + 0x27)));
    fcn_0050b710(ebx, *(u8*)0x773d75);
    tmp = fcn_0050b710(ebp, *(u8*)0x773d75, tmp);
    d2_SetElementValue((int)o, 0, 0, tmp);
    fcn_00473a90(0, 0);

    while (fcn_005373e0((void*)0x5a4bb0, 0x677c7)) {
        if (*(int*)0x14ce8e0 != 0 || *(int*)0x100f1dc == 1)
            *(int*)0x774654 = 1;

        tmp = fcn_0050b750(fcn_00471f80((int)dlg, *(u8*)0x773d75));
        *(int*)0x774698 = ebx - tmp;

        if (*(int*)0x100f1dc == 2) {
            tmp = fcn_0050b750(fcn_00471f80((int)dlg, *(u8*)0x773d75));
            if (ebx < tmp) {
                fcn_004c5150(*(int*)(o + 1),
                              *(int*)(0x7f4ca4 + 540 * *(u16*)(o + 0x27)),
                              *(u8*)0x773d75, tmp - ebx);
            } else {
                fcn_004c5150(*(int*)(o + 1),
                              *(int*)(0x7f4ca4 + 540 * *(u16*)(o + 0x27)),
                              *(u8*)0x773d75, ebx - tmp);
            }
            tmp = fcn_00471f80((int)dlg, *(u8*)0x773d75);
            fcn_004c4510(o, *(int*)(o + 1));
            fcn_004c4570(4, 1, 0x65, &tmp);
            fcn_004c5360();
            *(int*)0x774654 = 1;
        }
    }

    fcn_00471e30((int)dlg);
    *(int*)0x774698 = 0;
}
