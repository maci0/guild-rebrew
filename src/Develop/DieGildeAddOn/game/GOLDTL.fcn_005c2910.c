#include "client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl he_FreeAction(void*);
void* __cdecl he_fn_Handlung(void);
void* __cdecl he_StartHandlungSearch(int, ...);
void* __cdecl gm_SearchTable67(int);

/* ADDRESS: GOLDTL 0x005c2910 */
void __cdecl d2_ShowGebaeudeSaleDialog(char* e)
{
	int win;
	char* u;
	int id;
	int saved;
	int r;

	id = *(int*) (e + 1);
	u = (char*) he_StartHandlungSearch(1, 0, 0x1b);
	while (u != 0 && *(int*) (u + 0xac) != *(int*) (e + 1)) {
		u = (char*) he_fn_Handlung();
	}
	win = fcn_00470820(0, 0, "Panel\\Gebaeude_Verkaufen_pergament");
	d2_CenterDialogWindows(win);
	d2_SetForm(win, 2);
	saved = d2_GetWindowListItem(win, 2, io_AppendText(0x17cc, e, *(int*) (u + 0xb0)));
	d2_SetOverlayAnimation(0, 0);
	main_RunFrameLoop((void*) 0, 0x677c7);
	do {
		r = (int) gm_SearchTable67(id);
		if ((*(unsigned short*) (e + 0x5a) & 0x0400) || r == 0) {
			g_774654 = 1;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {
			if (d2_CurrentElementId == saved) {
				fcn_004c5420(*(int*) (e + 1), 0x5a, 2, 0, 2);
				he_FreeAction(u);
				g_774654 = 1;
			}
		} else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) d2_ShowGebaeudeSaleDialog, 0x677c7) != 0);
	fcn_00471e30(win);
}
