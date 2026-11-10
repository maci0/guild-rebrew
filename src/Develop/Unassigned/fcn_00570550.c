
#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

/* ADDRESS: GOLDTL 0x00570550 */
void __cdecl fcn_00570550(char* p)
{
	*(pos14_7f4c00*) (p + 0x52) = g_7f4c00;
	*(int*) (p + 0x84) = -1;
	*(short*) (p + 0x56) = 6;
	*(int*) (p + 0x58) = 0;
}
