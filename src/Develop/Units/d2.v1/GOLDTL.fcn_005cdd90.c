


extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern char g_6ac9b4[];
extern char g_6ac9a4[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char*, ...);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_ShowAmtInfo(int k)
{
	int h;

	h = fcn_00470820(0, 0, g_6ac9b4);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 2);
	io_AppendText(g_6ac9a4, k + 0x253);
	d2_SetForm(h, 1);
	io_AppendText((char*) (k * 2 + 0x134b));
	io_AppendText((char*) (k * 2 + 0x134c));
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop(d2_ShowAmtInfo, 0x657c7) != 0);
	d2_DestroyForm(h);
}
