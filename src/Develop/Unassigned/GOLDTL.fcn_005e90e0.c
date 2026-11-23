char __cdecl fcn_0045b990(int, float *, int *, int *, float *);
int __cdecl fcn_005ea2d0(int, float *, float *, int, int, int *, int *);

/* ADDRESS: GOLDTL 0x005e90e0 */
int __cdecl fcn_005e90e0(char *obj)
{
    float gravity, initial[3], next[3], v[3], step[3], height;
    float inv, signx, signy, signz;
    int map, remain, n, x, y, nx, ny, hit;
    gravity = *(float *)0x6660ec * *(float *)0x6660e8;
    map = *(int *)0x1043370;
    if (*(int *)(obj + 0x5c) != 1) return 0;
    remain = *(int *)0x6b7fac - *(int *)(obj + 0x60);
    if (!fcn_0045b990(map, (float *)(obj + 0x30), &x, &y, &height)) {
        *(int *)(obj + 0x5c) = 3;
        *(int *)(obj + 0x58) = 0;
        return 0;
    }
    signx = (*(float *)(obj + 0x40) > *(float *)0x6628a8) ? 1.0f : *(float *)0x662a94;
    signy = (*(float *)(obj + 0x44) > *(float *)0x6628a8) ? 1.0f : *(float *)0x662a94;
    signz = (*(float *)(obj + 0x48) > *(float *)0x6628a8) ? 1.0f : *(float *)0x662a94;
    inv = 1.0f / *(float *)(obj + 0x54);
    initial[0] = inv * (*(float *)(obj + 0x50) * *(float *)(obj + 0x40) * *(float *)(obj + 0x40) * signx * *(float *)0x6ad620 * *(float *)0x6660f8 * *(float *)0x6628cc) * *(float *)0x6660ec;
    initial[1] = inv * (*(float *)(obj + 0x44) * *(float *)(obj + 0x44) * *(float *)(obj + 0x50) * signy * *(float *)0x6ad620 * *(float *)0x6660f8 * *(float *)0x6628cc) * *(float *)0x6660ec;
    initial[2] = inv * (*(float *)(obj + 0x50) * *(float *)(obj + 0x48) * *(float *)(obj + 0x48) * signz * *(float *)0x6ad620 * *(float *)0x6660f8 * *(float *)0x6628cc) * *(float *)0x6660ec;
    n = 0;
    while (n < remain) {
        signx = (*(float *)(obj + 0x10) > *(float *)0x6628a8) ? 1.0f : *(float *)0x662a94;
        signy = (*(float *)(obj + 0x14) > *(float *)0x6628a8) ? 1.0f : *(float *)0x662a94;
        signz = (*(float *)(obj + 0x18) > *(float *)0x6628a8) ? 1.0f : *(float *)0x662a94;
        inv = 1.0f / *(float *)(obj + 0x54);
        v[0] = *(float *)(obj + 0x10);
        v[1] = *(float *)(obj + 0x14);
        v[2] = *(float *)(obj + 0x18);
        step[0] = inv * (v[0] * v[0] * *(float *)(obj + 0x50) * signx * *(float *)0x6ad620 * *(float *)0x6660f8 * *(float *)0x6628cc) * *(float *)0x6660ec;
        step[1] = inv * (*(float *)(obj + 0x50) * v[1] * v[1] * signy * *(float *)0x6ad620 * *(float *)0x6660f8 * *(float *)0x6628cc) * *(float *)0x6660ec;
        step[2] = inv * (*(float *)(obj + 0x50) * v[2] * v[2] * signz * *(float *)0x6ad620 * *(float *)0x6660f8 * *(float *)0x6628cc) * *(float *)0x6660ec;
        *(int *)(obj + 0x60) += 1;
        *(int *)(obj + 0x64) += 1;
        v[0] = step[0] + v[0] + initial[0];
        v[1] = v[1] - gravity + step[1] + initial[1];
        v[2] = step[2] + v[2] + initial[2];
        *(float *)(obj + 0x10) = v[0];
        *(float *)(obj + 0x14) = v[1];
        *(float *)(obj + 0x18) = v[2];
        next[0] = *(float *)(obj + 0x30) + v[0] * *(float *)0x6660e0 * *(float *)0x6660ec;
        next[1] = *(float *)(obj + 0x34) + v[1] * *(float *)0x6660e0 * *(float *)0x6660ec;
        next[2] = *(float *)(obj + 0x38) + v[2] * *(float *)0x6660e0 * *(float *)0x6660ec;
        hit = fcn_005ea2d0(map, (float *)(obj + 0x30), next, x, y, &nx, &ny);
        *(float *)(obj + 0x30) = next[0];
        *(float *)(obj + 0x34) = next[1];
        *(float *)(obj + 0x38) = next[2];
        if (hit && *(unsigned int *)(obj + 0x64) >= 0x33) {
            *(int *)(obj + 0x5c) = 2;
            *(float *)(obj + 0x58) = ((v[0] * v[0] + (v[1] * v[1] + v[2] * v[2])) * *(float *)0x6628cc + *(float *)0x662cf8) * *(float *)(obj + 0x54);
            return 0;
        }
        x = nx;
        y = ny;
        n++;
    }
    return 1;
}
