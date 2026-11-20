

// SIZE 0x3cc
#include "Develop/Units/d2.v1/d2_win.h"






#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int d2_CurrentWindowId;
extern char* g_7746c4;
extern unsigned char* g_7746c8;

void __cdecl fcn_0046f740(int, int, int, int);

void __cdecl d2_DrawPanelFrame(int wnd, int page, int icon)
{
	unsigned char* p;

	fcn_0046f740(0x257, 9, 0x520, wnd);
	if (icon != 0) {
		fcn_0046f740(0xb, 9, icon, wnd);
	} else {
		p = ((unsigned char*)g_7746c4);
		if (p == 0) {
			p = g_7746c8;
		}
		if (p == 0) {
			fcn_0046f740(0xb, 9, 0x520, wnd);
		} else {
			fcn_0046f740(0xb, 9, *p + 0x427, wnd);
		}
	}
	p = ((unsigned char*)g_7746c4);
	if (p == 0) {
		p = g_7746c8;
	}
	if (p == 0) {
		fcn_0046f740(0x257, 9, 0x444, wnd);
	} else if (page != 0x73b) {
		fcn_0046f740(0x257, 9, *p + 0x427, wnd);
	} else {
		fcn_0046f740(0x1eb, 9, 0x520, wnd);
		fcn_0046f740(0x1eb, 9, *p + 0x427, wnd);
	}
	if (page != 0x73b) {
		fcn_0046f740(0, 0, page, wnd);
		fcn_0046f740(0, 0x190, page + 1, wnd);
		fcn_0046f740(0, 0x4d, page + 2, wnd);
		fcn_0046f740(0x247, 0x4d, page + 3, wnd);
	} else {
		fcn_0046f740(0, 0, 0x73b, wnd);
		fcn_0046f740(0, 0x43, 0x73d, wnd);
		fcn_0046f740(0x1f7, 0x43, 0x73e, wnd);
		fcn_0046f740(0, 0x1a8, 0x73c, wnd);
	}
	((int*) ((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3a8)[0] = 0x18;
	((int*) ((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3a8)[1] = 0x18;
	((int*) ((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3a8)[2] = 0x18;
	((int*) ((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3a8)[3] = 0x18;
}
