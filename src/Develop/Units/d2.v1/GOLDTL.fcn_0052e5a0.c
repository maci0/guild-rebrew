

// SIZE 0x3cc
#include "Develop/Units/d2.v1/d2_window_view.h"





extern int g_6a25b8;
extern char* g_7746c4;
extern unsigned char* g_7746c8;
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
#include "client_types.h"


int __cdecl fcn_00470820(int a, int b, char* s);
void __cdecl d2_SetForm(int h, int mode);
int __cdecl fcn_0052dee0(int x, int y, int z);
int __cdecl fcn_00508da0(unsigned char* s);
void __cdecl fcn_005186c0(int id, int a, int b, char* out);
void __cdecl io_AppendText(char* fmt, ...);
int __cdecl fcn_0046f740(int x, int y, int kind, int owner);
int __cdecl fcn_004677e0(int a, int b, int c, int d, int e, int f, int g, int h);
#include "Develop/Units/d2.v1/d2_gui.h"

void __cdecl fcn_0052e5a0(void)
{
	char name[128];
	int pct;

	if (g_6a25b8 != -1) {
		return;
	}
	if (g_7746c8 == 0) {
		if (((unsigned char*)g_7746c4) != 0) {
			return;
		}
		g_6a25b8 = fcn_00470820(g_1040494 - 0x68, 0x106, g_6a2fac);
		d2_SetForm(g_6a25b8, 0);
		g_6a25dc = fcn_0052dee0(0, 0x8c, g_14ad0c8);
		g_6a25e0 = fcn_0052dee0(0, 0xa6, g_14ad0dc);
		return;
	}
	if (*(unsigned short*) (g_7746c8 + 0x27) != g_774970) {
		return;
	}
	pct = fcn_00508da0(g_7746c8);
	g_6a25b8 = fcn_00470820(g_1040494 - 0x68, 0x106, g_6a2f40);
	d2_SetForm(g_6a25b8, 0);
	d2_SetForm(g_6a25b8, 1);
	fcn_005186c0(*(unsigned short*) (g_7746c8 + 0x27), 2, 1, name);
	io_AppendText(g_6a2f9c, name, *g_7746c8 * 14 + 0x48e, g_7746c8 + 5);
	d2_SetForm(g_6a25b8, 0);
	fcn_0046f740(((((D2_WIN*)g_1015f40)[d2_CurrentWindowId].width - 0x30) >> 1) - 1, 0x4c, *g_7746c8 + 0x427, d2_CurrentWindowId);
	d2_CurrentValueBar = fcn_004677e0(0x15, 0x7a, 0x30, 0, 0x64, 0x75, 0x442, d2_CurrentWindowId);
	d2_SetElementValue(d2_CurrentValueBar, 0, 0x64, pct);
	g_6a25ec = fcn_0052dee0(0, 0x8c, g_14ad0cc);
	if (*g_7746c8 == 0x1e) {
		g_6a25f0 = fcn_0052dee0(0, 0xa6, g_14ad0d0);
	} else {
		g_6a25e0 = fcn_0052dee0(0, 0xa6, g_14ad0dc);
	}
}
