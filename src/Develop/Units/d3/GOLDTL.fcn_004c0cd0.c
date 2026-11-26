/* Weather rain-sound tier handler: reads the rain counter at g_7e4538, picks
 * one of four intensity tiers, starts/stops the per-tier loop sounds and
 * returns the volume through the shared voice bank. */

extern int g_6b8300;
extern char g_772d10;
extern int g_772d3c;
extern int g_772d40;
extern volatile int g_6b7fac;
extern char* d3_ActiveCamera;
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
extern short g_7f4c0c;
extern int gm_GameTime, g_7f4c04, g_7f4c08;
float __cdecl fcn_00413d10(float* pos);
int __cdecl gm_GetSeason(int* p);
int* __cdecl sb_PlayVoice(char* bank, char* name, int loop, int pan, int vol,
    int a, int b);
int __cdecl sb_SetVoiceVolume(int* voice, int vol);
void __cdecl sb_StopVoice(int* voice, int a2);
int __cdecl _ftol(void);
int __cdecl fcn_0064d3f8(void);

extern float g_664330;
extern float g_6628a0;
extern float g_662a18;
extern float g_664e80;
extern float g_664e88;

#define dbl_2600 (*(float*) 0x664e9c)
#define flt_889 (*(float*) 0x664e98)
#define flt_inv2600 (*(float*) 0x664e94)
#define flt_inv1300k (*(float*) 0x664e90)
#define flt_inv910k (*(float*) 0x664e8c)
#define flt_inv387k (*(float*) 0x664e84)
#define flt_500 g_664330
#define flt_350 g_664e88
#define flt_127 g_664e80
#define flt_1 1.0f
#define flt_inv32768 3.0518509447574615e-05f

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
        && g_772d3c == gm_GetSeason((int*) 0x7f4c00)) {
        scaled = 0;
        d = *(float*) (d3_ActiveCamera + 0x50)
            - fcn_00413d10((float*) (d3_ActiveCamera + 0x4c));
        g_1005840 = gm_GameTime;
        g_1005844 = g_7f4c04;
        g_1005848 = g_7f4c08;
        g_100584c = (short) g_7f4c0c;
        if (g_7e4538 != 0 && (count = *g_7e4538) != 0) {
            scaled = count * 8;
            if (count >= 999) {
                vol = (int) ((dbl_2600 - d) * flt_889 * flt_inv2600);
                if (g_100586c == 0) {
                    g_100586c = sb_PlayVoice((char*) g_7747bc, (char*) 0x689db0,
                        0, 0x3f, vol, 0, 0);
                } else {
                    sb_SetVoiceVolume(g_100586c, vol);
                }
                if (g_1005884 == 0) {
                    g_1005884 = sb_PlayVoice((char*) g_7747bc, (char*) 0x689da0,
                        0, 0x3f, (int) (flt_inv2600 * (flt_889 * d)), 0, 0);
                } else {
                    sb_SetVoiceVolume(g_1005884, (int) (flt_inv2600 * (flt_889 * d)));
                }
                if (g_1005854 == 0) {
                    g_1005854 = sb_PlayVoice((char*) g_7747bc, (char*) 0x689d94,
                        0, 0x3f, vol, 0, 0x3e8);
                } else {
                    sb_SetVoiceVolume(g_1005854, vol);
                }
                if (g_1005864 != 0) {
                    sb_StopVoice(g_1005864, 0);
                    g_1005864 = 0;
                }
                if (g_100585c != 0) {
                    sb_StopVoice(g_100585c, 0);
                    g_100585c = 0;
                }
                if (g_100587c != 0) {
                    sb_StopVoice(g_100587c, 0);
                    g_100587c = 0;
                }
                if (g_1005874 != 0) {
                    sb_StopVoice(g_1005874, 0);
                    g_1005874 = 0;
                }
            } else if (count >= 499) {
                s = (float) (count - 0x1f3);
                d2 = dbl_2600 - d;
                vol = (int) (((d2 * s) * flt_889) * flt_inv1300k);
                if (g_100586c == 0) {
                    g_100586c = sb_PlayVoice((char*) g_7747bc, (char*) 0x689db0,
                        0, 0x3f, vol, 0, 0);
                } else {
                    sb_SetVoiceVolume(g_100586c, vol);
                }
                if (g_1005884 == 0) {
                    g_1005884 = sb_PlayVoice((char*) g_7747bc, (char*) 0x689da0,
                        0, 0x3f, (int) (((s * d) * flt_889) * flt_inv1300k), 0, 0);
                } else {
                    sb_SetVoiceVolume(g_1005884,
                        (int) (((s * d) * flt_889) * flt_inv1300k));
                }
                r = flt_500 - s;
                if (g_1005864 == 0) {
                    g_1005864 = sb_PlayVoice((char*) g_7747bc, (char*) 0x689d84,
                        0, 0x3f, (int) (flt_inv1300k * (flt_889 * (d2 * r))), 0, 0);
                } else {
                    sb_SetVoiceVolume(g_1005864,
                        (int) (flt_inv1300k * (flt_889 * (d2 * r))));
                }
                if (g_100587c == 0) {
                    g_100587c = sb_PlayVoice((char*) g_7747bc, (char*) 0x689d74,
                        0, 0x3f, (int) (flt_inv1300k * (flt_889 * (r * d))), 0, 0);
                } else {
                    sb_SetVoiceVolume(g_100587c,
                        (int) (flt_inv1300k * (flt_889 * (r * d))));
                }
                if (g_1005854 == 0) {
                    g_1005854 = sb_PlayVoice((char*) g_7747bc, (char*) 0x689d94,
                        0, 0x3f, vol, 0, 0xa28);
                } else {
                    *(int*) ((char*) g_1005854 + 0x18) = 0x7d0;
                    sb_SetVoiceVolume(g_1005854, vol);
                }
                if (g_1005874 != 0) {
                    sb_StopVoice(g_1005874, 0);
                    g_1005874 = 0;
                }
                if (g_100585c != 0) {
                    sb_StopVoice(g_100585c, 0);
                    g_100585c = 0;
                }
            } else if (count >= 0x95) {
                s = (float) (count - 0x95);
                d2 = dbl_2600 - d;
                vol = (int) ((d2 * s) * flt_889 * flt_inv910k);
                if (g_1005864 == 0) {
                    g_1005864 = sb_PlayVoice((char*) g_7747bc, (char*) 0x689d84,
                        0, 0x3f, vol, 0, 0);
                } else {
                    sb_SetVoiceVolume(g_1005864, vol);
                }
                if (g_100587c == 0) {
                    g_100587c = sb_PlayVoice((char*) g_7747bc, (char*) 0x689d74,
                        0, 0x3f, (int) (flt_inv910k * (flt_889 * (s * d))), 0, 0);
                } else {
                    sb_SetVoiceVolume(g_100587c,
                        (int) (flt_inv910k * (flt_889 * (s * d))));
                }
                r = flt_350 - s;
                if (g_100585c == 0) {
                    g_100585c = sb_PlayVoice((char*) g_7747bc, (char*) 0x689d64,
                        0, 0x3f, (int) (flt_inv910k * (flt_889 * (d2 * r))), 0, 0);
                } else {
                    sb_SetVoiceVolume(g_100585c,
                        (int) (flt_inv910k * (flt_889 * (d2 * r))));
                }
                if (g_1005874 == 0) {
                    g_1005874 = sb_PlayVoice((char*) g_7747bc, (char*) 0x689d54,
                        0, 0x3f, (int) (flt_inv910k * (flt_889 * (r * d))), 0, 0);
                } else {
                    sb_SetVoiceVolume(g_1005874,
                        (int) (flt_inv910k * (flt_889 * (r * d))));
                }
                if (g_1005854 == 0) {
                    g_1005854 = sb_PlayVoice((char*) g_7747bc, (char*) 0x689d94,
                        1, 0x3f, (int) (d2 * flt_889 * flt_inv2600), 0, 0xbb8);
                } else {
                    *(int*) ((char*) g_1005854 + 0x18) = 0xbb8;
                    sb_SetVoiceVolume(g_1005854, vol);
                }
                if (g_1005884 != 0) {
                    sb_StopVoice(g_1005884, 0);
                    g_1005884 = 0;
                }
                if (g_100586c != 0) {
                    sb_StopVoice(g_100586c, 0);
                    g_100586c = 0;
                }
            } else {
                s = (float) count;
                vol = (int) (((dbl_2600 - d) * s) * flt_889 * flt_inv387k);
                if (g_100585c == 0) {
                    g_100585c = sb_PlayVoice((char*) g_7747bc, (char*) 0x689d64,
                        0, 0x3f, vol, 0, 0);
                } else {
                    sb_SetVoiceVolume(g_100585c, vol);
                }
                if (g_1005874 == 0) {
                    g_1005874 = sb_PlayVoice((char*) g_7747bc, (char*) 0x689d54,
                        0, 0x3f, (int) (flt_inv387k * (flt_889 * (s * d))), 0, 0);
                } else {
                    sb_SetVoiceVolume(g_1005874,
                        (int) (flt_inv387k * (flt_889 * (s * d))));
                }
                if (g_1005854 == 0) {
                    g_1005854 = sb_PlayVoice((char*) g_7747bc, (char*) 0x689d94,
                        0, 0x3f, vol, 0, 0xfa0);
                } else {
                    *(int*) ((char*) g_1005854 + 0x18) = 0xfa0;
                    sb_SetVoiceVolume(g_1005854, vol);
                }
                if (g_1005884 != 0) {
                    sb_StopVoice(g_1005884, 0);
                    g_1005884 = 0;
                }
                if (g_100586c != 0) {
                    sb_StopVoice(g_100586c, 0);
                    g_100586c = 0;
                }
                if (g_100587c != 0) {
                    sb_StopVoice(g_100587c, 0);
                    g_100587c = 0;
                }
                if (g_1005864 != 0) {
                    sb_StopVoice(g_1005864, 0);
                    g_1005864 = 0;
                }
            }
        } else {
            if (g_1005884 != 0) {
                sb_StopVoice(g_1005884, 0);
                g_1005884 = 0;
            }
            if (g_100586c != 0) {
                sb_StopVoice(g_100586c, 0);
                g_100586c = 0;
            }
            if (g_100587c != 0) {
                sb_StopVoice(g_100587c, 0);
                g_100587c = 0;
            }
            if (g_1005864 != 0) {
                sb_StopVoice(g_1005864, 0);
                g_1005864 = 0;
            }
            if (g_1005874 != 0) {
                sb_StopVoice(g_1005874, 0);
                g_1005874 = 0;
            }
            if (g_100585c != 0) {
                sb_StopVoice(g_100585c, 0);
                g_100585c = 0;
            }
            if (g_1005854 != 0) {
                sb_StopVoice(g_1005854, 0);
                g_1005854 = 0;
            }
        }
        if (g_6b8300 != 0 && g_772d10 != 0
            && (unsigned int) ((g_6b7fac
                        + g_6b7fac * 2) * 4
                    - g_772d40 + scaled + g_6b7fac)
                >= (unsigned int) ((int*) 0x6817f8)[g_772d3c * 3]) {
            g_772d40 = (g_6b7fac
                    + g_6b7fac * 2) * 4
                + g_6b7fac;
            if (((float*) 0x6817f0)[g_772d3c * 3]
                    + (float) fcn_0064d3f8() * flt_inv32768
                > flt_1) {
                pick = 0;
                if (scaled > 0x28a) {
                    pick = fcn_0064d3f8() % 3;
                } else if (scaled > 0xfa) {
                    pick = fcn_0064d3f8() % 2;
                }
                sb_PlayVoice(0, (char*) (0x681758 + pick * 0x32), 1, 0x3f,
                    (int) (((float*) 0x6817f4)[g_772d3c * 3] * flt_127),
                    0, 0);
            }
        }
    } else {
        g_772d3c = gm_GetSeason((int*) 0x7f4c00);
        if (g_1005884 != 0) {
            sb_StopVoice(g_1005884, 0);
            g_1005884 = 0;
        }
        if (g_100586c != 0) {
            sb_StopVoice(g_100586c, 0);
            g_100586c = 0;
        }
        if (g_100587c != 0) {
            sb_StopVoice(g_100587c, 0);
            g_100587c = 0;
        }
        if (g_1005864 != 0) {
            sb_StopVoice(g_1005864, 0);
            g_1005864 = 0;
        }
        if (g_1005874 != 0) {
            sb_StopVoice(g_1005874, 0);
            g_1005874 = 0;
        }
        if (g_100585c != 0) {
            sb_StopVoice(g_100585c, 0);
            g_100585c = 0;
        }
        if (g_1005854 != 0) {
            sb_StopVoice(g_1005854, 0);
            g_1005854 = 0;
        }
    }
}
