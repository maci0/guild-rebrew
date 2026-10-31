#include <string.h>
#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/event_callbacks.h"

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl fcn_004e6e20(int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00508cf0(unsigned char, int*);
int __cdecl fcn_00472250(int, int, int);
unsigned int __cdecl fcn_004e6cb0(unsigned int);
void __cdecl fcn_004c54c0(int, int, int, int);
int __cdecl fcn_00493be0(char*);
int __cdecl fcn_004f6810(char*, unsigned int);
void __cdecl fcn_00472640(int, int);
extern int g_100f1dc;
extern int g_774654;
extern int g_67d370;
extern int g_68bfb8;
extern int g_772514;
extern char* g_77255c;
#ifdef REBREW_GOLD
#define cut_SECOND_CHOICE 0
#define cut_WINDOW_WIDTH (*(short*) (g_77255c + 8))
#else
#define cut_SECOND_CHOICE 2
#define cut_WINDOW_WIDTH (*(int*) (g_77255c + 12))
#endif

/* Inferred name and source home; the native registry selects this two-argument callback. */
/* ADDRESS: GOLDTL 0x004df1b0 */
void __cdecl fcn_004df1b0(char* participant, int* action)
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
        dialog = fcn_00470820(0, 0, "cutscenes\\prozess");
        fcn_00471d80(dialog, 3);
        d2_SetForm(dialog, 0);
        io_AppendText(0x14bc, *(unsigned short*) own);
        g_100f1dc = -1;
        *(int*) (participant + 0x94) = 0;
        timer = fcn_004677e0((cut_WINDOW_WIDTH - 300) / 2 - 8,
            8, 300, 0, 100, 0x75, 0x42, g_772514);
        fcn_004e6e20(timer, 1500, 1);
        while (fcn_005373e0((void*) fcn_004df1b0, g_68bfb8)) {
            if (!fcn_004e6e20(timer, 0, 0)) {
                g_774654 = 1;
            } else if (g_100f1dc != -1) {
                g_774654 = 1;
                if (g_100f1dc == 1) {
                    *(int*) (participant + 0x94) = 0;
                } else if (g_100f1dc == cut_SECOND_CHOICE) {
                    *(int*) (participant + 0x94) = 1;
                }
            }
        }
        fcn_00471e30(dialog);
        return;
    case 1:
        if (*(int*) (participant + 0x10) != action[5]) return;
        dialog = fcn_00470820(0, 0, "cutscenes\\prozess");
        fcn_00471d80(dialog, 3);
        d2_SetForm(dialog, 0);
        io_AppendText(0x14cb, *(unsigned short*) own, *(unsigned short*) other);
        g_100f1dc = -1;
        *(int*) (participant + 0x94) = 0;
        timer = fcn_004677e0((cut_WINDOW_WIDTH - 300) / 2 - 8,
            8, 300, 0, 100, 0x75, 0x42, g_772514);
        fcn_004e6e20(timer, 1500, 1);
        while (fcn_005373e0((void*) fcn_004df1b0, g_68bfb8)) {
            if (!fcn_004e6e20(timer, 0, 0)) {
                g_774654 = 1;
            } else if (g_100f1dc != -1) {
                g_774654 = 1;
                if (g_100f1dc == 1) {
                    *(int*) (participant + 0x94) = 0;
                } else if (g_100f1dc == cut_SECOND_CHOICE) {
                    *(int*) (participant + 0x94) = 1;
                }
            }
        }
        fcn_00471e30(dialog);
        return;
    case 2:
        if (*(int*) (participant + 0x10) != action[5]) return;
        fcn_00508cf0(7, order);
        value = (gm_WalkEntityChain(*(unsigned short*) own)
            + gm_WalkEntityChain(*(unsigned short*) other)) / 2000;
        dialog = fcn_00470820(0, 0, "cutscenes\\folterwahl");
        fcn_00471d80(dialog, 3);
        d2_SetForm(dialog, 0);
        io_AppendText(0x14db, *(unsigned short*) own);
        for (i = 0; i < 3; i++) {
            choice = order[i];
            buttons[i] = fcn_00472250(dialog, 0, io_AppendText(0x14dc,
                choice * 2 + 0xb20, rates[choice] * value));
        }
        g_100f1dc = -1;
        *(int*) (participant + 0x94) = order[fcn_004e6cb0(3)];
        timer = fcn_004677e0((cut_WINDOW_WIDTH - 300) / 2 - 8,
            8, 300, 0, 100, 0x75, 0x42, g_772514);
        fcn_004e6e20(timer, 1500, 1);
        while (fcn_005373e0((void*) fcn_004df1b0, g_68bfb8)) {
            if (!fcn_004e6e20(timer, 0, 0)) {
                g_774654 = 1;
            } else if (g_100f1dc != -1) {
                for (i = 0; i < 3; i++) {
                    if (g_67d370 == buttons[i]) {
                        *(int*) (participant + 0x94) = order[i];
                        g_774654 = 1;
                        break;
                    }
                }
            }
        }
        fcn_00471e30(dialog);
        return;
    case 3:
        if (*(int*) (participant + 0x10) != action[10]) return;
        dialog = fcn_00470820(0, 0, "cutscenes\\folterwahl");
        fcn_00471d80(dialog, 3);
        d2_SetForm(dialog, 0);
        io_AppendText(0x14e3, *(unsigned short*) own, *(unsigned short*) other, *(unsigned short*) other);
        g_100f1dc = -1;
        *(int*) (participant + 0x94) = 0;
        timer = fcn_004677e0((cut_WINDOW_WIDTH - 300) / 2 - 8,
            8, 300, 0, 100, 0x75, 0x42, g_772514);
        fcn_004e6e20(timer, 1500, 1);
        while (fcn_005373e0((void*) fcn_004df1b0, g_68bfb8)) {
            if (!fcn_004e6e20(timer, 0, 0)) {
                g_774654 = 1;
            } else if (g_100f1dc != -1) {
                g_774654 = 1;
                if (g_100f1dc == 1) {
                    *(int*) (participant + 0x94) = 0;
                } else if (g_100f1dc == cut_SECOND_CHOICE) {
                    *(int*) (participant + 0x94) = 1;
                    fcn_004c54c0(*(int*) (own + 4), *(int*) (other + 4), 0x23, 1);
                }
            }
        }
        fcn_00471e30(dialog);
        return;
    case 6:
        if (*(int*) (participant + 0x10) != action[6]) return;
        dialog = fcn_00470820(0, 0, "cutscenes\\prozess");
        fcn_00471d80(dialog, 3);
        d2_SetForm(dialog, 0);
        io_AppendText(0x1512, *(unsigned short*) own);
        g_100f1dc = -1;
        *(int*) (participant + 0x94) = 0;
        timer = fcn_004677e0((cut_WINDOW_WIDTH - 300) / 2 - 8,
            8, 300, 0, 100, 0x75, 0x42, g_772514);
        fcn_004e6e20(timer, 1500, 1);
        while (fcn_005373e0((void*) fcn_004df1b0, g_68bfb8)) {
            if (!fcn_004e6e20(timer, 0, 0)) {
                g_774654 = 1;
            } else if (g_100f1dc != -1) {
                g_774654 = 1;
                if (g_100f1dc == 1) {
                    *(int*) (participant + 0x94) = 1;
                } else if (g_100f1dc == cut_SECOND_CHOICE) {
                    *(int*) (participant + 0x94) = 0;
                }
            }
        }
        fcn_00471e30(dialog);
        return;
    case 4:
        value = *(int*) (participant + 0x10);
        if (value != action[7] && value != action[8] && value != action[9]) return;
        dialog = fcn_00470820(0, 0, "cutscenes\\prozess");
        fcn_00471d80(dialog, 3);
        d2_SetForm(dialog, 0);
        io_AppendText(0x1529, *(unsigned short*) own);
        io_AppendText(0x152a);
        io_AppendText(0x152b);
        g_100f1dc = -1;
        *(int*) (participant + 0x94) = 1;
        timer = fcn_004677e0((cut_WINDOW_WIDTH - 300) / 2 - 8,
            8, 300, 0, 100, 0x75, 0x42, g_772514);
        fcn_004e6e20(timer, 1500, 1);
        while (fcn_005373e0((void*) fcn_004df1b0, g_68bfb8)) {
            if (!fcn_004e6e20(timer, 0, 0)) {
                g_774654 = 1;
            } else if (g_100f1dc != -1) {
                g_774654 = 1;
                if (g_100f1dc == 1) {
                    *(int*) (participant + 0x94) = 1;
                } else if (g_100f1dc == cut_SECOND_CHOICE) {
                    *(int*) (participant + 0x94) = 0;
                }
            }
        }
        fcn_00471e30(dialog);
        return;
    case 5:
        if (*(int*) (participant + 0x10) != action[7]) return;
        available[0] = -1;
        available[1] = -1;
        available[2] = -1;
        base = fcn_00493be0((char*) action);
        dialog = fcn_00470820(0, 0, "cutscenes\\prozess");
        fcn_00471d80(dialog, 3);
        d2_SetForm(dialog, 0);
        io_AppendText(0x1532, *(unsigned short*) own);
        i = 0;
        text_id = base * 3 + 0x1534;
        do {
            choice = fcn_00472250(dialog, 0, io_AppendText(0x1533, text_id));
            available[i] = choice;
            if (fcn_004f6810(other, i + base)) fcn_00472640(choice, 0);
            i++;
            text_id += 3;
        } while (i < 3);
        if (available[1] != -1) {
            *(int*) (participant + 0x94) = base + 1;
        } else if (fcn_004e6cb0(2)) {
            *(int*) (participant + 0x94) = base + 2;
        } else {
            *(int*) (participant + 0x94) = base;
        }
        g_100f1dc = -1;
        timer = fcn_004677e0((cut_WINDOW_WIDTH - 300) / 2 - 8,
            8, 300, 0, 100, 0x75, 0x42, g_772514);
        fcn_004e6e20(timer, 1500, 1);
        while (fcn_005373e0((void*) fcn_004df1b0, g_68bfb8)) {
            if (!fcn_004e6e20(timer, 0, 0)) {
                g_774654 = 1;
            } else if (g_100f1dc != -1) {
                g_774654 = 1;
                if (g_67d370 == available[0]) {
                    *(int*) (participant + 0x94) = base;
                } else if (g_67d370 == available[1]) {
                    *(int*) (participant + 0x94) = base + 1;
                } else if (g_67d370 == available[2]) {
                    *(int*) (participant + 0x94) = base + 2;
                }
            }
        }
        fcn_00471e30(dialog);
        return;
    }
}
unsigned char _dpad_100e760[2684];
