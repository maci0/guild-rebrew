/*
 * Reconstruction of the native body at 0x00547770.
 *
 * Building-mix driven economic command selection. The function counts 256
 * building records by type and ownership, derives a command slot from the
 * world counter modulo five, applies randomised thresholds to pick one of the
 * counted groups, then creates or polls the request and serialises the
 * resulting command.
 *
 * The five case blocks share a shape: a mask of scarce-group bits, an optional
 * zero-count mask, a random pick against the threshold, then one command per
 * set bit.
 */

#include <string.h>

typedef int i32;
typedef unsigned int u32;
typedef unsigned short u2;
typedef unsigned char u8;
typedef unsigned int u4;

extern void *__cdecl m_alloc(u32 size, const char *tag);
extern void __cdecl m_FreeTracked(void *p);
extern void *__cdecl memset(void *p, int v, u32 n);
int __cdecl rand(void);

int __cdecl fcn_0042e410();
float __cdecl fcn_0042e450();
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

#define REC_SIZE 0xa9

#define FIND_REC(T)                                                          \
    rp = *(u8 **)0x90e094;                                                   \
    tb = *(u8 **)0x868050;                                                   \
    wp = *(u2 **)0x773da8;                                                   \
    for (m = 0; m < 0x100; m++, rp += REC_SIZE) {                            \
        if (*rp != 0) {                                                      \
            q = tb + *rp + (u32)*rp * 0x24c;                                 \
            if (*q == (T)) {                                                 \
                w = *(u2 *)(rp + 0x27);                                      \
                if ((w == 0xffff) || (w == *wp)) {                           \
                    break;                                                   \
                }                                                            \
            }                                                                \
        }                                                                    \
    }

