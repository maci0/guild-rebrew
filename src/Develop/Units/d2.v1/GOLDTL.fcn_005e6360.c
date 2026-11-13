#include <string.h>
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "client_dialog_state.h"
#include "d2_gui.h"

extern char g_7f4ca0[];
extern int g_666018; extern int g_66601c;
extern char g_6811b0[];
extern int g_772514;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_67d370;

void __cdecl fcn_00532ef0(void);
void __cdecl fcn_005263d0(int, int, int);
int __cdecl fcn_005cd440(char*, int, int, void*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00533a60(int, int, int*, int, ...);
int __cdecl fcn_00471f80(int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00525f60(void*, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_005100f0(int, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00545d40(int, int, char*, int, int, char*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005e6360 */
void __cdecl fcn_005e6360(char* entity)
{
    int ids[2];
    int query[20];
    char text[1024];
    char* target;
    int dialog;
    int control;
    int amount;

    if (*(unsigned short*) (entity + 0x27) == 0xffff) {
        fcn_00532ef0();
        return;
    }
    if ((unsigned char) g_7f4ca0[g_774970 * 0x21c + 0x1cc] & 0x20) {
        fcn_005263d0(*(int*) 0x14b5b3c, *(int*) 0x14b5b40, 0);
        return;
    }
    memset(query, 0, sizeof(query));
    memset(query + 7, -1, 8 * sizeof(int));
    query[0] = 1;
    query[1] = 0x400;
    query[4] = 6;
    query[2] = g_666018; query[3] = g_66601c;
    target = (char*) fcn_005cd440((char*) query, *(int*) 0x14b5b44, 0, 0);
    if (target == 0) {
        fcn_00532ef0();
        return;
    }
    dialog = fcn_00470820(0, 0, "Locations\\zigeuner\\blutrache");
    d2_SetOverlayAnimation(0, 0);
    fcn_00471b60(dialog);
    d2_SetForm(dialog, 0);
    fcn_005340f0(g_772514);
    d2_SetForm(dialog, 2);
    control = fcn_004677e0(0x57, 7, 200, 0, 100, 0x7b, 2, g_772514);
    d2_SetElementValue(control, 2, 8, 2, 1);
    d2_SetForm(dialog, 3);
    fcn_00533a60(g_772514, 0, ids, 2, *(int*) 0x14b5b50, *(int*) 0x14b5b54);
    do {
        amount = fcn_00471f80(control);
        d2_SetForm(dialog, 1);
        io_AppendText((int) g_6811b0);
        io_AppendText(0x420a, 0x4207, *(unsigned short*) target, amount);
        if (g_14ce8e0 != 0) {
            g_774654 = 1;
        } else if (g_100f1dc != -1) {
            if (g_67d370 == ids[0]) {
                if (fcn_00525f60(g_7f4ca0 + g_774970 * 0x21c, amount) == 1) {
                    fcn_004c5420(*(int*) (g_7f4ca0 + g_774970 * 0x21c + 4), 0x1cc, 4, 0x20, 0);
                    fcn_005100f0(*(int*) (g_7f4ca0 + g_774970 * 0x21c + 4), -amount);
                    fcn_004c54c0(*(int*) (g_7f4ca0 + g_774970 * 0x21c + 4), *(int*) (target + 4), amount * 5, 1);
                    if (target[2] == 6 || target[2] == 7) {
                        io_FormatTextBuffer(text, 0x420e, g_774970);
                        fcn_00545d40(*(int*) (target + 4), -1, text, 0, 0x5f0, "_NACHRICHTEN_ZIGEUNER_04");
                    }
                    g_774654 = 1;
                }
            } else if (g_67d370 == ids[1]) {
                g_774654 = 1;
            }
        }
    } while (fcn_005373e0((void*) fcn_005e6360, 0x677c7) != 0);
    fcn_00471e30(dialog);
    fcn_00532ef0();
}
