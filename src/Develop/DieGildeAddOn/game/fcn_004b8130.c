#include <string.h>

extern unsigned short* __cdecl fcn_00508e40(int id);
extern int __cdecl gm_MapEntityStatRange(int type);
extern int __cdecl fcn_005c6270(unsigned short* rec, int mode);
extern int __cdecl gm_RandomMod(int range);
extern void __cdecl fcn_004c54c0(int a, int b, int c, int d);
extern int __cdecl gm_WalkEntityChain(int v);
extern void __cdecl fcn_004c51a0(int a, int b, int c, int d);
extern void __cdecl fcn_0051af00(char* buf, int a, int b, int c);
extern void __cdecl fcn_00545d40(int a, int b, char* buf, int c, int d, int e);

/* ADDRESS: GOLDTL 0x004b8130 */
int __cdecl fcn_004b8130(int* arg)
{
    char buf[0x400];
    unsigned char* rec;
    int i;
    int key;
    int n;
    int mode;
    int v;
    int t;
    double d;
    int r;

    rec = (unsigned char*) fcn_00508e40(arg[0]);
    if (rec == 0) {
        return 1;
    }
    if (rec[0x169] < 0x1e || rec[0x169] > 0x21) {
        return 0x400;
    }
    key = gm_MapEntityStatRange(rec[0x164]);
    if (key == 0) {
        return 0x400;
    }
    if (fcn_005c6270((unsigned short*) rec, 0x290) != 0) {
        return 0x400;
    }
    for (i = 0x7f4ca2; i < 0x85a0a2; i += 0x21c) {
        if (*(char*) i == 6 || *(char*) i == 7) {
            continue;
        }
        if (key != gm_MapEntityStatRange(*(unsigned char*) (i + 0x162))) {
            continue;
        }
        n = (gm_RandomMod(8) & 0xffff) + 1;
        fcn_004c54c0(*(int*) (rec + 4), *(int*) (i + 2), n, 1);
    }
    t = gm_RandomMod(4) & 0xffff;
    d = (double) t + *(double*) 0x6629c8;
    v = gm_WalkEntityChain(*(unsigned short*) rec);
    r = (int) ((double) v * d * *(double*) 0x6640e8);
    fcn_004c51a0(-1, arg[0], *(unsigned char*) 0x773d75, r);
    if (rec[0x169] == 0x1e) {
        mode = 0;
    } else if (rec[0x169] == 0x1f) {
        mode = 1;
    } else if (rec[0x169] == 0x20) {
        mode = 2;
    } else if (rec[0x169] == 0x21) {
        mode = 3;
    } else {
        return 0x400;
    }
    fcn_0051af00(buf, *(unsigned short*) ((char*) arg + 4) + 0x12e7,
                 mode + 0x2a3, r);
    fcn_00545d40(*(int*) (rec + 4), *(int*) (rec + 4), buf,
                 strlen(buf) > 0x100, 0x603, 0);
    return 0;
}
