#include <string.h>

#include "client_types.h"
#include "g_7f4ca2.h"

extern unsigned short g_774970;
extern unsigned char g_774964;
extern char* g_7746c4;
extern char* g_7746c8;
extern char* g_7746cc;
extern int g_7749e4;
extern char g_7749e8;
extern unsigned char g_7747b0;
extern char* g_7747b8;
extern int g_100f884;
extern int g_100f1dc;
extern int g_14ce8d8;
extern int g_6b5c8c;
extern volatile int g_6b7fc0;
extern pos14_7f4c00 gm_GameTime;
extern Slot7f4ca2 g_7f4ca2[768];
extern int g_7f4ca4;

int __cdecl gm_CompareGameTime(void*, void*);
int __cdecl d2_CreateActionPopupSlot(char*, int, int, char*, int);
void __cdecl he_FreeAction(char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl sb_PlayVoice(int, char*, int, int, int, int, int);
void __cdecl d2_HighlightSelectedControl(int);
int __cdecl d3snd_QueueSound(int, int, char*, int, int);
void __cdecl sb_StopVoice(void*, int);
void __cdecl gm_AddTime(void*, int, int, int);
char* __cdecl cut_FindCutsceneById(int);
int __cdecl cut_RemoveParticipant(int, int);
void __cdecl cm_RequestRemoveCutsceneParticipant(int, int);
int __cdecl fcn_00503fe0(int, int, int);
void __cdecl d2_EnterBuildingObjekt(char*, int, char*);
void __cdecl io_ClearInputState(void);
void __cdecl d2_CloseActionPopup(char*);

/* ADDRESS: GOLDTL 0x0055f590 */
void __cdecl he_StartEventMessagebox(char* e)
{
    *(int*) (e + 0x70) = 0;
    *(int*) (e + 0xec) = 0;
    if (g_7f4ca2[*(unsigned short*) (e + 8)].kind == 6)
        return;
    he_FreeAction(e);
}

/* One stage of the event message-box tick; state lives at +0x70. */
/* ADDRESS: GOLDTL 0x0055f5c0 */
void __cdecl he_RunEventMessagebox(char* e)
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
                d2_CreateActionPopupSlot(e, 0, 0, "misc\\EventMessagebox_QJ_BIG", *(int*) (e + 0xac));
            else
                d2_CreateActionPopupSlot(e, 0, 0, "misc\\EventMessagebox_QJ", *(int*) (e + 0xac));
            if (*(int*) (e + 0x74) == 0) {
                he_FreeAction(e);
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
            d2_CreateActionPopupSlot(e, 0, 0, "misc\\EventMessagebox_BIG", *(int*) (e + 0xac));
            if (*(int*) (e + 0x74) == 0)
                goto done;
            fcn_004727a0(*(int*) (*(int*) (e + 0x74) + 8), 1);
            fcn_00519190(0x1ba3);
        } else if (*(unsigned char*) (e + 0xf0) & 0x20) {
            d2_CreateActionPopupSlot(e, 0, 0, "misc\\EventMsgbox_History", *(int*) (e + 0xac));
            if (*(int*) (e + 0x74) == 0)
                goto done;
            fcn_004727a0(*(int*) (*(int*) (e + 0x74) + 8), 1);
            fcn_00519190(0x1ba3);
        } else if (*(unsigned char*) (e + 0xf0) & 4) {
            d2_CreateActionPopupSlot(e, 0, 0, "misc\\EventMessagebox_Cutscenes", *(int*) (e + 0xac));
        } else if (*(unsigned char*) (e + 0xf0) & 0x40) {
            d2_CreateActionPopupSlot(e, 0, 0, "misc\\EventMessagebox_Help", *(int*) (e + 0xac));
        } else {
            d2_CreateActionPopupSlot(e, 0, 0, "misc\\EventMessagebox", *(int*) (e + 0xac));
            if (*(int*) (e + 0x74) == 0)
                goto done;
            fcn_004727a0(*(int*) (*(int*) (e + 0x74) + 8), 1);
            fcn_00519190(0x7d);
        }
done:
        if (*(int*) (e + 0x74) == 0) {
            he_FreeAction(e);
            return;
        }
        d2_CenterDialogWindows(*(int*) (*(int*) (e + 0x74) + 8));
        fcn_004727a0(*(int*) (*(int*) (e + 0x74) + 8), 0);
        fcn_00519190(0x679060, *(int*) (e + 0x7c));
        if (g_774964 != 2)
            sb_PlayVoice((int) g_7747b8, "NeueMessage_s_01", 1, 0x3f, 0x7f, 0, 0);
        if (*(unsigned char*) (e + 0xf0) & 8)
            d2_HighlightSelectedControl(*(int*) (e + 0x74));
        if (*(unsigned char*) (e + 0xf0) & 0x10) {
            str = *(char**) (e + 0x7c);
            str = str + strlen(str) + 1;
            memcpy(text, str, strlen(str) + 1);
            *(int*) (e + 0xec) = d3snd_QueueSound(-7, 0, text, 0, 0x7d0);
        }
        *(pos14_7f4c00*) (e + 0x44) = gm_GameTime;
        *(pos14_7f4c00*) (e + 0x52) = gm_GameTime;






        if (*(unsigned char*) (e + 0xf0) & 4) {
            gm_AddTime(e + 0x52, 0x18, 0, 0);
        } else {
            gm_AddTime(e + 0x52, 8, 0, 0);
            if (*(unsigned short*) (e + 0x56) < 6)
                gm_AddTime(e + 0x52, 8, 0, 0);
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
            if (gm_CompareGameTime((void*) &gm_GameTime, rec + 0x18) <= 0)
                goto tail;
            if (*(unsigned char*) (rec + 0x26) & 0x80) {
                if (!((*(unsigned char*) (e + 0xf0) & 2)
                      && *(int*) (e + 0xb0) != -1
                      && (*(unsigned char*) (rec + 0x26) & 0x10)))
                    *(int*) (rec + 4) = 1;
                goto exit_b;
            }
            if (g_7747b0 & 8) {
                cut_RemoveParticipant(*(int*) (e + 0xb8), *(int*) (g_774970 * 0x21c + (unsigned long)&g_7f4ca4));
            } else if (g_7747b0 & 4) {
                cm_RequestRemoveCutsceneParticipant(*(int*) (e + 0xb8), *(int*) (g_774970 * 0x21c + (unsigned long)&g_7f4ca4));
            }
            *(int*) (e + 0x70) = state;
            goto tail;
        } else if (gm_CompareGameTime((void*) &gm_GameTime, e + 0x52) > 0) {
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
        if (g_100f1dc != 2) {
            if (g_100f1dc == 1)
                goto body1;
test_dl:
            if (!g_7749e8)
                goto exit_a;
body1:
            {
                unsigned char flags = *(unsigned char*) (e + 0xf0);
                if (flags & 4) {
                    rec = cut_FindCutsceneById(*(int*) (e + 0xb8));
                    if (rec != 0) {
                        if (*(unsigned char*) (rec + 0x26) & 0x80) {
                            if (!((flags & 2)
                                  && *(int*) (e + 0xb0) != -1
                                  && (*(unsigned char*) (rec + 0x26) & 0x10)))
                                *(int*) (rec + 4) = 1;
                        } else if (g_7747b0 & 8) {
                            cut_RemoveParticipant(*(int*) (e + 0xb8), *(int*) (g_774970 * 0x21c + (unsigned long)&g_7f4ca4));
                        } else if (g_7747b0 & 4) {
                            cm_RequestRemoveCutsceneParticipant(*(int*) (e + 0xb8), *(int*) (g_774970 * 0x21c + (unsigned long)&g_7f4ca4));
                        }
                    }
                }
                if ((flags & 0x10) && *(int*) (e + 0xec) != 0) {
                    sb_StopVoice(*(void**) (e + 0xec), 0);
                    *(int*) (e + 0xec) = 0;
                }
                if (flags & 0x40) {
                    if (!(*(unsigned char*) &g_7747b0 & 4))
                        *(int*) &g_6b7fc0 = 0;
                }
            }
            if (g_14ce8d8 != 0) {
                g_6b5c8c = 1;
                io_ClearInputState();
            }
            d2_CloseActionPopup(e);
            he_FreeAction(e);
exit_a:
            g_7749e8 = 0;
            return;
        } else {
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
                d2_EnterBuildingObjekt(rec, *(int*) (e + 0xb4), e + 0xbc);
            }
            if ((*(unsigned char*) (e + 0xf0) & 0x10) && *(int*) (e + 0xec) != 0) {
                sb_StopVoice(*(void**) (e + 0xec), 0);
                *(int*) (e + 0xec) = 0;
            }
            if (*(unsigned char*) (e + 0xf0) & 0x40) {
                if (!(*(unsigned char*) &g_7747b0 & 4))
                    *(int*) &g_6b7fc0 = 0;
            }
            if (g_14ce8d8 != 0) {
                g_6b5c8c = 1;
                io_ClearInputState();
            }
            goto exit_b;
        }
exit_clear:
        if (*(unsigned char*) (e + 0xf0) & 0x40) {
            if (!(*(unsigned char*) &g_7747b0 & 4))
                *(int*) &g_6b7fc0 = 0;
        }
exit_b:
        d2_CloseActionPopup(e);
        he_FreeAction(e);
        return;
    case -2:
    case -1:
        if ((*(unsigned char*) (e + 0xf0) & 0x10) && *(int*) (e + 0xec) != 0) {
            sb_StopVoice(*(void**) (e + 0xec), 0);
            *(int*) (e + 0xec) = 0;
        }
        goto exit_clear;
    default:
        return;
    }
}
