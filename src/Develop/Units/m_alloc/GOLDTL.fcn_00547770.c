/*
 * Reconstructed from the native body at 0x00547770.
 * Decompiler-shaped C89 transliteration: the load, store, call and branch shape
 * of the reference is kept in native order. x87 temporaries are modelled as
 * 64-bit floats; helper prototypes are unprototyped to mirror the reference
 * call sites.
 *
 * Building-mix driven economic command selection: counts 256 building records by type/owner, picks a world-counter modulo-5 case with random thresholds,
 * creates or polls requests and serialises commands.
 */

#include <string.h>

typedef int i32;
typedef unsigned int u32;
typedef unsigned short u2;
typedef unsigned char u1;
typedef unsigned char u8;
typedef unsigned int u4;
typedef double x87;

extern void* __cdecl m_alloc(unsigned int size, const char* tag);
extern void __cdecl m_FreeTracked(void* p);
int __cdecl rand(void);

#define CONCAT31(h, l) ((((u32) (h)) << 8) | ((u8) (l)))

int __cdecl fcn_0042e410();
double __cdecl fcn_0042e450();
int __cdecl fcn_004c4330();
int __cdecl fcn_004c4450();
int __cdecl fcn_004c4480();
int __cdecl fcn_004c4510();
int __cdecl fcn_004c4570();
int __cdecl fcn_004c4fc0();
int __cdecl fcn_004c5150();
int __cdecl fcn_004c5360();
int __cdecl fcn_00507400();
int __cdecl fcn_0050cf50();
int __cdecl fcn_0050d170();
int __cdecl fcn_00535960();
int __cdecl fcn_00547670();

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x00547770 */
u32 __cdecl fcn_00547770(i32 arg_b0h)
{
    char cVar1;
    x87 Var2;
    float fVar3;
    u32 uVar4;
    u2 uVar5;
    u32 uVar6;
    i32 iVar7;
    u32 uVar8;
    u32 uVar9;
    i32 iVar10;
    i32 *piVar11;
    i32 unaff_ESI;
    u8 *puVar12;
    i32 *piVar13;
    i32 unaff_EDI;
    i32 iVar14;
    u32 uVar15;
    u8 uVar16;
    i32 bVar17;
    x87 Var18;
    u4 uVar19;
    i32 iVar20;
    i32 iVar21;
    i32 iVar22;
    i32 iVar23;
    i32 var_124h;
    i32 var_120h;
    i32 var_11ch;
    i32 var_118h;
    i32 var_114h;
    i32 var_110h;
    float fStack_10c;
    i32 var_108h;
    i32 var_fch;
    i32 var_f8h;
    i32 var_f4h;
    i32 var_ech;
    i32 var_e8h;
    i32 var_e4h;
    i32 var_d0h;
    i32 var_c8h;
    i32 var_c0h;
    i32 var_bch;
    i32 var_b8h;
    i32 var_b4h;
    i32 var_b0h;
    u4 uStack_ac;
    u1 auStack_9c [8];
    i32 var_94h;
    i32 var_8ch;
    i32 var_88h;
    i32 var_84h;
    i32 var_74h;
    i32 iStack_70;
    i32 iStack_64;
    i32 iStack_60;
    i32 iStack_4c;
    i32 var_44h;
    i32 iStack_3c;
    i32 var_38h;
    i32 iStack_34;
    i32 iStack_30;
    i32 iStack_2c;
    i32 iStack_10;
    i32 iStack_8;
    i32 iStack_4;
    
    iVar10 = 0;
    var_124h = 0;
    var_114h = 0;
    if (*(i32 *)0x7747b4 < 5) {
        iVar7 = *(i32 *)0x7747b4;
        if (*(i32 *)0x7747b4 < 1) {
            iVar7 = 0;
        }
    } else {
        iVar7 = 4;
    }
    var_120h = ((i32)(*(i32 *)0x7f4c00 + (*(i32 *)0x7f4c00 >> 0x1f & 3U)) >> 2) + 1;
    fStack_10c = (float)var_120h / ((float)var_120h + *(float *)(iVar7 * 4 + 0x665e68));
    fcn_00547670();
    piVar11 = &var_108h;
    for (iVar7 = 0x21; iVar7 != 0; iVar7 = iVar7 + -1) {
        *piVar11 = 0;
        piVar11 = piVar11 + 1;
    }
    piVar11 = &var_84h;
    for (iVar7 = 0x21; iVar7 != 0; iVar7 = iVar7 + -1) {
        *piVar11 = 0;
        piVar11 = piVar11 + 1;
    }
    iVar7 = 0x100;
    puVar12 = *(u8 **)0x90e094;
    do {
        if ((*puVar12 != 0) && (uVar16 = *(u8 *)((u32)*puVar12 * 0x24d + *(i32 *)0x868050), uVar16 < 0x21)
           ) {
            (&var_108h)[uVar16] = (&var_108h)[uVar16] + 1;
            uVar5 = *(u2 *)(puVar12 + 0x27);
            if ((uVar5 == 0xffff) || (uVar5 == **(u2 **)0x773da8)) {
                (&var_84h)[uVar16] = (&var_84h)[uVar16] + 1;
            } else if (uVar16 == 7) {
                if (*(char *)((u32)uVar5 * 0x21c + 0x7f4cac) == '\0') {
                    var_124h = var_124h + 1;
                } else {
                    iVar10 = iVar10 + 1;
                }
            }
        }
        iVar23 = var_b8h;
        iVar21 = var_e4h;
        iVar20 = var_e8h;
        iVar14 = var_f4h;
        puVar12 = puVar12 + 0xa9;
        iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    uVar6 = *(i32 *)0x7f4c00 / 5;
    iVar7 = *(i32 *)0x7f4c00 % 5;
    var_114h = iVar10;
    if (iVar7 != 1) {
        if (iVar7 == 2) {
            if (var_c0h < 1) {
                var_11ch = 0;
            } else {
                var_11ch = (i32)((float)iStack_3c / (float)var_c0h);
            }
            if (var_b4h < 1) {
                var_114h = 0;
            } else {
                var_114h = (i32)((float)iStack_30 / (float)var_b4h);
            }
            if (var_b8h < 1) {
                var_118h = 0;
            } else {
                var_118h = (i32)((float)iStack_34 / (float)var_b8h);
            }
            if (var_d0h < 1) {
                fVar3 = 0.0;
            } else {
                fVar3 = (float)iStack_4c / (float)var_d0h;
            }
            uVar15 = 0;
            uVar9 = 0;
            var_124h = 0;
            uVar6 = var_d0h;
            if ((var_c0h < 3) || (uVar6 = (u32)((float)var_11ch < 0.5) << 8, (float)var_11ch < 0.5 == 0)) {
                uVar15 = 1;
                var_124h = 1;
                if (var_c0h == 0) {
                    uVar9 = 1;
                }
            }
            if (((var_b4h < 3) || (uVar6 = (u32)((float)var_114h < 0.5) << 8, (float)var_114h < 0.5 == 0)) &&
               (uVar15 = uVar15 | 2, var_124h = uVar15, var_b4h == 0)) {
                uVar9 = uVar9 | 2;
            }
            if (((var_b8h < 3) || (uVar6 = (u32)((float)var_118h < 0.5) << 8, (float)var_118h < 0.5 == 0)) &&
               (uVar15 = uVar15 | 4, var_124h = uVar15, var_b8h == 0)) {
                uVar9 = uVar9 | 4;
            }
            if (((var_d0h < 3) || (uVar6 = (u32)(fVar3 < 0.5) << 8, fVar3 < 0.5 == 0)) &&
               (uVar15 = uVar15 | 8, var_124h = uVar15, var_d0h == 0)) {
                uVar9 = uVar9 | 8;
            }
            uVar4 = uVar9;
            if (uVar9 == 0) {
                Var18 = (x87)fcn_0042e450();
                Var2 = (x87)fStack_10c;
                if (Var2 < Var18) {
                    return (u32)(u2)((u2)(Var18 < Var2) << 8 | (u2)(Var18 == Var2) << 0xe);
                }
                uVar5 = fcn_0042e410(4);
                uVar8 = (u32)uVar5;
                uVar6 = 4;
                do {
                    if ((uVar15 & 1 << ((u8)uVar8 & 0x1f)) != 0) {
                        uVar9 = 1 << ((u8)uVar8 & 0x1f);
                        uVar4 = uVar9;
                        break;
                    }
                    uVar6 = uVar6 - 1;
                    uVar8 = uVar8 + 1 & 0x80000003;
                    if ((i32)uVar8 < 0) {
                        uVar8 = (uVar8 - 1 | 0xfffffffc) + 1;
                    }
                    uVar9 = uVar15;
                    uVar4 = var_124h;
                } while (uVar6 != 0);
            }
            var_124h = uVar4;
            iVar7 = 0;
            iVar10 = *(i32 *)0x868050;
code_r0x00547d98:
            if (uVar9 == 0) {
                return uVar6;
            }
            uVar6 = 1 << ((u8)iVar7 & 0x1f) & uVar9;
            puVar12 = *(u8 **)0x90e094;
            if (uVar6 == 1) {
                if (2 < var_c0h) {
                    iVar7 = 0;
                    uVar6 = 1;
                    do {
                        if (*puVar12 != 0) {
                            uVar9 = (u32)*puVar12;
                            cVar1 = *(char *)(uVar9 + iVar10 + uVar9 * 0x24c);
                            uVar6 = CONCAT31((u32)(uVar9 * 0x93 >> 8), cVar1);
                            if (cVar1 == '\x12') {
                                uVar5 = *(u2 *)(puVar12 + 0x27);
                                uVar6 = (u32)uVar5;
                                if ((uVar5 == 0xffff) || (uVar5 == **(u2 **)0x773da8)) goto code_r0x00547e31;
                            }
                        }
                        iVar7 = iVar7 + 1;
                        puVar12 = puVar12 + 0xa9;
                        if (0xff < iVar7) {
                            return uVar6;
                        }
                    } while( 1 );
                }
                iVar10 = 0x29;
                iVar14 = fcn_0050d170();
                iVar14 = iVar14 * 2;
                iVar10 = fcn_00507400(1, 1, iVar10);
                goto code_r0x00548065;
            }
            if (uVar6 == 2) {
                if (2 < var_b4h) {
                    iVar7 = 0;
                    uVar6 = 2;
                    do {
                        if (*puVar12 != 0) {
                            uVar9 = (u32)*puVar12;
                            cVar1 = *(char *)(uVar9 + iVar10 + uVar9 * 0x24c);
                            uVar6 = CONCAT31((u32)(uVar9 * 0x93 >> 8), cVar1);
                            if (cVar1 == '\x15') {
                                uVar5 = *(u2 *)(puVar12 + 0x27);
                                uVar6 = (u32)uVar5;
                                if ((uVar5 == 0xffff) || (uVar5 == **(u2 **)0x773da8)) goto code_r0x00547ede;
                            }
                        }
                        iVar7 = iVar7 + 1;
                        puVar12 = puVar12 + 0xa9;
                        if (0xff < iVar7) {
                            return uVar6;
                        }
                    } while( 1 );
                }
                iVar10 = 0x32;
                iVar14 = fcn_0050d170();
                iVar14 = iVar14 * 2;
                iVar10 = fcn_00507400(3, 1, iVar10);
                goto code_r0x00548065;
            }
            if (uVar6 == 4) {
                if (2 < iVar23) {
                    iVar7 = 0;
                    uVar6 = 4;
                    do {
                        if (*puVar12 != 0) {
                            uVar9 = (u32)*puVar12;
                            cVar1 = *(char *)(uVar9 + iVar10 + uVar9 * 0x24c);
                            uVar6 = CONCAT31((u32)(uVar9 * 0x93 >> 8), cVar1);
                            if (cVar1 == '\x14') {
                                uVar5 = *(u2 *)(puVar12 + 0x27);
                                uVar6 = (u32)uVar5;
                                if ((uVar5 == 0xffff) || (uVar5 == **(u2 **)0x773da8)) goto code_r0x00547f86;
                            }
                        }
                        iVar7 = iVar7 + 1;
                        puVar12 = puVar12 + 0xa9;
                        if (0xff < iVar7) {
                            return uVar6;
                        }
                    } while( 1 );
                }
                iVar10 = 0x2f;
                iVar14 = fcn_0050d170();
                iVar14 = iVar14 * 2;
                iVar10 = fcn_00507400(2, 1, iVar10);
                goto code_r0x00548065;
            }
            if (uVar6 == 8) {
                if (2 < var_d0h) {
                    iVar7 = 0;
                    uVar6 = 8;
                    do {
                        if (*puVar12 != 0) {
                            uVar9 = (u32)*puVar12;
                            cVar1 = *(char *)(uVar9 + iVar10 + uVar9 * 0x24c);
                            uVar6 = CONCAT31((u32)(uVar9 * 0x93 >> 8), cVar1);
                            if (cVar1 == '\x0e') {
                                uVar5 = *(u2 *)(puVar12 + 0x27);
                                uVar6 = (u32)uVar5;
                                if ((uVar5 == 0xffff) || (uVar5 == **(u2 **)0x773da8)) goto code_r0x00548036;
                            }
                        }
                        iVar7 = iVar7 + 1;
                        puVar12 = puVar12 + 0xa9;
                        if (0xff < iVar7) {
                            return uVar6;
                        }
                    } while( 1 );
                }
                iVar10 = 0x21;
                iVar14 = fcn_0050d170();
                iVar14 = iVar14 * 2;
                iVar10 = fcn_00507400(5, 1, iVar10);
                goto code_r0x00548065;
            }
            goto code_r0x00548107;
        }
        if (iVar7 == 3) {
            if (var_e8h < 1) {
                var_11ch = 0;
            } else {
                var_11ch = (i32)((float)iStack_64 / (float)var_e8h);
            }
            if (var_b0h < 1) {
                fVar3 = 0.0;
            } else {
                fVar3 = (float)iStack_2c / (float)var_b0h;
            }
            uVar15 = 0;
            uVar9 = 0;
            var_124h = 0;
            uVar6 = var_b0h;
            if ((var_e8h < 3) || (uVar6 = (u32)((float)var_11ch < 0.5) << 8, (float)var_11ch < 0.5 == 0)) {
                uVar15 = 1;
                var_124h = 1;
                if (var_e8h == 0) {
                    uVar9 = 1;
                }
            }
            if (((var_b0h < 3) || (uVar6 = (u32)(fVar3 < 0.5) << 8, fVar3 < 0.5 == 0)) &&
               (uVar15 = uVar15 | 2, var_124h = uVar15, var_b0h == 0)) {
                uVar9 = uVar9 | 2;
            }
            uVar4 = uVar9;
            if (uVar9 == 0) {
                Var18 = (x87)fcn_0042e450();
                Var2 = (x87)fStack_10c;
                if (Var2 < Var18) {
                    return (u32)(u2)((u2)(Var18 < Var2) << 8 | (u2)(Var18 == Var2) << 0xe);
                }
                uVar5 = fcn_0042e410(2);
                uVar8 = (u32)uVar5;
                uVar6 = 2;
                do {
                    if ((uVar15 & 1 << ((u8)uVar8 & 0x1f)) != 0) {
                        uVar9 = 1 << ((u8)uVar8 & 0x1f);
                        uVar4 = uVar9;
                        break;
                    }
                    uVar6 = uVar6 - 1;
                    uVar8 = uVar8 + 1 & 0x80000001;
                    if ((i32)uVar8 < 0) {
                        uVar8 = (uVar8 - 1 | 0xfffffffe) + 1;
                    }
                    uVar9 = uVar15;
                    uVar4 = var_124h;
                } while (uVar6 != 0);
            }
            var_124h = uVar4;
            iVar7 = 0;
            iVar10 = *(i32 *)0x868050;
code_r0x00548238:
            if (uVar9 == 0) {
                return uVar6;
            }
            uVar6 = 1 << ((u8)iVar7 & 0x1f) & uVar9;
            puVar12 = *(u8 **)0x90e094;
            if (uVar6 == 1) {
                if (2 < iVar20) {
                    iVar7 = 0;
                    uVar6 = 1;
                    do {
                        if (*puVar12 != 0) {
                            uVar9 = (u32)*puVar12;
                            cVar1 = *(char *)(uVar9 + iVar10 + uVar9 * 0x24c);
                            uVar6 = CONCAT31((u32)(uVar9 * 0x93 >> 8), cVar1);
                            if (cVar1 == '\b') {
                                uVar5 = *(u2 *)(puVar12 + 0x27);
                                uVar6 = (u32)uVar5;
                                if ((uVar5 == 0xffff) || (uVar5 == **(u2 **)0x773da8)) goto code_r0x005482cf;
                            }
                        }
                        iVar7 = iVar7 + 1;
                        puVar12 = puVar12 + 0xa9;
                        if (0xff < iVar7) {
                            return uVar6;
                        }
                    } while( 1 );
                }
                iVar10 = 0x17;
                iVar14 = fcn_0050d170();
                iVar14 = iVar14 * 2;
                iVar10 = fcn_00507400(6, 1, iVar10);
                goto code_r0x005483b1;
            }
            if (uVar6 == 2) {
                if (2 < var_b0h) {
                    iVar7 = 0;
                    uVar6 = 2;
                    do {
                        if (*puVar12 != 0) {
                            uVar9 = (u32)*puVar12;
                            cVar1 = *(char *)(uVar9 + iVar10 + uVar9 * 0x24c);
                            uVar6 = CONCAT31((u32)(uVar9 * 0x93 >> 8), cVar1);
                            if (cVar1 == '\x16') {
                                uVar5 = *(u2 *)(puVar12 + 0x27);
                                uVar6 = (u32)uVar5;
                                if ((uVar5 == 0xffff) || (uVar5 == **(u2 **)0x773da8)) goto code_r0x00548382;
                            }
                        }
                        iVar7 = iVar7 + 1;
                        puVar12 = puVar12 + 0xa9;
                        if (0xff < iVar7) {
                            return uVar6;
                        }
                    } while( 1 );
                }
                iVar10 = 0x35;
                iVar14 = fcn_0050d170();
                iVar14 = iVar14 * 2;
                iVar10 = fcn_00507400(4, 1, iVar10);
                goto code_r0x005483b1;
            }
            goto code_r0x00548453;
        }
        if (iVar7 == 0) {
            if (var_e4h < 1) {
                var_110h = 0;
            } else {
                var_110h = (i32)((float)iStack_60 / (float)var_e4h);
            }
            if (var_f4h < 1) {
                var_120h = 0;
            } else {
                var_120h = (i32)((float)iStack_70 / (float)var_f4h);
            }
            uVar15 = 0;
            var_118h = 0;
            uVar6 = 0;
            uVar9 = fcn_0042e410(2);
            var_11ch = uVar9 & 0xffff;
            if ((iVar21 < 2) || (0.5 <= (float)var_110h)) {
                uVar15 = 1;
                var_118h = 1;
                if (iVar21 == 0) {
                    uVar6 = 1;
                }
            }
            if (((var_ech < 2) || ((var_ech < 3 && ((var_124h == 0 || (var_114h == 0)))))) &&
               (uVar15 = uVar15 | 2, var_118h = uVar15, var_ech == 0)) {
                uVar6 = uVar6 | 2;
            }
            uVar9 = var_ech;
            if (((iVar14 < 2) || (uVar9 = (u32)((float)var_120h < 0.5) << 8, (float)var_120h < 0.5 == 0)) &&
               (uVar15 = uVar15 | 4, var_118h = uVar15, iVar14 == 0)) {
                uVar6 = uVar6 | 4;
            }
            uVar4 = uVar6;
            if (uVar6 == 0) {
                Var18 = (x87)fcn_0042e450();
                Var2 = (x87)fStack_10c;
                if (Var2 < Var18) {
                    return (u32)(u2)((u2)(Var18 < Var2) << 8 | (u2)(Var18 == Var2) << 0xe);
                }
                uVar9 = fcn_0042e410(3);
                uVar9 = uVar9 & 0xffff;
                iVar10 = 3;
                do {
                    uVar6 = uVar15;
                    uVar4 = var_118h;
                    if ((uVar15 & 1 << ((u8)uVar9 & 0x1f)) != 0) break;
                    iVar10 = iVar10 + -1;
                    uVar9 = (i32)(uVar9 + 1) % 3;
                } while (iVar10 != 0);
            }
            var_118h = uVar4;
            iVar10 = 0;
code_r0x0054859d:
            if (uVar6 == 0) {
                return uVar9;
            }
            uVar9 = 1 << ((u8)iVar10 & 0x1f) & uVar6;
            puVar12 = *(u8 **)0x90e094;
            if (uVar9 == 1) {
                if (1 < iVar21) {
                    iVar10 = 0;
                    uVar6 = 1;
                    do {
                        if (*puVar12 != 0) {
                            uVar9 = (u32)*puVar12;
                            iVar7 = uVar9 + *(i32 *)0x868050;
                            cVar1 = *(char *)(iVar7 + uVar9 * 0x24c);
                            uVar6 = CONCAT31((u32)(uVar9 * 0x93 >> 8), cVar1);
                            if (cVar1 == '\t') {
                                uVar5 = *(u2 *)(puVar12 + 0x27);
                                uVar6 = (u32)uVar5;
                                if ((uVar5 == 0xffff) || (uVar5 == **(u2 **)0x773da8)) goto code_r0x00548643;
                            }
                        }
                        iVar10 = iVar10 + 1;
                        puVar12 = puVar12 + 0xa9;
                        if (0xff < iVar10) {
                            return uVar6;
                        }
                    } while( 1 );
                }
                iVar7 = 0x1a;
                iVar14 = fcn_0050d170();
                iVar14 = iVar14 * 2;
                iVar7 = fcn_00507400(8, 1, iVar7);
                goto code_r0x00548814;
            }
            if (uVar9 == 2) {
                if (var_124h < var_114h) {
                    var_11ch = 0;
                } else if (var_114h < var_124h) {
                    var_11ch = 1;
                }
                iVar10 = 0;
                do {
                    if (*puVar12 != 0) {
                        uVar6 = (u32)*puVar12;
                        iVar7 = uVar6 + *(i32 *)0x868050;
                        if ((*(char *)(iVar7 + uVar6 * 0x24c) == '\a') &&
                           ((*(u2 *)(puVar12 + 0x27) == 0xffff ||
                            (*(u2 *)(puVar12 + 0x27) == **(u2 **)0x773da8)))) {
                            iVar14 = fcn_0050cf50((i32)puVar12);
                            iVar14 = iVar14 * 2;
                            iVar7 = fcn_00507400(7, (u32)*(u8 *)(iVar7 + uVar6 * 0x24c + 0x247) * 2 + -1, 
                                                 (i32)puVar12);
                            if (iVar10 < 0x100) goto code_r0x00548814;
                            break;
                        }
                    }
                    iVar10 = iVar10 + 1;
                    puVar12 = puVar12 + 0xa9;
                } while (iVar10 < 0x100);
                if (var_ech < 2) {
                    iVar7 = 0x14;
                    iVar14 = fcn_0050d170();
                    iVar14 = iVar14 * 2;
                    iVar7 = fcn_00507400(7, 1, iVar7);
                } else {
                    iVar7 = 0x15;
                    iVar14 = fcn_0050d170();
                    iVar14 = iVar14 * 2;
                    iVar7 = fcn_00507400(7, 3, iVar7);
                }
                goto code_r0x00548814;
            }
            if (uVar9 == 4) {
                if (0 < var_f4h) {
                    iVar10 = 0;
                    uVar6 = 4;
                    do {
                        if (*puVar12 != 0) {
                            uVar9 = (u32)*puVar12;
                            iVar7 = uVar9 + *(i32 *)0x868050;
                            cVar1 = *(char *)(iVar7 + uVar9 * 0x24c);
                            uVar6 = CONCAT31((u32)(uVar9 * 0x93 >> 8), cVar1);
                            if (cVar1 == '\x05') {
                                uVar5 = *(u2 *)(puVar12 + 0x27);
                                uVar6 = (u32)uVar5;
                                if ((uVar5 == 0xffff) || (uVar5 == **(u2 **)0x773da8)) goto code_r0x005487e3;
                            }
                        }
                        iVar10 = iVar10 + 1;
                        puVar12 = puVar12 + 0xa9;
                        if (0xff < iVar10) {
                            return uVar6;
                        }
                    } while( 1 );
                }
                iVar7 = 0xe;
                iVar14 = fcn_0050d170();
                iVar14 = iVar14 * 2;
                iVar7 = fcn_00507400(9, 1, iVar7);
                goto code_r0x00548814;
            }
            goto code_r0x005488be;
        }
        if (iVar7 != 4) {
            return uVar6;
        }
        if (var_88h < 1) {
            var_120h = 0;
        } else {
            var_120h = (i32)((float)iStack_4 / (float)var_88h);
        }
        if (var_8ch < 1) {
            var_110h = 0;
        } else {
            var_110h = (i32)((float)iStack_8 / (float)var_8ch);
        }
        if (var_94h < 1) {
            fVar3 = 0.0;
        } else {
            fVar3 = (float)iStack_10 / (float)var_94h;
        }
        uVar15 = 0;
        uVar9 = 0;
        var_124h = 0;
        if ((var_88h < 3) || (uVar6 = (u32)((float)var_120h < 0.5) << 8, (float)var_120h < 0.5 == 0)) {
            uVar15 = 1;
            var_124h = 1;
            if (var_88h == 0) {
                uVar9 = 1;
            }
        }
        if (((var_8ch < 3) || (uVar6 = (u32)((float)var_110h < 0.5) << 8, (float)var_110h < 0.5 == 0)) &&
           (uVar15 = uVar15 | 2, var_124h = uVar15, var_8ch == 0)) {
            uVar9 = uVar9 | 2;
        }
        if (((var_94h < 3) || (uVar6 = (u32)(fVar3 < 0.5) << 8, fVar3 < 0.5 == 0)) &&
           (uVar15 = uVar15 | 4, var_124h = uVar15, var_94h == 0)) {
            uVar9 = uVar9 | 4;
        }
        if (uVar9 == 0) {
            Var18 = (x87)fcn_0042e450();
            Var2 = (x87)fStack_10c;
            if (Var2 < Var18) {
                return (u32)(u2)((u2)(Var18 < Var2) << 8 | (u2)(Var18 == Var2) << 0xe);
            }
            uVar5 = fcn_0042e410(3);
            uVar9 = (u32)uVar5;
            iVar10 = 3;
            do {
                uVar6 = 1 << ((u8)uVar9 & 0x1f);
                if ((uVar15 & uVar6) != 0) {
                    var_124h = 1 << ((u8)uVar9 & 0x1f);
                    iVar10 = 0;
                    uVar9 = var_124h;
                    goto code_r0x00548a38;
                }
                uVar6 = (i32)(uVar9 + 1) / 3;
                uVar9 = (i32)(uVar9 + 1) % 3;
                iVar10 = iVar10 + -1;
            } while (iVar10 != 0);
            iVar10 = 0;
            uVar9 = uVar15;
        } else {
            iVar10 = 0;
            var_124h = uVar9;
        }
code_r0x00548a38:
        if (uVar9 == 0) {
            return uVar6;
        }
        uVar9 = 0;
        uVar6 = 1 << ((u8)iVar10 & 0x1f) & var_124h;
        if (uVar6 == 1) {
            uVar5 = fcn_0042e410(2);
            uVar9 = (u32)uVar5;
            var_120h = uVar9;
            if (2 < var_88h) {
                iVar10 = 0;
                uVar6 = var_88h;
                puVar12 = *(u8 **)0x90e094;
                do {
                    if (*puVar12 != 0) {
                        uVar9 = (u32)*puVar12;
                        iVar7 = uVar9 + *(i32 *)0x868050;
                        cVar1 = *(char *)(iVar7 + uVar9 * 0x24c);
                        uVar6 = CONCAT31((u32)(uVar9 * 0x93 >> 8), cVar1);
                        if (cVar1 == ' ') {
                            uVar5 = *(u2 *)(puVar12 + 0x27);
                            uVar6 = (u32)uVar5;
                            if ((uVar5 == 0xffff) || (uVar5 == **(u2 **)0x773da8)) goto code_r0x00548afa;
                        }
                    }
                    iVar10 = iVar10 + 1;
                    puVar12 = puVar12 + 0xa9;
                    if (0xff < iVar10) {
                        return uVar6;
                    }
                } while( 1 );
            }
            iVar7 = 0x51;
            iVar14 = fcn_0050d170();
            iVar14 = iVar14 * 2;
            iVar7 = fcn_00507400(0xf, 1, iVar7);
            goto code_r0x00548ca6;
        }
        puVar12 = *(u8 **)0x90e094;
        if (uVar6 == 2) {
            if (2 < var_8ch) {
                iVar10 = 0;
                uVar6 = 2;
                do {
                    if (*puVar12 != 0) {
                        uVar15 = (u32)*puVar12;
                        iVar7 = *(i32 *)0x868050 + uVar15;
                        cVar1 = *(char *)(iVar7 + uVar15 * 0x24c);
                        uVar6 = CONCAT31((u32)(uVar15 * 0x93 >> 8), cVar1);
                        if (cVar1 == '\x1f') {
                            uVar5 = *(u2 *)(puVar12 + 0x27);
                            uVar6 = (u32)uVar5;
                            if ((uVar5 == 0xffff) || (uVar5 == **(u2 **)0x773da8)) goto code_r0x00548bbe;
                        }
                    }
                    iVar10 = iVar10 + 1;
                    puVar12 = puVar12 + 0xa9;
                    if (0xff < iVar10) {
                        return uVar6;
                    }
                } while( 1 );
            }
            iVar7 = 0x4e;
            iVar14 = fcn_0050d170();
            iVar14 = iVar14 * 2;
            iVar7 = fcn_00507400(0xe, 1, iVar7);
            goto code_r0x00548ca6;
        }
        if (uVar6 == 4) {
            if (2 < var_94h) {
                iVar10 = 0;
                uVar6 = 4;
                do {
                    if (*puVar12 != 0) {
                        uVar15 = (u32)*puVar12;
                        iVar7 = *(i32 *)0x868050 + uVar15;
                        cVar1 = *(char *)(iVar7 + uVar15 * 0x24c);
                        uVar6 = CONCAT31((u32)(uVar15 * 0x93 >> 8), cVar1);
                        if (cVar1 == '\x1d') {
                            uVar5 = *(u2 *)(puVar12 + 0x27);
                            uVar6 = (u32)uVar5;
                            if ((uVar5 == 0xffff) || (uVar5 == **(u2 **)0x773da8)) goto code_r0x00548c77;
                        }
                    }
                    iVar10 = iVar10 + 1;
                    puVar12 = puVar12 + 0xa9;
                    if (0xff < iVar10) {
                        return uVar6;
                    }
                } while( 1 );
            }
            iVar7 = 0x48;
            iVar14 = fcn_0050d170();
            iVar14 = iVar14 * 2;
            iVar7 = fcn_00507400(0xd, 1, iVar7);
            goto code_r0x00548ca6;
        }
        goto code_r0x00548d36;
    }
    iVar10 = var_c8h - var_44h;
    iVar7 = var_f8h - var_74h;
    iVar14 = var_bch - var_38h;
    var_124h = 0;
    uVar6 = (u32)(iVar7 < 3);
    uVar16 = iVar7 == 0;
    if (iVar14 < 3) {
        uVar6 = uVar6 | 2;
    }
    if (iVar14 == 0) {
        uVar16 = uVar16 | 2;
    }
    if (iVar10 < 3) {
        uVar6 = uVar6 | 4;
    }
    if (iVar10 == 0) {
        uVar16 = uVar16 | 4;
    }
    if (uVar16 == 0) {
        Var18 = (x87)fcn_0042e450();
        Var2 = (x87)fStack_10c;
        if (Var2 < Var18) {
            return (u32)(u2)((u2)(Var18 < Var2) << 8 | (u2)(Var18 == Var2) << 0xe);
        }
        iVar20 = iVar7 + iVar10;
        iVar21 = iVar14 * 2;
        bVar17 = iVar20 + iVar14 * -2 < 0;
        if (iVar20 != iVar21 && SBORROW4(iVar20, iVar21) == bVar17) {
            if ((uVar6 & 2) != 0) {
                var_124h = 2;
                goto code_r0x005479c1;
            }
            bVar17 = iVar20 + iVar14 * -2 < 0;
        }
        if (SBORROW4(iVar20, iVar21) == bVar17) {
            uVar16 = fcn_0042e410(3);
            var_124h = 1 << (uVar16 & 0x1f);
        } else if (iVar7 < iVar10) {
            if ((uVar6 & 1) != 0) {
                var_124h = 1;
            }
        } else if ((uVar6 & 4) != 0) {
            var_124h = 4;
        }
    } else {
        uVar5 = fcn_0042e410(3);
        uVar9 = (u32)uVar5;
        iVar10 = 3;
        do {
            if ((uVar6 & 1 << ((u8)uVar9 & 0x1f)) != 0) {
                var_124h = 1 << ((u8)uVar9 & 0x1f);
                uVar6 = var_124h;
                break;
            }
            uVar9 = (i32)(uVar9 + 1) % 3;
            iVar10 = iVar10 + -1;
        } while (iVar10 != 0);
    }
code_r0x005479c1:
    if ((uVar6 & var_124h) != 0) {
        if (var_124h == 1) {
            if (2 < var_f8h) {
                iVar10 = 0;
                uVar6 = 1;
                puVar12 = *(u8 **)0x90e094;
                do {
                    if (*puVar12 != 0) {
                        uVar9 = (u32)*puVar12;
                        iVar7 = uVar9 + *(i32 *)0x868050;
                        cVar1 = *(char *)(iVar7 + uVar9 * 0x24c);
                        uVar6 = CONCAT31((u32)(uVar9 * 0x93 >> 8), cVar1);
                        if (cVar1 == '\x04') {
                            uVar5 = *(u2 *)(puVar12 + 0x27);
                            uVar6 = (u32)uVar5;
                            if ((uVar5 == 0xffff) || (uVar5 == **(u2 **)0x773da8)) {
                                if (0xff < iVar10) {
                                    return uVar6;
                                }
                                iVar10 = fcn_0050cf50((i32)puVar12);
                                iVar10 = iVar10 * 2;
                                iVar7 = fcn_00507400(0xb, (u32)*(u8 *)(iVar7 + uVar9 * 0x24c + 0x247) * 2 + -1
                                                     , (i32)puVar12);
                                goto code_r0x00547b49;
                            }
                        }
                    }
                    iVar10 = iVar10 + 1;
                    puVar12 = puVar12 + 0xa9;
                    if (0xff < iVar10) {
                        return uVar6;
                    }
                } while( 1 );
            }
            iVar10 = fcn_0050d170(0xb);
            iVar7 = 6;
        } else if (var_124h == 2) {
            if (2 < var_bch) {
                iVar10 = 0;
                uVar6 = 2;
                puVar12 = *(u8 **)0x90e094;
                do {
                    if (*puVar12 != 0) {
                        uVar9 = (u32)*puVar12;
                        iVar7 = uVar9 + *(i32 *)0x868050;
                        cVar1 = *(char *)(iVar7 + uVar9 * 0x24c);
                        uVar6 = CONCAT31((u32)(uVar9 * 0x93 >> 8), cVar1);
                        if (cVar1 == '\x13') {
                            uVar5 = *(u2 *)(puVar12 + 0x27);
                            uVar6 = (u32)uVar5;
                            if ((uVar5 == 0xffff) || (uVar5 == **(u2 **)0x773da8)) {
                                if (0xff < iVar10) {
                                    return uVar6;
                                }
                                iVar10 = fcn_0050cf50((i32)puVar12);
                                iVar10 = iVar10 * 2;
                                iVar7 = fcn_00507400(10, (u32)*(u8 *)(iVar7 + uVar9 * 0x24c + 0x247) * 2 + -1
                                                     , (i32)puVar12);
                                goto code_r0x00547b49;
                            }
                        }
                    }
                    iVar10 = iVar10 + 1;
                    puVar12 = puVar12 + 0xa9;
                    if (0xff < iVar10) {
                        return uVar6;
                    }
                } while( 1 );
            }
            iVar10 = fcn_0050d170(0x2c);
            iVar7 = 0x39;
        } else {
            iVar7 = 0x2d;
            iVar10 = fcn_0050d170(0x27);
        }
        iVar10 = iVar10 * 2;
code_r0x00547b49:
        iVar23 = 0;
        iVar21 = 0;
        iVar20 = -1;
        iVar14 = fcn_0042e410(4);
        iVar7 = fcn_004c4fc0(4, -1, -1, iVar14 + 0xf, iVar20, iVar7, iVar21, iVar23);
        if (iVar7 != -1) {
            while (iVar14 = fcn_004c4450(iVar7), iVar14 == 0) {
                fcn_00535960();
            }
        }
        var_124h = fcn_004c4450(iVar7);
        if (var_124h == 1) {
            var_120h = 2;
            iVar7 = fcn_004c4480(iVar7);
            uVar19 = *(u4 *)(iVar7 + 4);
            iVar14 = -1;
            fcn_004c5150(uVar19, 0xffffffff, *(u1 *)0x773d75, iVar10);
            fcn_004c4510(iVar7, *(i32 *)(iVar7 + 4), uVar19, iVar14);
            fcn_004c4570(1, 1, 0xd, (i32)&var_120h, iVar14);
            auStack_9c[0] = 0x16;
            piVar11 = (i32 *)0xaed220;
            piVar13 = &var_8ch;
            for (iVar10 = 0x1f; iVar10 != 0; iVar10 = iVar10 + -1) {
                *piVar13 = *piVar11;
                piVar11 = piVar11 + 1;
                piVar13 = piVar13 + 1;
            }
            uStack_ac = 0x4c5387;
            uVar6 = fcn_004c4330((i32)auStack_9c, unaff_EDI, unaff_ESI);
            return uVar6;
        }
    }
    return var_124h;
code_r0x00547e31:
    if (0xff < iVar7) {
        return uVar6;
    }
    iVar14 = fcn_0050cf50((i32)puVar12);
    iVar10 = (u32)*(u8 *)(uVar9 + iVar10 + uVar9 * 0x24c + 0x247) * 2 + -1;
    iVar20 = 1;
    goto code_r0x0054805b;
code_r0x00547ede:
    if (0xff < iVar7) {
        return uVar6;
    }
    iVar14 = fcn_0050cf50((i32)puVar12);
    iVar10 = (u32)*(u8 *)(uVar9 + iVar10 + uVar9 * 0x24c + 0x247) * 2 + -1;
    iVar20 = 3;
    goto code_r0x0054805b;
code_r0x00547f86:
    if (0xff < iVar7) {
        return uVar6;
    }
    iVar14 = fcn_0050cf50((i32)puVar12);
    iVar10 = (u32)*(u8 *)(uVar9 + iVar10 + uVar9 * 0x24c + 0x247) * 2 + -1;
    iVar20 = 2;
    goto code_r0x0054805b;
code_r0x00548036:
    if (0xff < iVar7) {
        return uVar6;
    }
    iVar14 = fcn_0050cf50((i32)puVar12);
    iVar10 = (u32)*(u8 *)(uVar9 + iVar10 + uVar9 * 0x24c + 0x247) * 2 + -1;
    iVar20 = 5;
code_r0x0054805b:
    iVar14 = iVar14 * 2;
    iVar10 = fcn_00507400(iVar20, iVar10, (i32)puVar12);
code_r0x00548065:
    iVar20 = fcn_0042e410(2);
    iVar22 = 0;
    iVar23 = -1;
    iVar21 = fcn_0042e410(4);
    iVar20 = fcn_004c4fc0(4, -1, -1, iVar21 + 0xf, iVar23, iVar10, iVar22, iVar20);
    if (iVar20 != -1) {
        while (iVar10 = fcn_004c4450(iVar20), iVar10 == 0) {
            fcn_00535960();
        }
    }
    uVar6 = fcn_004c4450(iVar20);
    iVar10 = *(i32 *)0x868050;
    if (uVar6 == 1) {
        var_120h = 2;
        iVar10 = fcn_004c4480(iVar20);
        uVar19 = *(u4 *)(iVar10 + 4);
        iVar20 = -1;
        fcn_004c5150(uVar19, 0xffffffff, *(u1 *)0x773d75, iVar14);
        fcn_004c4510(iVar10, *(i32 *)(iVar10 + 4), uVar19, iVar20);
        fcn_004c4570(1, 1, 0xd, (i32)&var_120h, iVar20);
        uVar6 = fcn_004c5360();
        iVar10 = *(i32 *)0x868050;
    }
code_r0x00548107:
    iVar7 = iVar7 + 1;
    iVar23 = var_b8h;
    uVar9 = var_124h;
    if (3 < iVar7) {
        return uVar6;
    }
    goto code_r0x00547d98;
code_r0x005482cf:
    if (0xff < iVar7) {
        return uVar6;
    }
    iVar14 = fcn_0050cf50((i32)puVar12);
    uVar16 = *(u8 *)(uVar9 + iVar10 + uVar9 * 0x24c + 0x247);
    iVar10 = 6;
    goto code_r0x005483a7;
code_r0x00548382:
    if (0xff < iVar7) {
        return uVar6;
    }
    iVar14 = fcn_0050cf50((i32)puVar12);
    uVar16 = *(u8 *)(uVar9 + iVar10 + uVar9 * 0x24c + 0x247);
    iVar10 = 4;
code_r0x005483a7:
    iVar14 = iVar14 * 2;
    iVar10 = fcn_00507400(iVar10, (u32)uVar16 * 2 + -1, (i32)puVar12);
code_r0x005483b1:
    iVar20 = fcn_0042e410(2);
    iVar22 = 0;
    iVar23 = -1;
    iVar21 = fcn_0042e410(4);
    iVar20 = fcn_004c4fc0(4, -1, -1, iVar21 + 0xf, iVar23, iVar10, iVar22, iVar20);
    if (iVar20 != -1) {
        while (iVar10 = fcn_004c4450(iVar20), iVar10 == 0) {
            fcn_00535960();
        }
    }
    uVar6 = fcn_004c4450(iVar20);
    iVar10 = *(i32 *)0x868050;
    if (uVar6 == 1) {
        var_120h = 2;
        iVar10 = fcn_004c4480(iVar20);
        uVar19 = *(u4 *)(iVar10 + 4);
        iVar20 = -1;
        fcn_004c5150(uVar19, 0xffffffff, *(u1 *)0x773d75, iVar14);
        fcn_004c4510(iVar10, *(i32 *)(iVar10 + 4), uVar19, iVar20);
        fcn_004c4570(1, 1, 0xd, (i32)&var_120h, iVar20);
        uVar6 = fcn_004c5360();
        iVar10 = *(i32 *)0x868050;
    }
code_r0x00548453:
    iVar7 = iVar7 + 1;
    uVar9 = var_124h;
    iVar20 = var_e8h;
    if (1 < iVar7) {
        return uVar6;
    }
    goto code_r0x00548238;
code_r0x00548643:
    if (0xff < iVar10) {
        return uVar6;
    }
    iVar14 = fcn_0050cf50((i32)puVar12);
    uVar16 = *(u8 *)(iVar7 + uVar9 * 0x24c + 0x247);
    iVar7 = 8;
    goto code_r0x00548808;
code_r0x005487e3:
    if (0xff < iVar10) {
        return uVar6;
    }
    iVar14 = fcn_0050cf50((i32)puVar12);
    uVar16 = *(u8 *)(iVar7 + uVar9 * 0x24c + 0x247);
    iVar7 = 9;
code_r0x00548808:
    iVar14 = iVar14 * 2;
    iVar7 = fcn_00507400(iVar7, (u32)uVar16 * 2 + -1, (i32)puVar12);
code_r0x00548814:
    iVar20 = fcn_0042e410(2);
    iVar22 = 0;
    iVar23 = -1;
    iVar21 = fcn_0042e410(4);
    iVar7 = fcn_004c4fc0(4, -1, -1, iVar21 + 0xf, iVar23, iVar7, iVar22, iVar20);
    if (iVar7 != -1) {
        while (iVar20 = fcn_004c4450(iVar7), iVar20 == 0) {
            fcn_00535960();
        }
    }
    uVar9 = fcn_004c4450(iVar7);
    if (uVar9 == 1) {
        var_120h = 2;
        iVar7 = fcn_004c4480(iVar7);
        uVar19 = *(u4 *)(iVar7 + 4);
        iVar20 = -1;
        fcn_004c5150(uVar19, 0xffffffff, *(u1 *)0x773d75, iVar14);
        fcn_004c4510(iVar7, *(i32 *)(iVar7 + 4), uVar19, iVar20);
        piVar11 = &var_120h;
        fcn_004c4570(1, 1, 0xd, (i32)piVar11, iVar20);
        fcn_004c4570(1, 1, 0xc, (i32)&var_11ch, (i32)piVar11);
        uVar9 = fcn_004c5360();
    }
code_r0x005488be:
    iVar10 = iVar10 + 1;
    iVar21 = var_e4h;
    uVar6 = var_118h;
    if (2 < iVar10) {
        return uVar9;
    }
    goto code_r0x0054859d;
code_r0x00548afa:
    if (0xff < iVar10) {
        return uVar6;
    }
    iVar14 = fcn_0050cf50((i32)puVar12);
    iVar7 = fcn_00507400(0xf, (u32)*(u8 *)(iVar7 + uVar9 * 0x24c + 0x247) * 2 + -1, (i32)puVar12);
    uVar9 = var_120h;
    goto code_r0x00548ca3;
code_r0x00548bbe:
    if (0xff < iVar10) {
        return uVar6;
    }
    iVar14 = fcn_0050cf50((i32)puVar12);
    uVar16 = *(u8 *)(iVar7 + uVar15 * 0x24c + 0x247);
    iVar7 = 0xe;
    goto code_r0x00548c9c;
code_r0x00548c77:
    if (0xff < iVar10) {
        return uVar6;
    }
    iVar14 = fcn_0050cf50((i32)puVar12);
    uVar16 = *(u8 *)(iVar7 + uVar15 * 0x24c + 0x247);
    iVar7 = 0xd;
code_r0x00548c9c:
    iVar7 = fcn_00507400(iVar7, (u32)uVar16 * 2 + -1, (i32)puVar12);
code_r0x00548ca3:
    iVar14 = iVar14 * 2;
code_r0x00548ca6:
    iVar23 = 0;
    iVar21 = -1;
    iVar20 = fcn_0042e410(4);
    iVar7 = fcn_004c4fc0(4, -1, -1, iVar20 + 0xf, iVar21, iVar7, iVar23, uVar9);
    if (iVar7 != -1) {
        while (iVar20 = fcn_004c4450(iVar7), iVar20 == 0) {
            fcn_00535960();
        }
    }
    uVar6 = fcn_004c4450(iVar7);
    if (uVar6 == 1) {
        var_120h = 2;
        iVar7 = fcn_004c4480(iVar7);
        uVar19 = *(u4 *)(iVar7 + 4);
        iVar20 = -1;
        fcn_004c5150(uVar19, 0xffffffff, *(u1 *)0x773d75, iVar14);
        fcn_004c4510(iVar7, *(i32 *)(iVar7 + 4), uVar19, iVar20);
        fcn_004c4570(1, 1, 0xd, (i32)&var_120h, iVar20);
        uVar6 = fcn_004c5360();
    }
code_r0x00548d36:
    iVar10 = iVar10 + 1;
    uVar9 = var_124h;
    if (2 < iVar10) {
        return uVar6;
    }
    goto code_r0x00548a38;
}