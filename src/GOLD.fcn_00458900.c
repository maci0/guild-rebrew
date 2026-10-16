#include "Develop/Units/d3/d3_camera.h"

void __cdecl fcn_00458d90(void*, char*, int, void*);
void __cdecl fcn_004519d0(void*, int);

/* ADDRESS: GOLD 0x00458900 */
void __cdecl fcn_00458900(void* a1, int a2)
{
	char buf[0x40];

	fcn_00458d90(a1, (*(unsigned char*) ((char*) a1 + 0x210) & 0x80) ? 0 : g_6b8014,
	    1, buf);
	fcn_004519d0(buf, a2);
}
