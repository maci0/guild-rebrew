

extern int d2_CurrentWindowId;
extern int g_14ac498;
extern int g_14ac49c;
extern int g_14ac4a0;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char io_LastKeyScancode;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddMenuOptionButton(int, int, int);
int __cdecl d2_CreateRadioGroup(int, ...);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_ShowGameOptions(void);
void __cdecl d2_ShowGraphicsOptions(void);
void __cdecl d2_ShowSoundOptions(void);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_ShowOptionsMenu(void)
{
	int h;
	int b1;
	int b2;
	int b3;
	int p;

	h = d2_LoadForm(0, 0, "menu\\options");
	d2_CenterDialogWindows(h);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(0, 1);
	b1 = d2_AddMenuOptionButton(1, g_14ac498, d2_CurrentWindowId);
	b2 = d2_AddMenuOptionButton(2, g_14ac49c, d2_CurrentWindowId);
	b3 = d2_AddMenuOptionButton(3, g_14ac4a0, d2_CurrentWindowId);
	p = d2_CreateRadioGroup(3, b1, b2, b3);
	while (main_RunFrameLoop(d2_ShowOptionsMenu, 0x24087) != 0) {
		if (io_RightButtonReleased != 0 || (*(unsigned char*)&io_LastKeyScancode) == 1) {
			d2_DialogCloseRequested = 1;
		}
		d2_UpdateRadioGroup(p);
		if (g_14ce8d8 != 0 && d2_CurrentElementId != -1) {
			if (d2_CurrentElementId == b1) {
				d2_SetFormVisibility(h, 0);
				d2_ShowGameOptions();
				d2_SetFormVisibility(h, 1);
			} else if (d2_CurrentElementId == b2) {
				d2_SetFormVisibility(h, 0);
				d2_ShowGraphicsOptions();
				d2_SetFormVisibility(h, 1);
			} else if (d2_CurrentElementId == b3) {
				d2_SetFormVisibility(h, 0);
				d2_ShowSoundOptions();
				d2_SetFormVisibility(h, 1);
			}
		}
	}
	d2_ClearRadioGroup(p);
	d2_DestroyForm(h);
}
