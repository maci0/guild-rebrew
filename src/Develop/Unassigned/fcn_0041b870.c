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
    void **obj;

    lo = 1.0 / g_6777bc[0];
    mid = 1.0 / g_6777bc[1];
    hi = 1.0 / g_6777bc[2];

    for (i = 0; i < 0x100; i++) {
        m = i * g_662c30;

        st = __min(1.0, __max(0.0,
            pow(g_6777b0[0] * m, hi) + g_6b5df8[0]));



        table[2][i] = (unsigned short)(st * 65535.0);

        st = __min(1.0, __max(0.0,
            pow(g_6777b0[1] * m, mid) + g_6b5df8[1]));



        table[1][i] = (unsigned short)(st * 65535.0);

        st = __min(1.0, __max(0.0,
            pow(g_6777b0[2] * m, lo) + g_6b5df8[2]));



        table[0][i] = (unsigned short)(st * 65535.0);
    }

    obj = (void**)g_6b5de0;
    return ((int (__stdcall *)(void *, int, void *))
        (*(void ***)obj)[0x12])(obj, 0, table);
}
