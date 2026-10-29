#include "Develop/Units/d3/d3_camera.h"



#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl fcn_00438cb0(char*, void*);
void __cdecl fcn_00438b40(char*, void*);

void __cdecl fcn_004056a0(char* a1, int a2)
{
	float a[3];
	float b[4];

	fcn_004055a0(a1, a2, b, a);
	fcn_00438cb0(g_6b8014, a);
	fcn_00438b40(g_6b8014, b);
}
