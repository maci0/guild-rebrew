#include "Develop/Units/d3/d3_camera.h"


void __cdecl fcn_00433780(void*);

void __cdecl d3_RemoveCameraAnim(void)
{
	fcn_00433780(d3_ActiveCamera);
	*(int*) 0x6b5cc0 = 0;
	*(int*) 0x6b5cbc = 0;
}
