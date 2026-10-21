extern void __cdecl fcn_004727a0(int, int);
extern int __cdecl fcn_0046f740(int, int, int, int);
extern void __cdecl d2_SetElementImage(int, int);
extern void __cdecl fcn_00469c40(int, int, int);
extern void __cdecl fcn_00596d70(int, int, int *, int, int, int);
extern void __cdecl ResetDisplayCounters(void);
extern int __cdecl fcn_00471f80(int);
extern void __cdecl fcn_00473750(int, int);

/* ADDRESS: GOLDTL 0x00597940 */
void __cdecl fcn_00597940(int a0, int a1, int a2, int a3, short *a4)
{
    int *r;
    int v1;
    int *p;
    int n;
    int i;
    int col;
    int v9;

    r = (int *)(*(int *)((a1 + a0 * 0xaf) * 4 + 0x1038144) * 0x3cc + 0x1015f40);
    v1 = r[3];
    fcn_004727a0(a0, a1);

    p = (int *)0x778d50;
    do {
        if (*p == -1)
            *p = fcn_0046f740(0, 0, 0x743, *(int *)0x772514);
        p += 5;
    } while ((int)p < 0x778da0);

    /* col carries the lane 0x778d4c address for the loop bound only */
    i = 0;
    p = (int *)0x778d50;
    n = *(int *)0x772500;
    col = (int)(p - 1);
    do {
        if (p[-2] != p[-1]) {
            d2_SetElementImage(p[0], p[-1] + 0x741);
            n = *(int *)0x772500;
        }
        v9 = p[-1];
        p[-2] = v9;
        if (v9 >= 2) {
            p[-4] = (v1 - *(short *)(n + 0x261a4 + v9 * 0x54)) >> 1;
            p[-3] = (*(short *)(n + 0x2624e) + 0x23) * i;
        }
        p += 5;
        i += 1;
        col += 0x14;
    } while (col < 0x778d9c);

    fcn_004727a0(a0, a1);

    p = (int *)0x778d50;
    do {
        if (p[-2] >= 2) {
            *(int *)(*(int *)0x1015ea0 + p[0] * 0x2f4 + 0x48) = 0;
            fcn_00469c40(r[1] + p[-4], r[2] + p[-3], *p);
        } else {
            *(int *)(*(int *)0x1015ea0 + p[0] * 0x2f4 + 0x48) = 1;
        }
        p += 5;
    } while ((int)p < 0x778da0);

    col = 0;
    i = 0;
    p = (int *)0x778da0;
    do {
        col += 1;
        if (col > *(int *)(i * 0x14 + 0x778d48)) {
            col = 1;
            do {
                i += 1;
            } while (*(int *)(i * 0x14 + 0x778d48) < 1);
        }
        p[2] = *(int *)(i * 0x14 + 0x778d40) - 0x44 + col * 0x44;
        p[3] = *(int *)(i * 0x14 + 0x778d44);
        if (*a4 == 0x1db)
            fcn_00596d70(a0, a1, p, a2, 1, a3);
        else if (*a4 == 0x1dc)
            fcn_00596d70(a0, a1, p, a2, 2, a3);
        else
            fcn_00596d70(a0, a1, p, a2, 3, a3);
        p = (int *)((char *)p + 0x38);
    } while ((int)p < 0x779120);

    if (!a2)
        return;
    ResetDisplayCounters();

    p = (int *)0x778db0;
    do {
        if (*p != -1) {
            v9 = fcn_00471f80(*p);
            fcn_00473750(p[-4] + 0xdf, v9);
        }
        p += 0xe;
    } while ((int)p < 0x779130);

    p = (int *)0x7796f0;
    do {
        if (*p != -1) {
            v9 = fcn_00471f80(*p);
            fcn_00473750(p[-4] + 0xdf, v9);
        }
        p += 0xe;
    } while ((int)p < 0x7798b0);
}
