#include <math.h>
#include <stdlib.h>
extern float g_6777b0[3];
extern float g_6777bc[3];
extern float g_6b5df8[3];
extern float g_662c30;
extern void* g_6b5de0;

/* ADDRESS: GOLDTL 0x0041b870 */
int __cdecl fcn_0041b870(void)
{
    unsigned short table[3][256];
    int i;
    float m;
    double lo, mid, hi, st;
    void **obj, **vt;
    int (__stdcall *mth)(void *, int, void *);

    lo = 1.0 / g_6777bc[0];
    mid = 1.0 / g_6777bc[1];
    hi = 1.0 / g_6777bc[2];

    for (i = 0; i < 0x100; i++) {
        m = (float)((double)i * g_662c30);

        st = pow(g_6777b0[0] * m, hi) + g_6b5df8[0];
        st = __min(1.0, __max(0.0, st));



        table[2][i] = (unsigned short)(st * 65535.0);

        st = pow(g_6777b0[1] * m, mid) + g_6b5df8[1];
        st = __min(1.0, __max(0.0, st));



        table[1][i] = (unsigned short)(st * 65535.0);

        st = pow(g_6777b0[2] * m, lo) + g_6b5df8[2];
        st = __min(1.0, __max(0.0, st));



        table[0][i] = (unsigned short)(st * 65535.0);
    }

    obj = (void**)g_6b5de0;
    vt = *(void ***)obj;
    mth = (int (__stdcall *)(void *, int, void *))vt[0x12];
    return mth(obj, 0, table);
}
