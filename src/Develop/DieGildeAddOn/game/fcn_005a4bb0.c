typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

void* __cdecl fcn_00470820(short a, short b, char* c);
void __cdecl fcn_00471b60(int a);
void __cdecl d2_SetForm(int a, int b);
int __cdecl fcn_00519190(void* id, ...);
int __cdecl fcn_00472250(int a, int b, int c);
int __cdecl fcn_0050b710(int a, int b);
int __cdecl fcn_0050b750(int a);
void __cdecl fcn_00473a90(int a, int b);
int __cdecl fcn_005373e0(void* a, int b);
int __cdecl fcn_00471f80(int a);
int __cdecl gm_QueryEntitySum(int a, int b);
int __cdecl gm_AccumulateTyped2(int a);
void __cdecl fcn_00472380(int a, ...);
void __cdecl fcn_004c5150(int a, int b, int c, int d);
void __cdecl fcn_004c4510(void* a, int b);
void __cdecl fcn_004c4570(int a, int b, int c, void* d);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00471e30(int a);

/* ADDRESS: GOLDTL 0x005a4bb0 */
void __cdecl fcn_005a4bb0(char* o)
{
    char* dlg;
    int have;
    int idx;
    int r;
    int it1;
    int it2;
    int sval;
    int a;
    int b;
    int v;
    int d;

    dlg = (char*) fcn_00470820(0, 0, "locations\\geldleihe\\geldleihe_KreditFreigabe");
    fcn_00471b60((int)dlg);
    d2_SetForm((int)dlg, 1);
    fcn_00519190((void*)0x18e5);
    have = gm_QueryEntitySum(*(int*)(o + 0x5d), *(u8*)0x773d75);
    d2_SetForm((int)dlg, 2);
    idx = *(u16*)(*(u8*)0x773d75 * 0x2f4 + 0x8680b4);
    r = fcn_00519190((void*)0x18e6, (void*)(2 * idx + 0x9a8));
    it1 = fcn_00472250((int)dlg, 2, r);
    it2 = fcn_00472250((int)dlg, 2, r + 1);
    fcn_00472380(it1, 5, 0x28, *(int*)(o + 0x65));
    sval = gm_AccumulateTyped2(*(u16*)(o + 0x27) * 0x21c + 0x7f4ca0);
    a = fcn_0050b710(have, *(u8*)0x773d75);
    b = fcn_0050b710(sval, *(u8*)0x773d75);
    fcn_00472380(it2, 0, b);
    fcn_00473a90(0, 0);
    while (fcn_005373e0((void*)0x5a4bb0, 0x677c7) != 0) {
        if (*(int*)0x14ce8e0 != 0 || *(int*)0x100f1dc == 1)
            *(int*)0x774654 = 1;
        v = fcn_0050b750(fcn_00471f80(it2));
        *(int*)0x774698 = have - v;
        if (*(int*)0x100f1dc == 2) {
            v = fcn_0050b750(fcn_00471f80(it2));
            if (have < v)
                d = v - have;
            else
                d = have - v;
            fcn_004c5150(*(int*)(0x7f4ca4 + *(u16*)(o + 0x27) * 0x21c),
                         *(int*)(o + 1), *(u8*)0x773d75, d);
            r = fcn_00471f80(it1);
            fcn_004c4510(o, *(int*)(o + 1));
            fcn_004c4570(4, 1, 0x65, &r);
            fcn_004c5360();
            *(int*)0x774654 = 1;
        }
    }
    fcn_00471e30((int)dlg);
    *(int*)0x774698 = 0;
}
