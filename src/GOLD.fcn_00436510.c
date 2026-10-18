#include "Develop/Units/d3/d3_d3d.h"

/* ADDRESS: GOLD 0x00436510 */
void __cdecl fcn_00436510(int a, int b, unsigned int c)
{
	void *obj;
	int result;

	(void)a;
	if (c > 2) {
		obj = *(void **)0x633418;
		result = ((int (__stdcall *)(void *, int, int, int, unsigned int, int))(*(void ***)obj)[0x70 / 4])(
			obj, 4, 0x1c4, b, c, 0x1c);
		*(int *)0x14661a4 = result;
		if (result)
			fcn_00418e90((char*)0x5f944c, 0x1f0, (char*)0x5f98c8);
	}
}
