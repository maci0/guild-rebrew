


extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int d2_CurrentElementId;
#include "client_dialog_state.h"
extern int main_LoopFlags;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
extern int g_665f78[];
#include "Develop/DieGildeAddOn/game/entity_record.h"

int __cdecl fcn_00470820(int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl gm_CheckEntityStock(void*, int, char);
int __cdecl fcn_004f2f90(void*, int, char*, int, int, int);
int __cdecl cm_GetCommandStatus(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00526120(char*, int);

int __cdecl d2_RunFriedhofDialog(char* entity, int a2, unsigned char a3, int choice)
{
	int r;
	int ok;
	int cancel;
	char buf[0x200];
	int dlg;
	int cost;
	int id;
	int h;
	int s;

	r = 0;
	cost = *(unsigned short*) (entity + 0x27) != g_774970 ? 16000 : 0;
	dlg = fcn_00470820(0, 0, (int) "Locations\\Friedhof\\Friedhof");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	if (*(unsigned short*) (entity + 0x27) == g_774970) {
		io_AppendText(0x4115, 0x4112, entity, g_665f78[choice]);
	} else {
		io_AppendText(0x4114, 0x4112, g_665f78[choice], cost);
	}
	d2_SetForm(dlg, 2);
	id = io_AppendText(0x4116);
	ok = d2_GetWindowListItem(dlg, 2, id);
	cancel = d2_GetWindowListItem(dlg, 2, id + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == ok) {
				if (cost == 0 || gm_CheckEntityStock(((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), cost, (*(char*)&g_773d75)) != 0) {
					h = fcn_004f2f90(((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), choice, entity, a2, a3, cost);
					while (h != -1 && (s = cm_GetCommandStatus(h)) == 0) {
						main_RunFrameLoop((void*) s, 0x20007);
					}
					main_LoopFlags = 0x677c7;
					if (cm_GetCommandStatus(h) == 2) {
						io_FormatTextBuffer(buf, 0x411b, 0x4112, g_665f78[choice]);
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
	} while (main_RunFrameLoop((void*) d2_RunFriedhofDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	return r;
}
