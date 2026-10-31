#include <windows.h>

extern void __cdecl fcn_005e1ca0(void);
extern void __cdecl fcn_005356e0(void);
extern void __cdecl fcn_0041a380(int, int, int);
extern char __cdecl fcn_0041a970(HWND, void*, int, int);
extern void __cdecl ReportClientMessage(char*);
extern void __cdecl fcn_0041a2a0(void);
extern void __cdecl m_ShutdownAllocator(void);
extern void __cdecl fcn_0041d850(void);
extern char __cdecl fcn_00439020(void*, HWND, int);
extern void __cdecl fcn_00444040(void);
extern void __cdecl fcn_00411820(HWND, int, int);
extern void __cdecl fcn_00410610(int);
extern int __cdecl fcn_005386e0(void);
extern void __cdecl fcn_005386c0(int);
extern void __cdecl fcn_005e2510(void);
extern void __cdecl fcn_005e22a0(void);
extern void __cdecl fcn_0045bf50(char*);
extern void __cdecl fcn_00449aa0(char*);
extern int __cdecl d2_Open(HWND, int, int, char*, char*);
extern void __cdecl fcn_00473df0(void);
extern int __cdecl sprintf(char*, const char*, ...);

typedef struct Gfx538 {
	int width;
	int height0;
	int rcL;
	int rcT;
	int rcR;
	int rcB;
	int w2;
	int h2;
	int fmt;
	int count;
	int ms;
	int swap;
	int depth;
	int flags;
	int refresh;
	int interval;
	int a40;
	int a44;
	int a48;
	int dxt;
	int a50;
	int a54;
	int a58;
	int a5c;
	int a60;
	int a64;
	int a68;
	int a6c;
	int a70;
	float f74;
	float f78;
	float f7c;
	char a80[0x14];
	char text[0x100];
} Gfx538;

/* Creates the game window and the D3D8.1 device: work-area sizing, window
 * style round-trip, render-state defaults and the gfx file list. */
/* ADDRESS: GOLDTL 0x00538850 */
int __cdecl fcn_00538850(int topmost)
{
	Gfx538 g;
	RECT work;
	int style;
	int exstyle;
	int dx;
	int dy;
	int w;
	int h;

	g.width = 0;
	g.height0 = 0;
	g.rcL = 0;
	g.rcT = 0;
	g.rcR = 0;
	g.rcB = 0;
	g.w2 = 0;
	g.h2 = 0;
	g.fmt = 0x10;
	g.count = 1;
	g.ms = 1;
	g.swap = 0x4000;
	g.depth = 0x1000;
	g.flags = 8;
	g.refresh = 0x18;
	g.interval = 0;
	g.a40 = 0;
	g.a44 = 0;
	g.a48 = 0;
	g.dxt = 0;
	g.a50 = 0x20;
	g.a54 = 0;
	g.a58 = 0;
	g.a5c = 0;
	g.a60 = 0;
	g.f74 = 4.0f;
	g.f78 = 12000.0f;
	g.f7c = 32.0f;
	fcn_005e1ca0();
	*(int*) 0x6a376c = *(int*) 0x6acf80 - 0x6a;
	*(int*) 0x6a3764 = 0;
	*(int*) 0x6a3768 = 0;
	*(int*) 0x6a3770 = *(int*) 0x6acf84;
	SystemParametersInfoA(0x30, 0, &work, 0);
	w = work.right - work.left;
	h = work.bottom - work.top;
	*(int*) 0x6a3764 = 0;
	*(int*) 0x6a3768 = 0;
	*(int*) 0x6a376c = *(int*) 0x6acf80;
	*(int*) 0x6a3770 = *(int*) 0x6acf84;
	exstyle = GetWindowLongA(*(HWND*) 0x774940, -0x14);
	style = GetWindowLongA(*(HWND*) 0x774940, -0x10);
	g.rcL = 0;
	g.rcT = 0;
	g.rcR = *(int*) 0x6acf80;
	g.rcB = *(int*) 0x6acf84;
	if (AdjustWindowRectEx((RECT*) &g.rcL, style, 0, exstyle)) {
		dx = g.w2 - g.rcL;
		dy = g.h2 - g.rcT;
	} else {
		dy = g.width;
	}
	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;
	SetWindowPos(*(HWND*) 0x774940, topmost == 0 ? HWND_TOPMOST : HWND_TOP,
		(w - dx) / 2, (h - dy) / 2, dx, dy, 0);
	fcn_005356e0();
	g.width = *(int*) 0x6acf80;
	g.height0 = 0;
	g.w2 = *(int*) 0x6acf80;
	g.h2 = *(int*) 0x6acf84;
	g.a5c = *(int*) 0x7747e4;
	g.ms = (topmost == 1);
	g.a50 = 1;
	g.a54 = 0;
	g.a58 = 0;
	g.a60 = 0x20;
	g.flags = 8;
	g.dxt = 0x31545844;
	g.refresh = 0xfa00;
	g.interval = 0x1000;
	g.a48 = 0x20;
	g.f74 = 4.0f;
	g.f78 = 12000.0f;
	g.f7c = (float) (12000.0 / (double) g.width);
	*(int*) 0x67ac90 = 2;
	fcn_0041a380(*(int*) 0x6acf80, *(int*) 0x6acf84, topmost == 1);
	if (!fcn_0041a970(*(HWND*) 0x774940, (void*) 0x5387c0, topmost == 1, 1)) {
		ReportClientMessage((char*) 0x6a3904);
		fcn_0041a2a0();
		m_ShutdownAllocator();
		fcn_0041d850();
		return 0;
	}
	fcn_0041a2a0();
	if (!fcn_00439020(&g.w2, *(HWND*) 0x774940, *(int*) 0x7e1f80))
		return 0;
	fcn_00444040();
	while (ShowCursor(0) > 0)
		;
	if (topmost == 0) {
		if (*(int*) 0x7e246c == 0) {
			*(int*) 0x774974 = fcn_005386e0();
			if (*(int*) 0x774974 != 0)
				fcn_005386c0(0);
		}
		fcn_00411820(*(HWND*) 0x774940, *(int*) 0x7e1f80, 1);
		fcn_00410610(0x50);
	} else {
		fcn_00411820(*(HWND*) 0x774940, *(int*) 0x7e1f80, 6);
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
	fcn_005e22a0();
	sprintf(g.text, (char*) 0x6a38b0, (char*) 0x679888);
	if (!d2_Open(*(HWND*) 0x774940, *(int*) 0x6acf80, *(int*) 0x6acf84,
			(char*) 0x6a3550, g.text))
		return 0;
	*(int*) 0x1015ce0 = *(int*) 0x774940;
	*(int*) 0x6772bc = *(int*) 0x1040494 - 8;
	*(int*) 0x6772c0 = *(int*) 0x1040490;
	fcn_00473df0();
	fcn_005356e0();
	return 1;
}
