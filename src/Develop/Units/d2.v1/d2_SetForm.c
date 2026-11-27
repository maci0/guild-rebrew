#include <stdio.h>

#include "gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"
#include "Develop/Units/d2.v1/d2_win.h"
#include "client_types.h"
#include "Develop/Units/Error/error_message.h"
#include "GOLDTL.fcn_00472960_gconf.h"

typedef D2_FORM_RECORD Obj;

extern GOLD_GUI_WINDOW g_00f8f120[]; /* 0x00f8f120 */
extern GuiObj g_00fb1020[]; /* 0x00fb1020 */
extern int g_006ed958; /* 0x006ed958 */
extern int g_006ed938; /* 0x006ed938 */
extern GOLD_GUI_WINDOW* g_006ed980; /* 0x006ed980 */
extern char s_005feaf4[]; /* 0x005feaf4 */

extern Win_1015f40 g_1015f40[0x60];
extern char s_67d54c[];
extern D2_FORM_RECORD g_1038140[];
extern int g_772534;
extern int d2_CurrentWindowId;
extern char* g_77255c;
extern char s_67d7d0[];

void __cdecl fcn_004222b0(const char* msg);
void __cdecl d3_SafeReleaseSceneResource(void* tex);
void* __cdecl d3_LoadTextureWithDefaultTint(const char* name, int a2);
void __cdecl d2_LockSurface(void*);
int __cdecl d2_WriteSurfacePixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, void* s);
void __cdecl d2_UnlockSurface(void*);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00475f60 */
int __cdecl d2_SetForm(int k, int i)
{
	if (k) {
		g_006ed958 = k;
	} else {
		k = g_006ed958;
	}
	if (i > g_00fb1020[k].count || i < 0) {
		fcn_004222b0(s_005feaf4);
		return 0;
	}
	g_006ed938 = g_00fb1020[k].wins[i];
	g_006ed980 = &g_00f8f120[g_006ed938];
	return 1;
}
#else
/* ADDRESS: GOLDTL 0x004727a0 */
int __cdecl d2_SetForm(int k, int i)
{
	if (k) {
		g_772534 = k;
	} else {
		k = g_772534;
	}
	if (i > g_1038140[k].count || i < 0) {
		ReportClientMessage(s_67d7d0);
		return 0;
	}
	d2_CurrentWindowId = g_1038140[k].wins[i];
	(*(D2_WIN**)&g_77255c) = &((D2_WIN*)g_1015f40)[d2_CurrentWindowId];
	return 1;
}
#endif
