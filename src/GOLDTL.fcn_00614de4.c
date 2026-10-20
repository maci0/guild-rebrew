/* Rebuilds `out` from the direction `in`; `mode` selects the projection and
 * `flag` selects the sign variant.  Pure x87, no callees.
 *
 * The native body has an EBP frame but no local slot, so the recovered
 * formulas are the ones below; this build still materialises the shared
 * factor in a stack temp, which leaves the frame and the x87 stack
 * scheduling different (SIZE 173 native, 200 compiled). */
#include <math.h>

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x00614de4 */
void __cdecl fcn_00614de4(float *out, float *in, int mode, int flag)
{
    float t;

    switch (mode) {
    case 2:
        t = (float)sqrt(0.5f * in[2] + 0.5f);
        out[2] = t;
        t = 0.5f / t;
        out[0] = t * in[0];
        out[1] = t * in[1];
        break;
    case 3:
        out[0] = in[0];
        out[1] = in[1];
        if (flag != 0) {
            out[2] = -in[2];
        } else {
            out[2] = in[2];
        }
        break;
    case 4:
        if (flag == 0) {
            t = 0.5f / (0.5f * (in[2] + 1.0f));
            out[0] = t * in[0];
            out[1] = t * in[1];
            out[2] = in[2];
        } else {
            t = 0.5f / (0.5f - in[2] * 0.5f);
            out[0] = t * in[0];
            out[1] = t * in[1];
            out[2] = -in[2];
        }
        break;
    default:
        break;
    }
}
