

// SIZE 0x3cc
#include "Develop/Units/d2.v1/d2_window_view.h"





extern int g_6a25b8;
extern char* d2_VisitedBuilding;
extern unsigned char* d2_InteriorBuilding;
extern int g_1040494;
extern char g_6a2fac[];
extern char g_6a2f40[];
extern char g_6a2f9c[];
extern int g_14ad0c8;
extern int g_14ad0cc;
extern int g_14ad0d0;
extern int g_14ad0dc;
extern int g_6a25dc;
extern int g_6a25e0;
extern int g_6a25ec;
extern int g_6a25f0;
extern int d2_CurrentValueBar;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
#include "Develop/client_types.h"


int __cdecl d2_LoadForm(int a, int b, char* s);
void __cdecl d2_SetForm(int h, int mode);
int __cdecl d2_CreateWindowTextButton(int x, int y, int z);
int __cdecl gm_GetEntityMood(unsigned char* s);
void __cdecl io_FormatEntityNameMarkup(int id, int a, int b, char* out);
void __cdecl io_AppendText(char* fmt, ...);
int __cdecl d2_AddElementToWindow(int x, int y, int kind, int owner);
int __cdecl d2_AddWindowValueGauge(int a, int b, int c, int d, int e, int f, int g, int h);
#include "Develop/Units/d2.v1/d2_gui.h"

void __cdecl d2_OpenBuildingInfoPanel(void)
{
	char name[128];
	int pct;

	if (g_6a25b8 != -1) {
		return;
	}
	if (d2_InteriorBuilding == 0) {
		if (((unsigned char*)d2_VisitedBuilding) != 0) {
			return;
		}
		g_6a25b8 = d2_LoadForm(g_1040494 - 0x68, 0x106, g_6a2fac);
		d2_SetForm(g_6a25b8, 0);
		g_6a25dc = d2_CreateWindowTextButton(0, 0x8c, g_14ad0c8);
		g_6a25e0 = d2_CreateWindowTextButton(0, 0xa6, g_14ad0dc);
		return;
	}
	if (*(unsigned short*) (d2_InteriorBuilding + 0x27) != gm_LocalPlayerSlot) {
		return;
	}
	pct = gm_GetEntityMood(d2_InteriorBuilding);
	g_6a25b8 = d2_LoadForm(g_1040494 - 0x68, 0x106, g_6a2f40);
	d2_SetForm(g_6a25b8, 0);
	d2_SetForm(g_6a25b8, 1);
	io_FormatEntityNameMarkup(*(unsigned short*) (d2_InteriorBuilding + 0x27), 2, 1, name);
	io_AppendText(g_6a2f9c, name, *d2_InteriorBuilding * 14 + 0x48e, d2_InteriorBuilding + 5);
	d2_SetForm(g_6a25b8, 0);
	d2_AddElementToWindow(((((D2_WIN*)d2_Windows)[d2_CurrentWindowId].width - 0x30) >> 1) - 1, 0x4c, *d2_InteriorBuilding + 0x427, d2_CurrentWindowId);
	d2_CurrentValueBar = d2_AddWindowValueGauge(0x15, 0x7a, 0x30, 0, 0x64, 0x75, 0x442, d2_CurrentWindowId);
	d2_SetElementValue(d2_CurrentValueBar, 0, 0x64, pct);
	g_6a25ec = d2_CreateWindowTextButton(0, 0x8c, g_14ad0cc);
	if (*d2_InteriorBuilding == 0x1e) {
		g_6a25f0 = d2_CreateWindowTextButton(0, 0xa6, g_14ad0d0);
	} else {
		g_6a25e0 = d2_CreateWindowTextButton(0, 0xa6, g_14ad0dc);
	}
}
