/*
 * Reconstructed from the native body at 0x0043c640.
 * Decompiler-shaped C89 transliteration: every load, store, call and branch of
 * the reference is kept in native order. Helper types are byte/integer views.
 *
 * Layout note: one tile object; fields +0x000 W, +0x004 H, +0x014 material map, +0x020 vertex array, +0x024 edge flags, +0x030 slot mask,
 * +0xa0 region table (8x8 records of 0x34, stride 500), +0x802c jitter step, +0x8030 vertex step
 */

#include <string.h>

typedef int i32;
typedef unsigned int u32;
typedef unsigned short u2;
typedef unsigned char u1;
typedef unsigned int u4;
typedef unsigned char u8;
typedef signed char i8;
typedef short i16;

extern void* __cdecl m_alloc(unsigned int size, const char* tag);
extern void __cdecl m_FreeTracked(void* p);
int __cdecl rand(void);

static void* __cdecl fcn_0041db70(u32 size, u32 tag)
{
	return m_alloc(size, (const char*) tag);
}

static void __cdecl fcn_0041ddd0(u32 ptr)
{
	m_FreeTracked((void*) ptr);
}

static i32 __cdecl libc_rand(void)
{
	return rand();
}

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0043c640 */
void __cdecl fcn_0043c640(i32 arg_4h)
{
    float fVar1;
    i32 iVar2;
    u4 *arg_4h_00;
    u4 *arg_4h_01;
    u4 *arg_4h_02;
    u4 *arg_4h_03;
    i32 iVar3;
    i32 iVar4;
    u8 *puVar5;
    i32 *piVar6;
    i32 iVar7;
    i32 iVar8;
    i32 iVar9;
    i32 *piVar10;
    u32 uVar11;
    u4 *puVar12;
    u4 *puVar13;
    u8 uVar14;
    char *pcVar15;
    i32 iVar16;
    i32 iVar17;
    i32 iVar18;
    i32 iVar19;
    u32 uVar20;
    u32 uVar21;
    char *pcVar22;
    i32 var_8h;
    i32 var_ch;
    i32 var_10h;
    i32 var_14h;
    i32 var_18h;
    i32 var_1ch;
    i32 var_20h;
    i32 var_24h;
    i32 var_28h;
    i32 var_2ch;
    i32 var_30h;
    i32 var_34h;
    i32 var_38h;
    i32 var_3ch;
    i32 var_40h;
    i32 var_44h;
    i32 var_48h;
    i32 var_4ch;
    i32 var_50h;
    i32 var_54h;
    i32 var_58h;
    i32 var_5ch;
    i32 var_60h;
    i32 var_64h;
    
    iVar3 = *(i32 *)arg_4h;
    var_ch = 0;
    iVar2 = iVar3 + -1;
    if (0 < iVar2) {
        do {
            iVar9 = 0;
            if (0 < iVar2) {
                do {
                    iVar2 = iVar3 * var_ch;
                    pcVar15 = (char *)(*(i32 *)(arg_4h + 0x14) + iVar2 + iVar9);
                    pcVar22 = (char *)((var_ch + 1) * iVar3 + *(i32 *)(arg_4h + 0x14) + iVar9);
                    if (*pcVar15 == pcVar22[1]) {
                        if (pcVar15[1] != *pcVar22) {
                            iVar2 = *(i32 *)(arg_4h + 0x24) + iVar2;
                            uVar14 = *(u8 *)(iVar2 + iVar9) & 0x7f;
                            goto code_r0x0043c6a7;
                        }
                    } else {
                        iVar2 = *(i32 *)(arg_4h + 0x24) + iVar2;
                        uVar14 = *(u8 *)(iVar2 + iVar9) | 0x80;
code_r0x0043c6a7:
                        *(u8 *)(iVar2 + iVar9) = uVar14;
                    }
                    iVar3 = *(i32 *)arg_4h;
                    iVar9 = iVar9 + 1;
                } while (iVar9 < iVar3 + -1);
            }
            iVar3 = *(i32 *)arg_4h;
            var_ch = var_ch + 1;
            iVar2 = iVar3 + -1;
        } while (var_ch < iVar2);
    }
    arg_4h_00 = (u4 *)fcn_0041db70(*(i32 *)(arg_4h + 4) * *(i32 *)(arg_4h + 4), 0x67a694);
    arg_4h_01 = (u4 *)fcn_0041db70(*(i32 *)(arg_4h + 4) * *(i32 *)(arg_4h + 4), 0x67a680);
    arg_4h_02 = (u4 *)fcn_0041db70(*(i32 *)(arg_4h + 4) * *(i32 *)(arg_4h + 4), 0x67a668);
    iVar2 = *(i32 *)(arg_4h + 4) + 1;
    arg_4h_03 = (u4 *)fcn_0041db70(iVar2 * iVar2 * 4, 0x67a654);
    var_ch = 0;
    do {
        var_8h = 0;
        iVar2 = var_ch + 1;
        do {
            var_24h = -1;
            var_48h = 0x40000000;
            var_40h = 1;
            do {
                if (var_48h < 1) break;
                iVar3 = var_40h;
                if (0 < var_40h) {
                    piVar10 = (i32 *)(arg_4h + 0x30);
                    do {
                        if ((((u8)iVar3 & 1) == 1) && (*piVar10 == 0)) break;
                        iVar3 = iVar3 >> 1;
                        piVar10 = piVar10 + 1;
                    } while (0 < iVar3);
                }
                if (iVar3 == 0) {
                    iVar3 = *(i32 *)(arg_4h + 4) * *(i32 *)(arg_4h + 4);
                    uVar11 = (i32)arg_4h_01 * 3 & 3;
                    uVar20 = iVar3 - uVar11;
                    uVar21 = uVar20;
                    puVar12 = arg_4h_01;
                    if (uVar20 != 0 && (i32)uVar11 <= iVar3) {
                        for (; uVar11 != 0; uVar11 = uVar11 - 1) {
                            *(u1 *)puVar12 = 0;
                            puVar12 = (u4 *)((i32)puVar12 + 1);
                        }
                        uVar21 = uVar20 & 3;
                        for (uVar11 = uVar20 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
                            *puVar12 = 0;
                            puVar12 = puVar12 + 1;
                        }
                    }
                    for (iVar3 = uVar11 + uVar21; iVar3 != 0; iVar3 = iVar3 + -1) {
                        *(u1 *)puVar12 = 0;
                        puVar12 = (u4 *)((i32)puVar12 + 1);
                    }
                    iVar3 = *(i32 *)(arg_4h + 4);
                    iVar9 = iVar3 * var_ch;
                    while( 1 ) {
                        iVar16 = iVar3 * iVar2;
                        if (*(i32 *)arg_4h + -1 < iVar3 * iVar2) {
                            iVar16 = *(i32 *)arg_4h + -1;
                        }
                        if (iVar16 <= iVar9) break;
                        iVar16 = iVar3 * var_8h;
                        while( 1 ) {
                            iVar3 = *(i32 *)(arg_4h + 4);
                            iVar4 = iVar3 * (var_8h + 1);
                            if (*(i32 *)arg_4h + -1 < iVar4) {
                                iVar4 = *(i32 *)arg_4h + -1;
                            }
                            if (iVar4 <= iVar16) break;
                            var_50h = var_40h;
                            var_38h = 0;
                            do {
                                iVar3 = *(i32 *)arg_4h * iVar9 + *(i32 *)(arg_4h + 0x14);
                                uVar21 = (u32)*(u8 *)(iVar3 + iVar16);
                                iVar3 = iVar3 + iVar16;
                                if ((((((uVar21 == var_38h) || ((u32)*(u8 *)(iVar3 + 1) == var_38h)) ||
                                      (iVar4 = (iVar9 + 1) * *(i32 *)arg_4h + *(i32 *)(arg_4h + 0x14),
                                      (u32)*(u8 *)(iVar4 + iVar16) == var_38h)) ||
                                     ((u32)*(u8 *)(iVar4 + iVar16 + 1) == var_38h)) &&
                                    (((uVar21 != var_38h || ((u32)*(u8 *)(iVar3 + 1) != var_38h)) ||
                                     ((iVar3 = (iVar9 + 1) * *(i32 *)arg_4h + *(i32 *)(arg_4h + 0x14),
                                      (u32)*(u8 *)(iVar3 + iVar16) != var_38h ||
                                      ((u32)*(u8 *)(iVar3 + iVar16 + 1) != var_38h)))))) &&
                                   (puVar5 = (u8 *)
                                             ((i32)arg_4h_01 +
                                             ((iVar9 - *(i32 *)(arg_4h + 4) * var_ch) - var_8h) *
                                             *(i32 *)(arg_4h + 4) + iVar16), *puVar5 = *puVar5 | 0x10,
                                   ((u8)var_50h & 1) == 1)) {
                                    pcVar15 = (char *)((i32)arg_4h_01 +
                                                      ((iVar9 - *(i32 *)(arg_4h + 4) * var_ch) - var_8h) *
                                                      *(i32 *)(arg_4h + 4) + iVar16);
                                    *pcVar15 = *pcVar15 + '\x01';
                                }
                                var_50h = var_50h >> 1;
                                var_38h = var_38h + 1;
                            } while (var_38h < 8);
                            iVar16 = iVar16 + 1;
                        }
                        iVar9 = iVar9 + 1;
                    }
                    iVar9 = *(i32 *)(arg_4h + 4);
                    iVar3 = 0;
                    var_50h = 0;
                    puVar12 = arg_4h_01;
                    if (0 < iVar9) {
                        do {
                            if (0x3fffffff < iVar3) break;
                            var_54h = 0;
                            puVar13 = puVar12;
                            do {
                                uVar14 = *(u8 *)puVar13;
                                if ((uVar14 & 0x10) == 0x10) {
                                    if ((uVar14 & 0xf) == 0) {
                                        iVar3 = 0x40000000;
                                        break;
                                    }
                                    iVar3 = iVar3 + -1 + (uVar14 & 0xf);
                                }
                                var_54h = var_54h + 1;
                                puVar13 = (u4 *)((i32)puVar13 + 1);
                            } while (var_54h < iVar9);
                            var_50h = var_50h + 1;
                            puVar12 = (u4 *)((i32)puVar12 + iVar9);
                        } while (var_50h < iVar9);
                    }
                    if (iVar3 < var_48h) {
                        var_24h = var_40h;
                        uVar11 = (i32)arg_4h_02 * 3 & 3;
                        uVar20 = iVar9 * iVar9 - uVar11;
                        uVar21 = uVar20;
                        puVar12 = arg_4h_01;
                        puVar13 = arg_4h_02;
                        if (uVar20 != 0 && (i32)uVar11 <= iVar9 * iVar9) {
                            for (; uVar11 != 0; uVar11 = uVar11 - 1) {
                                *(u1 *)puVar13 = *(u1 *)puVar12;
                                puVar12 = (u4 *)((i32)puVar12 + 1);
                                puVar13 = (u4 *)((i32)puVar13 + 1);
                            }
                            uVar21 = uVar20 & 3;
                            for (uVar11 = uVar20 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
                                *puVar13 = *puVar12;
                                puVar12 = puVar12 + 1;
                                puVar13 = puVar13 + 1;
                            }
                        }
                        for (iVar9 = uVar11 + uVar21; var_48h = iVar3, iVar9 != 0; iVar9 = iVar9 + -1) {
                            *(u1 *)puVar13 = *(u1 *)puVar12;
                            puVar12 = (u4 *)((i32)puVar12 + 1);
                            puVar13 = (u4 *)((i32)puVar13 + 1);
                        }
                    }
                }
                var_40h = var_40h + 1;
            } while (var_40h < 0x100);
            iVar9 = 8;
            iVar3 = (var_8h + var_ch * 8) * 500;
            piVar10 = (i32 *)(iVar3 + 0xbc + arg_4h);
            piVar6 = piVar10;
            do {
                *piVar6 = 2;
                piVar6 = piVar6 + 0xd;
                iVar9 = iVar9 + -1;
            } while (iVar9 != 0);
            if (var_48h < 0x40000000) {
                for (; 0 < var_24h; var_24h = var_24h >> 1) {
                    *piVar10 = (((u8)var_24h & 1) != 1) + 1;
                    piVar10 = piVar10 + 0xd;
                }
            }
            var_38h = 0;
            do {
                iVar9 = iVar3 + var_38h * 0x34;
                iVar16 = *(i32 *)(iVar9 + 0xa4 + arg_4h);
                piVar10 = (i32 *)(iVar9 + 0xa0 + arg_4h);
                var_48h = 0;
                var_20h = 0;
                piVar10[9] = 0;
                piVar10[8] = 0;
                piVar10[0xc] = 0;
                piVar10[0xb] = 0;
                if (iVar16 != 0) {
                    fcn_0041ddd0(iVar16);
                    piVar10[1] = 0;
                }
                if (piVar10[2] != 0) {
                    fcn_0041ddd0(piVar10[2]);
                    piVar10[2] = 0;
                }
                if (piVar10[2] != 0) {
                    fcn_0041ddd0(piVar10[2]);
                    piVar10[2] = 0;
                }
                if (piVar10[3] != 0) {
                    fcn_0041ddd0(piVar10[3]);
                    piVar10[3] = 0;
                }
                if (piVar10[4] != 0) {
                    fcn_0041ddd0(piVar10[4]);
                    piVar10[4] = 0;
                }
                if (*piVar10 != 0) {
                    fcn_0041ddd0(*piVar10);
                    *piVar10 = 0;
                }
                iVar9 = *(i32 *)(arg_4h + 4) * *(i32 *)(arg_4h + 4);
                uVar11 = (i32)arg_4h_00 * 3 & 3;
                uVar20 = iVar9 - uVar11;
                uVar21 = uVar20;
                puVar12 = arg_4h_00;
                if (uVar20 != 0 && (i32)uVar11 <= iVar9) {
                    for (; uVar11 != 0; uVar11 = uVar11 - 1) {
                        *(u1 *)puVar12 = 0;
                        puVar12 = (u4 *)((i32)puVar12 + 1);
                    }
                    uVar21 = uVar20 & 3;
                    for (uVar11 = uVar20 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
                        *puVar12 = 0;
                        puVar12 = puVar12 + 1;
                    }
                }
                for (iVar9 = uVar11 + uVar21; iVar9 != 0; iVar9 = iVar9 + -1) {
                    *(u1 *)puVar12 = 0;
                    puVar12 = (u4 *)((i32)puVar12 + 1);
                }
                iVar9 = *(i32 *)(arg_4h + 4);
                iVar16 = iVar9 * var_ch;
code_r0x0043cafa:
                iVar4 = iVar9 * iVar2;
                if (*(i32 *)arg_4h + -1 < iVar9 * iVar2) {
                    iVar4 = *(i32 *)arg_4h + -1;
                }
                if (iVar16 < iVar4) {
                    iVar4 = iVar9 * var_8h;
code_r0x0043cb17:
                    do {
                        iVar9 = *(i32 *)(arg_4h + 4);
                        iVar17 = iVar9 * (var_8h + 1);
                        if (*(i32 *)arg_4h + -1 < iVar17) {
                            iVar17 = *(i32 *)arg_4h + -1;
                        }
                        if (iVar17 <= iVar4) goto code_r0x0043cc1d;
                        puVar5 = (u8 *)(*(i32 *)arg_4h * iVar16 + *(i32 *)(arg_4h + 0x14) + iVar4);
                        if ((u32)*puVar5 == var_38h) {
                            if ((((u32)puVar5[1] == var_38h) &&
                                (iVar17 = (iVar16 + 1) * *(i32 *)arg_4h + *(i32 *)(arg_4h + 0x14),
                                (u32)*(u8 *)(iVar17 + iVar4) == var_38h)) &&
                               ((u32)*(u8 *)(iVar17 + iVar4 + 1) == var_38h)) {
                                *(u1 *)
                                 (((iVar16 - iVar9 * var_ch) - var_8h) * iVar9 + iVar4 + (i32)arg_4h_00) = 1;
                                var_20h = var_20h + 1;
                                iVar4 = iVar4 + 1;
                                goto code_r0x0043cb17;
                            }
                            if ((u32)*puVar5 != var_38h) goto code_r0x0043cbbb;
code_r0x0043cbf5:
                            *(u1 *)(((iVar16 - iVar9 * var_ch) - var_8h) * iVar9 + iVar4 + (i32)arg_4h_00) =
                                 2;
                            var_48h = var_48h + 1;
                        } else {
code_r0x0043cbbb:
                            if ((((u32)puVar5[1] == var_38h) ||
                                (iVar17 = (iVar16 + 1) * *(i32 *)arg_4h + *(i32 *)(arg_4h + 0x14),
                                (u32)*(u8 *)(iVar17 + iVar4) == var_38h)) ||
                               ((u32)*(u8 *)(iVar17 + iVar4 + 1) == var_38h)) goto code_r0x0043cbf5;
                        }
                        iVar4 = iVar4 + 1;
                    } while( 1 );
                }
                if (0 < var_20h) {
                    iVar9 = *(i32 *)(arg_4h + 4) + 1;
                    var_24h = var_20h * 4;
                    iVar9 = iVar9 * iVar9 * 4;
                    uVar11 = (i32)arg_4h_03 * 3 & 3;
                    uVar20 = iVar9 - uVar11;
                    uVar21 = uVar20;
                    puVar12 = arg_4h_03;
                    if (uVar20 != 0 && (i32)uVar11 <= iVar9) {
                        for (; uVar11 != 0; uVar11 = uVar11 - 1) {
                            *(u1 *)puVar12 = 0xff;
                            puVar12 = (u4 *)((i32)puVar12 + 1);
                        }
                        uVar21 = uVar20 & 3;
                        for (uVar11 = uVar20 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
                            *puVar12 = 0xffffffff;
                            puVar12 = puVar12 + 1;
                        }
                    }
                    for (iVar9 = uVar11 + uVar21; iVar9 != 0; iVar9 = iVar9 + -1) {
                        *(u1 *)puVar12 = 0xff;
                        puVar12 = (u4 *)((i32)puVar12 + 1);
                    }
                    iVar9 = *(i32 *)(arg_4h + 4);
                    iVar16 = 0;
                    if (0 < iVar9) {
                        do {
                            iVar4 = 0;
                            var_40h = iVar9 * iVar16 + 1 + (i32)arg_4h_00;
                            do {
                                if (*(char *)(var_40h + -1) == '\x01') {
                                    if (((iVar4 < iVar9 + -1) && (iVar16 < iVar9 + -1)) &&
                                       ((*(char *)var_40h == '\x01' &&
                                        (*(char *)((iVar16 + 1) * iVar9 + iVar4 + (i32)arg_4h_00) == '\x01')))) {
                                        var_24h = var_24h + -3;
                                    } else if ((iVar4 < iVar9 + -1) && (*(char *)var_40h == '\x01')) {
                                        var_24h = var_24h + -2;
                                    } else if ((iVar16 < iVar9 + -1) &&
                                              (*(char *)((iVar16 + 1) * iVar9 + iVar4 + (i32)arg_4h_00) == '\x01'))
                                    {
                                        var_24h = var_24h + -2;
                                    } else if (((iVar4 < iVar9 + -1) && (iVar16 < iVar9 + -1)) &&
                                              (*(char *)((iVar16 + 1) * iVar9 + iVar4 + 1 + (i32)arg_4h_00) ==
                                               '\x01')) {
                                        var_24h = var_24h + -1;
                                    }
                                }
                                iVar4 = iVar4 + 1;
                                var_40h = var_40h + 1;
                            } while (iVar4 < iVar9);
                            iVar16 = iVar16 + 1;
                        } while (iVar16 < iVar9);
                    }
                    piVar10[8] = var_24h;
                    iVar9 = fcn_0041db70(var_24h * 4, 0x67a638);
                    piVar10[1] = iVar9;
                    piVar10[0xb] = var_20h * 2;
                    var_50h = fcn_0041db70(var_20h * 0xc, 0x67a624);
                    piVar10[3] = var_50h;
                    iVar9 = *(i32 *)(arg_4h + 4);
                    var_54h = iVar9;
                    if (var_8h == 7) {
                        var_54h = iVar9 + -4;
                    }
                    if (var_ch == 7) {
                        iVar9 = iVar9 + -4;
                    }
                    iVar16 = 0;
                    var_40h = 0;
                    piVar10[0xb] = 0;
                    if (0 < iVar9) {
                        do {
                            iVar4 = 0;
                            if (0 < var_54h) {
                                do {
                                    iVar17 = *(i32 *)(arg_4h + 4);
                                    if (*(char *)(iVar17 * iVar16 + iVar4 + (i32)arg_4h_00) == '\x01') {
                                        iVar18 = (iVar17 + 1) * iVar16 + iVar4;
                                        iVar19 = (iVar16 + 1) * (iVar17 + 1) + iVar4;
                                        if (arg_4h_03[iVar18] == -1) {
                                            *(i32 *)(piVar10[1] + var_40h * 4) =
                                                 iVar17 * var_8h + -0x1000000 +
                                                 iVar4 + (iVar17 * var_ch + iVar16) * *(i32 *)arg_4h;
                                            arg_4h_03[iVar18] = var_40h;
                                            var_40h = var_40h + 1;
                                            if (iVar4 == 0) {
                                                var_28h = 0;
                                            } else {
                                                var_28h = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            if (iVar16 == 0) {
                                                var_2ch = 0;
                                            } else {
                                                var_2ch = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            iVar17 = *(i32 *)(arg_4h + 4);
                                            iVar7 = iVar17 * var_8h;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_28h;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) +
                                                      ((iVar17 * var_ch + iVar16) * *(i32 *)arg_4h + iVar7 + iVar4)
                                                      * 8) =
                                                 ((float)(iVar7 + iVar4) * *(float *)(arg_4h + 0x8030) + fVar1 + fVar1)
                                                 - (float)var_28h;
                                            iVar17 = *(i32 *)(arg_4h + 4);
                                            iVar7 = iVar17 * var_ch + iVar16;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_2ch;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) + 4 +
                                                      (iVar17 * var_8h + iVar4 + *(i32 *)arg_4h * iVar7) * 8) =
                                                 ((float)iVar7 * *(float *)(arg_4h + 0x8030) + fVar1 + fVar1) -
                                                 (float)var_2ch;
                                        }
                                        if (arg_4h_03[iVar18 + 1] == -1) {
                                            *(i32 *)(piVar10[1] + var_40h * 4) =
                                                 *(i32 *)(arg_4h + 4) * var_8h + -0xffffff +
                                                 iVar4 + (*(i32 *)(arg_4h + 4) * var_ch + iVar16) *
                                                         *(i32 *)arg_4h;
                                            arg_4h_03[iVar18 + 1] = var_40h;
                                            var_40h = var_40h + 1;
                                            if (iVar4 == *(i32 *)(arg_4h + 4) + -1) {
                                                var_28h = 0;
                                            } else {
                                                var_28h = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            if (iVar16 == 0) {
                                                var_2ch = 0;
                                            } else {
                                                var_2ch = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            iVar17 = *(i32 *)(arg_4h + 4);
                                            iVar7 = iVar17 * var_8h;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_28h;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) + 8 +
                                                      ((iVar17 * var_ch + iVar16) * *(i32 *)arg_4h + iVar7 + iVar4)
                                                      * 8) =
                                                 ((float)(iVar7 + 1 + iVar4) * *(float *)(arg_4h + 0x8030) +
                                                 fVar1 + fVar1) - (float)var_28h;
                                            iVar17 = *(i32 *)(arg_4h + 4);
                                            iVar7 = iVar17 * var_ch + iVar16;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_2ch;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) + 0xc +
                                                      (iVar17 * var_8h + iVar4 + *(i32 *)arg_4h * iVar7) * 8) =
                                                 ((float)iVar7 * *(float *)(arg_4h + 0x8030) + fVar1 + fVar1) -
                                                 (float)var_2ch;
                                        }
                                        if (arg_4h_03[iVar19] == -1) {
                                            *(i32 *)(piVar10[1] + var_40h * 4) =
                                                 *(i32 *)(arg_4h + 4) * var_8h + -0x1000000 +
                                                 iVar4 + (*(i32 *)(arg_4h + 4) * var_ch + 1 + iVar16) *
                                                         *(i32 *)arg_4h;
                                            arg_4h_03[iVar19] = var_40h;
                                            var_40h = var_40h + 1;
                                            if (iVar4 == 0) {
                                                var_28h = 0;
                                            } else {
                                                var_28h = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            if (iVar16 == *(i32 *)(arg_4h + 4) + -1) {
                                                var_2ch = 0;
                                            } else {
                                                var_2ch = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            iVar17 = *(i32 *)(arg_4h + 4);
                                            iVar7 = iVar17 * var_8h;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_28h;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) +
                                                      ((iVar17 * var_ch + 1 + iVar16) * *(i32 *)arg_4h + iVar7 +
                                                      iVar4) * 8) =
                                                 ((float)(iVar7 + iVar4) * *(float *)(arg_4h + 0x8030) + fVar1 + fVar1)
                                                 - (float)var_28h;
                                            iVar7 = *(i32 *)(arg_4h + 4);
                                            iVar17 = iVar7 * var_ch + 1 + iVar16;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_2ch;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) + 4 +
                                                      (iVar7 * var_8h + iVar4 + *(i32 *)arg_4h * iVar17) * 8) =
                                                 ((float)iVar17 * *(float *)(arg_4h + 0x8030) + fVar1 + fVar1) -
                                                 (float)var_2ch;
                                        }
                                        if (arg_4h_03[iVar19 + 1] == -1) {
                                            *(i32 *)(piVar10[1] + var_40h * 4) =
                                                 *(i32 *)(arg_4h + 4) * var_8h + -0xffffff +
                                                 iVar4 + (*(i32 *)(arg_4h + 4) * var_ch + 1 + iVar16) *
                                                         *(i32 *)arg_4h;
                                            arg_4h_03[iVar19 + 1] = var_40h;
                                            var_40h = var_40h + 1;
                                            iVar17 = *(i32 *)(arg_4h + 4) + -1;
                                            if (iVar4 == iVar17) {
                                                var_28h = 0;
                                            } else {
                                                var_28h = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            if (iVar16 == iVar17) {
                                                var_2ch = 0;
                                            } else {
                                                var_2ch = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            iVar17 = *(i32 *)(arg_4h + 4);
                                            iVar7 = iVar17 * var_8h;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_28h;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) + 8 +
                                                      ((iVar17 * var_ch + 1 + iVar16) * *(i32 *)arg_4h + iVar7 +
                                                      iVar4) * 8) =
                                                 ((float)(iVar7 + 1 + iVar4) * *(float *)(arg_4h + 0x8030) +
                                                 fVar1 + fVar1) - (float)var_28h;
                                            iVar7 = *(i32 *)(arg_4h + 4);
                                            iVar17 = iVar7 * var_ch + 1 + iVar16;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_2ch;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) + 0xc +
                                                      (iVar7 * var_8h + iVar4 + *(i32 *)arg_4h * iVar17) * 8) =
                                                 ((float)iVar17 * *(float *)(arg_4h + 0x8030) + fVar1 + fVar1) -
                                                 (float)var_2ch;
                                        }
                                        if (*(char *)((*(i32 *)(arg_4h + 4) * var_ch + iVar16) * *(i32 *)arg_4h
                                                      + *(i32 *)(arg_4h + 4) * var_8h + *(i32 *)(arg_4h + 0x24)
                                                     + iVar4) < '\0') {
                                            *(u2 *)var_50h = *(u2 *)(arg_4h_03 + iVar18);
                                            *(u2 *)(var_50h + 2) = *(u2 *)(arg_4h_03 + iVar18 + 1);
                                            *(u2 *)(var_50h + 4) = *(u2 *)(arg_4h_03 + iVar19);
                                            *(u2 *)(var_50h + 6) = *(u2 *)(arg_4h_03 + iVar19);
                                            *(u2 *)(var_50h + 8) = *(u2 *)(arg_4h_03 + iVar18 + 1);
                                            iVar18 = iVar19;
                                        } else {
                                            *(u2 *)var_50h = *(u2 *)(arg_4h_03 + iVar19);
                                            *(u2 *)(var_50h + 2) = *(u2 *)(arg_4h_03 + iVar18);
                                            *(u2 *)(var_50h + 4) = *(u2 *)(arg_4h_03 + iVar19 + 1);
                                            *(u2 *)(var_50h + 6) = *(u2 *)(arg_4h_03 + iVar19 + 1);
                                            *(u2 *)(var_50h + 8) = *(u2 *)(arg_4h_03 + iVar18);
                                        }
                                        *(u2 *)(var_50h + 10) = *(u2 *)(arg_4h_03 + iVar18 + 1);
                                        var_50h = var_50h + 0xc;
                                        piVar10[0xb] = piVar10[0xb] + 2;
                                    }
                                    iVar4 = iVar4 + 1;
                                } while (iVar4 < var_54h);
                            }
                            iVar16 = iVar16 + 1;
                        } while (iVar16 < iVar9);
                    }
                    piVar10[8] = var_40h;
                }
                if (0 < var_48h) {
                    piVar10[10] = 0;
                    var_40h = var_48h * 4;
                    iVar9 = *(i32 *)(arg_4h + 4) + 1;
                    iVar9 = iVar9 * iVar9 * 4;
                    uVar11 = (i32)arg_4h_03 * 3 & 3;
                    uVar20 = iVar9 - uVar11;
                    uVar21 = uVar20;
                    puVar12 = arg_4h_03;
                    if (uVar20 != 0 && (i32)uVar11 <= iVar9) {
                        for (; uVar11 != 0; uVar11 = uVar11 - 1) {
                            *(u1 *)puVar12 = 0xff;
                            puVar12 = (u4 *)((i32)puVar12 + 1);
                        }
                        uVar21 = uVar20 & 3;
                        for (uVar11 = uVar20 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
                            *puVar12 = 0xffffffff;
                            puVar12 = puVar12 + 1;
                        }
                    }
                    for (iVar9 = uVar11 + uVar21; iVar9 != 0; iVar9 = iVar9 + -1) {
                        *(u1 *)puVar12 = 0xff;
                        puVar12 = (u4 *)((i32)puVar12 + 1);
                    }
                    iVar9 = *(i32 *)(arg_4h + 4);
                    iVar16 = 0;
                    if (0 < iVar9) {
                        do {
                            iVar4 = 0;
                            var_24h = iVar9 * iVar16 + 1 + (i32)arg_4h_00;
                            do {
                                if (*(char *)(var_24h + -1) == '\x02') {
                                    if (((iVar4 < iVar9 + -1) && (iVar16 < iVar9 + -1)) &&
                                       ((*(char *)var_24h == '\x02' &&
                                        (*(char *)((iVar16 + 1) * iVar9 + iVar4 + (i32)arg_4h_00) == '\x02')))) {
                                        var_40h = var_40h + -3;
                                    } else if ((iVar4 < iVar9 + -1) && (*(char *)var_24h == '\x02')) {
                                        var_40h = var_40h + -2;
                                    } else if ((iVar16 < iVar9 + -1) &&
                                              (*(char *)((iVar16 + 1) * iVar9 + iVar4 + (i32)arg_4h_00) == '\x02'))
                                    {
                                        var_40h = var_40h + -2;
                                    } else if (((iVar4 < iVar9 + -1) && (iVar16 < iVar9 + -1)) &&
                                              (*(char *)((iVar16 + 1) * iVar9 + iVar4 + 1 + (i32)arg_4h_00) ==
                                               '\x02')) {
                                        var_40h = var_40h + -1;
                                    }
                                }
                                iVar4 = iVar4 + 1;
                                var_24h = var_24h + 1;
                            } while (iVar4 < iVar9);
                            iVar16 = iVar16 + 1;
                        } while (iVar16 < iVar9);
                    }
                    piVar10[9] = var_40h;
                    iVar9 = fcn_0041db70(var_40h << 2, 0x67a60c);
                    piVar10[2] = iVar9;
                    piVar10[0xc] = var_48h * 2;
                    var_50h = fcn_0041db70(var_48h * 0xc, 0x67a5f8);
                    piVar10[4] = var_50h;
                    var_54h = fcn_0041db70(piVar10[0xc] << 2, 0x67a5e0);
                    *piVar10 = var_54h;
                    iVar9 = *(i32 *)(arg_4h + 4);
                    var_48h = iVar9;
                    if (var_8h == 7) {
                        var_48h = iVar9 + -4;
                    }
                    if (var_ch == 7) {
                        iVar9 = iVar9 + -4;
                    }
                    iVar16 = 0;
                    var_40h = 0;
                    piVar10[0xc] = 0;
                    if (0 < iVar9) {
                        do {
                            iVar4 = 0;
                            if (0 < var_48h) {
                                do {
                                    if (*(char *)(*(i32 *)(arg_4h + 4) * iVar16 + iVar4 + (i32)arg_4h_00) ==
                                        '\x02') {
                                        iVar18 = *(i32 *)(arg_4h + 4) + 1;
                                        iVar17 = iVar18 * iVar16 + iVar4;
                                        iVar18 = (iVar16 + 1) * iVar18 + iVar4;
                                        if (arg_4h_03[iVar17] == -1) {
                                            iVar7 = *(i32 *)(arg_4h + 4) * var_8h;
                                            iVar19 = (*(i32 *)(arg_4h + 4) * var_ch + iVar16) * *(i32 *)arg_4h;
                                            *(u32 *)(piVar10[2] + var_40h * 4) =
                                                 ((-(u32)
                                                    ((u32)
                                                     *(u8 *)(*(i32 *)(arg_4h + 0x14) + iVar19 + iVar7 + iVar4)
                                                    != var_38h) & 0x1000000) - 0x1000000) + iVar19 + iVar7 + iVar4;
                                            arg_4h_03[iVar17] = var_40h;
                                            var_40h = var_40h + 1;
                                            if (iVar4 == 0) {
                                                var_30h = 0;
                                            } else {
                                                var_30h = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            if (iVar16 == 0) {
                                                var_34h = 0;
                                            } else {
                                                var_34h = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            iVar19 = *(i32 *)(arg_4h + 4);
                                            iVar7 = iVar19 * var_8h;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_30h;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) +
                                                      ((iVar19 * var_ch + iVar16) * *(i32 *)arg_4h + iVar7 + iVar4)
                                                      * 8) =
                                                 ((float)(iVar7 + iVar4) * *(float *)(arg_4h + 0x8030) + fVar1 + fVar1)
                                                 - (float)var_30h;
                                            iVar19 = *(i32 *)(arg_4h + 4);
                                            iVar7 = iVar19 * var_ch + iVar16;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_34h;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) + 4 +
                                                      (iVar19 * var_8h + iVar4 + *(i32 *)arg_4h * iVar7) * 8) =
                                                 ((float)iVar7 * *(float *)(arg_4h + 0x8030) + fVar1 + fVar1) -
                                                 (float)var_34h;
                                        }
                                        if (arg_4h_03[iVar17 + 1] == -1) {
                                            iVar7 = *(i32 *)(arg_4h + 4) * var_8h;
                                            iVar19 = (*(i32 *)(arg_4h + 4) * var_ch + iVar16) * *(i32 *)arg_4h;
                                            *(u32 *)(piVar10[2] + var_40h * 4) =
                                                 (-(u32)
                                                   ((u32)
                                                    *(u8 *)
                                                     (*(i32 *)(arg_4h + 0x14) + iVar19 + iVar7 + 1 + iVar4) !=
                                                   var_38h) & 0x1000000) + iVar19 + iVar7 + -0xffffff + iVar4;
                                            arg_4h_03[iVar17 + 1] = var_40h;
                                            var_40h = var_40h + 1;
                                            if (iVar4 == *(i32 *)(arg_4h + 4) + -1) {
                                                var_30h = 0;
                                            } else {
                                                var_30h = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            if (iVar16 == 0) {
                                                var_34h = 0;
                                            } else {
                                                var_34h = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            iVar19 = *(i32 *)(arg_4h + 4);
                                            iVar7 = iVar19 * var_8h;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_30h;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) + 8 +
                                                      ((iVar19 * var_ch + iVar16) * *(i32 *)arg_4h + iVar7 + iVar4)
                                                      * 8) =
                                                 ((float)(iVar7 + 1 + iVar4) * *(float *)(arg_4h + 0x8030) +
                                                 fVar1 + fVar1) - (float)var_30h;
                                            iVar19 = *(i32 *)(arg_4h + 4);
                                            iVar7 = iVar19 * var_ch + iVar16;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_34h;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) + 0xc +
                                                      (iVar19 * var_8h + iVar4 + *(i32 *)arg_4h * iVar7) * 8) =
                                                 ((float)iVar7 * *(float *)(arg_4h + 0x8030) + fVar1 + fVar1) -
                                                 (float)var_34h;
                                        }
                                        if (arg_4h_03[iVar18] == -1) {
                                            iVar7 = *(i32 *)(arg_4h + 4) * var_8h;
                                            iVar19 = (*(i32 *)(arg_4h + 4) * var_ch + 1 + iVar16) *
                                                     *(i32 *)arg_4h;
                                            *(u32 *)(piVar10[2] + var_40h * 4) =
                                                 ((-(u32)
                                                    ((u32)
                                                     *(u8 *)(*(i32 *)(arg_4h + 0x14) + iVar19 + iVar7 + iVar4)
                                                    != var_38h) & 0x1000000) - 0x1000000) + iVar19 + iVar7 + iVar4;
                                            arg_4h_03[iVar18] = var_40h;
                                            var_40h = var_40h + 1;
                                            if (iVar4 == 0) {
                                                var_30h = 0;
                                            } else {
                                                var_30h = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            if (iVar16 == *(i32 *)(arg_4h + 4) + -1) {
                                                var_34h = 0;
                                            } else {
                                                var_34h = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            iVar19 = *(i32 *)(arg_4h + 4);
                                            iVar7 = iVar19 * var_8h;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_30h;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) +
                                                      ((iVar19 * var_ch + 1 + iVar16) * *(i32 *)arg_4h + iVar7 +
                                                      iVar4) * 8) =
                                                 ((float)(iVar7 + iVar4) * *(float *)(arg_4h + 0x8030) + fVar1 + fVar1)
                                                 - (float)var_30h;
                                            iVar7 = *(i32 *)(arg_4h + 4);
                                            iVar19 = iVar7 * var_ch + 1 + iVar16;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_34h;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) + 4 +
                                                      (iVar7 * var_8h + iVar4 + *(i32 *)arg_4h * iVar19) * 8) =
                                                 ((float)iVar19 * *(float *)(arg_4h + 0x8030) + fVar1 + fVar1) -
                                                 (float)var_34h;
                                        }
                                        if (arg_4h_03[iVar18 + 1] == -1) {
                                            iVar7 = *(i32 *)(arg_4h + 4) * var_8h;
                                            iVar19 = (*(i32 *)(arg_4h + 4) * var_ch + 1 + iVar16) *
                                                     *(i32 *)arg_4h;
                                            *(u32 *)(piVar10[2] + var_40h * 4) =
                                                 (-(u32)
                                                   ((u32)
                                                    *(u8 *)
                                                     (*(i32 *)(arg_4h + 0x14) + iVar19 + iVar7 + 1 + iVar4) !=
                                                   var_38h) & 0x1000000) + iVar19 + iVar7 + -0xffffff + iVar4;
                                            arg_4h_03[iVar18 + 1] = var_40h;
                                            var_40h = var_40h + 1;
                                            iVar19 = *(i32 *)(arg_4h + 4) + -1;
                                            if (iVar4 == iVar19) {
                                                var_30h = 0;
                                            } else {
                                                var_30h = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            if (iVar16 == iVar19) {
                                                var_34h = 0;
                                            } else {
                                                var_34h = *(i32 *)(arg_4h + 0x802c);
                                            }
                                            iVar19 = *(i32 *)(arg_4h + 4);
                                            iVar7 = iVar19 * var_8h;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_30h;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) + 8 +
                                                      ((iVar19 * var_ch + 1 + iVar16) * *(i32 *)arg_4h + iVar7 +
                                                      iVar4) * 8) =
                                                 ((float)(iVar7 + 1 + iVar4) * *(float *)(arg_4h + 0x8030) +
                                                 fVar1 + fVar1) - (float)var_30h;
                                            iVar7 = *(i32 *)(arg_4h + 4);
                                            iVar19 = iVar7 * var_ch + 1 + iVar16;
                                            iVar8 = libc_rand();
                                            fVar1 = (float)iVar8 * 3.051851e-05 * (float)var_34h;
                                            *(float *)(*(i32 *)(arg_4h + 0x20) + 0xc +
                                                      (iVar7 * var_8h + iVar4 + *(i32 *)arg_4h * iVar19) * 8) =
                                                 ((float)iVar19 * *(float *)(arg_4h + 0x8030) + fVar1 + fVar1) -
                                                 (float)var_34h;
                                        }
                                        if (piVar10[7] == 1) {
                                            puVar5 = (u8 *)
                                                     ((i32)arg_4h_02 + *(i32 *)(arg_4h + 4) * iVar16 + iVar4);
                                            uVar14 = *puVar5;
                                            if (1 < (uVar14 & 0xf)) {
                                                *puVar5 = uVar14 - 1;
                                                *(u4 *)var_54h = 1;
                                                *(u4 *)(var_54h + 4) = 1;
                                                piVar10[10] = 1;
                                            }
                                        }
                                        var_54h = var_54h + 8;
                                        if (*(char *)((*(i32 *)(arg_4h + 4) * var_ch + iVar16) * *(i32 *)arg_4h
                                                      + *(i32 *)(arg_4h + 4) * var_8h + *(i32 *)(arg_4h + 0x24)
                                                     + iVar4) < '\0') {
                                            *(u2 *)var_50h = *(u2 *)(arg_4h_03 + iVar17);
                                            *(u2 *)(var_50h + 2) = *(u2 *)(arg_4h_03 + iVar17 + 1);
                                            *(u2 *)(var_50h + 4) = *(u2 *)(arg_4h_03 + iVar18);
                                            *(u2 *)(var_50h + 6) = *(u2 *)(arg_4h_03 + iVar18);
                                            *(u2 *)(var_50h + 8) = *(u2 *)(arg_4h_03 + iVar17 + 1);
                                            iVar17 = iVar18;
                                        } else {
                                            *(u2 *)var_50h = *(u2 *)(arg_4h_03 + iVar18);
                                            *(u2 *)(var_50h + 2) = *(u2 *)(arg_4h_03 + iVar17);
                                            *(u2 *)(var_50h + 4) = *(u2 *)(arg_4h_03 + iVar18 + 1);
                                            *(u2 *)(var_50h + 6) = *(u2 *)(arg_4h_03 + iVar18 + 1);
                                            *(u2 *)(var_50h + 8) = *(u2 *)(arg_4h_03 + iVar17);
                                        }
                                        *(u2 *)(var_50h + 10) = *(u2 *)(arg_4h_03 + iVar17 + 1);
                                        var_50h = var_50h + 0xc;
                                        piVar10[0xc] = piVar10[0xc] + 2;
                                    }
                                    iVar4 = iVar4 + 1;
                                } while (iVar4 < var_48h);
                            }
                            iVar16 = iVar16 + 1;
                        } while (iVar16 < iVar9);
                    }
                    if (piVar10[10] == 0) {
                        fcn_0041ddd0(*piVar10);
                        *piVar10 = 0;
                    }
                    piVar10[9] = var_40h;
                }
                var_38h = var_38h + 1;
            } while (var_38h < 8);
            var_8h = var_8h + 1;
        } while (var_8h < 8);
        var_ch = iVar2;
        if (7 < iVar2) {
            fcn_0041ddd0((i32)arg_4h_03);
            fcn_0041ddd0((i32)arg_4h_01);
            fcn_0041ddd0((i32)arg_4h_02);
            fcn_0041ddd0((i32)arg_4h_00);
            return;
        }
    } while( 1 );
code_r0x0043cc1d:
    iVar16 = iVar16 + 1;
    goto code_r0x0043cafa;
}