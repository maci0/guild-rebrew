

// SIZE 0x3cc
#include "Develop/Units/d2.v1/d2_window_view.h"





// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int f5c;
	char pad60[0x2f4 - 0x60];
} Ent;

extern int g_6a25b8;
extern int g_1040494;
extern char g_6a2f80[];
extern char g_6a2f74[];
extern int d2_CurrentWindowId;
#include "Develop/client_types.h"

extern char* d2_Controls;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_14b5e84;
extern int g_6a25e8;
extern int d2_CurrentValueBar;
extern int g_6a25d4;
extern int g_6b5c48;

unsigned short* __cdecl gm_ResolveParentEntity(unsigned short* e);
int __cdecl d2_LoadForm(int a, int b, char* s);
void __cdecl d2_SetForm(int h, int mode);
void __cdecl io_AppendText(char* fmt, int a, int b);
int __cdecl d2_AddElementToWindow(int x, int y, int kind, int owner);
int __cdecl d2_CreateWindowTextButton(int x, int y, int z);
int __cdecl d2_AddWindowValueGauge(int a, int b, int c, int d, int e, int f, int g, int h);
#include "Develop/Units/d2.v1/d2_gui.h"

void __cdecl d2_OpenTransporterInfoPanel(unsigned short* e)
{
	unsigned short* parent;
	int x;
	int id;

	if (g_6a25b8 == -1) {
		parent = gm_ResolveParentEntity(e);
		if (parent != 0) {
			g_6a25b8 = d2_LoadForm(g_1040494 - 0x68, 0x106, g_6a2f80);
			d2_SetForm(g_6a25b8, 1);
			io_AppendText(g_6a2f74, *parent, *e * 2 + 0x9a8);
			d2_SetForm(g_6a25b8, 0);
			x = ((((D2_WIN*)d2_Windows)[d2_CurrentWindowId].width - 0x30) >> 1) - 1;
			id = d2_AddElementToWindow(x, 0x30, *e + 0xdf, d2_CurrentWindowId);
			((D2_CONTROL_TL*) d2_Controls)[id].value_05c = 1;
			if (*parent == gm_LocalPlayerSlot) {
				g_6a25e8 = d2_CreateWindowTextButton(x, 0xac, g_14b5e84);
			}
			d2_CurrentValueBar = d2_AddWindowValueGauge(0x18, 0x66, 0x30, 0, 0x64, 0x75, 0x442, d2_CurrentWindowId);
			d2_SetElementValue(d2_CurrentValueBar, 0, 0x64, *((unsigned char*) e + 0x12));
			d2_SetForm(g_6a25b8, 2);
			g_6a25d4 = d2_CurrentWindowId;
			g_6b5c48 = *(int*) ((char*) e + 0x3b);
		}
	}
}
