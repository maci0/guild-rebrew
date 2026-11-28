#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl he_FreeAction(void*);
void* __cdecl he_fn_Handlung(void);
void* __cdecl he_StartHandlungSearch(int, ...);
void* __cdecl gm_SearchTable67(int);

/* ADDRESS: GOLDTL 0x005c2910 */
/* ADDRESS: GOLDDE 0x005a4d50 */
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
	win = d2_LoadForm(0, 0, "Panel\\Gebaeude_Verkaufen_pergament");
	d2_CenterDialogWindows(win);
	d2_SetForm(win, 2);
	saved = d2_GetWindowListItem(win, 2, io_AppendText(0x17cc, e, *(int*) (u + 0xb0)));
	d2_SetOverlayAnimation(0, 0);
	main_RunFrameLoop((void*) 0, 0x677c7);
	do {
		r = (int) gm_SearchTable67(id);
		if ((*(unsigned short*) (e + 0x5a) & 0x0400) || r == 0) {
			d2_DialogCloseRequested = 1;
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction == 2) {
			if (d2_CurrentElementId == saved) {
				cm_RequestChangeBits(*(int*) (e + 1), 0x5a, 2, 0, 2);
				he_FreeAction(u);
				d2_DialogCloseRequested = 1;
			}
		} else if (d2_DialogButtonAction == 1) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) d2_ShowGebaeudeSaleDialog, 0x677c7) != 0);
	d2_DestroyForm(win);
}
