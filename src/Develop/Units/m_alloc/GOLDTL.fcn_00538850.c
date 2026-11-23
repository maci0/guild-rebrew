#include <windows.h>
#include <stdlib.h>
extern void __cdecl fcn_005e1ca0(void);
extern void __cdecl main_PumpWindowMessages(void);
extern int __cdecl fcn_0041a380(unsigned int, unsigned int, unsigned char);
extern char __cdecl fcn_0041a970(HWND, void*, unsigned char, unsigned char);
extern void __cdecl ReportClientMessage(char*);
extern void __cdecl d3_ClearDisplayAdapterList(void);
extern void __cdecl m_ShutdownAllocator(void);
extern void __cdecl fcn_0041d850(void);
extern char __cdecl fcn_00439020(void*, HWND, int);
extern void __cdecl d3_CreateSceneCameras(void);
extern void __cdecl fcn_00411820(HWND, int, int);
extern void __cdecl fcn_00410610(int);
extern int __cdecl fcn_005386e0(void);
extern void __cdecl fcn_005386c0(int);
extern void __cdecl fcn_005e2510(void);
extern void __cdecl d3_ApplyGraphicsOptions(void);
extern void __cdecl fcn_0045bf50(char*);
extern void __cdecl fcn_00449aa0(char*);
extern int __cdecl d2_Open(HWND, int, int, char*, char*);
extern void __cdecl fcn_00473df0(void);
extern int __cdecl sprintf(char*, const char*, ...);
extern int g_1015ce0;
extern int d2_ScreenHeight;
extern int g_1040494;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_6acf80;
extern int g_6acf84;

typedef struct Gfx538 {
	int w2;
	int h2;
	int fmt;
	int count;
	int ms;
	int swap;
	int depth;
	int flags;
	int refresh;
	int dxt;
	int a50;
	int a54;
	int a58;
	int a5c;
	int a60;
	float x;
	float y;
	float a6c;
	float a70;
	float f74;
	float f78;
	float f7c;
} Gfx538;

/* Creates the game window and the D3D8.1 device: work-area sizing, window
 * style round-trip, render-state defaults and the gfx file list. */
/* ADDRESS: GOLDTL 0x00538850 */
int __cdecl fcn_00538850(int topmost)
{
	Gfx538 g;
	RECT work;
	RECT rc;
	char text[MAX_PATH];
	int style;
	int exstyle;
	int dx;
	int dy;
	int w;
	int h;

	g.w2 = 0;
	g.h2 = 0;
	g.fmt = 0x10;
	g.count = 1;
	g.ms = 1;
	g.swap = 0x4000;
	g.depth = 0x1000;
	g.flags = 8;
	g.refresh = 0x18;
	g.dxt = 0;
	g.a50 = 0;
	g.a54 = 0;
	g.a58 = 0;
	g.a5c = 0;
	g.a60 = 0x20;
	g.x = 0.0f;
	g.y = 0.0f;
	g.a6c = 0.0f;
	g.a70 = 0.0f;
	g.f74 = 4.0f;
	g.f78 = 12000.0f;
	g.f7c = 640.0f;
	dx = 0;
	dy = 0;
	fcn_005e1ca0();
	g_6a3764 = 0;
	g_6a3768 = 0;
	g_6a376c = g_6acf80 - 0x6a;
	g_6a3770 = g_6acf84;
	SystemParametersInfoA(0x30, 0, &work, 0);
	w = work.right - work.left;
	h = work.bottom - work.top;
	rc.left = 0;
	rc.top = 0;
	rc.right = g_6acf80;
	rc.bottom = g_6acf84;
	exstyle = GetWindowLongA(*(HWND*) 0x774940, -0x14);
	style = GetWindowLongA(*(HWND*) 0x774940, -0x10);
	if (AdjustWindowRectEx(&rc, style, 0, exstyle)) {
		dx = rc.right - rc.left;
		dy = rc.bottom - rc.top;
	}
	if (topmost != 0) {
		SetWindowPos(*(HWND*) 0x774940, HWND_TOP,
			abs(w - dx) / 2, abs(h - dy) / 2, dx, dy, 0);
	} else {
		SetWindowPos(*(HWND*) 0x774940, HWND_TOPMOST,
			abs(w - dx) / 2, abs(h - dy) / 2, dx, dy, 0);
	}
	main_PumpWindowMessages();
	g.x = (float) g_6acf80;
	g.y = (float) g_6acf84;
	g.w2 = g_6acf80;
	g.h2 = g_6acf84;
	g.ms = (topmost == 1);
	g.a5c = *(int*) 0x7747e4;
	g.fmt = 0x10;
	g.count = 0;
	g.a6c = 0.0f;
	g.a70 = 0.0f;
	g.a50 = 1;
	g.a54 = 0;
	g.a58 = 0;
	g.a60 = 0x20;
	g.flags = 8;
	g.dxt = 0x31545844;
	g.swap = 0xfa00;
	g.depth = 0x1000;
	g.refresh = 0x20;
	g.f74 = 4.0f;
	g.f78 = 12000.0f;
	d3_LODMode = 2;
	g.f7c = (float) (512.0 / (640.0 / (double) (unsigned int) g_6acf80));
	fcn_0041a380(g_6acf80, g_6acf84, topmost == 1);
	if (!fcn_0041a970(*(HWND*) 0x774940, (void*) 0x5387c0, topmost == 1, 1)) {
		ReportClientMessage((char*) 0x6a3904);
		d3_ClearDisplayAdapterList();
		m_ShutdownAllocator();
		fcn_0041d850();
		return 0;
	}
	d3_ClearDisplayAdapterList();
	if (!fcn_00439020(&g, *(HWND*) 0x774940, main_Instance))
		return 0;
	d3_CreateSceneCameras();
	while (ShowCursor(0) > 0)
		;
	if (topmost == 0) {
		if (*(int*) 0x7e246c == 0) {
			*(int*) 0x774974 = fcn_005386e0();
			if (*(int*) 0x774974 != 0)
				fcn_005386c0(0);
		}
		fcn_00411820(*(HWND*) 0x774940, main_Instance, 1);
		fcn_00410610(0x50);
	} else {
		fcn_00411820(*(HWND*) 0x774940, main_Instance, 6);
	}
	fcn_005e2510();
	fcn_0045bf50((char*) 0x6a38f8);
	*(int*) 0x67ac98 = *(int*) 0x6a38ec;
	*(int*) 0x67ac9c = *(int*) 0x6a38f0;
	*(int*) 0x67aca0 = *(int*) 0x6a38f4;
	fcn_00449aa0((char*) 0x6a38e0);
	*(int*) 0x7e1ae0 = *(int*) 0x6a38d8;
	*(int*) 0x7e1ae4 = *(int*) 0x6a38dc;
	*(int*) 0x6790c8 = *(int*) 0x6a38cc;
	*(int*) 0x6790cc = *(int*) 0x6a38d0;
	*(unsigned char*) 0x6790d0 = *(unsigned char*) 0x6a38d4;
	sprintf((char*) 0x67d268, (char*) 0x6a38c4);
	d3_ApplyGraphicsOptions();
	sprintf(text, (char*) 0x6a38b0, (char*) 0x679888);
	if (!d2_Open(*(HWND*) 0x774940, g_6acf80, g_6acf84,
			(char*) 0x6a3550, text))
		return 0;
	g_1015ce0 = *(int*) 0x774940;
	d2_MouseRightBoundary = g_1040494 - 8;
	d2_MouseBottomBoundary = d2_ScreenHeight;
	fcn_00473df0();
	main_PumpWindowMessages();
	return 1;
}
