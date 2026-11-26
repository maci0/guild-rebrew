#include "client_types.h"

extern float g_665bf8; /* 1020.0 */
extern float g_665bfc; /* 1380.0 */
extern float g_665c00; /* 360.0 */

int __cdecl gm_CompareGameTime(int* a, int* b);
int __cdecl sim_SetSyncParams(int* a, int mode, int b, int c);

/* ADDRESS: GOLDTL 0x0050cad0 */
int __cdecl fcn_0050cad0(int* a, int* b)
{
    pos14_7f4c00 cur;
    int v3;
    int minutes;
    int v5;
    int v6;
    int v7;
    float f;
    if (gm_CompareGameTime(a, b) > 0) {
        return 0;
    }
    cur = *(pos14_7f4c00*) a;
    v3 = cur.a;
    v7 = b[0];
    if (v3 < v7) {
        f = (float) (*(unsigned short*) ((char*) &cur + 4) * 60 + *(int*) ((char*) &cur + 6));
        if (g_665c00 > f) goto clamp1;
        if (f < g_665bfc) {
        clamp1:
            f = (g_665c00 > f ? g_665c00 : f);
        } else {
            f = g_665bfc;
        }
        v5 = (int) f;
        minutes = (int) (g_665bfc - (float) v5);
        cur.a = v3 + 1;
        sim_SetSyncParams((int*) &cur, 6, 0, 0);
        v3 = cur.a;
    } else {
        minutes = 0;
    }
    if (v3 < v7) {
        v7 -= v3;
        do {
            f = (float) minutes + g_665bf8;
            minutes = (int) f;
        } while (--v7);
    }
    f = (float) (*(unsigned short*) ((char*) b + 4) * 60 + *(int*) ((char*) b + 6));
    if (g_665c00 > f) goto clamp2;
    if (f < g_665bfc) {
    clamp2:
        f = (g_665c00 > f ? g_665c00 : f);
    } else {
        f = g_665bfc;
    }
    v5 = (int) f;
    f = (float) (*(unsigned short*) ((char*) &cur + 4) * 60 + *(int*) ((char*) &cur + 6));
    if (g_665c00 > f) goto clamp3;
    if (f < g_665bfc) {
    clamp3:
        f = (g_665c00 > f ? g_665c00 : f);
    } else {
        f = g_665bfc;
    }
    v6 = (int) f;
    return (minutes - v6) + v5;
}
