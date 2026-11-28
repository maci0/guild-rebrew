extern volatile int gm_GameTicks;
extern char *tp_ch_PathGrid[];
char __cdecl d3sm_SampleHeight(int, float *, int *, int *, float *);
int __cdecl d3_TraceTerrainSegment(int, float *, float *, int, int, int *, int *);

/* ADDRESS: GOLDTL 0x005e94b0 */
int __cdecl d3_StepProjectile(char *obj)
{
    float gravity;
    float initial[3], next[3], step[3], dv[3];
    float fx, fy, fz, inv;
    float sx, sy, sz;
    float vx, vy, vz;
    float height;
    int map, n, remain, x, y, nx, ny, hit;
    gravity = *(float *)0x6660f0 * *(float *)0x6660e8;
    map = (int)tp_ch_PathGrid[0];
    if (*(int *)(obj + 0x5c) != 1) return 0;
    remain = gm_GameTicks - *(int *)(obj + 0x60);
    if (!d3sm_SampleHeight(map, (float *)(obj + 0x30), &x, &y, &height)) {
        *(int *)(obj + 0x5c) = 3;
        *(int *)(obj + 0x58) = 0;
        return 0;
    }
    fx = ((*(float *)(obj + 0x40) > *(float *)0x6628a8) ? 1.0f : *(float *)0x662a94)
        * (*(float *)(obj + 0x40) * *(float *)(obj + 0x40) * *(float *)(obj + 0x50))
        * *(float *)0x6ad620 * *(float *)0x6660f8 * *(float *)0x6628cc;
    fy = ((*(float *)(obj + 0x44) > *(float *)0x6628a8) ? 1.0f : *(float *)0x662a94)
        * (*(float *)(obj + 0x50) * *(float *)(obj + 0x44) * *(float *)(obj + 0x44))
        * *(float *)0x6ad620 * *(float *)0x6660f8 * *(float *)0x6628cc;
    fz = ((*(float *)(obj + 0x48) > *(float *)0x6628a8) ? 1.0f : *(float *)0x662a94)
        * (*(float *)(obj + 0x48) * *(float *)(obj + 0x48) * *(float *)(obj + 0x50))
        * *(float *)0x6ad620 * *(float *)0x6660f8 * *(float *)0x6628cc;
    inv = 1.0f / *(float *)(obj + 0x54);
    initial[0] = (inv * fx) * *(float *)0x6660f0;
    initial[1] = (inv * fy) * *(float *)0x6660f0;
    initial[2] = (inv * fz) * *(float *)0x6660f0;
    n = 0;
    while (n < remain) {
        sx = ((*(float *)(obj + 0x10) > *(float *)0x6628a8) ? 1.0f : *(float *)0x662a94)
            * (*(float *)(obj + 0x10) * *(float *)(obj + 0x10) * *(float *)(obj + 0x50))
            * *(float *)0x6ad620 * *(float *)0x6660f8 * *(float *)0x6628cc;
        sy = ((*(float *)(obj + 0x14) > *(float *)0x6628a8) ? 1.0f : *(float *)0x662a94)
            * (*(float *)(obj + 0x50) * *(float *)(obj + 0x14) * *(float *)(obj + 0x14))
            * *(float *)0x6ad620 * *(float *)0x6660f8 * *(float *)0x6628cc;
        sz = ((*(float *)(obj + 0x18) > *(float *)0x6628a8) ? 1.0f : *(float *)0x662a94)
            * (*(float *)(obj + 0x50) * *(float *)(obj + 0x18) * *(float *)(obj + 0x18))
            * *(float *)0x6ad620 * *(float *)0x6660f8 * *(float *)0x6628cc;
        inv = 1.0f / *(float *)(obj + 0x54);
        step[0] = (inv * sx) * *(float *)0x6660f0;
        step[1] = (inv * sy) * *(float *)0x6660f0;
        step[2] = (inv * sz) * *(float *)0x6660f0;
        *(int *)(obj + 0x60) += 1;
        *(int *)(obj + 0x64) += 1;
        *(float *)(obj + 0x10) = step[0] + *(float *)(obj + 0x10) + initial[0];
        *(float *)(obj + 0x14) = *(float *)(obj + 0x14) - gravity + initial[1] + step[1];
        *(float *)(obj + 0x18) = step[2] + *(float *)(obj + 0x18) + initial[2];
        next[0] = *(float *)(obj + 0x30);
        next[1] = *(float *)(obj + 0x34);
        next[2] = *(float *)(obj + 0x38);
        dv[0] = (*(float *)(obj + 0x10) * *(float *)0x6660e0) * *(float *)0x6660f0;
        dv[1] = (*(float *)(obj + 0x14) * *(float *)0x6660e0) * *(float *)0x6660f0;
        dv[2] = (*(float *)(obj + 0x18) * *(float *)0x6660e0) * *(float *)0x6660f0;
        next[0] += dv[0];
        next[1] += dv[1];
        next[2] += dv[2];
        hit = d3_TraceTerrainSegment(map, (float *)(obj + 0x30), next, x, y, &nx, &ny);
        if (hit && *(unsigned int *)(obj + 0x64) > 0x32) {
            *(float *)(obj + 0x30) = next[0];
            *(float *)(obj + 0x34) = next[1];
            *(float *)(obj + 0x38) = next[2];
            *(int *)(obj + 0x5c) = 2;
            vz = *(float *)(obj + 0x18);
            vy = *(float *)(obj + 0x14);
            vx = *(float *)(obj + 0x10);
            *(float *)(obj + 0x58) = (vx * vx + vy * vy + vz * vz) * *(float *)(obj + 0x54) * *(float *)0x6628cc;
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
