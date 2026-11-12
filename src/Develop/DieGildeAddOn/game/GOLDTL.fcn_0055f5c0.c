#include <string.h>

#include "client_types.h"
#include "g_7f4ca2.h"

extern unsigned short g_774970;
extern unsigned char g_774964;
extern char* g_7746c4;
extern char* g_7746c8;
extern char* g_7746cc;
extern int g_7749e4;
extern unsigned char g_7749e8;
extern unsigned char g_7747b0;
extern int g_7747b8;
extern int g_100f884;
extern int g_100f1dc;
extern int g_14ce8d8;
extern int g_6b5c8c;
extern int g_6b7fc0;
extern pos14_7f4c00 g_7f4c00;
extern Slot7f4ca2 g_7f4ca2[768];
extern int g_7f4ca4;

int __cdecl fcn_00500cb0(void*, void*);
int __cdecl fcn_00545670(char*, int, int, char*, int);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_004234e0(int, char*, int, int, int, int, int);
void __cdecl fcn_00545c50(int);
int __cdecl fcn_004c30a0(int, int, char*, int, int);
void __cdecl fcn_004237f0(void*, int);
void __cdecl fcn_00500bb0(void*, int, int, int);
char* __cdecl cut_FindCutsceneById(int);
int __cdecl cut_RemoveParticipant(int, int);
void __cdecl fcn_004c5a20(int, int);
int __cdecl fcn_00503fe0(int, int, int);
void __cdecl fcn_00526920(char*, int, char*);
void __cdecl fcn_004116d0(void);
void __cdecl fcn_00545780(char*);

/* ADDRESS: GOLDTL 0x0055f590 */
void __cdecl fcn_0055f590(char* e)
{
    *(int*) (e + 0x70) = 0;
    *(int*) (e + 0xec) = 0;
    if (g_7f4ca2[*(unsigned short*) (e + 8)].kind == 6)
        return;
    fcn_00546190(e);
}

