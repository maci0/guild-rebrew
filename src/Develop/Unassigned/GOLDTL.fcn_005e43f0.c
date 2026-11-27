#include <string.h>

extern int d2_CurrentWindowId;

void __cdecl ls_CaptureSavePreview(void);
void __cdecl d2_EnterMenuScreen(void);
int __cdecl d2_LoadForm(int, int, char *);
void __cdecl d2_UpdateViewportCenter(int);
void __cdecl d2_PositionFormWindows(int, int);
void __cdecl fcn_00471d80(int, int);
int __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_ResetUiInputAndBounds(void);
int __cdecl d2_AddMenuOptionButton(int, int, int);
int __cdecl d2_SetElementEnabled(int, int);
void __cdecl d2_PauseTutorialUpdates(void);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl fcn_004c3140(void *);
void __cdecl fcn_004c3a10(void);
int __cdecl main_RunFrameLoop(void *, int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl d2_ShowLoadGameMenu(void);
int __cdecl d2_RunSaveGameDialog(void *);
int __cdecl d2_ShowNetworkLoadGame(void *);
void __cdecl io_FormatTextBuffer(char *, int, ...);
int __cdecl d2_ConfirmTextIdMessageBox(char *, int);
int __cdecl cm_SendQuitGameCommand(void);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
void __cdecl main_ExitToFrameHandler(int);
void __cdecl d2_ShowGameOptions(void);
void __cdecl fcn_005e2b60(void);
void __cdecl d2_ShowSoundOptions(void);
void __cdecl d2_RestoreHudAfterPause(void);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);
void __cdecl fcn_004c39b0(void);
void __cdecl d2_ResumeTutorialUpdates(void);

/* ADDRESS: GOLDTL 0x005e43f0 */
void __cdecl d2_RunPauseOptionsMenu(void)
{
    char message[0x200], preview[0x9600];
    int dialog, a, b, c, d, e, f, g, group, current, handle;
    int saved;

    ls_CaptureSavePreview();
    memcpy(preview, (void *)0x7ea3c0, 0x9600);
    d2_EnterMenuScreen();
    dialog = d2_LoadForm(0, 0, (char *)0x6ad384);
    d2_UpdateViewportCenter(0x24087);
    d2_PositionFormWindows(dialog, 1);
    fcn_00471d80(dialog, 2);
    d2_SetForm(dialog, 0);
    d2_InitWindowBounds(d2_CurrentWindowId);
    d2_ResetUiInputAndBounds();
    d2_SetForm(0, 0);
    a = d2_AddMenuOptionButton(0, *(int *)0x14ac490, d2_CurrentWindowId);
    b = d2_AddMenuOptionButton(1, *(int *)0x14ac494, d2_CurrentWindowId);
    if (*(unsigned char *)0x7747b0 & 4) {
        d2_SetElementEnabled(a, 0);
        if (!(*(unsigned char *)0x7747b0 & 0x10)) d2_SetElementEnabled(b, 0);
    }
    if (*(signed char *)0x7747b0 & 0x80) {
        d2_PauseTutorialUpdates();
        d2_SetElementEnabled(a, 0);
        d2_SetElementEnabled(b, 0);
    }
    *(unsigned char *)0x774966 = 1;
    c = d2_AddMenuOptionButton(2, *(int *)0x14ac498, d2_CurrentWindowId);
    d = d2_AddMenuOptionButton(3, *(int *)0x14ac49c, d2_CurrentWindowId);
    e = d2_AddMenuOptionButton(4, *(int *)0x14ac4a0, d2_CurrentWindowId);
    f = d2_AddMenuOptionButton(5, *(int *)0x14ac4a4, d2_CurrentWindowId);
    if (!(*(unsigned char *)0x7747b0 & 4)) *(int *)0x6b7fc0 = 1;
    g = d2_AddMenuOptionButton(7, *(int *)0x14ac4a8, d2_CurrentWindowId);
    group = d2_CreateRadioGroup(7, a, b, c, d, e, f, g);
    fcn_004c3140(0);
    saved = *(unsigned char *)0x772d10;
    *(unsigned char *)0x772d10 = 0;
    fcn_004c3a10();
    while (main_RunFrameLoop((void *)d2_RunPauseOptionsMenu, 0x24087)) {
        d2_UpdateRadioGroup(group);
        if (*(int *)0x14ce8e0 || *(unsigned char *)0x14cf950 == 1) *(int *)0x774654 = 1;
        if (*(int *)0x14ce8d8) {
            current = *(int *)0x67d370;
            if (current != -1) {
                if (current == a) {
                    d2_SetFormVisibility(dialog, 0);
                    if (d2_ShowLoadGameMenu()) {
                        *(int *)0x774958 = 1;
                        *(int *)0x774954 = 1;
                        main_ExitToFrameHandler(0x5438c0);
                    } else d2_SetFormVisibility(dialog, 1);
                } else if (current == b) {
                    d2_SetFormVisibility(dialog, 0);
                    if (!(*(unsigned char *)0x7747b0 & 4)) d2_RunSaveGameDialog(preview);
                    else d2_ShowNetworkLoadGame(preview);
                    d2_SetFormVisibility(dialog, 1);
                } else if (current == f) {
                    d2_SetFormVisibility(dialog, 0);
                    io_FormatTextBuffer(message, 0x1ca4);
                    if (d2_ConfirmTextIdMessageBox(message, 1)) {
                        handle = cm_SendQuitGameCommand();
                        while (handle != -1) {
                            if (cm_GetCommandStatus(handle)) {
                                break;
                            }
                            cm_StepCommandQueue();
                        }
                        *(int *)0x774954 = 1;
                        main_ExitToFrameHandler(0x5438c0);
                    } else d2_SetFormVisibility(dialog, 1);
                } else if (current == c) {
                    d2_SetFormVisibility(dialog, 0); d2_ShowGameOptions(); d2_SetFormVisibility(dialog, 1);
                } else if (current == d) {
                    d2_SetFormVisibility(dialog, 0); fcn_005e2b60(); d2_SetFormVisibility(dialog, 1);
                } else if (current == e) {
                    d2_SetFormVisibility(dialog, 0); d2_ShowSoundOptions(); d2_SetFormVisibility(dialog, 1);
                } else if (current == g) *(int *)0x774654 = 1;
            }
        }
    }
    d2_RestoreHudAfterPause();
    if (!(*(unsigned char *)0x7747b0 & 4)) *(int *)0x6b7fc0 = 0;
    *(unsigned char *)0x774966 = 0;
    d2_ClearRadioGroup(group);
    d2_DestroyForm(dialog);
    fcn_004c3140((void *)(unsigned int)*(unsigned char *)0x7766a1);
    *(unsigned char *)0x772d10 = saved;
    fcn_004c39b0();
    if ((*(signed char *)0x7747b0 & 0x80) && !*(int *)0x774954) d2_ResumeTutorialUpdates();
}
