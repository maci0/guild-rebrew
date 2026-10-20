extern void __cdecl fcn_004727a0(int, int);
extern int __cdecl fcn_0046f740(int, int, int, int);
extern void __cdecl fcn_00466330(int, int);
extern void __cdecl fcn_00469c40(int, int, int);
extern void __cdecl fcn_00596d70(int, int, int *, int, int, int);
extern void __cdecl fcn_004737c0(void);
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
    } while (p < (int *)0x778da0);
    i = 0;
    p = (int *)0x778d4c;
    do {
        if (p[-1] != *p) {
            fcn_00466330(p[1], *p + 0x741);
        }
        n = *p;
        p[-1] = n;
        if (n >= 2) {
            p[-3] = (v1 - *(short *)(*(int *)0x772500 + 0x261a4 + n * 0x54)) >> 1;
            p[-2] = (*(short *)(*(int *)0x772500 + 0x2624e) + 0x23) * i;
        }
        p += 5;
        i++;
    } while (p < (int *)0x778d9c);
    fcn_004727a0(a0, a1);
    p = (int *)0x778d50;
    do {
        if (p[-2] >= 2) {
            *(int *)(*(int *)0x1015ea0 + p[0] * 0x2f4 + 0x48) = 0;
            fcn_00469c40(p[-4] + r[1], r[2] + p[-3], p[0]);
        } else {
            *(int *)(*(int *)0x1015ea0 + p[0] * 0x2f4 + 0x48) = 1;
        }
        p += 5;
    } while (p < (int *)0x778da0);
    col = 0;
    i = 0;
    p = (int *)0x778da0;
    do {
        col++;
        n = i * 0x14 + 0x778d48;
        if (*(int *)n < col) {
            col = 1;
            do {
                n += 0x14;
                i++;
            } while (*(int *)n < 1);
        }
        p[2] = *(int *)(i * 0x14 + 0x778d40) - 0x44 + col * 0x44;
        p[3] = *(int *)(i * 0x14 + 0x778d44);
        if (*a4 == 0x1db)
            v9 = 1;
        else if (*a4 == 0x1dc)
            v9 = 2;
        else
            v9 = 3;
        fcn_00596d70(a0, a1, p, a2, v9, a3);
        p = (int *)((char *)p + 0x38);
    } while (p < (int *)0x779120);
    if (!a2)
        return;
    fcn_004737c0();
    p = (int *)0x778db0;
    do {
        if (*p != -1) {
            v9 = fcn_00471f80(*p);
            fcn_00473750(p[-4] + 0xdf, v9);
        }
        p += 0xe;
    } while (p < (int *)0x779130);
    p = (int *)0x7796f0;
    do {
        if (*p != -1) {
            v9 = fcn_00471f80(*p);
            fcn_00473750(p[-4] + 0xdf, v9);
        }
        p += 0xe;
    } while (p < (int *)0x7798b0);
}
