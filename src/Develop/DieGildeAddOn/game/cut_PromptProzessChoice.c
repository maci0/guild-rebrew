#include <string.h>
#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/event_callbacks.h"

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterForm(int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
int __cdecl d2_UpdateProgressBar(int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl gm_GenerateShuffledIndices(unsigned char, int*);
int __cdecl d2_GetWindowListItem(int, int, int);
unsigned int __cdecl cut_RandMod(unsigned int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
int __cdecl gm_CalcProzessBasePenalty(char*);
int __cdecl gm_ValidateProzessCharge(char*, unsigned int);
void __cdecl d2_SetElementEnabled(int, int);
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char* d2_CurrentWindow;
#ifdef REBREW_GOLD
#define cut_SECOND_CHOICE 0
#define cut_WINDOW_WIDTH (*(short*) (d2_CurrentWindow + 8))
#else
#define cut_SECOND_CHOICE 2
#define cut_WINDOW_WIDTH (*(int*) (d2_CurrentWindow + 12))
#endif

/* Inferred name and source home; the native registry selects this two-argument callback. */
/* ADDRESS: GOLDTL 0x004df1b0 */
void __cdecl cut_PromptProzessChoice(char* participant, int* action)
{
    /* Reference allocator order needs two extra register candidates here. */
    register int _dummy_19 = 0;
    register int _dummy_4 = 0;
    int buttons[7];
    unsigned char rates[7] = {8, 10, 12, 15, 18, 21, 24};
    int available[3];
    int order[7];
    char* own;
    char* other;
    int dialog;
    int timer;
    int value;
    int base;
    int i;
    int choice;
    int text_id;

    *(int*) (participant + 0x94) = -1;
    memset(buttons, 0xff, sizeof(buttons));
    own = gm_LookupEntityRecordById(*(int*) (participant + 0x10));
    other = gm_LookupEntityRecordById(action[6]);
    switch (action[0]) {
    case 0:
        if (*(int*) (participant + 0x10) != action[6]) return;
        *(float*) (participant + 0x98) = *(int*) (other + 0x24) + *(float*) (other + 0x1c);
        dialog = d2_LoadForm(0, 0, "cutscenes\\prozess");
        d2_CenterForm(dialog, 3);
        d2_SetForm(dialog, 0);
        io_AppendText(0x14bc, *(unsigned short*) own);
        d2_DialogButtonAction = -1;
        *(int*) (participant + 0x94) = 0;
        timer = d2_AddWindowValueGauge((cut_WINDOW_WIDTH - 300) / 2 - 8,
            8, 300, 0, 100, 0x75, 0x42, d2_CurrentWindowId);
        d2_UpdateProgressBar(timer, 1500, 1);
        while (main_RunFrameLoop((void*) cut_PromptProzessChoice, cut_EventLoopFlags)) {
            if (!d2_UpdateProgressBar(timer, 0, 0)) {
                d2_DialogCloseRequested = 1;
            } else if (d2_DialogButtonAction != -1) {
                d2_DialogCloseRequested = 1;
                if (d2_DialogButtonAction == 1) {
                    *(int*) (participant + 0x94) = 0;
                } else if (d2_DialogButtonAction == cut_SECOND_CHOICE) {
                    *(int*) (participant + 0x94) = 1;
                }
            }
        }
        d2_DestroyForm(dialog);
        return;
    case 1:
        if (*(int*) (participant + 0x10) != action[5]) return;
        dialog = d2_LoadForm(0, 0, "cutscenes\\prozess");
        d2_CenterForm(dialog, 3);
        d2_SetForm(dialog, 0);
        io_AppendText(0x14cb, *(unsigned short*) own, *(unsigned short*) other);
        d2_DialogButtonAction = -1;
        *(int*) (participant + 0x94) = 0;
        timer = d2_AddWindowValueGauge((cut_WINDOW_WIDTH - 300) / 2 - 8,
            8, 300, 0, 100, 0x75, 0x42, d2_CurrentWindowId);
        d2_UpdateProgressBar(timer, 1500, 1);
        while (main_RunFrameLoop((void*) cut_PromptProzessChoice, cut_EventLoopFlags)) {
            if (!d2_UpdateProgressBar(timer, 0, 0)) {
                d2_DialogCloseRequested = 1;
            } else if (d2_DialogButtonAction != -1) {
                d2_DialogCloseRequested = 1;
                if (d2_DialogButtonAction == 1) {
                    *(int*) (participant + 0x94) = 0;
                } else if (d2_DialogButtonAction == cut_SECOND_CHOICE) {
                    *(int*) (participant + 0x94) = 1;
                }
            }
        }
        d2_DestroyForm(dialog);
        return;
    case 2:
        if (*(int*) (participant + 0x10) != action[5]) return;
        gm_GenerateShuffledIndices(7, order);
        value = (gm_CalcPersonWealth(*(unsigned short*) own)
            + gm_CalcPersonWealth(*(unsigned short*) other)) / 2000;
        dialog = d2_LoadForm(0, 0, "cutscenes\\folterwahl");
        d2_CenterForm(dialog, 3);
        d2_SetForm(dialog, 0);
        io_AppendText(0x14db, *(unsigned short*) own);
        for (i = 0; i < 3; i++) {
            choice = order[i];
            buttons[i] = d2_GetWindowListItem(dialog, 0, io_AppendText(0x14dc,
                choice * 2 + 0xb20, rates[choice] * value));
        }
        d2_DialogButtonAction = -1;
        *(int*) (participant + 0x94) = order[cut_RandMod(3)];
        timer = d2_AddWindowValueGauge((cut_WINDOW_WIDTH - 300) / 2 - 8,
            8, 300, 0, 100, 0x75, 0x42, d2_CurrentWindowId);
        d2_UpdateProgressBar(timer, 1500, 1);
        while (main_RunFrameLoop((void*) cut_PromptProzessChoice, cut_EventLoopFlags)) {
            if (!d2_UpdateProgressBar(timer, 0, 0)) {
                d2_DialogCloseRequested = 1;
            } else if (d2_DialogButtonAction != -1) {
                for (i = 0; i < 3; i++) {
                    if (d2_CurrentElementId == buttons[i]) {
                        *(int*) (participant + 0x94) = order[i];
                        d2_DialogCloseRequested = 1;
                        break;
                    }
                }
            }
        }
        d2_DestroyForm(dialog);
        return;
    case 3:
        if (*(int*) (participant + 0x10) != action[10]) return;
        dialog = d2_LoadForm(0, 0, "cutscenes\\folterwahl");
        d2_CenterForm(dialog, 3);
        d2_SetForm(dialog, 0);
        io_AppendText(0x14e3, *(unsigned short*) own, *(unsigned short*) other, *(unsigned short*) other);
        d2_DialogButtonAction = -1;
        *(int*) (participant + 0x94) = 0;
        timer = d2_AddWindowValueGauge((cut_WINDOW_WIDTH - 300) / 2 - 8,
            8, 300, 0, 100, 0x75, 0x42, d2_CurrentWindowId);
        d2_UpdateProgressBar(timer, 1500, 1);
        while (main_RunFrameLoop((void*) cut_PromptProzessChoice, cut_EventLoopFlags)) {
            if (!d2_UpdateProgressBar(timer, 0, 0)) {
                d2_DialogCloseRequested = 1;
            } else if (d2_DialogButtonAction != -1) {
                d2_DialogCloseRequested = 1;
                if (d2_DialogButtonAction == 1) {
                    *(int*) (participant + 0x94) = 0;
                } else if (d2_DialogButtonAction == cut_SECOND_CHOICE) {
                    *(int*) (participant + 0x94) = 1;
                    cm_RequestCopyEntityData(*(int*) (own + 4), *(int*) (other + 4), 0x23, 1);
                }
            }
        }
        d2_DestroyForm(dialog);
        return;
    case 6:
        if (*(int*) (participant + 0x10) != action[6]) return;
        dialog = d2_LoadForm(0, 0, "cutscenes\\prozess");
        d2_CenterForm(dialog, 3);
        d2_SetForm(dialog, 0);
        io_AppendText(0x1512, *(unsigned short*) own);
        d2_DialogButtonAction = -1;
        *(int*) (participant + 0x94) = 0;
        timer = d2_AddWindowValueGauge((cut_WINDOW_WIDTH - 300) / 2 - 8,
            8, 300, 0, 100, 0x75, 0x42, d2_CurrentWindowId);
        d2_UpdateProgressBar(timer, 1500, 1);
        while (main_RunFrameLoop((void*) cut_PromptProzessChoice, cut_EventLoopFlags)) {
            if (!d2_UpdateProgressBar(timer, 0, 0)) {
                d2_DialogCloseRequested = 1;
            } else if (d2_DialogButtonAction != -1) {
                d2_DialogCloseRequested = 1;
                if (d2_DialogButtonAction == 1) {
                    *(int*) (participant + 0x94) = 1;
                } else if (d2_DialogButtonAction == cut_SECOND_CHOICE) {
                    *(int*) (participant + 0x94) = 0;
                }
            }
        }
        d2_DestroyForm(dialog);
        return;
    case 4:
        value = *(int*) (participant + 0x10);
        if (value != action[7] && value != action[8] && value != action[9]) return;
        dialog = d2_LoadForm(0, 0, "cutscenes\\prozess");
        d2_CenterForm(dialog, 3);
        d2_SetForm(dialog, 0);
        io_AppendText(0x1529, *(unsigned short*) own);
        io_AppendText(0x152a);
        io_AppendText(0x152b);
        d2_DialogButtonAction = -1;
        *(int*) (participant + 0x94) = 1;
        timer = d2_AddWindowValueGauge((cut_WINDOW_WIDTH - 300) / 2 - 8,
            8, 300, 0, 100, 0x75, 0x42, d2_CurrentWindowId);
        d2_UpdateProgressBar(timer, 1500, 1);
        while (main_RunFrameLoop((void*) cut_PromptProzessChoice, cut_EventLoopFlags)) {
            if (!d2_UpdateProgressBar(timer, 0, 0)) {
                d2_DialogCloseRequested = 1;
            } else if (d2_DialogButtonAction != -1) {
                d2_DialogCloseRequested = 1;
                if (d2_DialogButtonAction == 1) {
                    *(int*) (participant + 0x94) = 1;
                } else if (d2_DialogButtonAction == cut_SECOND_CHOICE) {
                    *(int*) (participant + 0x94) = 0;
                }
            }
        }
        d2_DestroyForm(dialog);
        return;
    case 5:
        if (*(int*) (participant + 0x10) != action[7]) return;
        available[0] = -1;
        available[1] = -1;
        available[2] = -1;
        base = gm_CalcProzessBasePenalty((char*) action);
        dialog = d2_LoadForm(0, 0, "cutscenes\\prozess");
        d2_CenterForm(dialog, 3);
        d2_SetForm(dialog, 0);
        io_AppendText(0x1532, *(unsigned short*) own);
        i = 0;
        text_id = base * 3 + 0x1534;
        do {
            choice = d2_GetWindowListItem(dialog, 0, io_AppendText(0x1533, text_id));
            available[i] = choice;
            if (gm_ValidateProzessCharge(other, i + base)) d2_SetElementEnabled(choice, 0);
            i++;
            text_id += 3;
        } while (i < 3);
        if (available[1] != -1) {
            *(int*) (participant + 0x94) = base + 1;
        } else if (cut_RandMod(2)) {
            *(int*) (participant + 0x94) = base + 2;
        } else {
            *(int*) (participant + 0x94) = base;
        }
        d2_DialogButtonAction = -1;
        timer = d2_AddWindowValueGauge((cut_WINDOW_WIDTH - 300) / 2 - 8,
            8, 300, 0, 100, 0x75, 0x42, d2_CurrentWindowId);
        d2_UpdateProgressBar(timer, 1500, 1);
        while (main_RunFrameLoop((void*) cut_PromptProzessChoice, cut_EventLoopFlags)) {
            if (!d2_UpdateProgressBar(timer, 0, 0)) {
                d2_DialogCloseRequested = 1;
            } else if (d2_DialogButtonAction != -1) {
                d2_DialogCloseRequested = 1;
                if (d2_CurrentElementId == available[0]) {
                    *(int*) (participant + 0x94) = base;
                } else if (d2_CurrentElementId == available[1]) {
                    *(int*) (participant + 0x94) = base + 1;
                } else if (d2_CurrentElementId == available[2]) {
                    *(int*) (participant + 0x94) = base + 2;
                }
            }
        }
        d2_DestroyForm(dialog);
        return;
    }
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_100e760[2684];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_100e778[40];
unsigned char _dpad_100e860[800];
unsigned char _dpad_100eb84[1020];
unsigned char _dpad_100ef84[540];
unsigned char _dpad_100f1a4[4];
unsigned char _dpad_100f1ac[12];
#endif
