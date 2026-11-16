#include "Develop/Units/d3/d3_d3d.h"

/* ADDRESS: GOLD 0x004360e0 */
void __cdecl fcn_004360e0(void* a0)
{
	if (a0 != 0) {
		d3d_LastResult = ((int (__stdcall*)(void*, int, void*)) (*(int**) d3d_Device)[0x98 / 4])(d3d_Device, 0, a0);
		if (d3d_LastResult != 0) {
			fcn_00418e90((char*) 0x5f944c, 0x167, (char*) 0x5f9640);
		}
		d3d_LastResult = ((int (__stdcall*)(void*, int, int, void*, int, int)) (*(int**) d3d_Device)[0x70 / 4])(d3d_Device, 4, 0x1c4, d3d_PrecacheBuffer, 3, 0);
		if (d3d_LastResult != 0) {
			fcn_00418e90((char*) 0x5f944c, 0x168, (char*) 0x5f95c8);
		}
	}
}
