


#include "Develop/Units/d3/d3_camera.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl fcn_00433780(void*);
void __cdecl fcn_00412cf0(char*, float*, float*, int, int);

void __cdecl fcn_004056f0(char* a1, int a2, int a3)
{
	float a[3];
	float b[4];

	if (a1 != 0) {
		ch_GetCameraView(a1, a2, b, a);
		fcn_00433780(g_6b8014);
		g_6b5cbc = 0;
		d3_ActiveCameraAnimation = 0;
		fcn_00412cf0(g_6b8014, b, a, a3, 0x28);
	}
}
