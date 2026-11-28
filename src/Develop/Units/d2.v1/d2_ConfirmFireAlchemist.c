


extern char g_6a93e0[];
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

char* __cdecl ahm_GetWorkshopOwner(char*);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl main_RunFrameLoop(int (__cdecl*)(char*), int);
void __cdecl he_CancelErforschenActions(char*);
void __cdecl ahm_SendFireCommand(char*);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x0056c740 */
int __cdecl d2_ConfirmFireAlchemist(char* a, int* unused)
{
	int result;
	int h;
	int s;
	int b1;
	int b2;
	char* p;

	result = 0;
	if (ahm_GetWorkshopOwner(a) == 0) {
		return 0;
	}
	h = d2_LoadForm(0, 0, g_6a93e0);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	io_AppendText(0x403d, 0x182);
	d2_SetForm(h, 2);
	s = io_AppendText(0x403e);
	b1 = d2_GetWindowListItem(h, 2, s);
	b2 = d2_GetWindowListItem(h, 2, s + 1);
	d2_DialogButtonAction = -1;
	do {
		p = ahm_GetWorkshopOwner(a);
		if (p == 0) {
			d2_DialogCloseRequested = 1;
			main_RunFrameLoop(d2_ConfirmFireAlchemist, 0x20007);
			d2_DestroyForm(h);
			return 0;
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == b1) {
				result = 1;
				he_CancelErforschenActions(a);
				ahm_SendFireCommand(p);
				d2_DialogCloseRequested = 1;
			} else if (d2_CurrentElementId == b2) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop(d2_ConfirmFireAlchemist, 0x677c7) != 0);
	d2_DestroyForm(h);
	return result;
}
