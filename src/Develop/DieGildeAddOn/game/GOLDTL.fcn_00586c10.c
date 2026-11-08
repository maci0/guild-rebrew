typedef unsigned char u8;

void* __cdecl memset(void*, int, unsigned int);
int __cdecl fcn_004efd30(int);
int __cdecl fcn_004f08d0(char*);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_005373e0(int, unsigned int);
void __cdecl fcn_004f0e40(int, void*, void*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl sv_ClearObjectSelection(void);
void __cdecl ResetDisplayCounters(void);
void __cdecl fcn_00525ef0(void);
void* __cdecl fcn_004730c0(int, int, int, int, int, int, int);
void __cdecl fcn_00438da0(float, float, float, float, float, float, float, int, int);
void __cdecl fcn_005270c0(int);
void __cdecl fcn_004432d0(int, char);
void __cdecl fcn_00459710(char*, char);
void __cdecl fcn_00414960(float*, float*, char*);
void __cdecl fcn_00455350(char*, float*, float*);
char* __cdecl fcn_00442910(int, float*, float*, char*);
int __cdecl fcn_00412f10(char*, char*, int);
int __cdecl fcn_00476970(void*);
void __cdecl fcn_00473150(char*);
void __cdecl fcn_005893d0(int, int);
void __cdecl fcn_00588200(char*, char*, char*);
char __cdecl fcn_00442c00(char*, char);
char __cdecl fcn_00442d50(int, unsigned char);
void __cdecl fcn_00546bb0(int, int);
void __cdecl fcn_00587f40(char*);
void __cdecl fcn_005875c0(char*, float);
void __cdecl fcn_00587a50(char*);
void __cdecl fcn_00588000(char*);
void __cdecl fcn_00588710(int, int, int, int, int);
int __cdecl fcn_00587f90(char*);
int __cdecl fcn_00588aa0(void*, char*);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_0046b2b0(int);
char __cdecl d3_DestroyObject(int);
void __cdecl fcn_00533a40(char*);
void __cdecl fcn_00438b40(char*, int*);
void __cdecl fcn_00438cb0(char*, int*);
void __cdecl fcn_00516de0(int, int);
void __cdecl fcn_00443230(int);
void __cdecl fcn_00528fd0(void);

/* ADDRESS: GOLDTL 0x00586c10 */
void __cdecl fcn_00586c10(char* obj)
{
    int flags;
    int tbl;
    int count;
    int v[4];
    int a0;
    int a1;
    int a2;
    int g28;
    int s0;
    int s1;
    int s2;
    int s3;
    int p[4];
    int S[57];
    float f0[4];
    float f1[4];
    short idx[1024];
    char* res;
    char* sp;
    int id;
    int i;
    int j;
    int* g;
    float dt;

    flags = *(int*) 0x7e46ac;
    *(u8*) 0x14cf72f = 0;
    memset(S, 0, sizeof(S));
    flags |= 0x80;
    *(int*) ((char*) S + 0x68) = *(int*) 0x6b7fac;
    if (*(int*) (obj + 0x61) == 0)
        return;

    res = (char*) fcn_004efd30(*(int*) (obj + 1));
    if (res == 0) {
        id = fcn_004f08d0(obj);
        if (id != -1) {
            while (fcn_004c4450(id) == 0)
                fcn_005373e0(0, 0x20007);
        }
        res = (char*) fcn_004efd30(*(int*) (obj + 1));
        if (res == 0)
            return;
    }

    fcn_004f0e40(*(int*) (obj + 1), (void*) 0x586bd0, (void*) 0x77de60);
    flags = (flags & 0xffffdef7) | 0x10000;
    g = (int*) *(int*) 0x6b8014;
    p[0] = *(int*) ((char*) g + 0x4c);
    p[1] = *(int*) ((char*) g + 0x50);
    p[2] = *(int*) ((char*) g + 0x54);
    v[0] = *(int*) ((char*) g + 0x84);
    v[1] = *(int*) ((char*) g + 0x88);
    v[2] = *(int*) ((char*) g + 0x8c);
    s0 = *(int*) 0x1040480;
    s1 = *(int*) 0x1040484;
    s2 = *(int*) 0x1040488;
    s3 = *(int*) 0x104048c;
    g28 = *(int*) 0x6b8010;

    d2_SetOverlayAnimation(0, 0);
    sv_ClearObjectSelection();
    ResetDisplayCounters();
    fcn_00525ef0();
    sp = (char*) fcn_004730c0(0, 0, *(int*) 0x1040494, *(int*) 0x1040490, 0x67d67c, 0x5a, 1);
    *(int*) 0x7e2700 = 0;
    *(u8*) 0x100f8c0 = 0;
    while (!(*(u8*) sp & 4))
        fcn_005373e0(0, flags | 0x100);

    j = *(int*) 0x1015ea0;
    count = 0;
    for (tbl = 0x10382e0; tbl < 0x1040620; tbl += 0x2bc) {
        if (*(int*) (tbl - 0x10) == 0)
            continue;
        if (*(int*) tbl == 0)
            continue;
        for (i = 0, id = 0; i < 0xbd000; i += 0x2f4, id++) {
            if (*(int*) (j + i + 0x20) == 0)
                continue;
            if (*(int*) (j + i + 0x50) != tbl - 0x1a0)
                continue;
            if (*(int*) (j + i + 0x48) != 0)
                continue;
            *(int*) (j + i + 0x48) = 1;
            idx[count] = (short) id;
            count++;
            j = *(int*) 0x1015ea0;
        }
    }

    fcn_00438da0((float) *(int*) 0x1040494,
                 (float) *(int*) 0x1040490 - *(float*) 0x662d98,
                 0.0f, 75.0f,
                 *(float*) 0x10529c8, *(float*) 0x10421a0, *(float*) 0x10432a4,
                 *(int*) 0x1040494, *(int*) 0x1040490);
    i = 0;
    *(int*) 0x1040488 = 0;
    *(int*) 0x1040480 = *(int*) 0x1040494;
    *(int*) 0x1040484 = 0x4b;
    *(int*) 0x104048c = *(int*) 0x1040490 - 0x4b;
    fcn_005270c0(0);
    g = (int*) *(int*) 0x6b8014;
    p[0] = *(int*) ((char*) g + 0x4c);
    p[1] = *(int*) ((char*) g + 0x50);
    p[2] = *(int*) ((char*) g + 0x54);
    v[0] = *(int*) ((char*) g + 0x84);
    v[1] = *(int*) ((char*) g + 0x88);
    v[2] = *(int*) ((char*) g + 0x8c);
    fcn_004432d0(0, 0);
    if (*(int*) 0x6b89c0 != 0)
        fcn_00459710((char*) *(int*) 0x6b89c0, 1);

    fcn_00414960(f0, f1, (char*) *(int*) (obj + 0x61));
    if (*(int*) 0x9a9200 != *(int*) (obj + 1)) {
        *(int*) 0x9a9200 = *(int*) (obj + 1);
        *(int*) 0x9a9208 = v[0];
        *(int*) 0x9a920c = v[1];
        *(int*) 0x9a9210 = v[2];
        *(int*) 0x9a9214 = 0;
        *(int*) 0x9a9218 = 0;
        *(int*) 0x9a921c = 0;
    }

    fcn_00455350((char*) *(int*) (obj + 0x61), (float*) (obj + 0x4c), (float*) S);
    dt = f1[1] - f0[1];
    *(int*) ((char*) S + 0x10) = *(int*) 0x9a9208;
    *(int*) ((char*) S + 0x14) = *(int*) 0x9a920c;
    *(int*) ((char*) S + 0x18) = *(int*) 0x9a9210;
    dt = dt * *(float*) 0x662948 + *(float*) ((char*) S + 0x04);
    *(float*) ((char*) S + 0x04) = dt;
    a0 = 0;
    a1 = *(int*) 0x9a920c;
    a2 = *(int*) 0x9a9210;
    *(char**) ((char*) S + 0x98) = fcn_00442910(0, (float*) 0x662d70, (float*) &a0, (char*) 0x6a946c);
    *(char**) ((char*) S + 0x8c) = fcn_00442910((int) *(char**) ((char*) S + 0x98), (float*) 0x662d70, (float*) 0x662d80, (char*) 0x6a945c);
    *(char**) ((char*) S + 0x90) = fcn_00442910((int) *(char**) ((char*) S + 0x98), (float*) 0x662d70, (float*) 0x662d80, (char*) 0x6a9444);
    *(char**) ((char*) S + 0x94) = fcn_00442910((int) *(char**) ((char*) S + 0x98), (float*) 0x662d70, (float*) 0x662d80, (char*) 0x6a942c);
    fcn_00438b40(*(char**) ((char*) S + 0x98), (int*) S);
    fcn_00438cb0(*(char**) ((char*) S + 0x98), (int*) ((char*) S + 0x10));
    *(int*) ((char*) S + 0xa0) = *(int*) 0x9a921c;
    *(int*) ((char*) S + 0x20) = 0;
    *(char**) ((char*) S + 0x9c) = fcn_00442910((int) *(char**) ((char*) S + 0x98), (float*) 0x665f28, (float*) 0x662d80, (char*) 0x6a9418);
    fcn_00412f10(*(char**) ((char*) S + 0x9c), (char*) 0x6a93f8, 1);
    *(u8*) (*(char**) ((char*) S + 0x9c) + 0x216) = (u8) (((u8) (*(char**) ((char*) S + 0x9c))[0x216] & 0xfd) | 1);
    *(u8*) (*(char**) ((char*) S + 0x9c) + 0x216) |= 0x10;
    *(u8*) (*(char**) ((char*) S + 0x9c) + 0x214) &= 0x7f;
    fcn_00476970((void*) *(int*) 0x77250c);
    fcn_005373e0(0, 0x86);
    fcn_00476970((void*) *(int*) 0x77250c);
    fcn_00473150(0);

    sp = (char*) fcn_004730c0(0, 0, *(int*) 0x1040494, *(int*) 0x1040490, 0x67d67c, 0x5a, 0xa);
    fcn_005893d0((int) S, (int) res);
    fcn_00588200(obj, (char*) S, res);
    if (*(int*) (res + 4) > *(int*) ((char*) S + 0xdc))
        *(int*) ((char*) S + 0xa0) = *(int*) (res + 4);
    for (i = 0; i < 3; i++)
        fcn_00442c00(*(char**) ((char*) S + 0x8c + i * 4), 0);
    fcn_00442c00(*(char**) ((char*) S + 0x8c + *(int*) ((char*) S + 0xa0) * 4), 1);
    fcn_00442d50(*(int*) (obj + 0x61), 0);
    fcn_00546bb0(*(int*) (obj + 0x61), 0);
    i = -1;
    fcn_00587f40((char*) S);
    *(int*) 0x100f1dc = -1;
    *(int*) 0x77de10 = -1;
    *(int*) 0x77ddd8 = -1;
    *(int*) 0x77dda0 = -1;
    while (fcn_005373e0(0x586c10, 0x2656c7)) {
        fcn_005270c0(0);
        *(unsigned int*) ((char*) S + 0x6c) = *(unsigned int*) 0x6b7fac;
        a0 = *(int*) 0x6b7fac - *(int*) ((char*) S + 0x68);
        a1 = 0;
        dt = (float) (unsigned int) a0 * *(float*) 0x665f44;
        if (*(int*) (res + 4) == 0
            && (*(int*) 0x14ce8e0 != 0
                || (*(int*) 0x100f1dc != -1
                    && *(int*) 0x67d370 == *(int*) ((char*) S + 0xbc)))) {
            *(int*) 0x774654 = 1;
        } else {
            fcn_005875c0((char*) S, dt);
            fcn_00587a50((char*) S);
            fcn_00588200(obj, (char*) S, res);
            fcn_00588000((char*) S);
            if (*(int*) (res + 4) == 0) {
                if (*(int*) 0x100f1dc != -1) {
                    if (*(int*) 0x67d370 == *(int*) ((char*) S + 0xc8))
                        fcn_00588710((int) obj, (int) S, (int) res, 0, 0x2656c7);
                    else if (*(int*) 0x67d370 == *(int*) ((char*) S + 0xcc))
                        fcn_00588710((int) obj, (int) S, (int) res, 1, 0x2656c7);
                    else if (*(int*) 0x67d370 == *(int*) ((char*) S + 0xd0))
                        fcn_00588710((int) obj, (int) S, (int) res, 2, 0x2656c7);
                }
                if (*(int*) (res + 4) == 0 && fcn_00587f90((char*) S)) {
                    fcn_00588aa0(obj, (char*) S);
                    *(int*) 0x77de10 = -1;
                    *(int*) 0x77ddd8 = -1;
                    *(int*) 0x77dda0 = -1;
                }
            }
        }
        *(int*) ((char*) S + 0x68) = *(int*) ((char*) S + 0x6c);
    }

    fcn_00533a40((char*) 0x6b5c60);
    sp = (char*) fcn_004730c0(0, 0, *(int*) 0x1040494, *(int*) 0x1040490, 0x67d67c, 0x5a, 1);
    while (!(*(u8*) sp & 4))
        fcn_005373e0(0, flags);
    fcn_00471e30(*(int*) ((char*) S + 0xa4));
    fcn_00471e30(*(int*) ((char*) S + 0xc0));
    fcn_00471e30(*(int*) ((char*) S + 0x74));
    fcn_0046b2b0(*(int*) ((char*) S + 0xd4));
    fcn_0046b2b0(*(int*) ((char*) S + 0xd8));
    if (*(int*) ((char*) S + 0x8c) != 0)
        d3_DestroyObject(*(int*) ((char*) S + 0x8c));
    if (*(int*) ((char*) S + 0x90) != 0)
        d3_DestroyObject(*(int*) ((char*) S + 0x90));
    if (*(int*) ((char*) S + 0x94) != 0)
        d3_DestroyObject(*(int*) ((char*) S + 0x94));
    if (*(int*) ((char*) S + 0x9c) != 0)
        d3_DestroyObject(*(int*) ((char*) S + 0x9c));
    if (*(int*) ((char*) S + 0x98) != 0)
        d3_DestroyObject(*(int*) ((char*) S + 0x98));
    fcn_00442d50(*(int*) (obj + 0x61), 1);
    fcn_00546bb0(*(int*) (obj + 0x61), 1);
    for (i = 0; i < count; i++)
        *(int*) (*(int*) 0x1015ea0 + idx[i] * 0x2f4 + 0x48) = 0;
    fcn_00438da0((float) (*(int*) 0x6a376c - *(int*) 0x6a3764),
                 (float) (*(int*) 0x6a3770 - *(int*) 0x6a3768),
                 (float) *(int*) 0x6a3764, (float) *(int*) 0x6a3768,
                 *(float*) 0x10529c8, *(float*) 0x10421a0, *(float*) 0x10432a4,
                 *(int*) 0x1040494, *(int*) 0x1040490);
    *(int*) 0x1040488 = s2;
    *(int*) 0x1040480 = s0;
    *(int*) 0x1040484 = s1;
    *(int*) 0x104048c = s3;
    fcn_005270c0(1);
    fcn_00528fd0();
    fcn_004432d0(g28, 0);
    if (*(int*) 0x6b89c0 != 0)
        fcn_00459710((char*) *(int*) 0x6b89c0, 1);
    g = (int*) *(int*) 0x6b8014;
    fcn_00438b40((char*) g, p);
    fcn_00438cb0((char*) g, v);
    fcn_00516de0(*(int*) 0x6b8300, 0);
    fcn_00443230(1);
    fcn_00473150(sp);
    fcn_004730c0(0, 0, *(int*) 0x1040494, *(int*) 0x1040490, 0x67d67c, 0x5a, 0xa);
    fcn_004f0e40(*(int*) (obj + 1), 0, 0);
}
