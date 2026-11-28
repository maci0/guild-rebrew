#include <math.h>
#include <stdlib.h>
extern float d3_GammaContrast[3];
extern float d3_GammaExponent[3];
extern float d3_GammaBrightness[3];
/* 1/255 is written as a float literal below. */
#include "Develop/Units/d8_vesa/d3d_device_view.h"

/* ADDRESS: GOLDTL 0x0041b870 */
int __cdecl d3_ApplyGammaRamp(void)
{
    unsigned short table[3][256];
    int i;
    float m;
    double lo, mid, hi, st;
    D3D_DEVICE_VIEW *obj;

    lo = 1.0 / d3_GammaExponent[0];
    mid = 1.0 / d3_GammaExponent[1];
    hi = 1.0 / d3_GammaExponent[2];

    for (i = 0; i < 0x100; i++) {
        m = i * 0.0039215689f;

        st = __min(1.0, __max(0.0,
            pow(d3_GammaContrast[0] * m, hi) + d3_GammaBrightness[0]));



        table[2][i] = (unsigned short)(st * 65535.0);

        st = __min(1.0, __max(0.0,
            pow(d3_GammaContrast[1] * m, mid) + d3_GammaBrightness[1]));



        table[1][i] = (unsigned short)(st * 65535.0);

        st = __min(1.0, __max(0.0,
            pow(d3_GammaContrast[2] * m, lo) + d3_GammaBrightness[2]));



        table[0][i] = (unsigned short)(st * 65535.0);
    }

    obj = (D3D_DEVICE_VIEW*)g_6b5de0;
    return ((int (__stdcall *)(void *, int, void *))
        obj->vtbl->unk_00[0x12])(obj, 0, table);
}
