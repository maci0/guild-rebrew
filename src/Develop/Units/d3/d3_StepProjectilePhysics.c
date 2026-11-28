#include "Develop/DieGildeAddOn/game/game_data.h"
extern int tp_ch_PathGrid;
extern float flt_100_0;
char __cdecl d3sm_SampleHeight(int, float *, int *, int *, float *);
int __cdecl d3_TraceTerrainSegment(int, float *, float *, int, int, int *, int *);

/* ADDRESS: GOLDTL 0x005e90e0 */
int __cdecl d3_StepProjectilePhysics(char *obj)
{
    float gravity, initial[3], next[3], step[3], height;
    float inv, fx, fy, fz;
    int map, remain, n, x, y, nx, ny, hit;
    gravity = *(float *)0x6660ec * *(float *)0x6660e8;
    map = tp_ch_PathGrid;
    if (*(int *)(obj + 0x5c) != 1) return 0;
    remain = gm_GameTicks - *(int *)(obj + 0x60);
    if (!d3sm_SampleHeight(map, (float *)(obj + 0x30), &x, &y, &height)) {
        *(int *)(obj + 0x5c) = 3;
        *(int *)(obj + 0x58) = 0;
        return 0;
    }
    fx = (((*(float *)(obj + 0x40) > *(float *)0x6628a8) ? flt_1_0 : *(float *)0x662a94) *
         (*(float *)(obj + 0x50) * *(float *)(obj + 0x40) * *(float *)(obj + 0x40))) *
         *(float *)0x6ad620 * *(float *)0x6660f8 * g_6628cc;
    fy = (((*(float *)(obj + 0x44) > *(float *)0x6628a8) ? flt_1_0 : *(float *)0x662a94) *
         (*(float *)(obj + 0x44) * *(float *)(obj + 0x44) * *(float *)(obj + 0x50))) *
         *(float *)0x6ad620 * *(float *)0x6660f8 * g_6628cc;
    fz = (((*(float *)(obj + 0x48) > *(float *)0x6628a8) ? flt_1_0 : *(float *)0x662a94) *
         (*(float *)(obj + 0x50) * *(float *)(obj + 0x48) * *(float *)(obj + 0x48))) *
         *(float *)0x6ad620 * *(float *)0x6660f8 * g_6628cc;
    inv = flt_1_0 / *(float *)(obj + 0x54);
    initial[0] = inv * fx * *(float *)0x6660ec;
    initial[1] = inv * fy * *(float *)0x6660ec;
    initial[2] = inv * fz * *(float *)0x6660ec;
    n = 0;
    while (n < remain) {
        fx = (((*(float *)(obj + 0x10) > *(float *)0x6628a8) ? flt_1_0 : *(float *)0x662a94) *
             (*(float *)(obj + 0x10) * *(float *)(obj + 0x10) * *(float *)(obj + 0x50))) *
             *(float *)0x6ad620 * *(float *)0x6660f8 * g_6628cc;
        fy = (((*(float *)(obj + 0x14) > *(float *)0x6628a8) ? flt_1_0 : *(float *)0x662a94) *
             (*(float *)(obj + 0x50) * *(float *)(obj + 0x14) * *(float *)(obj + 0x14))) *
             *(float *)0x6ad620 * *(float *)0x6660f8 * g_6628cc;
        fz = (((*(float *)(obj + 0x18) > *(float *)0x6628a8) ? flt_1_0 : *(float *)0x662a94) *
             (*(float *)(obj + 0x50) * *(float *)(obj + 0x18) * *(float *)(obj + 0x18))) *
             *(float *)0x6ad620 * *(float *)0x6660f8 * g_6628cc;
        inv = flt_1_0 / *(float *)(obj + 0x54);
        step[0] = inv * fx * *(float *)0x6660ec;
        step[1] = inv * fy * *(float *)0x6660ec;
        step[2] = inv * fz * *(float *)0x6660ec;
        *(int *)(obj + 0x60) += 1;
        *(int *)(obj + 0x64) += 1;
        *(float *)(obj + 0x10) = step[0] + *(float *)(obj + 0x10) + initial[0];
        *(float *)(obj + 0x14) = *(float *)(obj + 0x14) - gravity + initial[1] + step[1];
        *(float *)(obj + 0x18) = step[2] + *(float *)(obj + 0x18) + initial[2];
        next[0] = *(float *)(obj + 0x10) * *(float *)0x6660e0 * *(float *)0x6660ec + *(float *)(obj + 0x30);
        next[1] = *(float *)(obj + 0x14) * *(float *)0x6660e0 * *(float *)0x6660ec + *(float *)(obj + 0x34);
        next[2] = *(float *)(obj + 0x18) * *(float *)0x6660e0 * *(float *)0x6660ec + *(float *)(obj + 0x38);
        hit = d3_TraceTerrainSegment(map, (float *)(obj + 0x30), next, x, y, &nx, &ny);
        if (hit && *(unsigned int *)(obj + 0x64) > 0x32) {
            *(float *)(obj + 0x30) = next[0];
            *(float *)(obj + 0x34) = next[1];
            *(float *)(obj + 0x38) = next[2];
            *(int *)(obj + 0x5c) = 2;
            *(float *)(obj + 0x58) = (((*(float *)(obj + 0x18) * *(float *)(obj + 0x18) +
                *(float *)(obj + 0x14) * *(float *)(obj + 0x14)) +
                *(float *)(obj + 0x10) * *(float *)(obj + 0x10)) * g_6628cc +
                flt_100_0) * *(float *)(obj + 0x54);
            return 0;
        }
        *(float *)(obj + 0x30) = next[0];
        *(float *)(obj + 0x34) = next[1];
        *(float *)(obj + 0x38) = next[2];
        x = nx;
        y = ny;
        n++;
    }
    return 1;
}
