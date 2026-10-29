#include <math.h>
#include <stdlib.h>

void __cdecl fcn_004518a0(float *v);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* Particle-system update: advances, reflects, recolors or respawns each of
 * P->count particles (stride 0x54) from E = P->particles. Returns 1 when the
 * update ran; P+0x20 bit 1 stays set when no particle died this pass. */
/* ADDRESS: GOLDTL 0x00416d50 */
char __cdecl fcn_00416d50(unsigned char *P, int pos)
{
    float v3[4];    /* 16-byte slot: fcn_004518a0 normalizes v3[0..2] */
    unsigned char *E;
    int spawned;
    int killed;
    int i;
    unsigned int d;
    float ratio;
    float f, vx, vy, vz, nlen;

    spawned = 0;
    killed = 0;
    *(unsigned *)(P + 0x20) &= ~2u;
    ratio = *(float *)(P + 0x10) /
            (2.0f * *(float *)(P + 0xc) + *(float *)(P + 4));
    E = *(unsigned char **)(P + 0x28);

    for (i = 0; i < *(int *)(P + 0xd8); i++) {
        if ((*(unsigned *)(P + 0x20) & 1u) == 0 &&
            ((*(unsigned char *)(E + 0x51) & 1u) != 0 ||
             (unsigned)spawned >= *(unsigned *)(P + 0x24))) {
            if ((*(unsigned char *)(E + 0x51) & 1u) == 0)
                continue;

            d = pos - *(int *)(E + 0x30);
            *(int *)(E + 0x30) = pos;
            f = (float)d * 0.33333334f;
            vx = f * *(float *)E + *(float *)(E + 0x38);
            *(float *)(E + 0x38) = vx;
            vy = f * *(float *)(E + 4) + *(float *)(E + 0x3c);
            *(float *)(E + 0x3c) = vy;
            vz = f * *(float *)(E + 8) + *(float *)(E + 0x40);
            *(float *)(E + 0x40) = vz;
            nlen = (float)sqrt(*(float *)E * *(float *)E +
                               *(float *)(E + 4) * *(float *)(E + 4) +
                               *(float *)(E + 8) * *(float *)(E + 8));
            if (!((float)sqrt(vx * vx + vy * vy + vz * vz) <=
                  *(float *)(P + 0xc)) ||
                !(nlen > *(float *)(P + 0x14))) {
                *(float *)(E + 4) =
                    *(float *)(E + 4) - f * *(float *)(P + 0x1c);
            } else {
                v3[0] = vx;
                v3[1] = vy;
                v3[2] = vz;
                fcn_004518a0(v3);
                if (v3[1] < 0.0f)
                    *(unsigned char *)(E + 0x51) &= ~1u;
                else {
                    *(float *)(E + 0x38) = *(float *)(P + 0xc) * v3[0];
                    *(float *)(E + 0x3c) = *(float *)(P + 0xc) * v3[1];
                    *(float *)(E + 0x40) = *(float *)(P + 0xc) * v3[2];
                    f = (v3[0] * *(float *)E + v3[1] * *(float *)(E + 4) +
                         v3[2] * *(float *)(E + 8)) *
                        -2.0f;
                    vx = v3[0] * f + *(float *)E;
                    *(float *)E = vx;
                    vy = v3[1] * f + *(float *)(E + 4);
                    *(float *)(E + 4) = vy;
                    vz = v3[2] * f + *(float *)(E + 8);
                    *(float *)(E + 8) = vz;
                    if (nlen > *(float *)(P + 0x14)) {
                        *(float *)E = *(float *)(P + 0x18) * vx;
                        *(float *)(E + 4) = *(float *)(P + 0x18) * vy;
                        *(float *)(E + 8) = *(float *)(P + 0x18) * vz;
                    }
                }
            }

            f = MIN(1.0f, 0.2f + MAX(0.0f, *(float *)(E + 0x3c) /
                                              *(float *)(P + 4))) *
                255.0f;
            *(float *)(E + 0x10) = f;
            if (f > 0.0 && *(float *)(E + 0x3c) > 0.0f)
                *(unsigned char *)(E + 0x4f) = (unsigned char)f;
            else
                *(unsigned char *)(E + 0x51) &= ~1u;
            killed++;
            continue;
        }

        *(float *)(E + 0x38) =
            (float)(rand() * 3.0518509e-05f * 10.0) - 5.0f;
        *(float *)(E + 0x3c) =
            (float)(rand() * 3.0518509e-05f * 10.0) - 5.0f;
        *(float *)(E + 0x40) =
            (float)(rand() * 3.0518509e-05f * 10.0) - 5.0f;
        *(float *)(E + 0x38) += *(float *)(P + 0);
        *(float *)(E + 0x3c) += *(float *)(P + 4);
        *(float *)(E + 0x40) += *(float *)(P + 8);
        *(float *)(E + 4) = -(*(float *)(P + 4) - *(float *)(P + 0xc));
        *(float *)E = (float)(rand() * 3.0518509e-05f) *
                          ((2.0f * *(float *)(P + 0xc)) + (2.0f * *(float *)(P + 0xc))) -
                      (2.0f * *(float *)(P + 0xc));
        *(float *)(E + 8) = (float)(rand() * 3.0518509e-05f) *
                                ((2.0f * *(float *)(P + 0xc)) + (2.0f * *(float *)(P + 0xc))) -
                            (2.0f * *(float *)(P + 0xc));
        *(float *)E *= ratio;
        *(float *)(E + 4) *= ratio;
        *(float *)(E + 8) *= ratio;
        *(float *)(E + 0x10) = 255.0f;
        *(int *)(E + 0x4c) = *(int *)(P + 0xd0);
        *(int *)(E + 0x48) = *(int *)(P + 0xe4);
        *(int *)(E + 0x30) = pos;
        *(unsigned char *)(E + 0x51) |= 1u;
        spawned++;
    }

    *(unsigned *)(P + 0x20) &= ~1u;
    if (killed == 0)
        *(unsigned *)(P + 0x20) |= 2u;
    return 1;
}
