/* Weather rain-sound tier handler: reads the rain counter at g_7e4538, picks
 * one of four intensity tiers, starts/stops the per-tier loop sounds and
 * returns the volume through the shared voice bank. */

extern int g_6b8300;
extern char g_772d10;
extern int g_772d3c;
extern int g_772d40;
extern int g_6b7fac;
extern char* g_6b8014;
extern int* g_7e4538;
extern int g_7747bc;
extern int* g_1005854;
extern int* g_100585c;
extern int* g_1005864;
extern int* g_100586c;
extern int* g_1005874;
extern int* g_100587c;
extern int* g_1005884;
extern int g_1005840;
extern int g_1005844;
extern int g_1005848;
extern short g_100584c;

float __cdecl fcn_00413d10(float* pos);
int __cdecl fcn_00500e20(int* p);
int* __cdecl fcn_004234e0(char* bank, char* name, int loop, int pan, int vol,
    int a, int b);
int __cdecl fcn_00423890(int* voice, int vol);
void __cdecl fcn_004237f0(int* voice, int a2);
int __cdecl fcn_0064d228(void);
int __cdecl fcn_0064d3f8(void);

#define dbl_2600 (*(float*) 0x664e9c)
#define flt_889 (*(float*) 0x664e98)
#define flt_inv2600 (*(float*) 0x664e94)
#define flt_inv1300k (*(float*) 0x664e90)
#define flt_inv910k (*(float*) 0x664e8c)
#define flt_500 (*(float*) 0x664330)
#define flt_350 (*(float*) 0x664e88)
#define flt_inv387k (*(float*) 0x664e84)
#define flt_127 (*(float*) 0x664e80)
#define flt_1 (*(float*) 0x6628a0)
#define flt_inv32768 (*(float*) 0x662a18)

