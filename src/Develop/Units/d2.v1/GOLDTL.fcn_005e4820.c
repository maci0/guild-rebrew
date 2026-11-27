

extern int d2_CurrentWindowId;
extern int g_14ac498;
extern int g_14ac49c;
extern int g_14ac4a0;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_14cf950;
#include "client_dialog_state.h"

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_005e3b10(int, int, int);
int __cdecl d2_CreateRadioGroup(int, ...);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_SetFormVisibility(int, int);
void __cdecl fcn_005e3520(void);
void __cdecl fcn_005e2b60(void);
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

	h = fcn_00470820(0, 0, "menu\\options");
	d2_CenterDialogWindows(h);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(0, 1);
	b1 = fcn_005e3b10(1, g_14ac498, d2_CurrentWindowId);
	b2 = fcn_005e3b10(2, g_14ac49c, d2_CurrentWindowId);
	b3 = fcn_005e3b10(3, g_14ac4a0, d2_CurrentWindowId);
	p = d2_CreateRadioGroup(3, b1, b2, b3);
	while (main_RunFrameLoop(d2_ShowOptionsMenu, 0x24087) != 0) {
		if (g_14ce8e0 != 0 || (*(unsigned char*)&g_14cf950) == 1) {
			g_774654 = 1;
		}
		d2_UpdateRadioGroup(p);
		if (g_14ce8d8 != 0 && d2_CurrentElementId != -1) {
			if (d2_CurrentElementId == b1) {
				d2_SetFormVisibility(h, 0);
				fcn_005e3520();
				d2_SetFormVisibility(h, 1);
			} else if (d2_CurrentElementId == b2) {
				d2_SetFormVisibility(h, 0);
				fcn_005e2b60();
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
