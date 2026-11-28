

#include <string.h>

// SIZE 0x220
typedef struct {
	int f0;
	int id;
	int slot;
	unsigned char used;
	char padd[0xc];
	char name[0x207];
} SaveItem;

extern int main_LoopFlags;
extern int d2_CurrentWindowId;
extern int g_14ce8e0;
extern int g_14ce8d8;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_HoveredWindow;
#include "Develop/Units/d2.v1/d2_gui.h"
#include "client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"
extern Win_1015f40 g_1015f40[0x60];
extern int d2_CurrentElementId;
extern char g_774964;
extern int g_14ac644;
extern char g_7e21a0[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_PositionFormWindows(int, int);
void __cdecl d2_CenterForm(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(int);
int __cdecl d2_GetFormWindow(int, int);
void __cdecl d2_CreateWindowScrollbar(int, int, int, int, int, int*, int*, int*);
void __cdecl d2_PopulateSaveSlotList(int, int, void*, void*, char*, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl d2_ConfirmTextIdMessageBox(int, unsigned int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_RunLoadNetworkGameDialog(void)
{
	int result;
	int style;
	int h;
	int c;
	int a;
	int b;
	SaveItem items[16];
	char buf[0x4200];
	int i;

	result = 0;
	style = main_LoopFlags;
	h = d2_LoadForm(0, 0, "menu\\loadgame_new");
	d2_PositionFormWindows(h, 1);
	d2_CenterForm(h, 2);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(0, 2);
	io_AppendText(0x1c57);
	d2_SetForm(0, 0);
	d2_CreateWindowScrollbar(0x214, 0x168, d2_CurrentWindowId, d2_GetFormWindow(h, 1), 0x82, &a, &b, &c);
	d2_PopulateSaveSlotList(h, 1, items, buf, "gamedata/network", 1);
	while (main_RunFrameLoop(d2_RunLoadNetworkGameDialog, style) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_14ce8d8 != 0) {
			for (i = 0; i < 16; i++) {
				if (items[i].used != 0 && items[i].slot != -1
				    && (d2_CurrentElementId == items[i].id || d2_HoveredWindow == items[i].slot
				        || (d2_HoveredWindow != -1
				            && *(char**)&((D2_CONTROL_TL*)g_1015ea0)
				                   [((D2_WIN*)g_1015f40)[d2_HoveredWindow].slot].parent
				                == (char*) &((D2_WIN*)g_1015f40)[items[i].slot]))) {
					goto found;
				}
			}
			continue;
found:
			if (g_774964 == 0 || d2_ConfirmTextIdMessageBox(g_14ac644, 0x101) != 0) {
				strcpy(g_7e21a0, items[i].name);
				g_774654 = 1;
				result = 1;
			}
		}
	}
	d2_DestroyForm(h);
	return result;
}
