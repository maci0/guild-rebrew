

// SIZE 0x3cc
#include "Develop/Units/d2.v1/d2_win.h"






#include "Develop/client_types.h"
extern Win_1015f40 d2_Windows[0x60];
extern int d2_CurrentWindowId;
extern char* d2_VisitedBuilding;
extern unsigned char* d2_InteriorBuilding;

void __cdecl d2_AddElementToWindow(int, int, int, int);

void __cdecl d2_DrawPanelFrame(int wnd, int page, int icon)
{
	unsigned char* p;

	d2_AddElementToWindow(0x257, 9, 0x520, wnd);
	if (icon != 0) {
		d2_AddElementToWindow(0xb, 9, icon, wnd);
	} else {
		p = ((unsigned char*)d2_VisitedBuilding);
		if (p == 0) {
			p = d2_InteriorBuilding;
		}
		if (p == 0) {
			d2_AddElementToWindow(0xb, 9, 0x520, wnd);
		} else {
			d2_AddElementToWindow(0xb, 9, *p + 0x427, wnd);
		}
	}
	p = ((unsigned char*)d2_VisitedBuilding);
	if (p == 0) {
		p = d2_InteriorBuilding;
	}
	if (p == 0) {
		d2_AddElementToWindow(0x257, 9, 0x444, wnd);
	} else if (page != 0x73b) {
		d2_AddElementToWindow(0x257, 9, *p + 0x427, wnd);
	} else {
		d2_AddElementToWindow(0x1eb, 9, 0x520, wnd);
		d2_AddElementToWindow(0x1eb, 9, *p + 0x427, wnd);
	}
	if (page != 0x73b) {
		d2_AddElementToWindow(0, 0, page, wnd);
		d2_AddElementToWindow(0, 0x190, page + 1, wnd);
		d2_AddElementToWindow(0, 0x4d, page + 2, wnd);
		d2_AddElementToWindow(0x247, 0x4d, page + 3, wnd);
	} else {
		d2_AddElementToWindow(0, 0, 0x73b, wnd);
		d2_AddElementToWindow(0, 0x43, 0x73d, wnd);
		d2_AddElementToWindow(0x1f7, 0x43, 0x73e, wnd);
		d2_AddElementToWindow(0, 0x1a8, 0x73c, wnd);
	}
	((int*) ((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3a8)[0] = 0x18;
	((int*) ((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3a8)[1] = 0x18;
	((int*) ((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3a8)[2] = 0x18;
	((int*) ((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3a8)[3] = 0x18;
}
