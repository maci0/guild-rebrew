#include <stdio.h>

#include "Develop/Units/d2.v1/gold_window.h"
#include "Develop/Units/d2.v1/d2_win.h"
#include "Develop/client_types.h"
#include "Develop/Units/Error/error_message.h"
#include "GOLDTL.fcn_00472960_gconf.h"

typedef D2_FORM_RECORD Obj;

extern int d2_CurrentWindowId;
extern D2_FORM_RECORD d2_Forms[];
extern int g_772534;
extern char* d2_CurrentWindow;
extern char s_67d54c[];
extern char s_67d7d0[];

void __cdecl fcn_004222b0(char*);
void __cdecl d2_LockSurface(void*);
int __cdecl d3_UnlockSurfaceHandle(void*);
int __cdecl d2_WriteSurfacePixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, void* s);
void __cdecl d3_SafeReleaseSceneResource(void* tex);
void* __cdecl d3_LoadTextureWithDefaultTint(const char* name, int a2);
void __cdecl d2_UnlockSurface(void*);

#if defined(REBREW_GOLD)
extern GOLD_GUI_WINDOW d2_Windows[];

/* ADDRESS: GOLD 0x00476210 */
void __cdecl d2_Plot(int x, int y, int r, int g, int b)
{
	GOLD_GUI_WINDOW* win;
	int border;

	win = &d2_Windows[d2_CurrentWindowId];
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
	d3_UnlockSurfaceHandle((void*) win->unk_028);
}
#else
extern Win_1015f40 d2_Windows[0x60];

/* ADDRESS: GOLDTL 0x00472960 */
/* ADDRESS: GOLDDE 0x00465b20 */
void __cdecl d2_Plot(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	D2_WIN* w;

	w = &((D2_WIN*)d2_Windows)[d2_CurrentWindowId];
	if (w->active == 0) {
		return;
	}
	if (w->surf == 0) {
		ReportClientMessage("d2_Plot:Window is not a paintbox!");
		return;
	}
	if (x < (unsigned char) d2_PlotRadius || x > w->width - (unsigned char) d2_PlotRadius
	    || y < (unsigned char) d2_PlotRadius || y > w->height - (unsigned char) d2_PlotRadius) {
		return;
	}
	d2_LockSurface(w->surf);
	switch ((unsigned char) d2_PlotRadius) {
	case 0:
		d2_WriteSurfacePixel(x, y, r, g, b, w->surf);
		break;
	case 1:
		d2_WriteSurfacePixel(x - 1, y, r, g, b, w->surf);
		d2_WriteSurfacePixel(x + 1, y, r, g, b, w->surf);
		d2_WriteSurfacePixel(x, y + 1, r, g, b, w->surf);
		d2_WriteSurfacePixel(x, y - 1, r, g, b, w->surf);
		d2_WriteSurfacePixel(x, y, r, g, b, w->surf);
		break;
	case 2:
		d2_WriteSurfacePixel(x - 1, y, r, g, b, w->surf);
		d2_WriteSurfacePixel(x + 1, y, r, g, b, w->surf);
		d2_WriteSurfacePixel(x - 2, y, r, g, b, w->surf);
		d2_WriteSurfacePixel(x + 2, y, r, g, b, w->surf);
		d2_WriteSurfacePixel(x, y, r, g, b, w->surf);
		d2_WriteSurfacePixel(x, y + 1, r, g, b, w->surf);
		d2_WriteSurfacePixel(x, y - 1, r, g, b, w->surf);
		d2_WriteSurfacePixel(x, y + 2, r, g, b, w->surf);
		d2_WriteSurfacePixel(x, y - 2, r, g, b, w->surf);
		d2_WriteSurfacePixel(x + 1, y + 1, r, g, b, w->surf);
		d2_WriteSurfacePixel(x - 1, y - 1, r, g, b, w->surf);
		d2_WriteSurfacePixel(x - 1, y + 1, r, g, b, w->surf);
		d2_WriteSurfacePixel(x + 1, y - 1, r, g, b, w->surf);
		break;
	}
	d2_UnlockSurface(w->surf);
}
#endif
