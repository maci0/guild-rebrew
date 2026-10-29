typedef int(__stdcall* Fn3)(void* self, int a, int b);

extern void* g_6b5de0;
extern int g_14ce764;
#include "GOLDTL.fcn_00436f70_gconf.h"

/* ADDRESS: GOLDTL 0x00436f70 */
void __cdecl fcn_00436f70(char on)
{
	if (((void**)g_6b5de0) != 0 && (g_14ce764 & 0x40000) != 0 && on != g_6b7ff9) {
		((Fn3) ((void**) *((void**)g_6b5de0))[0xc8 / 4])(((void**)g_6b5de0), 7, (on != 0) + 1);
		g_6b7ff9 = on;
	}
}
