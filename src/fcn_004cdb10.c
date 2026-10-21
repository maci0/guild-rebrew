int __cdecl fcn_0064d3f8(void);
int __cdecl srv_SeedRandom(int);
int __cdecl ahm_ExAllocAlchemist(int *);

/* ADDRESS: GOLDTL 0x004cdb10 */
int __cdecl fcn_004cdb10(int *p, unsigned char *out)
{
    int v;

    if (out) {
        out[0] = 2;
        out[1] = 0;
        *(int *)(out + 6) = 0;
    }
    if (*(int *)0x14cbca0 != -1) {
        *(int *)0x699364 = p[5];
    } else {
        p[4] = fcn_0064d3f8();
    }
    srv_SeedRandom(p[4]);
    v = ahm_ExAllocAlchemist(&p[4]);
    if (v == 0xffff) return -1;
    if (out) {
        out[0] = 1;
        out[1] = 1;
        *(int *)(out + 6) = 540 * v + 0x7f4ca0;
    }
    return 0;
}
