

// SIZE 0x3c4
#include "Develop/Units/d2.v1/gold_window.h"





#include "Develop/client_types.h"
extern Slot_f8f110 g_f8f110[];
extern int g_6ed938;
extern unsigned char* g_6f2308;
extern unsigned char* g_6f230c;

void __cdecl d2_AddElementToWindow(int, int, int, int);

void __cdecl d2_DrawWindowFrame(int wnd, int page, int icon)
{
	unsigned char* p;

	d2_AddElementToWindow(0x257, 9, 0x520, wnd);
	if (icon != 0) {
		d2_AddElementToWindow(0xb, 9, icon, wnd);
	} else {
		p = g_6f2308;
		if (p == 0) {
			p = g_6f230c;
		}
		if (p == 0) {
			d2_AddElementToWindow(0xb, 9, 0x520, wnd);
		} else {
			d2_AddElementToWindow(0xb, 9, *p + 0x427, wnd);
		}
	}
	p = g_6f2308;
	if (p == 0) {
		p = g_6f230c;
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
	((GOLD_GUI_WINDOW*) ((char*) g_f8f110 + 0x10))[g_6ed938].margin[0] = 0x18;
	((GOLD_GUI_WINDOW*) ((char*) g_f8f110 + 0x10))[g_6ed938].margin[1] = 0x18;
	((GOLD_GUI_WINDOW*) ((char*) g_f8f110 + 0x10))[g_6ed938].margin[2] = 0x18;
	((GOLD_GUI_WINDOW*) ((char*) g_f8f110 + 0x10))[g_6ed938].margin[3] = 0x18;
}
