


extern char g_696470[];
extern char g_69645c[];
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char g_99f6a0[];
extern int g_14ce8e0;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl d2_LoadForm(int a, int b, char* s);
void __cdecl d2_CenterDialogWindows(int h);
void __cdecl d2_SetOverlayAnimation(int a, int b);
void __cdecl d2_SetForm(int h, int b);
void __cdecl io_AppendText(char* fmt, ...);
int __cdecl main_RunFrameLoop(void* fn, int y);
void __cdecl d2_DestroyForm(int h);

void __cdecl d2_ShowTaxStatistics(void)
{
	int h;
	int i;

	h = d2_LoadForm(0, 0, g_696470);
	d2_CenterDialogWindows(h);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(h, 0);
	for (i = 0; i < 0x11; i++) {
		io_AppendText(g_69645c, (*(int*)&gm_GameTime) + i - 0x10, ((int*)g_99f6a0)[i]);
	}
	do {
		if (g_14ce8e0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) d2_ShowTaxStatistics, 0x677c7));
	d2_DestroyForm(h);
}
