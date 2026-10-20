extern char* g_1015ea0; /* 0x1015ea0, GUI pool, stride 0x2f4 */

int __cdecl fcn_004727a0(int k, int i);
int __cdecl fcn_0046f740(int x, int y, int id, int win);
void __cdecl d2_SetElementImage(int element, int bild);
void __cdecl fcn_00469c30(int x, int y, int element);
void __cdecl fcn_00596d70(int a0, int a1, int* rect, int w, int n,
                          unsigned int a5);
void __cdecl ResetDisplayCounters(void);
int __cdecl fcn_00471f80(int element);
void __cdecl fcn_00473750(int a1, int a2);

/* ADDRESS: GOLDTL 0x00596b10 */
void __cdecl fcn_00596b10(int a0, int a1, int a2, unsigned int a3)
{
    int v1;
    int v2;
    int v3;
    int v4;
    int v5;
    int v6;
    int v9;
    int v10;
    int* v7;
    unsigned int* v8;

    v4 = a1;
    v10 = a0;
    v6 = *(int*) ((a1 + a0 * 0xaf) * 4 + 0x1038144) * 0x3cc;
    v1 = *(int*) ((char*) 0x1015f40 + v6 + 0x0c);
    fcn_004727a0(a0, a1);

    v7 = (int*) 0x778d50;
    do {
        if (*v7 == -1) {
            v3 = fcn_0046f740(0, 0, 0x743, *(int*) 0x772514);
            *v7 = v3;
        }
        v7 += 5;
    } while ((int) v7 < 0x778da0);

    v9 = 0;
    v7 = (int*) 0x778d4c;
    v3 = *(int*) 0x772500;
    do {
        if (v7[-1] != *v7) {
            d2_SetElementImage(v7[1], *v7 + 0x741);
            v3 = *(int*) 0x772500;
        }
        v2 = *v7;
        v7[-1] = v2;
        if (v2 >= 2) {
            v7[-3] = (v1 - *(short*) (v3 + 0x261a4 + v2 * 0x54)) >> 1;
            v7[-2] = (*(short*) (v3 + 0x2624e) + 0x1c) * v9;
        }
        v7 += 5;
        v9 += 1;
    } while ((int) v7 < 0x778d9c);

    fcn_004727a0(v10, v4);

    v7 = (int*) 0x778d50;
    do {
        if (v7[-2] >= 2) {
            *(unsigned int*) (g_1015ea0 + 0x48 + *v7 * 0x2f4) = 0;
            fcn_00469c30(*(int*) ((char*) 0x1015f40 + v6 + 4),
                         *(int*) ((char*) 0x1015f40 + v6 + 8) + v7[-3],
                         *v7);
        } else {
            *(unsigned int*) (g_1015ea0 + 0x48 + *v7 * 0x2f4) = 1;
        }
        v7 += 5;
    } while ((int) v7 < 0x778da0);

    v6 = 0;
    v10 = 0;
    v8 = (unsigned int*) 0x778dac;
    do {
        v6 += 1;
        v4 = v10 * 0x14 + 0x778d48;
        if (*(int*) (v10 * 0x14 + 0x778d48) < v6) {
            v6 = 1;
            do {
                v7 = (int*) (v4 + 0x14);
                v4 += 0x14;
                v10 += 1;
            } while (*v7 < 1);
        }
        v5 = *(unsigned int*) (v10 * 0x14 + 0x778d44);
        v8[-1] = *(int*) (v10 * 0x14 + 0x778d40) - 0x44 + v6 * 0x44;
        *v8 = v5;
        fcn_00596d70(a0, a1, (int*) &v8[-3], v1, 3, a3);
        v8 += 0xe;
    } while ((int) v8 < 0x77912c);

    if (!v1) {
        return;
    }
    ResetDisplayCounters();

    v7 = (int*) 0x778db0;
    do {
        if (*v7 != -1) {
            v5 = fcn_00471f80(*v7);
            fcn_00473750(v7[-4] + 0xdf, v5);
        }
        v7 += 0xe;
    } while ((int) v7 < 0x779130);

    v7 = (int*) 0x7796f0;
    do {
        if (*v7 != -1) {
            v5 = fcn_00471f80(*v7);
            fcn_00473750(v7[-4] + 0xdf, v5);
        }
        v7 += 0xe;
    } while ((int) v7 < 0x7798b0);
}
