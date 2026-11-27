


#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_681130[];
extern int g_100f1dc;
#include "client_dialog_state.h"

unsigned short* __cdecl gm_LookupEntityRecordById(int h);
int __cdecl d2_LoadForm(int a, int b, int* c);
void __cdecl d2_CenterDialogWindows(int h);
void __cdecl d2_SetForm(int h, int on);
void __cdecl io_AppendText(int id, int a, int b);
int __cdecl main_RunFrameLoop(void (__cdecl* cb)(int), int flags);
void __cdecl d2_DestroyForm(int h);
void __cdecl main_ExitToGameLoop(int arg);

void __cdecl d2_ShowMissionDialog(int arg)
{
	int mode;
	unsigned short* p;
	int h;

	mode = 0;
	p = gm_LookupEntityRecordById(g_6a3760);
	h = d2_LoadForm(mode, mode, &(*(int*)g_681130));
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText(0x1b97, *p, *p);
	g_100f1dc = -1;
	do {
		if (g_6a3760 == -1) {
			mode = (g_774954 != 0) + 1;
			g_774654 = 1;
		}
	} while (main_RunFrameLoop(d2_ShowMissionDialog, arg | 0x80) != 0);
	d2_DestroyForm(h);
	if (mode == 2) {
		main_ExitToGameLoop(arg);
	}
}
