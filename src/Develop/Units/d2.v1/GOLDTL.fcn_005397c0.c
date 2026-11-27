


#include <windows.h>
#include <string.h>

extern char g_7e22c0[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6a3a34[];
extern char g_14cf950;
#include "client_dialog_state.h"
extern int g_100f1dc;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_GetWindowListItem(int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(int (__cdecl*)(void), int);
char* __cdecl d2_GetControlValue(int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_PromptNetworkHost(void)
{
	int ok;
	char buf[0x104];
	int result;
	int h;
	int e;

	result = 0;
	GetPrivateProfileStringA("Network", "Host", "127.0.0.1", buf, 0x104, g_7e22c0);
	h = d2_LoadForm(0, 0, g_6a3a34);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 2);
	io_AppendText(0x1cae);
	d2_SetForm(h, 0);
	e = d2_GetWindowListItem(h, 0, 0);
	d2_SetElementValue(e, buf);
	d2_SetForm(h, 1);
	ok = d2_GetWindowListItem(h, 1, io_AppendText(0x1cb0));
	while (main_RunFrameLoop(d2_PromptNetworkHost, 0x24087) != 0) {
		if (g_14ce8e0 != 0 || g_14cf950 == 1) {
			g_774654 = 1;
		}
		if ((g_100f1dc != -1 || g_14cf950 == 0x1c) && (d2_CurrentElementId == ok || g_14cf950 == 0x1c)) {
			result = 1;
			strcpy(buf, d2_GetControlValue(e));
			strcpy(g_7e2000, buf);
			WritePrivateProfileStringA("Network", "Host", buf, g_7e22c0);
			g_774654 = 1;
		}
	}
	d2_DestroyForm(h);
	return result;
}
