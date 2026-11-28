#include "Develop/Units/d3/client_scene_loader.h"

extern int g_7749c8;




void __cdecl d2_SetProgressPercent(int, int);

/* ADDRESS: GOLDDE 0x005261b0 */
void __cdecl d2_UpdateSceneLoadProgress(int mode, int a, int b)
{
	int v;

	if (mode == 0) {
		d2_SetProgressPercent(0, a * 70 / (b * 2) + 10);
	} else if (mode == 1) {
		v = a * 70 / (b * 2) + 0x2d;
		if (v != g_7749c8) {
			g_7749c8 = v;
			d2_SetProgressPercent(0, v);
		}
	}
}
