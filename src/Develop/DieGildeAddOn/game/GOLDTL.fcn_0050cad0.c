#include "client_types.h"

extern float g_665bf8; /* 1020.0 */
extern float g_665bfc; /* 1380.0 */
extern float g_665c00; /* 360.0 */

int __cdecl fcn_00500cb0(int* a, int* b);
int __cdecl sim_SetSyncParams(int* a, int mode, int b, int c);

/* ADDRESS: GOLDTL 0x0050cad0 */
int __cdecl fcn_0050cad0(int* a, int* b)
{
    pos14_7f4c00 cur;
    int v3;
    int v4;
    int v5;
    int v6;
    int v7;
    float f;

    if (fcn_00500cb0(a, b) >= 1) {
        return 0;
    }
    cur = *(pos14_7f4c00*) a;
    v3 = cur.a;
    v7 = b[0];
    v4 = 0;
    if (v7 > v3) {
        f = (float) (*(unsigned short*) ((char*) &cur + 4) * 60 + *(int*) ((char*) &cur + 6));
        f = (g_665c00 > f || f < g_665bfc) ? (g_665c00 > f ? g_665c00 : f) : g_665bfc;
        v5 = (int) f;
        v4 = (int) (g_665bfc - (float) v5);
        cur.a = v3 + 1;
        sim_SetSyncParams((int*) &cur, 6, 0, 0);
        v3 = cur.a;
    }
    if (v3 < v7) {
        v7 -= v3;
        do {
            f = (float) v4 + g_665bf8;
            v4 = (int) f;
        } while (--v7);
    }
    f = (float) (*(unsigned short*) ((char*) b + 4) * 60 + *(int*) ((char*) b + 6));
    f = (g_665c00 > f || f < g_665bfc) ? (g_665c00 > f ? g_665c00 : f) : g_665bfc;
    v5 = (int) f;
    f = (float) (*(unsigned short*) ((char*) &cur + 4) * 60 + *(int*) ((char*) &cur + 6));
    f = (g_665c00 > f || f < g_665bfc) ? (g_665c00 > f ? g_665c00 : f) : g_665bfc;
    v6 = (int) f;
    return (v4 - v6) + v5;
}
