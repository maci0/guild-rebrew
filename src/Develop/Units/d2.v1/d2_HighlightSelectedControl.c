extern int g_6a476c;
extern unsigned char g_7747b0;
extern volatile int g_6b7fc0;

// SIZE 0xc
struct D2_ACTIVE_HUD_SLOT {
	unsigned char* e;
	int s;
	int h;
};

extern unsigned char** g_7749e4;




#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_BringFormToFront(int);

void __cdecl d2_HighlightSelectedControl(struct D2_ACTIVE_HUD_SLOT* ne)
{
	unsigned char* e;

	if (g_6a476c == -1) {
		return;
	}
	if ((*(struct D2_ACTIVE_HUD_SLOT**)&g_7749e4) != 0) {
		if ((*(struct D2_ACTIVE_HUD_SLOT**)&g_7749e4)->s != -1) {
			d2_SetElementValue((*(struct D2_ACTIVE_HUD_SLOT**)&g_7749e4)->s, 0);
		}
		d2_SetFormVisibility((*(struct D2_ACTIVE_HUD_SLOT**)&g_7749e4)->h, 0);
		e = (*(struct D2_ACTIVE_HUD_SLOT**)&g_7749e4)->e;
		if (e != 0 && ((e[0] == 0x11 && (e[0xf0] & 0x40) != 0) || e[0] == 0x87) &&
		    (g_7747b0 & 4) == 0) {
			g_6b7fc0 = 0;
		}
		(*(struct D2_ACTIVE_HUD_SLOT**)&g_7749e4) = 0;
	}
	if (ne != 0 && ne->h != -1) {
		if (ne->s != -1) {
			d2_SetElementValue(ne->s, 1);
		}
		d2_SetFormVisibility(ne->h, 1);
		d2_BringFormToFront(ne->h);
		e = ne->e;
		if (e != 0 && ((e[0] == 0x11 && (e[0xf0] & 0x40) != 0) || e[0] == 0x87) &&
		    (g_7747b0 & 4) == 0) {
			g_6b7fc0 = 1;
		}
	}
	(*(struct D2_ACTIVE_HUD_SLOT**)&g_7749e4) = ne;
}