/* ADDRESS: GOLDTL 0x004c0cd0 */
void __cdecl fcn_004c0cd0(void)
{
    float d;
    float s;
    int count;
    float d2;
    float r;
    int scaled;
    int vol;
    int pick;

    if (g_6b8300 != 0 && g_772d10 != 0
        && g_772d3c == fcn_00500e20((int*) 0x7f4c00)) {
        scaled = 0;
        d = *(float*) (g_6b8014 + 0x50)
            - fcn_00413d10((float*) (g_6b8014 + 0x4c));
        g_1005840 = *(int*) 0x7f4c00;
        g_1005844 = *(int*) 0x7f4c04;
        g_1005848 = *(int*) 0x7f4c08;
        g_100584c = *(short*) 0x7f4c0c;
        if (g_7e4538 != 0 && (count = *g_7e4538) != 0) {
            scaled = count * 8;
            if (count >= 999) {
                vol = (int) ((dbl_2600 - d) * flt_889 * flt_inv2600);
                if (g_100586c != 0) {
                    fcn_00423890(g_100586c, vol);
                } else {
                    g_100586c = fcn_004234e0((char*) g_7747bc, (char*) 0x689db0,
                        0, 0x3f, vol, 0, 0);
                }
                if (g_1005884 != 0) {
                    fcn_00423890(g_1005884,
                        (int) (d * flt_889 * flt_inv2600));
                } else {
                    g_1005884 = fcn_004234e0((char*) g_7747bc, (char*) 0x689da0,
                        0, 0x3f, (int) (d * flt_889 * flt_inv2600), 0, 0);
                }
                if (g_1005854 != 0) {
                    fcn_00423890(g_1005854, vol);
                } else {
                    g_1005854 = fcn_004234e0((char*) g_7747bc, (char*) 0x689d94,
                        0, 0x3f, vol, 0, 0x3e8);
                }
                if (g_1005864 != 0) {
                    fcn_004237f0(g_1005864, 0);
                    g_1005864 = 0;
                }
                if (g_100585c != 0) {
                    fcn_004237f0(g_100585c, 0);
                    g_100585c = 0;
                }
                if (g_100587c != 0) {
                    fcn_004237f0(g_100587c, 0);
                    g_100587c = 0;
                }
                if (g_1005874 != 0) {
                    fcn_004237f0(g_1005874, 0);
                    g_1005874 = 0;
                }
            } else if (count >= 499) {
                s = (float) (count - 0x1f3);
                d2 = dbl_2600 - d;
                vol = (int) (d2 * s * flt_889 * flt_inv1300k);
                if (g_100586c != 0) {
                    fcn_00423890(g_100586c, vol);
                } else {
                    g_100586c = fcn_004234e0((char*) g_7747bc, (char*) 0x689db0,
                        0, 0x3f, vol, 0, 0);
                }
                if (g_1005884 != 0) {
                    fcn_00423890(g_1005884,
                        (int) (s * d * flt_889 * flt_inv1300k));
                } else {
                    g_1005884 = fcn_004234e0((char*) g_7747bc, (char*) 0x689da0,
                        0, 0x3f, (int) (s * d * flt_889 * flt_inv1300k), 0, 0);
                }
                r = flt_500 - s;
                if (g_1005864 != 0) {
                    fcn_00423890(g_1005864,
                        (int) (d2 * r * flt_889 * flt_inv1300k));
                } else {
                    g_1005864 = fcn_004234e0((char*) g_7747bc, (char*) 0x689d84,
                        0, 0x3f, (int) (d2 * r * flt_889 * flt_inv1300k), 0, 0);
                }
                if (g_100587c != 0) {
                    fcn_00423890(g_100587c,
                        (int) (r * d * flt_889 * flt_inv1300k));
                } else {
                    g_100587c = fcn_004234e0((char*) g_7747bc, (char*) 0x689d74,
                        0, 0x3f, (int) (r * d * flt_889 * flt_inv1300k), 0, 0);
                }
                if (g_1005854 != 0) {
                    *(int*) ((char*) g_1005854 + 0x18) = 0x7d0;
                    fcn_00423890(g_1005854, vol);
                } else {
                    g_1005854 = fcn_004234e0((char*) g_7747bc, (char*) 0x689d94,
                        0, 0x3f, vol, 0, 0xa28);
                }
                if (g_1005874 != 0) {
                    fcn_004237f0(g_1005874, 0);
                    g_1005874 = 0;
                }
                if (g_100585c != 0) {
                    fcn_004237f0(g_100585c, 0);
                    g_100585c = 0;
                }
            } else if (count >= 0x95) {
                s = (float) (count - 0x95);
                d2 = dbl_2600 - d;
                vol = (int) (d2 * s * flt_889 * flt_inv910k);
                if (g_1005864 != 0) {
                    fcn_00423890(g_1005864, vol);
                } else {
                    g_1005864 = fcn_004234e0((char*) g_7747bc, (char*) 0x689d84,
                        0, 0x3f, vol, 0, 0);
                }
                if (g_100587c != 0) {
                    fcn_00423890(g_100587c,
                        (int) (s * d * flt_889 * flt_inv910k));
                } else {
                    g_100587c = fcn_004234e0((char*) g_7747bc, (char*) 0x689d74,
                        0, 0x3f, (int) (s * d * flt_889 * flt_inv910k), 0, 0);
                }
                r = flt_350 - s;
                if (g_100585c != 0) {
                    fcn_00423890(g_100585c,
                        (int) (d2 * r * flt_889 * flt_inv910k));
                } else {
                    g_100585c = fcn_004234e0((char*) g_7747bc, (char*) 0x689d64,
                        0, 0x3f, (int) (d2 * r * flt_889 * flt_inv910k), 0, 0);
                }
                if (g_1005874 != 0) {
                    fcn_00423890(g_1005874,
                        (int) (r * d * flt_889 * flt_inv910k));
                } else {
                    g_1005874 = fcn_004234e0((char*) g_7747bc, (char*) 0x689d54,
                        0, 0x3f, (int) (r * d * flt_889 * flt_inv910k), 0, 0);
                }
                if (g_1005854 != 0) {
                    *(int*) ((char*) g_1005854 + 0x18) = 0xbb8;
                    fcn_00423890(g_1005854, vol);
                } else {
                    g_1005854 = fcn_004234e0((char*) g_7747bc, (char*) 0x689d94,
                        1, 0x3f, (int) (d2 * flt_889 * flt_inv2600), 0, 0xbb8);
                }
                if (g_1005884 != 0) {
                    fcn_004237f0(g_1005884, 0);
                    g_1005884 = 0;
                }
                if (g_100586c != 0) {
                    fcn_004237f0(g_100586c, 0);
                    g_100586c = 0;
                }
            } else {
                s = (float) count;
                d2 = dbl_2600 - d;
                vol = (int) (d2 * s * flt_889 * flt_inv387k);
                if (g_100585c != 0) {
                    fcn_00423890(g_100585c, vol);
                } else {
                    g_100585c = fcn_004234e0((char*) g_7747bc, (char*) 0x689d64,
                        0, 0x3f, vol, 0, 0);
                }
                if (g_1005874 != 0) {
                    fcn_00423890(g_1005874,
                        (int) (s * d * flt_889 * flt_inv387k));
                } else {
                    g_1005874 = fcn_004234e0((char*) g_7747bc, (char*) 0x689d54,
                        0, 0x3f, (int) (s * d * flt_889 * flt_inv387k), 0, 0);
                }
                if (g_1005854 != 0) {
                    *(int*) ((char*) g_1005854 + 0x18) = 0xfa0;
                    fcn_00423890(g_1005854, vol);
                } else {
                    g_1005854 = fcn_004234e0((char*) g_7747bc, (char*) 0x689d94,
                        0, 0x3f, vol, 0, 0xfa0);
                }
                if (g_1005884 != 0) {
                    fcn_004237f0(g_1005884, 0);
                    g_1005884 = 0;
                }
                if (g_100586c != 0) {
                    fcn_004237f0(g_100586c, 0);
                    g_100586c = 0;
                }
                if (g_100587c != 0) {
                    fcn_004237f0(g_100587c, 0);
                    g_100587c = 0;
                }
                if (g_1005864 != 0) {
                    fcn_004237f0(g_1005864, 0);
                    g_1005864 = 0;
                }
            }
        } else {
            if (g_1005884 != 0) {
                fcn_004237f0(g_1005884, 0);
                g_1005884 = 0;
            }
            if (g_100586c != 0) {
                fcn_004237f0(g_100586c, 0);
                g_100586c = 0;
            }
            if (g_100587c != 0) {
                fcn_004237f0(g_100587c, 0);
                g_100587c = 0;
            }
            if (g_1005864 != 0) {
                fcn_004237f0(g_1005864, 0);
                g_1005864 = 0;
            }
            if (g_1005874 != 0) {
                fcn_004237f0(g_1005874, 0);
                g_1005874 = 0;
            }
            if (g_100585c != 0) {
                fcn_004237f0(g_100585c, 0);
                g_100585c = 0;
            }
            if (g_1005854 != 0) {
                fcn_004237f0(g_1005854, 0);
                g_1005854 = 0;
            }
        }
        if (g_6b8300 != 0 && g_772d10 != 0
            && (unsigned int) (g_6b7fac * 13 - g_772d40 + scaled)
                >= *(unsigned int*) (0x6817f8 + g_772d3c * 0xc)) {
            g_772d40 = g_6b7fac * 13;
            if (*(float*) (0x6817f0 + g_772d3c * 0xc)
                    + (float) fcn_0064d3f8() * flt_inv32768
                > flt_1) {
                pick = 0;
                if (scaled > 0x28a) {
                    pick = fcn_0064d3f8() % 3;
                } else if (scaled > 0xfa) {
                    pick = fcn_0064d3f8() % 2;
                }
                fcn_004234e0(0, (char*) (0x681758 + pick * 0x32), 1, 0x3f,
                    (int) (*(float*) (0x6817f4 + g_772d3c * 0xc) * flt_127),
                    0, 0);
            }
        }
    } else {
        g_772d3c = fcn_00500e20((int*) 0x7f4c00);
        if (g_1005884 != 0) {
            fcn_004237f0(g_1005884, 0);
            g_1005884 = 0;
        }
        if (g_100586c != 0) {
            fcn_004237f0(g_100586c, 0);
            g_100586c = 0;
        }
        if (g_100587c != 0) {
            fcn_004237f0(g_100587c, 0);
            g_100587c = 0;
        }
        if (g_1005864 != 0) {
            fcn_004237f0(g_1005864, 0);
            g_1005864 = 0;
        }
        if (g_1005874 != 0) {
            fcn_004237f0(g_1005874, 0);
            g_1005874 = 0;
        }
        if (g_100585c != 0) {
            fcn_004237f0(g_100585c, 0);
            g_100585c = 0;
        }
        if (g_1005854 != 0) {
            fcn_004237f0(g_1005854, 0);
            g_1005854 = 0;
        }
    }
}