/* ADDRESS: GOLDTL 0x00547770 */
void __cdecl fcn_00547770(void)
{
    int cnt2[33];
    int cnt[33];
    float thr;
    int n7a = 0;
    int n7b = 0;
    int sel = 0;
    int sw;
    int a;
    int b;
    int c;
    int wi;
    int j;
    int m;
    int u;
    int lvl;
    int e2;
    int *p;
    u2 r;
    u2 v;
    float p1;
    float p2;
    float p3;
    float p4;
    u8 *rp;
    u8 *tb;
    u8 *q;
    u8 t;
    u2 w;
    u2 *wp;

    wi = *(i32 *)0x7747b4;
    wi = (wi > 4) ? 4 : wi;
    wi = (wi <= 0) ? 0 : wi;
    a = *(i32 *)0x7f4c00 / 4 + 1;
    thr = (float)a / ((float)a + *(float *)(wi * 4 + 0x665e68));
    fcn_00547670();
    memset(cnt, 0, 0x84);
    memset(cnt2, 0, 0x84);
    rp = *(u8 **)0x90e094;
    for (j = 0; j < 0x100; j++, rp += REC_SIZE) {
        if (*rp != 0) {
            q = *(u8 **)0x868050 + *rp + (u32)*rp * 0x24c;
            t = *q;
            if (t < 0x21) {
                cnt[t]++;
                w = *(u2 *)(rp + 0x27);
                if ((w == 0xffff) || (w == **(u2 **)0x773da8)) {
                    cnt2[t]++;
                } else if (t == 7) {
                    if (*(u8 *)((u32)w * 0x21c + 0x7f4cac) == 0) {
                        n7a++;
                    } else {
                        n7b++;
                    }
                }
            }
        }
    }
    sw = *(i32 *)0x7f4c00 % 5;
    if (sw == 1) {
        int msk = 0;
        int zer = 0;
        a = cnt[4] - cnt2[4];
        b = cnt[19] - cnt2[19];
        c = cnt[16] - cnt2[16];
        sel = 0;
        if (a < 3) {
            msk |= 1;
        }
        if (a == 0) {
            zer |= 1;
        }
        if (b < 3) {
            msk |= 2;
        }
        if (b == 0) {
            zer |= 2;
        }
        if (c < 3) {
            msk |= 4;
        }
        if (c == 0) {
            zer |= 4;
        }
        if (zer != 0) {
            r = (u2)fcn_0042e410(3);
            for (j = 3; j != 0; j--) {
                if ((msk & (1 << r)) != 0) {
                    sel = 1 << r;
                    break;
                }
                r = (u2)((r + 1) % 3);
            }
        } else {
            if (fcn_0042e450() > thr) {
                return;
            }
            if ((a + c > b * 2) && ((msk & 2) != 0)) {
                sel = 2;
            } else if (a + c >= b * 2) {
                sel = 1 << fcn_0042e410(3);
            } else if (a >= c) {
                if ((msk & 4) != 0) {
                    sel = 4;
                }
            } else if ((msk & 1) != 0) {
                sel = 1;
            }
        }
        if ((msk & sel) != 0) {
            if (sel == 1) {
                if (cnt[4] < 3) {
                    e2 = fcn_0050d170(0xb) * 2;
                    lvl = 6;
                } else {
                    FIND_REC(4);
                    if (m >= 0x100) {
                        return;
                    }
                    e2 = fcn_0050cf50(rp, 0x64) * 2;
                    lvl = fcn_00507400(0xb, (u32)q[0x247] * 2 - 1);
                }
            } else if (sel == 2) {
                if (cnt[19] < 3) {
                    e2 = fcn_0050d170(0x2c) * 2;
                    lvl = 0x39;
                } else {
                    FIND_REC(0x13);
                    if (m >= 0x100) {
                        return;
                    }
                    e2 = fcn_0050cf50(rp, 0x64) * 2;
                    lvl = fcn_00507400(0xa, (u32)q[0x247] * 2 - 1);
                }
            } else {
                e2 = fcn_0050d170(0x27) * 2;
                lvl = 0x2d;
            }
            u = fcn_004c4fc0(4, -1, -1, fcn_0042e410(4) + 0xf, -1, lvl, 0, 0);
            if (u != -1) {
                while (fcn_004c4450(u) == 0) {
                    fcn_00535960();
                }
            }
            if (fcn_004c4450(u) == 1) {
                int two = 2;
                p = (int *)fcn_004c4480(u);
                fcn_004c5150(p[1], -1, *(u8 *)0x773d75, e2);
                fcn_004c4510(p, p[1]);
                fcn_004c4570(1, 1, 0xd, &two);
                fcn_004c5360();
                return;
            }
            return;
        }
        return;
    }
    if (sw == 2) {
        int msk = 0;
        int zer = 0;
        p1 = 0.0f;
        if (cnt[18] > 0) {
            p1 = (float)cnt2[18] / (float)cnt[18];
        }
        p2 = 0.0f;
        if (cnt[21] > 0) {
            p2 = (float)cnt2[21] / (float)cnt[21];
        }
        p3 = 0.0f;
        if (cnt[20] > 0) {
            p3 = (float)cnt2[20] / (float)cnt[20];
        }
        p4 = 0.0f;
        if (cnt[14] > 0) {
            p4 = (float)cnt2[14] / (float)cnt[14];
        }
        sel = 0;
        if (1) {
            if ((cnt[18] < 3) || (p1 >= 0.5f)) {
                msk |= 1;
                if (cnt[18] == 0) {
                    zer |= 1;
                }
            }
            if ((cnt[21] < 3) || (p2 >= 0.5f)) {
                msk |= 2;
                if (cnt[21] == 0) {
                    zer |= 2;
                }
            }
            if ((cnt[20] < 3) || (p3 >= 0.5f)) {
                msk |= 4;
                if (cnt[20] == 0) {
                    zer |= 4;
                }
            }
            if ((cnt[14] < 3) || (p4 >= 0.5f)) {
                msk |= 8;
                if (cnt[14] == 0) {
                    zer |= 8;
                }
            }
        }
        if (zer != 0) {
            sel = zer;
        } else {
            if (fcn_0042e450() > thr) {
                return;
            }
            r = (u2)fcn_0042e410(4);
            for (j = 4; j != 0; j--) {
                if ((msk & (1 << r)) != 0) {
                    sel = 1 << r;
                    break;
                }
                r = (u2)((r + 1) % 4);
            }
        }
        for (j = 0; j < 4; j++) {
            if ((sel & (1 << j)) == 0) {
                continue;
            }
            if (j == 0) {
                if (cnt[18] < 3) {
                    e2 = fcn_0050d170(0x29) * 2;
                    lvl = fcn_00507400(1, 1);
                } else {
                    FIND_REC(0x12);
                    if (m >= 0x100) {
                        return;
                    }
                    e2 = fcn_0050cf50(rp, 0x64) * 2;
                    lvl = fcn_00507400(1, (u32)q[0x247] * 2 - 1);
                }
            } else if (j == 1) {
                if (cnt[21] < 3) {
                    e2 = fcn_0050d170(0x32) * 2;
                    lvl = fcn_00507400(3, 1);
                } else {
                    FIND_REC(0x15);
                    if (m >= 0x100) {
                        return;
                    }
                    e2 = fcn_0050cf50(rp, 0x64) * 2;
                    lvl = fcn_00507400(3, (u32)q[0x247] * 2 - 1);
                }
            } else if (j == 2) {
                if (cnt[20] < 3) {
                    e2 = fcn_0050d170(0x2f) * 2;
                    lvl = fcn_00507400(2, 1);
                } else {
                    FIND_REC(0x14);
                    if (m >= 0x100) {
                        return;
                    }
                    e2 = fcn_0050cf50(rp, 0x64) * 2;
                    lvl = fcn_00507400(2, (u32)q[0x247] * 2 - 1);
                }
            } else {
                if (cnt[14] < 3) {
                    e2 = fcn_0050d170(0x21) * 2;
                    lvl = fcn_00507400(5, 1);
                } else {
                    FIND_REC(0xe);
                    if (m >= 0x100) {
                        return;
                    }
                    e2 = fcn_0050cf50(rp, 0x64) * 2;
                    lvl = fcn_00507400(5, (u32)q[0x247] * 2 - 1);
                }
            }
            u = fcn_004c4fc0(4, -1, -1, fcn_0042e410(4) + 0xf, -1, lvl, 0,
                             fcn_0042e410(2));
            if (u != -1) {
                while (fcn_004c4450(u) == 0) {
                    fcn_00535960();
                }
            }
            if (fcn_004c4450(u) == 1) {
                int two = 2;
                p = (int *)fcn_004c4480(u);
                fcn_004c5150(p[1], -1, *(u8 *)0x773d75, e2);
                fcn_004c4510(p, p[1]);
                fcn_004c4570(1, 1, 0xd, &two);
                fcn_004c5360();
            }
        }
        return;
    }
    if (sw == 3) {
        int msk = 0;
        int zer = 0;
        p1 = 0.0f;
        if (cnt[8] > 0) {
            p1 = (float)cnt2[8] / (float)cnt[8];
        }
        p2 = 0.0f;
        if (cnt[22] > 0) {
            p2 = (float)cnt2[22] / (float)cnt[22];
        }
        sel = 0;
        if ((cnt[8] < 3) || (p1 >= 0.5f)) {
            msk |= 1;
            if (cnt[8] == 0) {
                zer |= 1;
            }
        }
        if ((cnt[22] < 3) || (p2 >= 0.5f)) {
            msk |= 2;
            if (cnt[22] == 0) {
                zer |= 2;
            }
        }
        if (zer != 0) {
            sel = zer;
        } else {
            if (fcn_0042e450() > thr) {
                return;
            }
            r = (u2)fcn_0042e410(2);
            for (j = 2; j != 0; j--) {
                if ((msk & (1 << r)) != 0) {
                    sel = 1 << r;
                    break;
                }
                r = (u2)((r + 1) % 2);
            }
        }
        for (j = 0; j < 2; j++) {
            if ((sel & (1 << j)) == 0) {
                continue;
            }
            if (j == 0) {
                if (cnt[8] < 3) {
                    e2 = fcn_0050d170(0x17) * 2;
                    lvl = fcn_00507400(6, 1);
                } else {
                    FIND_REC(8);
                    if (m >= 0x100) {
                        return;
                    }
                    e2 = fcn_0050cf50(rp, 0x64) * 2;
                    lvl = fcn_00507400(6, (u32)q[0x247] * 2 - 1);
                }
            } else {
                if (cnt[22] < 3) {
                    e2 = fcn_0050d170(0x35) * 2;
                    lvl = fcn_00507400(4, 1);
                } else {
                    FIND_REC(0x16);
                    if (m >= 0x100) {
                        return;
                    }
                    e2 = fcn_0050cf50(rp, 0x64) * 2;
                    lvl = fcn_00507400(4, (u32)q[0x247] * 2 - 1);
                }
            }
            u = fcn_004c4fc0(4, -1, -1, fcn_0042e410(4) + 0xf, -1, lvl, 0,
                             fcn_0042e410(2));
            if (u != -1) {
                while (fcn_004c4450(u) == 0) {
                    fcn_00535960();
                }
            }
            if (fcn_004c4450(u) == 1) {
                int two = 2;
                p = (int *)fcn_004c4480(u);
                fcn_004c5150(p[1], -1, *(u8 *)0x773d75, e2);
                fcn_004c4510(p, p[1]);
                fcn_004c4570(1, 1, 0xd, &two);
                fcn_004c5360();
            }
        }
        return;
    }
    if (sw == 0) {
        int msk = 0;
        int zer = 0;
        p1 = 0.0f;
        if (cnt[9] > 0) {
            p1 = (float)cnt2[9] / (float)cnt[9];
        }
        p2 = 0.0f;
        if (cnt[5] > 0) {
            p2 = (float)cnt2[5] / (float)cnt[5];
        }
        v = (u2)fcn_0042e410(2);
        sel = 0;
        if ((cnt[9] < 2) || (p1 >= 0.5f)) {
            msk |= 1;
            if (cnt[9] == 0) {
                zer |= 1;
            }
        }
        if ((cnt[7] < 2) || ((cnt[7] < 3) && ((n7a == 0) || (n7b == 0)))) {
            msk |= 2;
            if (cnt[7] == 0) {
                zer |= 2;
            }
        }
        if ((cnt[5] < 2) || (p2 >= 0.5f)) {
            msk |= 4;
            if (cnt[5] == 0) {
                zer |= 4;
            }
        }
        if (zer != 0) {
            sel = zer;
        } else {
            if (fcn_0042e450() > thr) {
                return;
            }
            r = (u2)fcn_0042e410(3);
            for (j = 3; j != 0; j--) {
                if ((msk & (1 << r)) != 0) {
                    sel = 1 << r;
                    break;
                }
                r = (u2)((r + 1) % 3);
            }
        }
        for (j = 0; j < 3; j++) {
            if ((sel & (1 << j)) == 0) {
                continue;
            }
            if (j == 0) {
                if (cnt[9] < 2) {
                    e2 = fcn_0050d170(0x1a) * 2;
                    lvl = fcn_00507400(8, 1);
                } else {
                    FIND_REC(9);
                    if (m >= 0x100) {
                        return;
                    }
                    e2 = fcn_0050cf50(rp, 0x64) * 2;
                    lvl = fcn_00507400(8, (u32)q[0x247] * 2 - 1);
                }
            } else if (j == 1) {
                if (n7a < n7b) {
                    v = 0;
                } else if (n7a > n7b) {
                    v = 1;
                }
                FIND_REC(7);
                if (m < 0x100) {
                    e2 = fcn_0050cf50(rp, 0x64) * 2;
                    lvl = fcn_00507400(7, (u32)q[0x247] * 2 - 1);
                } else if (cnt[7] < 2) {
                    e2 = fcn_0050d170(0x14) * 2;
                    lvl = fcn_00507400(7, 1);
                } else {
                    e2 = fcn_0050d170(0x15) * 2;
                    lvl = fcn_00507400(7, 3);
                }
            } else {
                if (cnt[5] < 2) {
                    e2 = fcn_0050d170(0xe) * 2;
                    lvl = fcn_00507400(9, 1);
                } else {
                    FIND_REC(5);
                    if (m >= 0x100) {
                        return;
                    }
                    e2 = fcn_0050cf50(rp, 0x64) * 2;
                    lvl = fcn_00507400(9, (u32)q[0x247] * 2 - 1);
                }
            }
            u = fcn_004c4fc0(4, -1, -1, fcn_0042e410(4) + 0xf, -1, lvl, 0,
                             fcn_0042e410(2));
            if (u != -1) {
                while (fcn_004c4450(u) == 0) {
                    fcn_00535960();
                }
            }
            if (fcn_004c4450(u) == 1) {
                int two = 2;
                p = (int *)fcn_004c4480(u);
                fcn_004c5150(p[1], -1, *(u8 *)0x773d75, e2);
                fcn_004c4510(p, p[1]);
                fcn_004c4570(1, 1, 0xd, &two);
                fcn_004c4570(1, 1, 0xc, &v);
                fcn_004c5360();
            }
        }
        return;
    }
    if (sw == 4) {
        int msk = 0;
        int zer = 0;
        p1 = 0.0f;
        if (cnt[32] > 0) {
            p1 = (float)cnt2[32] / (float)cnt[32];
        }
        p2 = 0.0f;
        if (cnt[31] > 0) {
            p2 = (float)cnt2[31] / (float)cnt[31];
        }
        p3 = 0.0f;
        if (cnt[29] > 0) {
            p3 = (float)cnt2[29] / (float)cnt[29];
        }
        sel = 0;
        if ((cnt[32] < 3) || (p1 >= 0.5f)) {
            msk |= 1;
            if (cnt[32] == 0) {
                zer |= 1;
            }
        }
        if ((cnt[31] < 3) || (p2 >= 0.5f)) {
            msk |= 2;
            if (cnt[31] == 0) {
                zer |= 2;
            }
        }
        if ((cnt[29] < 3) || (p3 >= 0.5f)) {
            msk |= 4;
            if (cnt[29] == 0) {
                zer |= 4;
            }
        }
        if (zer != 0) {
            sel = zer;
        } else {
            if (fcn_0042e450() > thr) {
                return;
            }
            r = (u2)fcn_0042e410(3);
            for (j = 3; j != 0; j--) {
                if ((msk & (1 << r)) != 0) {
                    sel = 1 << r;
                    break;
                }
                r = (u2)((r + 1) % 3);
            }
        }
        v = 0;
        for (j = 0; j < 3; j++) {
            if ((sel & (1 << j)) == 0) {
                continue;
            }
            if (j == 0) {
                v = (u2)fcn_0042e410(2);
                if (cnt[32] < 3) {
                    e2 = fcn_0050d170(0x51) * 2;
                    lvl = fcn_00507400(0xf, 1);
                } else {
                    FIND_REC(0x20);
                    if (m >= 0x100) {
                        return;
                    }
                    e2 = fcn_0050cf50(rp, 0x64) * 2;
                    lvl = fcn_00507400(0xf, (u32)q[0x247] * 2 - 1);
                }
            } else if (j == 1) {
                if (cnt[31] < 3) {
                    e2 = fcn_0050d170(0x4e) * 2;
                    lvl = fcn_00507400(0xe, 1);
                } else {
                    FIND_REC(0x1f);
                    if (m >= 0x100) {
                        return;
                    }
                    e2 = fcn_0050cf50(rp, 0x64) * 2;
                    lvl = fcn_00507400(0xe, (u32)q[0x247] * 2 - 1);
                }
            } else {
                if (cnt[29] < 3) {
                    e2 = fcn_0050d170(0x48) * 2;
                    lvl = fcn_00507400(0xd, 1);
                } else {
                    FIND_REC(0x1d);
                    if (m >= 0x100) {
                        return;
                    }
                    e2 = fcn_0050cf50(rp, 0x64) * 2;
                    lvl = fcn_00507400(0xd, (u32)q[0x247] * 2 - 1);
                }
            }
            u = fcn_004c4fc0(4, -1, -1, fcn_0042e410(4) + 0xf, -1, lvl, 0, v);
            if (u != -1) {
                while (fcn_004c4450(u) == 0) {
                    fcn_00535960();
                }
            }
            if (fcn_004c4450(u) == 1) {
                int two = 2;
                p = (int *)fcn_004c4480(u);
                fcn_004c5150(p[1], -1, *(u8 *)0x773d75, e2);
                fcn_004c4510(p, p[1]);
                fcn_004c4570(1, 1, 0xd, &two);
                fcn_004c5360();
            }
        }
        return;
    }
    return;
}
