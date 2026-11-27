

#include <stdio.h>
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
#include "client_dialog_state.h"
extern int d2_HoveredWindow;
extern char* g_1015ea0;
#include "client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"
extern Win_1015f40 g_1015f40[0x60];
extern int d2_CurrentElementId;
extern char g_774964;
extern int g_14ac644;
extern char g_7e21a0[];
extern unsigned char g_7747b0;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471db0(int, int);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(int);
int __cdecl d2_GetFormWindow(int, int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);
void __cdecl fcn_005e0140(int, int, void*, void*, char*, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl fcn_005dfe80(int, unsigned int);
void __cdecl d2_DestroyForm(int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_ShowLoadGameMenu(void)
{
	int result;
	int style;
	int h;
	int c;
	int a;
	int b;
	char text[0x104];
	SaveItem items[16];
	char buf[0x4200];
	int i;

	result = 0;
	style = main_LoopFlags;
	h = fcn_00470820(0, 0, "menu\\loadgame_new");
	fcn_00471db0(h, 1);
	fcn_00471d80(h, 2);
	d2_SetForm(h, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(0, 2);
	io_AppendText(0x1c57);
	d2_SetForm(0, 0);
	fcn_00533f40(0x214, 0x168, d2_CurrentWindowId, d2_GetFormWindow(h, 1), 0x82, &b, &c, &a);
	fcn_005e0140(h, 1, items, buf, "gamedata/saves", 0);
	while (main_RunFrameLoop(d2_ShowLoadGameMenu, style) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_14ce8d8 != 0) {
			for (i = 0; i < 16; i++) {
				if (items[i].used != 0 && items[i].slot != -1
				    && (d2_CurrentElementId == items[i].id || d2_HoveredWindow == items[i].slot
				        || (d2_HoveredWindow != -1
				            && *(char**) (&((D2_CONTROL_TL*) g_1015ea0)
				                   [((D2_WIN*)g_1015f40)[d2_HoveredWindow].slot].parent)
				                == (char*) &((D2_WIN*)g_1015f40)[items[i].slot]))) {
					goto found;
				}
			}
			continue;
found:
			if (g_774964 == 0 || fcn_005dfe80(g_14ac644, 0x101) != 0) {
				sprintf(text, "Gamedata\\Saves\\%s.SAV", items[i].name);
				strcpy(g_7e21a0, text);
				(*(int*)&g_7747b0) = 0xa;
				g_774654 = 1;
				result = 1;
			}
		}
	}
	d2_DestroyForm(h);
	return result;
}
