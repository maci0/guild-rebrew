#include <math.h>
#include <string.h>

extern int __cdecl fcn_00407d90(void *, char *);
extern int __cdecl fcn_00408540(void *, int, char *);
extern void __cdecl ch_FinishAni(void *);
extern void __cdecl fcn_004050c0(void *);
extern void __cdecl fcn_004053a0(void *, int);
extern void __cdecl fcn_004090d0(void *);
extern void __cdecl m_FreeTracked(void *);
extern void __cdecl fcn_00438b40(int, void *);
extern float __cdecl fcn_00444700(int, float *);
extern int __cdecl fcn_00451840(void *, void *, float);
extern char __cdecl fcn_0045b920(void *, char, char, float *);

/* ADDRESS: GOLDTL 0x00409c90 */
unsigned int __cdecl fcn_00409c90(int a0, int a1)
{
    char *v6;
    char *v5;
    char *v4;
    char v10[64];
    int v8;
    int v9;
    float v13;
    float ct;
    float v14;
    float v15;
    float *v2;

    v6 = (char *)a0;
    v5 = (char *)a1;
    v4 = *(char **)(v6 + 0x14);
    if (*(unsigned char *)(v4 + 0x8e) >= 1)
        goto Lafter;
    if (!(*(unsigned char *)(v4 + 4) & 1))
        goto Lafter;
    if (*(int *)(v4 + 0x70) != 0 &&
        (*(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) & 8))
        goto Lafter;
    if (*(int *)0x67a370 != *(int *)(v4 + 0x88) &&
        *(int *)(v4 + 0x88) != 0x10432c0)
        goto Lafter;
    v8 = fcn_00407d90(v4, v10);
    if (!v8)
        goto Lafter;
    v8 = fcn_00408540(v4, v8, v10);
    if (v8 > 0) {
        if (!*(int *)(v4 + 0x70))
            goto Lafter;
    if (*(int *)(v4 + 4) & 8)
        v13 = *(float *)0x66293c;
    else if (*(int *)(v4 + 4) & 0x10)
        v13 = *(float *)0x66293c;
    else
        v13 = *(float *)0x662938;
    if (*(int *)(*(int *)(v4 + 0x88) + 0xac))
        v13 = (float)(v13 * *(double *)0x662930);
    v14 = *(float *)0x662914 / *(float *)(v5 + 0x10);
    ct = *(float *)0x662918;
    if (ct < v14)
        v14 = v13;
    *(float *)(*(int *)(v4 + 0x70) + 0x5c) = v14 + v13;
    *(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) =
        *(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) | 2;
    *(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) =
        *(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) & 0xf7;
    *(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) =
        *(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) | 4;
    *(unsigned char *)(*(int *)(v4 + 0x70) + 0x6d) =
        *(unsigned char *)(*(int *)(v4 + 0x70) + 0x6d) & 0xdf;
    v8 = *(int *)(*(int *)(v6 + 0x14) + 0x34);
    v13 = *(float *)(v8 + 0x4c) - *(float *)(v6 + 0x124);
    v14 = *(float *)(v8 + 0x50) - *(float *)(v6 + 0x128);
    v15 = *(float *)(v8 + 0x54) - *(float *)(v6 + 0x12c);
    v13 = (float)sqrt(v13 * v13 + v14 * v14 + v15 * v15);
    *(float *)(v6 + 0x10c) = v13;
    } else if (v8 == -1) {
        if (*(int *)(v4 + 0x70))
            *(int *)(*(int *)(v4 + 0x70) + 0x60) = 0x3c23d70a;
        *(int *)(v6 + 0x154) = *(int *)0x6b5c24;
        return 0;
    } else if (v8 == -2) {
        ch_FinishAni(v4);
        if (*(char *)0x6b5c28)
            *(unsigned char *)(*(int *)(v6 + 0x14) + 0x8c) |= 8;
        if (*(int *)(v6 + 0xf4)) {
            m_FreeTracked(*(void **)(v6 + 0xf4));
            *(int *)(v6 + 0xf4) = 0;
        }
        fcn_004050c0(v6);
        return 0;
    }
Lafter:
    if (*(int *)(v6 + 0xf8) &&
        (!*(int *)(v4 + 0x70) ||
         !(*(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) & 8)))
        return 1;
    if (*(unsigned char *)(v6 + 0x160) & 8) {
        if (*(int *)(v6 + 0xf8) % 4 == 0) {
            if (!fcn_00451840((void *)(v6 + 0x134),
                    (void *)(*(int *)(*(int *)(v6 + 0x110) + 0x34) + 0x4c), 70.0f))
                fcn_004090d0(v6);
        }
    }
    ++*(int *)(v6 + 0xf8);
    if (*(unsigned char *)(v4 + 0x8e) > 0) {
        if (--*(unsigned char *)(v4 + 0x8e) == 0)
            memset((void *)(v4 + 0x90), 0, 0x80);
    }
    v9 = *(int *)(v6 + 0xf8);
    if (!(v9 < *(int *)(v6 + 0xf0))) {
        if (*(int *)(v6 + 0xf4)) {
            m_FreeTracked(*(void **)(v6 + 0xf4));
            *(int *)(v6 + 0xf4) = 0;
        }
        if (*(unsigned int *)(v6 + 0x160) & 0x10) {
            if (*(int *)(v4 + 0x88) == 0x10432c0 &&
                *(unsigned char *)(v6 + 0x158) > 4)
                *(unsigned int *)(v6 + 0x160) =
                    *(unsigned int *)(v6 + 0x160) & 0xffffffef;
            v8 = *(int *)(v4 + 0x34);
            if (!fcn_00451840((void *)(v8 + 0x4c), (void *)(v6 + 0x144), 5.0f)) {
                *(int *)(v6 + 0x124) = *(int *)(v6 + 0x144);
                *(int *)(v6 + 0x128) = *(int *)(v6 + 0x148);
                *(int *)(v6 + 0x12c) = *(int *)(v6 + 0x14c);
                *(int *)(*(int *)(v4 + 0x70) + 0x4c) = *(int *)(v6 + 0x124);
                *(int *)(*(int *)(v4 + 0x70) + 0x50) = *(int *)(v6 + 0x128);
                *(int *)(*(int *)(v4 + 0x70) + 0x54) = *(int *)(v6 + 0x12c);
                v5 = *(char **)(*(int *)(v6 + 0x14) + 0x34);
                v13 = *(float *)(v5 + 0x4c) - *(float *)(v6 + 0x124);
                v14 = *(float *)(v5 + 0x50) - *(float *)(v6 + 0x128);
                v15 = *(float *)(v5 + 0x54) - *(float *)(v6 + 0x12c);
                *(int *)(v6 + 0x108) = 0xbf800000;
                *(float *)(v6 + 0x10c) =
                    (float)sqrt(v13 * v13 + v14 * v14 + v15 * v15);
                *(int *)(*(int *)(v4 + 0x70) + 0x5c) = 0x40a00000;
                *(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) =
                    *(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) | 2;
                *(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) =
                    *(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) & 0xf7;
                *(unsigned char *)(*(int *)(v4 + 0x70) + 0x6d) =
                    *(unsigned char *)(*(int *)(v4 + 0x70) + 0x6d) & 0xdf;
                ++*(unsigned char *)(v6 + 0x158);
                return 0;
            }
            fcn_00438b40(*(int *)(v4 + 0x34), (void *)(v6 + 0x144));
            fcn_004053a0(v4, 1);
        }
        ch_FinishAni(v4);
        if (*(char *)0x6b5c28)
            *(unsigned char *)(*(int *)(v6 + 0x14) + 0x8c) |= 8;
        fcn_004050c0(v6);
        return 0;
    }
    v2 = (float *)(v6 + 0x124);
    v8 = *(int *)(v6 + 0xf4);
    fcn_0045b920(v5, *(char *)(v8 + v9 * 2), *(char *)(v8 + 1 + v9 * 2), v2);
    *v2 = *(float *)0x6b5c38 + *v2;
    *(float *)(v6 + 0x128) = *(float *)0x6b5c3c + *(float *)(v6 + 0x128);
    *(float *)(v6 + 0x12c) = *(float *)0x6b5c40 + *(float *)(v6 + 0x12c);
    *(float *)(v6 + 0x108) = fcn_00444700(*(int *)(v4 + 0x34), v2);
    v8 = *(int *)(*(int *)(v6 + 0x14) + 0x34);
    v13 = *(float *)(v8 + 0x4c) - *v2;
    v14 = *(float *)(v8 + 0x50) - *(float *)(v6 + 0x128);
    v15 = *(float *)(v8 + 0x54) - *(float *)(v6 + 0x12c);
    *(float *)(v6 + 0x10c) = (float)sqrt(v13 * v13 + v14 * v14 + v15 * v15);
    if (*(int *)(v4 + 0x70)) {
        if (*(int *)(v6 + 0xf0) - 1 <= *(int *)(v6 + 0xf8) &&
            2 <= *(int *)(v6 + 0xf0)) {
            if (*(int *)(v4 + 4) & 8)
                v13 = *(float *)0x66292c;
            else if (*(int *)(v4 + 4) & 0x10)
                v13 = *(float *)0x662928;
            else
                v13 = *(float *)0x662924;
        } else if (*(int *)(v4 + 4) & 8)
            v13 = *(float *)0x662920;
        else if (*(int *)(v4 + 4) & 0x10)
            v13 = *(float *)0x66291c;
        else
            v13 = *(float *)0x662938;
        if (*(int *)(*(int *)(v4 + 0x88) + 0xac))
            v13 = (float)(v13 * *(double *)0x662930);
        *(int *)(*(int *)(v4 + 0x70) + 0x4c) = *(int *)v2;
        *(int *)(*(int *)(v4 + 0x70) + 0x50) = *(int *)(v6 + 0x128);
        *(int *)(*(int *)(v4 + 0x70) + 0x54) = *(int *)(v6 + 0x12c);
        *(float *)(*(int *)(v4 + 0x70) + 0x5c) = v13;
        *(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) =
            *(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) | 2;
        *(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) =
            *(unsigned char *)(*(int *)(v4 + 0x70) + 0x74) & 0xf7;
        *(unsigned char *)(*(int *)(v4 + 0x70) + 0x6d) =
            *(unsigned char *)(*(int *)(v4 + 0x70) + 0x6d) & 0xdf;
    }
    return 1;
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")
unsigned char _tlead_GOLDTL_fcn_00409c90[16] = {
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90
};
