


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int d2_CurrentElementId;
#include "client_dialog_state.h"
extern int g_665f78[];
extern int main_LoopFlags;

int __cdecl gm_CalcBribeOrPriceScore(ENTITY_RECORD*, int, int, int, int*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText();
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl gm_CheckEntityStock(ENTITY_RECORD*, int, unsigned char);
int __cdecl fcn_004f0430(ENTITY_RECORD*, char*, int, int, int);
int __cdecl cm_GetCommandStatus(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00526120(char*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_ConfirmRentAGrave(char* who, int k)
{
	int h;
	int r;
	int ok;
	int cancel;
	int got;
	char buf[0x200];
	int x;
	int s;
	int id;

	r = 0;
	if (*(unsigned short*) (who + 0x27) == g_774970) {
		x = 0;
	} else {
		x = gm_CalcBribeOrPriceScore(((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970]), 0xff, k, 1, &got);
	}
	h = fcn_00470820(0, 0, "Locations\\Friedhof\\Friedhof");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	if (*(unsigned short*) (who + 0x27) == g_774970) {
		io_AppendText(0x410c, 0x4109, who, g_665f78[k]);
	} else {
		io_AppendText(0x410b, 0x4108, g_665f78[k], x);
	}
	d2_SetForm(h, 2);
	s = io_AppendText(0x410d);
	ok = d2_GetWindowListItem(h, 2, s);
	cancel = d2_GetWindowListItem(h, 2, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == ok) {
				if (x == 0 || gm_CheckEntityStock(((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970]), x, g_773d75) != 0) {
					id = fcn_004f0430(((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970]), who, k, 10, x);
					while (id != -1 && cm_GetCommandStatus(id) == 0) {
						main_RunFrameLoop(0, 0x20007);
					}
					main_LoopFlags = 0x677c7;
					if (cm_GetCommandStatus(id) == 2) {
						io_FormatTextBuffer(buf, 0x411b, (*(unsigned short*) (who + 0x27) == g_774970) + 0x4108,
						    g_665f78[k]);
						fcn_00526120(buf, 0x100);
					} else {
						g_774654 = 1;
						r = 1;
					}
				}
			} else if (d2_CurrentElementId == cancel) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop(d2_ConfirmRentAGrave, 0x677c7) != 0);
	d2_DestroyForm(h);
	return r;
}
