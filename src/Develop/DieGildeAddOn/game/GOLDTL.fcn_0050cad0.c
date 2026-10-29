extern float g_665bf8; /* 1020.0 */
extern float g_665bfc; /* 1380.0 */
extern float g_665c00; /* 360.0 */

int __cdecl fcn_00500cb0(int* a, int* b);
int __cdecl sim_SetSyncParams(int* a, int mode, int b, int c);

/* ADDRESS: GOLDTL 0x0050cad0 */
int __cdecl fcn_0050cad0(int* a, int* b)
{
    int v3;
    int v4;
    int v5;
    int v6;
    int v7;
    int v9;
    int v10;
    float f;

    if (fcn_00500cb0(a, b) >= 1) {
        return 0;
    }
    v3 = a[0];
    v6 = a[1];
    v7 = b[0];
    v9 = v6 & 0xffff;
    v10 = (v6 >> 16) & 0xffff;
    v4 = 0;
    if (v7 > v3) {
        f = (float) (v10 + v9 * 0x3c);
        if (f < g_665c00) {
            f = g_665c00;
        } else if (f > g_665bfc) {
            f = g_665bfc;
        }
        v4 = (int) f;
        v5 = (int) (g_665bfc - (float) v4);
        v5 = v3 + 1;
        sim_SetSyncParams(&v5, 6, 0, 0);
        v3 = v5;
    }
    if (v3 < v7) {
        v7 -= v3;
        do {
            f = (float) v4 + g_665bf8;
            v4 = (int) f;
        } while (--v7);
    }
    f = (float) ((a[1] >> 16) + (a[1] & 0xffff) * 0x3c);
    if (f < g_665c00) {
        f = g_665c00;
    } else if (f > g_665bfc) {
        f = g_665bfc;
    }
    v5 = (int) f;
    f = (float) v4;
    if (f < g_665c00) {
        f = g_665c00;
    } else if (f > g_665bfc) {
        f = g_665bfc;
    }
    v6 = (int) f;
    return (v5 - v6) + v4;
}
