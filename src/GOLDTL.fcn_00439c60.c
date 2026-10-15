#include "Develop/Units/d3/d3_camera.h"



void __cdecl fcn_00438af0(unsigned char);

void __cdecl fcn_00439c60(char* a1)
{
	if (a1 == g_6b8014) {
		return;
	}
	if (*(int*) (a1 + 0x218) != 3) {
		return;
	}
	g_6b8014 = a1;
	fcn_00438af0(0);
}
