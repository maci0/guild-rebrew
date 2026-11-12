/* Domicile cabinet: lets the player pick a target, then offers a priced spy
 * order in a dialog and sends it when confirmed. */

#include <string.h>
#include "client_types.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "client_dialog_state.h"

/* SIZE 0x21c */
typedef struct {
    char p0[4];
    int f4;
    char p8[0x21c - 8];
} Slot58a6;

typedef struct F8 {
    int mask;
    int b;
} F8;
// SIZE 0x8

extern Slot58a6 g_7f4ca0[];
extern pos14_7f4c00 g_7f4c00;
extern unsigned char g_773d75;
extern float g_6628ac;
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;

int __cdecl gm_WalkEntityChain(unsigned short);
char *__cdecl fcn_005cd440(int *, int, int, int);
int __cdecl fcn_00577ab0(char *);
void __cdecl io_FormatTextBuffer(char *, int, ...);
int __cdecl fcn_00526120(char *, int);
int __cdecl fcn_00470820(int, int, char *);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText();
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00526010(Slot58a6 *, int, unsigned char);
int __cdecl fcn_00525f60(Slot58a6 *, int);
int __cdecl fcn_005898f0(char *);
char *__cdecl gm_GetEntityTableEntry(Slot58a6 *);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_005100f0(int, int);
int __cdecl fcn_004a5e60(Slot58a6 *p, int kind, F8 f, int c, float r, int *out);
int __cdecl fcn_004c5530(char *);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_005373e0(void *, int);
int __cdecl fcn_004c3030(int, int, char *, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x0058a6b0 */
void __cdecl fcn_0058a6b0(char *a0)
{
    int tmp;
    int dlg;
    int h2;
    int h1;
    int query[0x14];
    char msg[0xf8];
    char text[0x400];
    int base;
    int price;
    char *sel;
    char *rec;
    F8 f;

    base = gm_WalkEntityChain(g_774970);
    memset(query, 0, sizeof(query));
    memset(query + 7, 0xff, 8 * sizeof(int));
    query[0] = 1;
    query[1] = 0x400;
    query[4] = 6;
    sel = fcn_005cd440(query, *(int *) 0x14b53d0, 0, 0);
    if (fcn_00577ab0(sel) == 0) {
        io_FormatTextBuffer(text, 0x4030, *(unsigned short *) sel);
        fcn_00526120(text, 0);
        return;
    }
    if (sel == 0)
        return;
    tmp = gm_WalkEntityChain(*(unsigned short *) sel) + base;
    price = (int) (tmp * g_6628ac);
    dlg = fcn_00470820(0, 0, "Locations\\Domizil\\kabinett");
    d2_SetOverlayAnimation(0, 0);
    fcn_00471b60(dlg);
    d2_SetForm(dlg, 0);
    fcn_005340f0(g_772514);
    d2_SetForm(dlg, 1);
    io_AppendText("$C");
    io_AppendText(0x402e, 0x402b, price, *(unsigned short *) sel);
    d2_SetForm(dlg, 2);
    h2 = io_AppendText(0x402f);
    h1 = fcn_00472250(dlg, 2, h2);
    h2 = fcn_00472250(dlg, 2, h2 + 1);
    g_100f1dc = -1;
    do {
        if (g_14ce8e0 != 0) {
            g_774654 = 1;
        } else if (g_100f1dc != -1) {
            if (g_67d370 == h1) {
                if (fcn_00526010(&g_7f4ca0[g_774970], price, g_773d75) != 0
                    && fcn_00525f60(&g_7f4ca0[g_774970], 0x10) == 1
                    && fcn_005898f0(a0) != 0) {
                    rec = gm_GetEntityTableEntry(&g_7f4ca0[g_774970]);
                    if (rec != 0)
                        *(int *) (rec + 0x28) += price;
                    fcn_004c51a0(-1, g_7f4ca0[g_774970].f4, g_773d75, price);
                    fcn_005100f0(g_7f4ca0[g_774970].f4, -0x10);
                    memset(msg, 0, sizeof(msg));
                    msg[4] = (char) 0x99;
                    *(int *) (msg + 8) = g_7f4ca0[*(unsigned short *) (a0 + 0x27)].f4;
                    *(int *) (msg + 0xc) = *(int *) (a0 + 1);
                    *(int *) (msg + 0x28) = g_7f4c00.a;
                    *(int *) (msg + 0x2c) = g_7f4c00.b;
                    *(int *) (msg + 0x30) = g_7f4c00.c;
                    *(short *) (msg + 0x34) = g_7f4c00.d;
                    msg[0x36] = 2;
                    *(int *) (msg + 0x5c) = *(int *) (a0 + 1);
                    *(int *) (msg + 0x60) = *(int *) (sel + 4);
                    *(int *) (msg + 0x64) = -1;
                    *(int *) (msg + 0x68) = 4;
                    *(int *) (msg + 0x6c) = 0;
                    if (*(char **) (sel + 0x170) != 0) {
                        *(int *) (msg + 0x58) = *(int *) (*(char **) (sel + 0x170) + 1);
                    } else if (*(char **) (sel + 0x16c) != 0) {
                        *(int *) (msg + 0x58) = *(int *) (*(char **) (sel + 0x16c) + 1);
                    } else {
                        tmp = -1;
                        f.mask = 0x7b4c4a0;
                        f.b = 0;
                        fcn_004a5e60(&g_7f4ca0[g_774970], 0, f, 0, 100.0f, &tmp);
                        *(int *) (msg + 0x58) = tmp;
                    }
                    tmp = fcn_004c5530(msg);
                    if (tmp != -1) {
                        while (fcn_004c4450(tmp) == 0)
                            fcn_005373e0(0, 0x20007);
                    }
                    fcn_004c3030(-7, 0, "KOMMENTARE", -1);
                    g_774654 = 1;
                }
            } else if (g_67d370 == h2) {
                g_774654 = 1;
            }
        }
    } while (fcn_005373e0((void *) fcn_0058a6b0, 0x677c7) != 0);
    fcn_00471e30(dlg);
    fcn_00532ef0();
}
