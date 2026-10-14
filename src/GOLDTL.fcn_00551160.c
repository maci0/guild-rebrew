#include "client_types.h"
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

extern pos14_7f4c00 g_7f4c00;

/* ADDRESS: GOLDTL 0x00551160 */

void __cdecl fcn_00551160(char* o)
{
	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0x60, 0, 0);
}
