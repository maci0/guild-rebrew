#include "client_scene_transform.h"

/* ADDRESS: GOLDTL 0x004bdfb0 */
/* ADDRESS: GOLD 0x004bd710 */

void __cdecl fcn_004bdfb0(float* ox, float* oy, float* position, char* object, char** ctx)
{
	float v[4];

	fcn_00455540(object, position, v);
#ifdef REBREW_GOLD
	*ox = (v[0] - *(float*) (*ctx + 0x90)) / *(float*) (*ctx + 0xa0);
	*oy = (v[2] - *(float*) (*ctx + 0x98)) / *(float*) (*ctx + 0xb8);
#else
	*ox = (v[0] - *(float*) (*ctx + 0x50)) / *(float*) (*ctx + 0x60);
	*oy = (v[2] - *(float*) (*ctx + 0x58)) / *(float*) (*ctx + 0x78);
#endif
}
