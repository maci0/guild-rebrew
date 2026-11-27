#include "Develop/Units/d2.v1/gold_window.h"

extern int d2_CurrentWindowId;
extern GOLD_GUI_WINDOW g_1015f40[];

void __cdecl fcn_004222b0(char*);
int __cdecl d2_LockSurface(void*);
int __cdecl fcn_004790d0(void*);
int __cdecl d2_WriteSurfacePixel(int, int, unsigned char, unsigned char, unsigned char, void*);

/* ADDRESS: GOLD 0x00476210 */
void __cdecl d2_Plot(int x, int y, int r, int g, int b)
{
	GOLD_GUI_WINDOW* win;
	int border;

	win = &g_1015f40[d2_CurrentWindowId];
	if (win->active == 0) {
		return;
	}
	if (win->unk_028 == 0) {
		fcn_004222b0((char*) 0x5feb18);
		return;
	}
	border = *(unsigned int*) 0x6ed97c & 0xff;
	if (x < border || x > win->width - border || y < border || y > win->height - border) {
		return;
	}
	d2_LockSurface((void*) win->unk_028);
	switch (*(unsigned int*) 0x6ed97c & 0xff) {
	case 0:
		d2_WriteSurfacePixel(x, y, r, g, b, (void*) win->unk_028);
		break;
	case 1:
		d2_WriteSurfacePixel(x - 1, y, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x + 1, y, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x, y + 1, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x, y - 1, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x, y, r, g, b, (void*) win->unk_028);
		break;
	case 2:
		d2_WriteSurfacePixel(x - 1, y, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x + 1, y, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x - 2, y, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x + 2, y, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x, y, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x, y + 1, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x, y - 1, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x, y + 2, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x, y - 2, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x + 1, y + 1, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x - 1, y - 1, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x - 1, y + 1, r, g, b, (void*) win->unk_028);
		d2_WriteSurfacePixel(x + 1, y - 1, r, g, b, (void*) win->unk_028);
		break;
	}
	fcn_004790d0((void*) win->unk_028);
}
