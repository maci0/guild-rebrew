#include "Develop/Units/d3/d3_camera.h"


void __cdecl d3_FreeObjectAnimation(void*);

void __cdecl d3_RemoveCameraAnim(void)
{
	d3_FreeObjectAnimation(d3_ActiveCamera);
	*(int*) 0x6b5cc0 = 0;
	*(int*) 0x6b5cbc = 0;
}
