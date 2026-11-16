#include "Develop/Units/d3/d3_d3d.h"

int __cdecl fcn_00418e90(char*, int, char*);

/* ADDRESS: GOLD 0x00437060 */
void __cdecl fcn_00437060(unsigned char mode)
{
	void* obj;
	int value;

	obj = *(void**) 0x633418;
	if (obj != 0 && *(int*) 0x633420 != 0 && (*(unsigned char*) 0xfe798d & 0x10) != 0 && mode != *(unsigned char*) 0x63342d) {
		value = (mode != 0) + 1;
		*(int*) 0xfe79a0 = value;
		d3d_LastResult = ((int (__stdcall*)(void*, int, int)) (*(int**) obj)[0x58 / 4])(obj, 7, value);
		if (d3d_LastResult != 0) {
			fcn_00418e90((char*) 0x5f944c, 0x2bb, (char*) 0x5fa1b8);
		}
		*(unsigned char*) 0x63342d = mode;
	}
}
