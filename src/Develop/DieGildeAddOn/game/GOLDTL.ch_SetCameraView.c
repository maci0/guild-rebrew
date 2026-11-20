#include "Develop/Units/d3/d3_camera.h"



#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl d3_SetObjectRotation(char*, void*);
void __cdecl fcn_00438b40(char*, void*);

void __cdecl ch_SetCameraView(char* a1, int a2)
{
	float a[3];
	float b[4];

	ch_GetCameraView(a1, a2, b, a);
	d3_SetObjectRotation(d3_ActiveCamera, a);
	fcn_00438b40(d3_ActiveCamera, b);
}
