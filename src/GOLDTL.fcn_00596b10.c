extern char* g_1015ea0; /* 0x1015ea0, GUI pool, stride 0x2f4 */

int __cdecl fcn_004727a0(int k, int i);
int __cdecl fcn_0046f740(int x, int y, int id, int win);
void __cdecl d2_SetElementImage(int element, int bild);
int __cdecl fcn_00469c40(int x, int y, int a3);
void __cdecl fcn_00596d70(int a0, int a1, int* rect, int w, int n,
                          unsigned int a5);
void __cdecl ResetDisplayCounters(void);
int __cdecl fcn_00471f80(int element);
void __cdecl fcn_00473750(int a1, int a2);

/* ADDRESS: GOLDTL 0x00596b10 */
void __cdecl fcn_00596b10(int a0, int a1, int a2, unsigned int a3)
{
    int* r;
    int v1;
    int* p;
    int n;
    int i;
    int col;
    int v9;

    r = (int*) (*(int*) ((a1 + a0 * 0xaf) * 4 + 0x1038144) * 0x3cc + 0x1015f40);
    v1 = r[3];
    fcn_004727a0(a0, a1);

    p = (int*) 0x778d50;
    do {
        if (*p == -1) {
            *p = fcn_0046f740(0, 0, 0x743, *(int*) 0x772514);
        }
        p += 5;
    } while ((int) p < 0x778da0);

    i = 0;
    p = (int*) 0x778d50;
    n = *(int*) 0x772500;
    /* col carries the 0x778d4c lane address; it is the loop's induction base */
    col = (int) (p - 1);
    do {
        if (p[-2] != p[-1]) {
            d2_SetElementImage(p[0], p[-1] + 0x741);
            n = *(int*) 0x772500;
        }
        v9 = p[-1];
        p[-2] = v9;
        if (v9 >= 2) {
            p[-4] = (v1 - *(short*) (n + 0x261a4 + v9 * 0x54)) >> 1;
            p[-3] = (*(short*) (n + 0x2624e) + 0x1c) * i;
        }
        p += 5;
        i += 1;
        col += 0x14;
    } while (col < 0x778d9c);

    fcn_004727a0(a0, a1);

    p = (int*) 0x778d50;
    do {
        if (p[-2] >= 2) {
            *(unsigned int*) (g_1015ea0 + p[0] * 0x2f4 + 0x48) = 0;
            fcn_00469c40(r[1] + p[-4], r[2] + p[-3], *p);
        } else {
            *(unsigned int*) (g_1015ea0 + p[0] * 0x2f4 + 0x48) = 1;
        }
        p += 5;
    } while ((int) p < 0x778da0);

    col = 0;
    i = 0;
    p = (int*) 0x778da0;
    /* n carries the 0x778dac lane address, the second loop's induction base */
    n = (int) (p + 3);
    do {
        col += 1;
        if (col > *(int*) (i * 0x14 + 0x778d48)) {
            col = 1;
            do {
                i += 1;
            } while (*(int*) (i * 0x14 + 0x778d48) < 1);
        }
        p[2] = *(int*) (i * 0x14 + 0x778d40) - 0x44 + col * 0x44;
        p[3] = *(int*) (i * 0x14 + 0x778d44);
        fcn_00596d70(a0, a1, p, a2, 3, a3);
        p += 0xe;
        n += 0x38;
    } while (n < 0x77912c);

    if (!a2) {
        return;
    }
    ResetDisplayCounters();

    p = (int*) 0x778db0;
    do {
        if (*p != -1) {
            v9 = fcn_00471f80(*p);
            fcn_00473750(p[-4] + 0xdf, v9);
        }
        p += 0xe;
    } while ((int) p < 0x779130);

    p = (int*) 0x7796f0;
    do {
        if (*p != -1) {
            v9 = fcn_00471f80(*p);
            fcn_00473750(p[-4] + 0xdf, v9);
        }
        p += 0xe;
    } while ((int) p < 0x7798b0);
}
