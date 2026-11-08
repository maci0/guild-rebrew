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

/* ADDRESS: GOLDTL 0x0046e7a0 */
void __cdecl d2_SetBackgroundTexture(const char* name, int win)
{
	char msg[0x400];
	D2_WIN* w;

	w = &((D2_WIN*)g_1015f40)[win];
	if (w->tex) {
		fcn_0047ce50(w->tex);
		w->tex = 0;
	}
	if (name && *name) {
		w->tex = fcn_0047ce00(name, 1);
		if (!w->tex) {
			sprintf(msg, s_67d54c);
			ReportClientMessage(msg);
		}
		w->alpha = 0.5f;
	}
}
