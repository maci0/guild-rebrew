#include "client_types.h"
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

extern pos14_7f4c00 g_7f4c00;

/* ADDRESS: GOLD 0x0056b620 */
/* ADDRESS: GOLDTL 0x00573a10 */

void __cdecl fcn_00573a10(char* o)
{
	*(pos14_7f4c00*) (o + 0x52) = *(pos14_7f4c00*) (o + 0x44);
	*(pos14_7f4c00*) (o + 0x60) = *(pos14_7f4c00*) (o + 0x44);
	fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0, 1, 0);
	*(int*) (o + 0xbc) = 0;
	*(int*) (o + 0xc0) = 0;
	*(int*) (o + 0xc4) = 0;
}