/* One stage of the event message-box tick; state lives at +0x70. */
/* ADDRESS: GOLDTL 0x0055f5c0 */
void __cdecl fcn_0055f5c0(char* e)
{
    char text[0x80];
    char* win;
    char* rec;
    char* str;
    int state;

    if (g_774970 != *(unsigned short*) (e + 8))
        return;
    if (!g_774964)
        return;

    switch (*(int*) (e + 0x70)) {
    case 0:
        if (*(unsigned char*) (e + 0xf0) & 2) {
            win = 0;
            if (*(unsigned char*) (e + 0xf0) & 1)
                fcn_00545670(e, 0, 0, "misc\\EventMessagebox_QJ_BIG", *(int*) (e + 0xac));
            else
                fcn_00545670(e, 0, 0, "misc\\EventMessagebox_QJ", *(int*) (e + 0xac));
            if (*(int*) (e + 0x74) == 0) {
                fcn_00546190(e);
                return;
            }
            if (g_7746c4 != 0)
                win = g_7746c4;
            else if (g_7746c8 != 0)
                win = g_7746c8;
            fcn_004727a0(*(int*) (*(int*) (e + 0x74) + 8), 1);
            if (win != 0 && *(int*) (win + 1) == *(int*) (e + 0xb0) && *(unsigned char*) (e + 0xbc) == 0
                && ((g_7746cc != 0 && *(int*) (g_7746cc + 2) == *(int*) (e + 0xb4)) || *(int*) (e + 0xb4) == -1)) {
                fcn_00519190(0x1ba2);
            } else {
                fcn_00519190(0x1ba1);
            }
        } else if (*(unsigned char*) (e + 0xf0) & 1) {
            fcn_00545670(e, 0, 0, "misc\\EventMessagebox_BIG", *(int*) (e + 0xac));
            if (*(int*) (e + 0x74) == 0)
                goto done;
            fcn_004727a0(*(int*) (*(int*) (e + 0x74) + 8), 1);
            fcn_00519190(0x1ba3);
        } else if (*(unsigned char*) (e + 0xf0) & 0x20) {
            fcn_00545670(e, 0, 0, "misc\\EventMsgbox_History", *(int*) (e + 0xac));
            if (*(int*) (e + 0x74) == 0)
                goto done;
            fcn_004727a0(*(int*) (*(int*) (e + 0x74) + 8), 1);
            fcn_00519190(0x1ba3);
        } else if (*(unsigned char*) (e + 0xf0) & 4) {
            fcn_00545670(e, 0, 0, "misc\\EventMessagebox_Cutscenes", *(int*) (e + 0xac));
        } else if (*(unsigned char*) (e + 0xf0) & 0x40) {
            fcn_00545670(e, 0, 0, "misc\\EventMessagebox_Help", *(int*) (e + 0xac));
        } else {
            fcn_00545670(e, 0, 0, "misc\\EventMessagebox", *(int*) (e + 0xac));
            if (*(int*) (e + 0x74) == 0)
                goto done;
            fcn_004727a0(*(int*) (*(int*) (e + 0x74) + 8), 1);
            fcn_00519190(0x7d);
        }
done:
        if (*(int*) (e + 0x74) == 0) {
            fcn_00546190(e);
            return;
        }
        fcn_00471b60(*(int*) (*(int*) (e + 0x74) + 8));
        fcn_004727a0(*(int*) (*(int*) (e + 0x74) + 8), 0);
        fcn_00519190(0x679060, *(int*) (e + 0x7c));
        if (g_774964 != 2)
            fcn_004234e0(g_7747b8, "NeueMessage_s_01", 1, 0x3f, 0x7f, 0, 0);
        if (*(unsigned char*) (e + 0xf0) & 8)
            fcn_00545c50(*(int*) (e + 0x74));
        if (*(unsigned char*) (e + 0xf0) & 0x10) {
            str = *(char**) (e + 0x7c);
            str = str + strlen(str) + 1;
            memcpy(text, str, strlen(str) + 1);
            *(int*) (e + 0xec) = fcn_004c30a0(-7, 0, text, 0, 0x7d0);
        }
        *(int*) (e + 0x44) = g_7f4c00.a;
        *(int*) (e + 0x48) = g_7f4c00.b;
        *(int*) (e + 0x4c) = g_7f4c00.c;
        *(short*) (e + 0x50) = g_7f4c00.d;
        *(int*) (e + 0x52) = g_7f4c00.a;
        *(int*) (e + 0x56) = g_7f4c00.b;
        *(int*) (e + 0x5a) = g_7f4c00.c;
        *(short*) (e + 0x5e) = g_7f4c00.d;
        if (*(unsigned char*) (e + 0xf0) & 4) {
            fcn_00500bb0(e + 0x52, 0x18, 0, 0);
        } else {
            fcn_00500bb0(e + 0x52, 8, 0, 0);
            if (*(unsigned short*) (e + 0x56) < 6)
                fcn_00500bb0(e + 0x52, 8, 0, 0);
        }
        *(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
        return;
    case 1:
        state = -1;
        if (*(unsigned char*) (e + 0xf0) & 4) {
            rec = cut_FindCutsceneById(*(int*) (e + 0xb8));
            if (rec == 0) {
                *(int*) (e + 0x70) = state;
                goto tail;
            }
            if (fcn_00500cb0((void*) &g_7f4c00, rec + 0x18) <= 0)
                goto tail;
            if (*(signed char*) (rec + 0x26) < 0) {
                if (!((*(unsigned char*) (e + 0xf0) & 2)
                      && *(int*) (e + 0xb0) != -1
                      && (*(unsigned char*) (rec + 0x26) & 0x10)))
                    *(int*) (rec + 4) = 1;
                goto exit_b;
            }
            if (g_7747b0 & 8) {
                cut_RemoveParticipant(*(int*) (e + 0xb8), *(int*) (g_774970 * 0x21c + (unsigned long)&g_7f4ca4));
            } else if (g_7747b0 & 4) {
                fcn_004c5a20(*(int*) (e + 0xb8), *(int*) (g_774970 * 0x21c + (unsigned long)&g_7f4ca4));
            }
            *(int*) (e + 0x70) = state;
            goto tail;
        } else if (fcn_00500cb0((void*) &g_7f4c00, e + 0x52) > 0) {
            goto exit_clear;
        }
tail:
        if (*(int*) (e + 0x74) == 0)
            return;
        if (g_100f884 != *(int*) (*(int*) (e + 0x74) + 8)) {
            if (!g_7749e8)
                return;
            if (g_7749e4 != *(int*) (e + 0x74))
                return;
        }
        if (g_100f1dc == -1) {
            if (!g_7749e8)
                return;
            if (g_7749e4 != *(int*) (e + 0x74))
                return;
            goto test_dl;
        }
        if (g_100f1dc == 2)
            goto body2;
        if (g_100f1dc == 1)
            goto body1;
test_dl:
        if (!g_7749e8)
            goto exit_a;
body1:
        if (*(unsigned char*) (e + 0xf0) & 4) {
            rec = cut_FindCutsceneById(*(int*) (e + 0xb8));
            if (rec != 0) {
                if (*(signed char*) (rec + 0x26) < 0) {
                    if (!((*(unsigned char*) (e + 0xf0) & 2)
                          && *(int*) (e + 0xb0) != -1
                          && (*(unsigned char*) (rec + 0x26) & 0x10)))
                        *(int*) (rec + 4) = 1;
                } else if (g_7747b0 & 8) {
                    cut_RemoveParticipant(*(int*) (e + 0xb8), *(int*) (g_774970 * 0x21c + (unsigned long)&g_7f4ca4));
                } else if (g_7747b0 & 4) {
                    fcn_004c5a20(*(int*) (e + 0xb8), *(int*) (g_774970 * 0x21c + (unsigned long)&g_7f4ca4));
                }
            }
        }
        if ((*(unsigned char*) (e + 0xf0) & 0x10) && *(int*) (e + 0xec) != 0) {
            fcn_004237f0(*(void**) (e + 0xec), 0);
            *(int*) (e + 0xec) = 0;
        }
        if (*(unsigned char*) (e + 0xf0) & 0x40) {
            if (!(*(unsigned char*) &g_7747b0 & 4))
                *(int*) &g_6b7fc0 = 0;
        }
        if (g_14ce8d8 != 0) {
            g_6b5c8c = 1;
            fcn_004116d0();
        }
        fcn_00545780(e);
        fcn_00546190(e);
exit_a:
        g_7749e8 = 0;
        return;
body2:
        if (*(unsigned char*) (e + 0xf0) & 4) {
            rec = cut_FindCutsceneById(*(int*) (e + 0xb8));
            if (!((*(unsigned char*) (e + 0xf0) & 2)
                  && *(int*) (e + 0xb0) != -1
                  && (*(unsigned char*) (rec + 0x26) & 0x10)))
                *(int*) (rec + 4) = 1;
        }
        if (*(unsigned char*) (e + 0xf0) & 2) {
            rec = (char*) fcn_00503fe0(1, 1, *(int*) (e + 0xb0));
            if (rec == 0)
                return;
            fcn_00526920(rec, *(int*) (e + 0xb4), e + 0xbc);
        }
        if ((*(unsigned char*) (e + 0xf0) & 0x10) && *(int*) (e + 0xec) != 0) {
            fcn_004237f0(*(void**) (e + 0xec), 0);
            *(int*) (e + 0xec) = 0;
        }
        if (*(unsigned char*) (e + 0xf0) & 0x40) {
            if (!(*(unsigned char*) &g_7747b0 & 4))
                *(int*) &g_6b7fc0 = 0;
        }
        if (g_14ce8d8 != 0) {
            g_6b5c8c = 1;
            fcn_004116d0();
        }
        goto exit_b;
exit_clear:
        if (*(unsigned char*) (e + 0xf0) & 0x40) {
            if (!(*(unsigned char*) &g_7747b0 & 4))
                *(int*) &g_6b7fc0 = 0;
        }
exit_b:
        fcn_00545780(e);
        fcn_00546190(e);
        return;
    case -2:
    case -1:
        if ((*(unsigned char*) (e + 0xf0) & 0x10) && *(int*) (e + 0xec) != 0) {
            fcn_004237f0(*(void**) (e + 0xec), 0);
            *(int*) (e + 0xec) = 0;
        }
        goto exit_clear;
    default:
        return;
    }
}
