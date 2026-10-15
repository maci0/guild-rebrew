#include <string.h>
#include "Develop/DieGildeAddOn/game/event_callbacks.h"

struct unit;
char* __cdecl fcn_00508e40(int);
struct unit* __cdecl fcn_005463a0(int, ...);
struct unit* __cdecl fcn_005462a0(void);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_004e6240(int*, char*, char*, char*);
int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);
void __cdecl fcn_004c6040(int, int, int, int);
extern char g_6b5c60[];

/* Inferred source placement; registration proves the validator slot. */
/* ADDRESS: GOLDTL 0x004dc7d0 */
/* ADDRESS: GOLD 0x004daf80 */
int __cdecl fcn_004dc7d0(char* cmd)
{
    char* a;
    char* b;
    char* c;
    char* d;
    char* e;
    char* f;
    char* bad;
    char* unit;
    char suffix[64];
    char text[512];
    int error;

    bad = 0;
    error = 0;
    a = fcn_00508e40(*(int*) (cmd + 0x34));
    if (a != 0 && a[2] != 15 && a[8] != 0) {
        if (a[0x1b1] != 0) {
            bad = a;
            error = 7;
            unit = (char*) fcn_005463a0(1, 0, 0x3d);
            while (unit != 0) {
                if (*(int*) (unit + 0xac) == *(int*) (a + 4)) {
                    error = 6;
                    break;
                }
                unit = (char*) fcn_005462a0();
            }
        }
    } else {
        error = 1;
    }
    b = fcn_00508e40(*(int*) (cmd + 0x38));
    if (error == 0) {
        if (b != 0 && b[2] != 15 && b[8] != 0) {
            /* Native second-participant validation reuses the first. */
            if (a[0x1b1] != 0) {
                bad = a;
                error = 7;
                unit = (char*) fcn_005463a0(1, 0, 0x3d);
                while (unit != 0) {
                    if (*(int*) (unit + 0xac) == *(int*) (a + 4)) {
                        error = 6;
                        break;
                    }
                    unit = (char*) fcn_005462a0();
                }
            }
        } else {
            error = 2;
        }
    }
    c = fcn_00508e40(*(int*) (cmd + 0x3c));
    if (error == 0) {
        if (c != 0 && c[2] != 15 && c[8] != 0) {
            if (c[0x1b1] != 0) {
                bad = c;
                error = 7;
                unit = (char*) fcn_005463a0(1, 0, 0x3d);
                while (unit != 0) {
                    if (*(int*) (unit + 0xac) == *(int*) (c + 4)) {
                        error = 6;
                        break;
                    }
                    unit = (char*) fcn_005462a0();
                }
            }
        } else {
            error = 3;
        }
    }
    d = fcn_00508e40(*(int*) (cmd + 0x40));
    if (error == 0) {
        if (d != 0 && d[2] != 15 && d[8] != 0) {
            if (d[0x1b1] != 0) {
                bad = d;
                error = 7;
                unit = (char*) fcn_005463a0(1, 0, 0x3d);
                while (unit != 0) {
                    if (*(int*) (unit + 0xac) == *(int*) (d + 4)) {
                        error = 6;
                        break;
                    }
                    unit = (char*) fcn_005462a0();
                }
            }
        } else {
            error = 4;
        }
    }
    e = fcn_00508e40(*(int*) (cmd + 0x44));
    if (error == 0) {
        if (e != 0 && e[2] != 15 && e[8] != 0) {
            if (e[0x1b1] != 0) {
                bad = e;
                error = 7;
                unit = (char*) fcn_005463a0(1, 0, 0x3d);
                while (unit != 0) {
                    if (*(int*) (unit + 0xac) == *(int*) (e + 4)) {
                        error = 6;
                        break;
                    }
                    unit = (char*) fcn_005462a0();
                }
            }
        } else {
            error = 4;
        }
    }
    f = fcn_00508e40(*(int*) (cmd + 0x48));
    if (error == 0 && (unsigned char) cmd[0x30] >= 6) {
        if (f != 0 && f[2] != 15 && f[8] != 0) {
            if (f[0x1b1] != 0) {
                bad = f;
                error = 7;
                unit = (char*) fcn_005463a0(1, 0, 0x3d);
                while (unit != 0) {
                    if (*(int*) (unit + 0xac) == *(int*) (f + 4)) {
                        error = 6;
                        break;
                    }
                    unit = (char*) fcn_005462a0();
                }
            }
        } else {
            error = 5;
        }
    }
    if (error == 0) {
        /* Native formatter treats its second word as an ID below 0x4800, otherwise an address. */
        fcn_0051af00(suffix, (int) "%s", 0x11d7);
        if (a[2] == 6 || a[2] == 7) {
            fcn_0051af00(text, 0x11d0, *(unsigned short*) b);
            strcat(text, suffix);
            fcn_004e6240((int*) a, cmd, text, g_6b5c60);
        }
        if (b[2] == 6 || b[2] == 7) {
            fcn_0051af00(text, 0x11d1, *(unsigned short*) a);
            strcat(text, suffix);
            fcn_004e6240((int*) b, cmd, text, g_6b5c60);
        }
        if (c[2] == 6 || c[2] == 7) {
            fcn_0051af00(text, 0x11d2, *(unsigned short*) a, *(unsigned short*) b);
            strcat(text, suffix);
            fcn_004e6240((int*) c, cmd, text, g_6b5c60);
        }
        fcn_0051af00(text, 0x11d3, *(unsigned short*) a, *(unsigned short*) b);
        strcat(text, suffix);
        if (d[2] == 6 || d[2] == 7)
            fcn_004e6240((int*) d, cmd, text, g_6b5c60);
        if (e[2] == 6 || e[2] == 7)
            fcn_004e6240((int*) e, cmd, text, g_6b5c60);
        if (f != 0 && (f[2] == 6 || f[2] == 7)) {
            fcn_0051af00(text, 0x11d5, *(unsigned short*) a, *(unsigned short*) b);
            strcat(text, suffix);
            fcn_004e6240((int*) f, cmd, text, g_6b5c60);
        }
        return 1;
    }
    switch (error) {
    case 1:
        fcn_0051af00(text, 0x11d8);
        break;
    case 2:
        fcn_0051af00(text, 0x11d9);
        break;
    case 3:
        fcn_0051af00(text, 0x11da);
        break;
    case 4:
        fcn_0051af00(text, 0x11db);
        break;
    case 5:
        fcn_0051af00(text, 0x11dc);
        break;
    case 6:
        fcn_0051af00(text, 0x11df, *(unsigned short*) bad);
        break;
    case 7:
        fcn_0051af00(text, 0x11de, *(unsigned short*) bad);
        break;
    }
    if (a != 0 && a != bad && (a[2] == 6 || a[2] == 7))
        fcn_00545d40(*(int*) (a + 4), -1, text, 0, 0x5f5, 0);
    if (b != 0 && b != bad && (b[2] == 6 || b[2] == 7))
        fcn_00545d40(*(int*) (b + 4), -1, text, 0, 0x5f5, 0);
    if (c != 0 && c != bad && (c[2] == 6 || c[2] == 7))
        fcn_00545d40(*(int*) (c + 4), -1, text, 0, 0x5f5, 0);
    if (d != 0 && d != bad && (d[2] == 6 || d[2] == 7))
        fcn_00545d40(*(int*) (d + 4), -1, text, 0, 0x5f5, 0);
    if (e != 0 && e != bad && (e[2] == 6 || e[2] == 7))
        fcn_00545d40(*(int*) (e + 4), -1, text, 0, 0x5f5, 0);
    if (f != 0 && f != bad && (f[2] == 6 || f[2] == 7))
        fcn_00545d40(*(int*) (f + 4), -1, text, 0, 0x5f5, 0);
    fcn_004c6040(*(int*) (cmd + 0x34), *(int*) (cmd + 0x34), *(int*) (cmd + 0x7c), 0);
    return 0;
}
