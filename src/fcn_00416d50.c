int __cdecl sub_64d3f8(void);
char __cdecl sub_64d228(float);
int __cdecl sub_4518a0(float *);

/* ADDRESS: GOLDTL 0x00416d50 */
int __cdecl fcn_00416d50(unsigned char *P, int pos)
{
    unsigned char *E;
    int c1, c2, d;
    float f, vx, vy, vz, len, nlen;
    float v3[3];

    c2 = 0;
    c1 = 0;
    *(unsigned *)(P + 0x20) &= ~2u;
    /* dead precompute: 2*P[0xc]+P[4] / P[0x10] */
    (void)((2.0f * *(float *)(P + 0xc) + *(float *)(P + 4)) /
           *(float *)(P + 0x10));

    if ((int)*(int *)(P + 0xd8) <= 0)
        goto finish;

    E = *(unsigned char **)(P + 0x28);
    for (;;) {
        if (*(unsigned *)(P + 0x20) & 1u)
            goto pathB;
        if ((*(unsigned char *)(E + 0x51) & 1u) == 0 &&
            (unsigned)c2 < *(unsigned *)(P + 0x24))
            goto pathB;
        if (*(unsigned char *)(E + 0x51) & 1u) {
            d = pos - *(int *)(E + 0x30);
            *(int *)(E + 0x30) = pos;
            f = (float)d * *(float *)0x662a68;
            vx = f * *(float *)E + *(float *)(E + 0x38);
            vy = f * *(float *)(E + 4) + *(float *)(E + 0x3c);
            vz = f * *(float *)(E + 8) + *(float *)(E + 0x40);
            *(float *)(E + 0x38) = vx;
            *(float *)(E + 0x3c) = vy;
            *(float *)(E + 0x40) = vz;
            len = sqrtf(vx * vx + vy * vy + vz * vz);
            nlen = sqrtf(*(float *)E * *(float *)E +
                         *(float *)(E + 4) * *(float *)(E + 4) +
                         *(float *)(E + 8) * *(float *)(E + 8));
            if (nlen >= *(float *)(P + 0xc) &&
                nlen >= *(float *)(P + 0x14)) {
                v3[0] = vx;
                v3[1] = vy;
                v3[2] = vz;
                sub_4518a0(v3);
                vx = v3[0];
                vy = v3[1];
                vz = v3[2];
                if (!(vx >= *(float *)0x6628a8)) {
                    *(unsigned char *)(E + 0x51) &= ~1u;
                    c1++;
                    goto tail;
                }
                *(float *)(E + 0x38) = *(float *)(P + 0xc) * vx;
                *(float *)(E + 0x3c) = *(float *)(P + 0xc) * vy;
                *(float *)(E + 0x40) = *(float *)(P + 0xc) * vz;
                if (len >= *(float *)(P + 0x14)) {
                    *(float *)E = *(float *)(P + 0x18) * vx;
                    *(float *)(E + 4) = *(float *)(P + 0x18) * vy;
                    *(float *)(E + 8) = *(float *)(P + 0x18) * vz;
                }
            } else {
                *(float *)(E + 4) =
                    *(float *)(P + 0x1c) - *(float *)(E + 4);
            }
        }
        goto common;
    pathB:
        *(float *)(E + 0x38) =
            (float)((double)sub_64d3f8() * *(float *)0x662a18 *
                    *(double *)0x662aa0 - *(float *)0x662a98);
        *(float *)(E + 0x3c) =
            (float)((double)sub_64d3f8() * *(float *)0x662a18 *
                    *(double *)0x662aa0 - *(float *)0x662a98);
        *(float *)(E + 0x40) =
            (float)((double)sub_64d3f8() * *(float *)0x662a18 *
                    *(double *)0x662aa0 - *(float *)0x662a98);
        *(float *)(E + 0x38) += *(float *)(P + 0);
        *(float *)(E + 0x3c) += *(float *)(P + 4);
        *(float *)(E + 0x40) += *(float *)(P + 8);
        *(float *)(E + 4) = *(float *)(P + 4) - 2.0f * *(float *)(P + 0xc);
        f = 2.0f * *(float *)(P + 0xc);
        *(float *)E = (float)((double)sub_64d3f8() * *(float *)0x662a18) * f - f;
        *(float *)(E + 8) = (float)((double)sub_64d3f8() * *(float *)0x662a18) * f - f;
        f = *(float *)(P + 0xc) * 2.0f;
        *(float *)E *= f;
        *(float *)(E + 4) *= f;
        *(float *)(E + 8) *= f;
        *(float *)(E + 0x10) = 255.0f;
        *(int *)(E + 0x4c) = *(int *)(P + 0xd0);
        *(int *)(E + 0x48) = *(int *)(P + 0xe4);
        *(int *)(E + 0x30) = pos;
        *(unsigned char *)(E + 0x51) |= 1u;
        c2++;
        goto tail;
    common:
        f = *(float *)(E + 0x3c) / *(float *)(P + 4);
        if (f < 0.0f)
            f = 0.0f;
        f += *(float *)0x6629d0;
        if (f > *(float *)0x6628a0)
            f = *(float *)0x6628a0;
        f *= *(float *)0x6628a4;
        *(float *)(E + 0x10) = f;
        if (!(*(float *)(E + 0x3c) >= *(float *)0x6628a8)) {
            if (*(int *)(E + 0x4f) == 0) {
                *(unsigned char *)(E + 0x4f) = sub_64d228(f);
                c1++;
                goto tail;
            }
            *(unsigned char *)(E + 0x51) &= ~1u;
            c1++;
            goto tail;
        }
    tail:
        c1++;
        E += 0x54;
        if (c1 >= *(int *)(P + 0xd8))
            break;
    }
finish:
    *(int *)(P + 0x20) &= ~1u;
    if (c2 == 0)
        *(int *)(P + 0x20) |= 2u;
    return 1;
}
