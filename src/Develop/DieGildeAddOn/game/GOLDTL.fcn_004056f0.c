


#include "Develop/Units/d3/d3_camera.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl fcn_00433780(void*);
void __cdecl d3_AnimateObjectTransform(char*, float*, float*, int, int);

void __cdecl ch_AnimateCameraView(char* a1, int a2, int a3)
{
	float a[3];
	float b[4];

	if (a1 != 0) {
		ch_GetCameraView(a1, a2, b, a);
		fcn_00433780(d3_ActiveCamera);
		d3_CameraAnimating = 0;
		d3_ActiveCameraAnimation = 0;
		d3_AnimateObjectTransform(d3_ActiveCamera, b, a, a3, 0x28);
	}
}
