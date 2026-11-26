#include "Develop/DieGildeAddOn/game/entity_record.h"

typedef struct
{
	char pad[0x21c];
} Player;
// SIZE 0x21c

extern int main_LoopFlags;
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca0[];
extern int g_100f1dc;
#include "client_dialog_state.h"
extern char g_14cf950;
extern int g_14abbf4;
extern int g_14ce8e0;
extern char s_68d704[];

int __cdecl gm_CheckEntityStock(Player*, int, char);
int __cdecl fcn_00470820(int, int, char*);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl gm_AccumulateTyped2(Player*);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_CenterDialogWindows(int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl fcn_00526120(int, int);
int __cdecl d2_GetControlValue(int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005b5750(void)
{
	int timer;
	int r;
	int dlg;
	int ctl;
	int v;

	r = 0;
	timer = main_LoopFlags;
	if (gm_CheckEntityStock(((Player *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970]), 0x140, (*(char*)&g_773d75)) == 0) {
		return 0;
	}
	dlg = fcn_00470820(0, 0, s_68d704);
	ctl = d2_GetWindowListItem(dlg, 0, io_AppendText(0x1a34, (unsigned char) (*(char*)&g_773d75)));
	v = gm_AccumulateTyped2(((Player *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970]));
	if (v >= 0x12c0) {
		v = 0x12c0;
	}
	d2_SetElementValue(ctl, 0xa, v / 32, 0xa);
	d2_CenterDialogWindows(dlg);
	if (main_RunFrameLoop((void*) fcn_005b5750, timer) != 0) {
		do {
			if (g_100f1dc != 2) {
				if (g_100f1dc == 1 || g_14cf950 == 1) {
					g_774654 = 1;
					r = 0;
				}
			}
			else {
				fcn_00526120(g_14abbf4, 4);
				g_774654 = 1;
				r = d2_GetControlValue(ctl);
			}
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		} while (main_RunFrameLoop((void*) fcn_005b5750, timer) != 0);
	}
	fcn_00471e30(dlg);
	return r;
}
