#include "Develop/Units/d3/d3_camera.h"



void __cdecl fcn_00438af0(unsigned char);

void __cdecl fcn_00439c60(char* camera)
{
	if (camera == d3_ActiveCamera) {
		return;
	}
	if (*(int*) (camera + 0x218) != 3) {
		return;
	}
	d3_ActiveCamera = camera;
	fcn_00438af0(0);
}
