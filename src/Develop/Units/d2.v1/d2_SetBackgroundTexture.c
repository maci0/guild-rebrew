#include <stdio.h>

#include "Develop/Units/d2.v1/d2_win.h"
#include "Develop/client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char s_67d54c[];

void __cdecl d3_SafeReleaseSceneResource(void* tex);
void* __cdecl d3_LoadTextureWithDefaultTint(const char* name, int a2);
#include "Develop/Units/Error/error_message.h"
typedef D2_FORM_RECORD Obj;

extern D2_FORM_RECORD g_1038140[];
extern int g_772534;
extern int d2_CurrentWindowId;
extern char* g_77255c;
extern char s_67d7d0[];

#include "GOLDTL.fcn_00472960_gconf.h"

void __cdecl d2_LockSurface(void*);
int __cdecl d2_WriteSurfacePixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, void* s);
void __cdecl d2_UnlockSurface(void*);

/* ADDRESS: GOLDTL 0x0046e7a0 */
void __cdecl d2_SetBackgroundTexture(const char* name, int win)
{
	char msg[0x400];
	D2_WIN* w;

	w = &((D2_WIN*)g_1015f40)[win];
	if (w->tex) {
		d3_SafeReleaseSceneResource(w->tex);
		w->tex = 0;
	}
	if (name && *name) {
		w->tex = d3_LoadTextureWithDefaultTint(name, 1);
		if (!w->tex) {
			sprintf(msg, s_67d54c);
			ReportClientMessage(msg);
		}
		w->alpha = 0.5f;
	}
}
