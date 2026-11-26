#include <string.h>

extern int d2_CurrentWindowId;

void __cdecl ls_CaptureSavePreview(void);
void __cdecl d2_EnterMenuScreen(void);
int __cdecl fcn_00470820(int, int, char *);
void __cdecl fcn_00537320(int);
void __cdecl fcn_00471db0(int, int);
void __cdecl fcn_00471d80(int, int);
int __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00525ef0(void);
int __cdecl fcn_005e3b10(int, int, int);
int __cdecl fcn_00472640(int, int);
void __cdecl d2_PauseTutorialUpdates(void);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl fcn_004c3140(void *);
void __cdecl fcn_004c3a10(void);
int __cdecl main_RunFrameLoop(void *, int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl fcn_00471af0(int, int);
int __cdecl d2_ShowLoadGameMenu(void);
int __cdecl d2_RunSaveGameDialog(void *);
int __cdecl d2_ShowNetworkLoadGame(void *);
void __cdecl io_FormatTextBuffer(char *, int, ...);
int __cdecl fcn_005dfe80(char *, int);
int __cdecl cm_SendQuitGameCommand(void);
int __cdecl cm_GetCommandStatus(int);
void __cdecl fcn_00535960(void);
void __cdecl main_ExitToFrameHandler(int);
void __cdecl fcn_005e3520(void);
void __cdecl fcn_005e2b60(void);
void __cdecl d2_ShowSoundOptions(void);
void __cdecl fcn_005e3c40(void);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);
void __cdecl fcn_004c39b0(void);
void __cdecl fcn_0057e870(void);

/* ADDRESS: GOLDTL 0x005e43f0 */
void __cdecl fcn_005e43f0(void)
{
    char message[0x200], preview[0x9600];
    int dialog, a, b, c, d, e, f, g, group, current, handle;
    int saved;

    ls_CaptureSavePreview();
    memcpy(preview, (void *)0x7ea3c0, 0x9600);
    d2_EnterMenuScreen();
    dialog = fcn_00470820(0, 0, (char *)0x6ad384);
    fcn_00537320(0x24087);
    fcn_00471db0(dialog, 1);
    fcn_00471d80(dialog, 2);
    d2_SetForm(dialog, 0);
    fcn_005340f0(d2_CurrentWindowId);
    fcn_00525ef0();
    d2_SetForm(0, 0);
    a = fcn_005e3b10(0, *(int *)0x14ac490, d2_CurrentWindowId);
    b = fcn_005e3b10(1, *(int *)0x14ac494, d2_CurrentWindowId);
    if (*(unsigned char *)0x7747b0 & 4) {
        fcn_00472640(a, 0);
        if (!(*(unsigned char *)0x7747b0 & 0x10)) fcn_00472640(b, 0);
    }
    if (*(signed char *)0x7747b0 & 0x80) {
        d2_PauseTutorialUpdates();
        fcn_00472640(a, 0);
        fcn_00472640(b, 0);
    }
    *(unsigned char *)0x774966 = 1;
    c = fcn_005e3b10(2, *(int *)0x14ac498, d2_CurrentWindowId);
    d = fcn_005e3b10(3, *(int *)0x14ac49c, d2_CurrentWindowId);
    e = fcn_005e3b10(4, *(int *)0x14ac4a0, d2_CurrentWindowId);
    f = fcn_005e3b10(5, *(int *)0x14ac4a4, d2_CurrentWindowId);
    if (!(*(unsigned char *)0x7747b0 & 4)) *(int *)0x6b7fc0 = 1;
    g = fcn_005e3b10(7, *(int *)0x14ac4a8, d2_CurrentWindowId);
    group = d2_CreateRadioGroup(7, a, b, c, d, e, f, g);
    fcn_004c3140(0);
    saved = *(unsigned char *)0x772d10;
    *(unsigned char *)0x772d10 = 0;
    fcn_004c3a10();
    while (main_RunFrameLoop((void *)fcn_005e43f0, 0x24087)) {
        d2_UpdateRadioGroup(group);
        if (*(int *)0x14ce8e0 || *(unsigned char *)0x14cf950 == 1) *(int *)0x774654 = 1;
        if (*(int *)0x14ce8d8) {
            current = *(int *)0x67d370;
            if (current != -1) {
                if (current == a) {
                    fcn_00471af0(dialog, 0);
                    if (d2_ShowLoadGameMenu()) {
                        *(int *)0x774958 = 1;
                        *(int *)0x774954 = 1;
                        main_ExitToFrameHandler(0x5438c0);
                    } else fcn_00471af0(dialog, 1);
                } else if (current == b) {
                    fcn_00471af0(dialog, 0);
                    if (!(*(unsigned char *)0x7747b0 & 4)) d2_RunSaveGameDialog(preview);
                    else d2_ShowNetworkLoadGame(preview);
                    fcn_00471af0(dialog, 1);
                } else if (current == f) {
                    fcn_00471af0(dialog, 0);
                    io_FormatTextBuffer(message, 0x1ca4);
                    if (fcn_005dfe80(message, 1)) {
                        handle = cm_SendQuitGameCommand();
                        while (handle != -1) {
                            if (cm_GetCommandStatus(handle)) {
                                break;
                            }
                            fcn_00535960();
                        }
                        *(int *)0x774954 = 1;
                        main_ExitToFrameHandler(0x5438c0);
                    } else fcn_00471af0(dialog, 1);
                } else if (current == c) {
                    fcn_00471af0(dialog, 0); fcn_005e3520(); fcn_00471af0(dialog, 1);
                } else if (current == d) {
                    fcn_00471af0(dialog, 0); fcn_005e2b60(); fcn_00471af0(dialog, 1);
                } else if (current == e) {
                    fcn_00471af0(dialog, 0); d2_ShowSoundOptions(); fcn_00471af0(dialog, 1);
                } else if (current == g) *(int *)0x774654 = 1;
            }
        }
    }
    fcn_005e3c40();
    if (!(*(unsigned char *)0x7747b0 & 4)) *(int *)0x6b7fc0 = 0;
    *(unsigned char *)0x774966 = 0;
    d2_ClearRadioGroup(group);
    d2_DestroyForm(dialog);
    fcn_004c3140((void *)(unsigned int)*(unsigned char *)0x7766a1);
    *(unsigned char *)0x772d10 = saved;
    fcn_004c39b0();
    if ((*(signed char *)0x7747b0 & 0x80) && !*(int *)0x774954) fcn_0057e870();
}
