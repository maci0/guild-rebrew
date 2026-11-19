#include "Develop/Units/d3/d3_camera.h"


void __cdecl d3_AnimateObjectTransform(char*, char*, char*, int, int);

void __cdecl fcn_00412e50(char* p, int a2)
{
	d3_AnimateObjectTransform(d3_ActiveCamera, p + 0x5c, p + 0x90, a2, 8);
}
