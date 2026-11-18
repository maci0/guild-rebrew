#include <math.h>
#include <string.h>

extern int __cdecl fcn_00407d90(void *, char *);
extern int __cdecl fcn_00408540(void *, int, char *);
extern void __cdecl ch_FinishAni(void *);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
#include "Develop/DieGildeAddOn/game/ch_ground.h"
extern void __cdecl fcn_004090d0(void *);
extern void __cdecl m_FreeTracked(void *);
extern void __cdecl fcn_00438b40(int, void *);
extern float __cdecl fcn_00444700(int, float *);
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);
extern char __cdecl fcn_0045b920(void *, int, int, float *);

/* ADDRESS: GOLDTL 0x00409c90 */
unsigned int __cdecl fcn_00409c90(int a0, int a1)
{
    char *eventEntry;
    char *v5;
    char *character;
    char buffer[64];
    int v8;
    int v9;
    float v13;
    float ct;
    float v14;
    float v15;
    float *v2;

    eventEntry = (char *)a0;
    v5 = (char *)a1;
    character = *(char **)(eventEntry + 0x14);
    if (*(unsigned char *)(character + 0x8e) >= 1)
        goto Lafter;
    if (!(*(unsigned char *)(character + 4) & 1))
        goto Lafter;
    if (*(int *)(character + 0x70) != 0 &&
        (*(unsigned char *)(*(int *)(character + 0x70) + 0x74) & 8))
        goto Lafter;
    if (*(int *)0x67a370 != *(int *)(character + 0x88) &&
        *(int *)(character + 0x88) != 0x10432c0)
        goto Lafter;
    v8 = fcn_00407d90(character, buffer);
    if (!v8)
        goto Lafter;
    v8 = fcn_00408540(character, v8, buffer);
    if (v8 > 0) {
        if (!*(int *)(character + 0x70))
            goto Lafter;
    if (*(int *)(character + 4) & 8)
        v13 = *(float *)0x66293c;
    else if (*(int *)(character + 4) & 0x10)
        v13 = *(float *)0x66293c;
    else
        v13 = *(float *)0x662938;
    if (*(int *)(*(int *)(character + 0x88) + 0xac))
        v13 = (float)(v13 * *(double *)0x662930);
    v14 = *(float *)0x662914 / *(float *)(v5 + 0x10);
    ct = *(float *)0x662918;
    if (ct < v14)
        v14 = v13;
    *(float *)(*(int *)(character + 0x70) + 0x5c) = v14 + v13;
    *(unsigned char *)(*(int *)(character + 0x70) + 0x74) =
        *(unsigned char *)(*(int *)(character + 0x70) + 0x74) | 2;
    *(unsigned char *)(*(int *)(character + 0x70) + 0x74) =
        *(unsigned char *)(*(int *)(character + 0x70) + 0x74) & 0xf7;
    *(unsigned char *)(*(int *)(character + 0x70) + 0x74) =
        *(unsigned char *)(*(int *)(character + 0x70) + 0x74) | 4;
    *(unsigned char *)(*(int *)(character + 0x70) + 0x6d) =
        *(unsigned char *)(*(int *)(character + 0x70) + 0x6d) & 0xdf;
    v8 = *(int *)(*(int *)(eventEntry + 0x14) + 0x34);
    v13 = *(float *)(v8 + 0x4c) - *(float *)(eventEntry + 0x124);
    v14 = *(float *)(v8 + 0x50) - *(float *)(eventEntry + 0x128);
    v15 = *(float *)(v8 + 0x54) - *(float *)(eventEntry + 0x12c);
    v13 = (float)sqrt(v13 * v13 + v14 * v14 + v15 * v15);
    *(float *)(eventEntry + 0x10c) = v13;
    } else if (v8 == -1) {
        if (*(int *)(character + 0x70))
            *(int *)(*(int *)(character + 0x70) + 0x60) = 0x3c23d70a;
        *(int *)(eventEntry + 0x154) = *(int *)0x6b5c24;
        return 0;
    } else if (v8 == -2) {
        ch_FinishAni(character);
        if (*(char *)0x6b5c28)
            *(unsigned char *)(*(int *)(eventEntry + 0x14) + 0x8c) |= 8;
        if (*(int *)(eventEntry + 0xf4)) {
            m_FreeTracked(*(void **)(eventEntry + 0xf4));
            *(int *)(eventEntry + 0xf4) = 0;
        }
        ch_RemoveQueueEntry(eventEntry);
        return 0;
    }
Lafter:
    if (*(int *)(eventEntry + 0xf8) &&
        (!*(int *)(character + 0x70) ||
         !(*(unsigned char *)(*(int *)(character + 0x70) + 0x74) & 8)))
        return 1;
    if (*(unsigned char *)(eventEntry + 0x160) & 8) {
        if (*(int *)(eventEntry + 0xf8) % 4 == 0) {
            if (!CompareVector3WithinTolerance((void *)(eventEntry + 0x134),
                    (void *)(*(int *)(*(int *)(eventEntry + 0x110) + 0x34) + 0x4c), 70.0f))
                fcn_004090d0(eventEntry);
        }
    }
    ++*(int *)(eventEntry + 0xf8);
    if (*(unsigned char *)(character + 0x8e) > 0) {
        if (--*(unsigned char *)(character + 0x8e) == 0)
            memset((void *)(character + 0x90), 0, 0x80);
    }
    v9 = *(int *)(eventEntry + 0xf8);
    if (v9 >= *(int *)(eventEntry + 0xf0)) {
        if (*(int *)(eventEntry + 0xf4)) {
            m_FreeTracked(*(void **)(eventEntry + 0xf4));
            *(int *)(eventEntry + 0xf4) = 0;
        }
        if (*(unsigned int *)(eventEntry + 0x160) & 0x10) {
            if (*(int *)(character + 0x88) == 0x10432c0 &&
                *(unsigned char *)(eventEntry + 0x158) > 4)
                *(unsigned int *)(eventEntry + 0x160) =
                    *(unsigned int *)(eventEntry + 0x160) & 0xffffffef;
            if (!CompareVector3WithinTolerance((void *)(*(int *)(character + 0x34) + 0x4c),
                    (void *)(eventEntry + 0x144), 5.0f)) {
                v13 = *(float *)(eventEntry + 0x144);
                *(float *)(eventEntry + 0x124) = v13;
                *(int *)(eventEntry + 0x128) = *(int *)(eventEntry + 0x148);
                *(int *)(eventEntry + 0x12c) = *(int *)(eventEntry + 0x14c);
                *(float *)(*(int *)(character + 0x70) + 0x4c) = v13;
                *(int *)(*(int *)(character + 0x70) + 0x50) = *(int *)(eventEntry + 0x128);
                *(int *)(*(int *)(character + 0x70) + 0x54) = *(int *)(eventEntry + 0x12c);
                v5 = *(char **)(*(int *)(eventEntry + 0x14) + 0x34);
                v13 = *(float *)(v5 + 0x4c) - *(float *)(eventEntry + 0x124);
                v14 = *(float *)(v5 + 0x50) - *(float *)(eventEntry + 0x128);
                v15 = *(float *)(v5 + 0x54) - *(float *)(eventEntry + 0x12c);
                *(int *)(eventEntry + 0x108) = 0xbf800000;
                v13 = (float)sqrt(v13 * v13 + v14 * v14 + v15 * v15);
                *(float *)(eventEntry + 0x10c) = v13;
                *(int *)(*(int *)(character + 0x70) + 0x5c) = 0x40a00000;
                *(unsigned char *)(*(int *)(character + 0x70) + 0x74) =
                    *(unsigned char *)(*(int *)(character + 0x70) + 0x74) | 2;
                *(unsigned char *)(*(int *)(character + 0x70) + 0x74) =
                    *(unsigned char *)(*(int *)(character + 0x70) + 0x74) & 0xf7;
                *(unsigned char *)(*(int *)(character + 0x70) + 0x6d) =
                    *(unsigned char *)(*(int *)(character + 0x70) + 0x6d) & 0xdf;
                ++*(unsigned char *)(eventEntry + 0x158);
                return 0;
            }
            fcn_00438b40(*(int *)(character + 0x34), (void *)(eventEntry + 0x144));
            ch_PlaceOnGround(character, 1);
        }
        ch_FinishAni(character);
        if (*(char *)0x6b5c28)
            *(unsigned char *)(*(int *)(eventEntry + 0x14) + 0x8c) |= 8;
        ch_RemoveQueueEntry(eventEntry);
        return 0;
    }
    v2 = (float *)(eventEntry + 0x124);
    fcn_0045b920(v5, *(unsigned char *)(*(int *)(eventEntry + 0xf4) + v9 * 2),
        *(unsigned char *)(*(int *)(eventEntry + 0xf4) + 1 + v9 * 2), v2);
    v14 = *(float *)0x6b5c38;
    *v2 = v14 + *v2;
    v14 = *(float *)0x6b5c3c;
    *(float *)(eventEntry + 0x128) = v14 + *(float *)(eventEntry + 0x128);
    v14 = *(float *)0x6b5c40;
    *(float *)(eventEntry + 0x12c) = v14 + *(float *)(eventEntry + 0x12c);
    *(float *)(eventEntry + 0x108) = fcn_00444700(*(int *)(character + 0x34), v2);
    v8 = *(int *)(*(int *)(eventEntry + 0x14) + 0x34);
    v13 = *(float *)(v8 + 0x4c) - *v2;
    v14 = *(float *)(v8 + 0x50) - *(float *)(eventEntry + 0x128);
    v15 = *(float *)(v8 + 0x54) - *(float *)(eventEntry + 0x12c);
    v13 = (float)sqrt(v13 * v13 + v14 * v14 + v15 * v15);
    *(float *)(eventEntry + 0x10c) = v13;
    if (*(int *)(character + 0x70)) {
        if (*(int *)(eventEntry + 0xf8) >= *(int *)(eventEntry + 0xf0) - 1 &&
            *(int *)(eventEntry + 0xf0) > 1) {
            if (*(int *)(character + 4) & 8)
                v13 = *(float *)0x66292c;
            else if (*(int *)(character + 4) & 0x10)
                v13 = *(float *)0x662928;
            else
                v13 = *(float *)0x662924;
        } else if (*(int *)(character + 4) & 8)
            v13 = *(float *)0x662920;
        else if (*(int *)(character + 4) & 0x10)
            v13 = *(float *)0x66291c;
        else
            v13 = *(float *)0x662938;
        if (*(int *)(*(int *)(character + 0x88) + 0xac))
            v13 = (float)(v13 * *(double *)0x662930);
        *(int *)(*(int *)(character + 0x70) + 0x4c) = *(int *)v2;
        *(int *)(*(int *)(character + 0x70) + 0x50) = *(int *)(eventEntry + 0x128);
        *(int *)(*(int *)(character + 0x70) + 0x54) = *(int *)(eventEntry + 0x12c);
        *(float *)(*(int *)(character + 0x70) + 0x5c) = v13;
        *(unsigned char *)(*(int *)(character + 0x70) + 0x74) =
            *(unsigned char *)(*(int *)(character + 0x70) + 0x74) | 2;
        *(unsigned char *)(*(int *)(character + 0x70) + 0x74) =
            *(unsigned char *)(*(int *)(character + 0x70) + 0x74) & 0xf7;
        *(unsigned char *)(*(int *)(character + 0x70) + 0x6d) =
            *(unsigned char *)(*(int *)(character + 0x70) + 0x6d) & 0xdf;
    }
    return 1;
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

