

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern char g_6aca54[];
extern char g_6aca2c[];
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(char*, ...);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_ShowApplicationError(char* text)
{
	int h;

	h = d2_LoadForm(0, 0, g_6aca54);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	if (text != 0) {
		io_AppendText(text);
	}
	else {
		io_AppendText(g_6aca2c);
	}
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop(d2_ShowApplicationError, 0x677c7) != 0);
	d2_DestroyForm(h);
}
