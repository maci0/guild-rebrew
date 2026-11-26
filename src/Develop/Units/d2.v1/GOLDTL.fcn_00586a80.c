


extern char g_6a93e0[];
extern int d2_CurrentWindowId;
extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

char* __cdecl fcn_004ec7d0(char*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl main_RunFrameLoop(int (__cdecl*)(char*), int);
void __cdecl he_CancelErforschenActions(char*);
void __cdecl ahm_SendFireCommand(char*);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_ConfirmFireAlchemist(char* a, int* unused)
{
	int result;
	int h;
	int s;
	int b1;
	int b2;
	char* p;

	result = 0;
	if (fcn_004ec7d0(a) == 0) {
		return 0;
	}
	h = fcn_00470820(0, 0, g_6a93e0);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	io_AppendText(0x403d, 0x182);
	d2_SetForm(h, 2);
	s = io_AppendText(0x403e);
	b1 = d2_GetWindowListItem(h, 2, s);
	b2 = d2_GetWindowListItem(h, 2, s + 1);
	g_100f1dc = -1;
	do {
		p = fcn_004ec7d0(a);
		if (p == 0) {
			g_774654 = 1;
			main_RunFrameLoop(d2_ConfirmFireAlchemist, 0x20007);
			d2_DestroyForm(h);
			return 0;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == b1) {
				result = 1;
				he_CancelErforschenActions(a);
				ahm_SendFireCommand(p);
				g_774654 = 1;
			} else if (d2_CurrentElementId == b2) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop(d2_ConfirmFireAlchemist, 0x677c7) != 0);
	d2_DestroyForm(h);
	return result;
}
