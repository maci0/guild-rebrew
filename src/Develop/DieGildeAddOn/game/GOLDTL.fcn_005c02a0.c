#include <stdlib.h>
#include <string.h>
#include "game_player.h"
#include "spiel.h"
#include "client_dialog_state.h"
#include "Develop/Units/d2.v1/d2_gui.h"

#pragma intrinsic(memset)

extern unsigned char g_773d75;
extern char g_7f4ca0[];
extern float g_664164;
extern float g_662ac8;
extern char g_67eab0[];
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;

int __cdecl fcn_00470820(short, short, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl gm_AccumulateTyped2(char*);
int __cdecl fcn_005c9030(int, int, int, int*);
int __cdecl fcn_0050b710(int, unsigned char);
void __cdecl fcn_005c9220(int*);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_0050b750(int, unsigned char);
int __cdecl fcn_00526010(void*, int, unsigned char);
void __cdecl fcn_004c5150(int, int, char, int);
/* The native caller consumes the command queue index returned in EAX. */
int __cdecl fcn_004c54c0(int, int, int, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00545d40(int, int, char*, int, int, char*);
int __cdecl fcn_004f4f60(int, int, int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

/* Inferred payment dialog callback; record accesses are slot +0, kind +2, id +4. */
/* ADDRESS: GOLDTL 0x005c02a0 */
int __cdecl fcn_005c02a0(char* entity)
{
    int result;
    int dlg;
    int edit;
    int accept;
    int cancel;
    int text_id;
    int amount;
    int limit;
    int command;
    short* stats;
    float duration;
    int ids[6];
    char text[0x400];

    result = 0;
    if (entity == 0)
        return 0;
    dlg = fcn_00470820(0, 0, "misc\\perga_rolle");
    fcn_00471b60(dlg);
    d2_SetOverlayAnimation(0, 0);
    d2_SetForm(dlg, 1);
    text_id = io_AppendText(0x174d, *(unsigned short*)entity, g_773d75);
    edit = fcn_00472250(dlg, 1, text_id);
    accept = fcn_00472250(dlg, 1, text_id + 1);
    amount = gm_WalkEntityChain(g_774970);
    amount = (int)(abs(amount + gm_WalkEntityChain(*(unsigned short*)entity)) * 0.0007843137136660516f);
    command = gm_AccumulateTyped2(g_7f4ca0 + g_774970 * 0x21c);
    fcn_005c9030(amount, command, 0x20, &limit);
    d2_SetElementValue(edit, fcn_0050b710(amount, g_773d75),
        fcn_0050b710(limit, g_773d75), fcn_0050b710(amount, g_773d75));
    cancel = fcn_00472250(dlg, 1, io_AppendText(0x174e));
    memset(ids, 0xff, sizeof(ids));
    ids[0] = dlg;
    ids[1] = 2;
    ids[2] = 3;
    ids[3] = 4;
    ids[4] = 2;
    ids[5] = 0x10;
    fcn_005c9220(ids);
    g_100f1dc = -1;
    do {
        if (g_14ce8e0 != 0)
            g_774654 = 1;
        if (g_100f1dc != -1) {
            if (g_67d370 == accept) {
                amount = fcn_00471f80(edit);
                amount = fcn_0050b750(amount, g_773d75);
                if (fcn_00526010(g_7f4ca0 + g_774970 * 0x21c, amount, g_773d75)) {
                    stats = gm_GetEntityTableEntry(g_7f4ca0 + g_774970 * 0x21c);
                    if (stats != 0)
                        *(int*)((char*)stats + 0x28) += amount;
                    fcn_004c5150(*(int*)(entity + 4), *(int*)(g_7f4ca0 + g_774970 * 0x21c + 4), g_773d75, amount);
                    duration = amount * ((*(int*)(g_7f4ca0 + g_774970 * 0x21c + 0x1cc) & 0x800)
                        ? g_664164 : g_662ac8) * 500.0f;
                    command = gm_WalkEntityChain(g_774970);
                    command += gm_WalkEntityChain(*(unsigned short*)entity);
                    command = (int)(duration / command);
                    command = fcn_004c54c0(*(int*)(g_7f4ca0 + g_774970 * 0x21c + 4), *(int*)(entity + 4), command, 1);
                    while (!fcn_004c4450(command))
                        fcn_00535960();
                    if (entity[2] == 6 || entity[2] == 7) {
                        io_FormatTextBuffer(text, 0x1751, g_774970, amount);
                        fcn_00545d40(*(int*)(entity + 4), -1, text, 0, 0x5fb, g_67eab0);
                    }
                    fcn_004f4f60(0x10, 1, *(int*)(g_7f4ca0 + g_774970 * 0x21c + 4), *(int*)(entity + 4), -1);
                    g_774654 = 1;
                    result = 1;
                }
            } else if (g_67d370 == cancel)
                g_774654 = 1;
        }
    } while (fcn_005373e0((void*)fcn_005c02a0, 0x677c7));
    fcn_00471e30(dlg);
    return result;
}
