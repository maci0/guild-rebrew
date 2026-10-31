typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

void* __cdecl gm_LookupEntityRecordById(int a1);
int __cdecl fcn_004c5620(char a1, unsigned char* e);
void* __cdecl fcn_005463a0(int n, ...);
void* __cdecl he_fn_Handlung(void);
void __cdecl fcn_005b22d0(void* a1);
void __cdecl fcn_00500bb0(void* clock, int a2, int a3, int a4);
void __cdecl fcn_005100f0(int id, int amount);
int __cdecl fcn_004f4f60(int idx, int id, int a3, int a4, int a5);
int __cdecl gm_RandomMod(int);
float __cdecl gm_GetEntitySkill(char* entity, int idx);
int __cdecl fcn_005c6270(char* a1, int a2);
void __cdecl fcn_005b2350(void* a1, void* a2);
void __cdecl fcn_005b2310(void* a1);

#define CP14(d) do { \
    *((u32*)(d)) = *((u32*)0x7f4c00); \
    *((u32*)((d)+4)) = *((u32*)0x7f4c04); \
    *((u32*)((d)+8)) = *((u32*)0x7f4c08); \
    *((u16*)((d)+12)) = *((u16*)0x7f4c0c); \
} while (0)

/* ADDRESS: GOLDTL 0x0054c240 */
void __cdecl fcn_0054c240(u8* o)
{
    char* r;
    int cnt = 0;
    u32 k;
    u8* d;

    if (o[0x78] & 4)
        return;

    r = gm_LookupEntityRecordById(*((u32*)(o + 0xbc)));
    if (r == 0) {
        d = o + 0x52;
        CP14(d);
        *((u32*)(o + 0x84)) = (u32)fcn_004c5620(-1, o);
        return;
    }

    if (fcn_005463a0(1, 0, 0x35) != 0) {
        do {
            cnt++;
        } while (he_fn_Handlung() != 0);
        if (cnt > 4) {
            d = o + 0x52;
            CP14(d);
            *((u32*)(o + 0x84)) = (u32)fcn_004c5620(-1, o);
            return fcn_005b22d0((void*)(0x7f4ca0 + 540 * (u32)*(u16*)(o + 8)));
        }
    }

    d = o + 0x52;
    CP14(d);
    CP14(o + 0x44);
    CP14(o + 0xac);

    fcn_00500bb0(d, 0, 1, 0);
    fcn_00500bb0(o + 0xac, 0x18, 0, 0);

    k = 540 * (u32)*(u16*)(o + 8);
    fcn_005100f0(*((u32*)(0x7f4ca4 + k)), -1);

    {
        u32 p = *((u32*)(0x7f4e10 + k));
        int id2;
        if (p)
            id2 = *((u32*)(p + 1));
        else
            id2 = -1;
        fcn_004f4f60(id2, *((u32*)(o + 0xbc)),
                      *((u32*)(0x7f4ca4 + k)), 1, 3);
    }

    *((u32*)(o + 0xc4)) = (u32)(gm_RandomMod(0x300) & 0xffff);
    *((u32*)(o + 0xc8)) = *((u32*)(0x664398 +
                              4 * (u32)(gm_RandomMod(0x10) & 0xffff)));
    *((float*)(o + 0xd0)) = gm_GetEntitySkill((char*)(0x7f4ca0 + k), 4);
    *((u32*)(o + 0xcc)) = 0x300;

    if (fcn_005c6270((char*)0x15c, r) != 0) {
        CP14(d);
        *((u32*)(o + 0x84)) = (u32)fcn_004c5620(-1, o);
        fcn_005b2350(r, (void*)(0x7f4ca0 + k));
        return;
    }

    fcn_005b2310(r);
    *((u32*)(o + 0x84)) = (u32)fcn_004c5620(0, o);
}
