#include "client_types.h"

void __cdecl fcn_00500bb0(void* clock, int arg2, int arg3, int arg4);

/* ADDRESS: GOLDTL 0x0055c700 */
void __cdecl fcn_0055c700(char* a0)
{
	*(pos14_7f4c00*) (a0 + 0x52) = *(pos14_7f4c00*) (a0 + 0x44);
	fcn_00500bb0(a0 + 0x52, 0, 0xf, 0);
}
