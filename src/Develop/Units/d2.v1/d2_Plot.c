#include <stdio.h>

#include "Develop/Units/d2.v1/d2_win.h"
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char s_67d54c[];

void __cdecl fcn_0047ce50(void* tex);
void* __cdecl fcn_0047ce00(const char* name, int a2);
#include "Develop/Units/Error/error_message.h"
typedef Obj_1038140 Obj;

extern Obj_1038140 g_1038140[];
extern int g_772534;
extern int g_772514;
extern char* g_77255c;
extern char s_67d7d0[];

#include "GOLDTL.fcn_00472960_gconf.h"

void __cdecl fcn_00475fd0(void*);
int __cdecl fcn_00476b10(int x, int y, unsigned char r, unsigned char g, unsigned char b, void* s);
void __cdecl fcn_00476060(void*);

/* ADDRESS: GOLDTL 0x00472960 */
void __cdecl d2_Plot(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	D2_WIN* w;

	w = &((D2_WIN*)g_1015f40)[g_772514];
	if (w->active == 0) {
		return;
	}
	if (w->surf == 0) {
		ReportClientMessage("d2_Plot:Window is not a paintbox!");
		return;
	}
	if (x < (unsigned char) g_772558 || x > w->width - (unsigned char) g_772558
	    || y < (unsigned char) g_772558 || y > w->height - (unsigned char) g_772558) {
		return;
	}
	fcn_00475fd0(w->surf);
	switch ((unsigned char) g_772558) {
	case 0:
		fcn_00476b10(x, y, r, g, b, w->surf);
		break;
	case 1:
		fcn_00476b10(x - 1, y, r, g, b, w->surf);
		fcn_00476b10(x + 1, y, r, g, b, w->surf);
		fcn_00476b10(x, y + 1, r, g, b, w->surf);
		fcn_00476b10(x, y - 1, r, g, b, w->surf);
		fcn_00476b10(x, y, r, g, b, w->surf);
		break;
	case 2:
		fcn_00476b10(x - 1, y, r, g, b, w->surf);
		fcn_00476b10(x + 1, y, r, g, b, w->surf);
		fcn_00476b10(x - 2, y, r, g, b, w->surf);
		fcn_00476b10(x + 2, y, r, g, b, w->surf);
		fcn_00476b10(x, y, r, g, b, w->surf);
		fcn_00476b10(x, y + 1, r, g, b, w->surf);
		fcn_00476b10(x, y - 1, r, g, b, w->surf);
		fcn_00476b10(x, y + 2, r, g, b, w->surf);
		fcn_00476b10(x, y - 2, r, g, b, w->surf);
		fcn_00476b10(x + 1, y + 1, r, g, b, w->surf);
		fcn_00476b10(x - 1, y - 1, r, g, b, w->surf);
		fcn_00476b10(x - 1, y + 1, r, g, b, w->surf);
		fcn_00476b10(x + 1, y - 1, r, g, b, w->surf);
		break;
	}
	fcn_00476060(w->surf);
}
