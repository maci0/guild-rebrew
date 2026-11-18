#include "Develop/Units/d3/d3_camera.h"



void __cdecl fcn_00438af0(unsigned char);

void __cdecl fcn_00439c60(char* camera)
{
	if (camera == g_6b8014) {
		return;
	}
	if (*(int*) (camera + 0x218) != 3) {
		return;
	}
	g_6b8014 = camera;
	fcn_00438af0(0);
}
