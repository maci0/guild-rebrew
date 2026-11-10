void __cdecl fcn_00500bb0(char*, int, int, int);

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

/* ADDRESS: GOLDTL 0x005512f0 */
void __cdecl fcn_005512f0(char* a1)
{
	*(pos14_7f4c00*) (a1 + 0x52) = g_7f4c00;
	fcn_00500bb0(a1 + 0x52, 0, 5, 0);
}
