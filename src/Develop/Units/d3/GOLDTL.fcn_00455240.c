#include "Develop/Units/d3/d3_camera.h"


void __cdecl fcn_004557c0(void*, char*, int, void*);
void __cdecl fcn_004519d0(void*, int);

void __cdecl fcn_00455240(void* obj, int a2)
{
	char buf[0x40];

	fcn_004557c0(obj, (*(unsigned char*) ((char*) obj + 0x214) & 0x20) ? 0 : d3_ActiveCamera,
	    1, buf);
	fcn_004519d0(buf, a2);
}
