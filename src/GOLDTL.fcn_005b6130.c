extern char* g_1015ea0; /* 0x1015ea0, GUI pool, stride 0x2f4 */
extern char* g_773d78;   /* 0x773d78 */
extern int g_67d370;     /* 0x67d370 */
extern int g_100f1dc;    /* 0x100f1dc */
extern int g_14abc14;    /* 0x14abc14 */

int __cdecl fcn_0046f740(int x, int y, int id, int win);
void __cdecl fcn_0046f940(int element, char* text);
void __cdecl fcn_0046f9b0(int element, int a2);
void __cdecl fcn_00472900(int element, int a2);
char* __cdecl fcn_00503fe0(int a1, int a2, int a3);
char* __cdecl fcn_0050d570(int entity);
void __cdecl fcn_0051af00(char* buf, char* fmt, ...);
void __cdecl fcn_00526920(char* text, int a2, int a3);

/* ADDRESS: GOLDTL 0x005b6130 */
void __cdecl fcn_005b6130(int a0, char* a1)
{
    char v5[512];
    int v1;
    char* v2;
    int v3;
    int v4;
    unsigned int v8;
    int* v6;
    int v7;

    v4 = 0;
    if (*(int*) 0x777cc0 > 0) {
        v7 = 0x5a;
        do {
            v3 = *(int*) (v4 * 4 + 0x777cc4);
            v1 = *(int*) (v3 + 0x24);
            if (v1) {
                v2 = fcn_00503fe0(1, 1, *(unsigned int*) (v1 + 0xb4));
                if (v2) {
                    v8 = 0x1a3e;
                    fcn_0051af00(v5, (char*) v8, v2);
                }
            } else {
                v2 = fcn_0050d570(v3);
                if (*v2 == 'D') {
                    v2 = g_773d78;
                }
                v8 = 0x1a3f;
                fcn_0051af00(v5, (char*) v8, v2);
            }
            v3 = *(int*) (v4 * 4 + 0x777cdc);
            if (v3 != -1) {
                fcn_0046f940(v3, v5);
                if (a1 != v2 &&
                    *(int*) (v4 * 4 + 0x777cd0) == -1) {
                    v3 = fcn_0046f740(0, v7, 5, *(int*) 0x772514);
                    *(int*) (v4 * 4 + 0x777cd0) = v3;
                    *(unsigned int*) (g_1015ea0 + 0x5c + v3 * 0x2f4) = 1;
                    *(char**) (g_1015ea0 + 0x2f0 +
                               *(int*) (v4 * 4 + 0x777cd0) * 0x2f4) = v2;
                    fcn_00472900(*(unsigned int*) (v4 * 4 + 0x777cd0),
                                 0x56);
                    *(unsigned int*) (g_1015ea0 + 0x1d0 +
                                      *(int*) (v4 * 4 + 0x777cd0) * 0x2f4) = 3;
                }
                v3 = *(int*) (v4 * 4 + 0x777cd0);
                if (v3 != -1) {
                    fcn_0046f9b0(v3, g_14abc14);
                }
            }
            v4 += 1;
            v7 += 0x78;
        } while (v4 < *(int*) 0x777cc0);
    }

    if (*(char*) (a0 + 0x270) == 2 && g_100f1dc == 5) {
        v6 = (int*) 0x777cd0;
        do {
            v4 = *v6;
            if (v4 != -1 && g_67d370 == v4) {
                fcn_00526920(*(char**) (g_1015ea0 + 0x2f0 +
                                        v4 * 0x2f4),
                             -1, 0x6b5c60);
            }
            v6 += 1;
        } while ((int) v6 < 0x777cdc);
    }
}
