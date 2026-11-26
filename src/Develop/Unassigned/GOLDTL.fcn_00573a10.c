#include "client_types.h"
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

extern pos14_7f4c00 gm_GameTime;


/* ADDRESS: GOLDTL 0x00573a10 */
void __cdecl fcn_00573a10(char* o)
{
	*(pos14_7f4c00*) (o + 0x52) = *(pos14_7f4c00*) (o + 0x44);
	*(pos14_7f4c00*) (o + 0x60) = *(pos14_7f4c00*) (o + 0x44);
	gm_AddTime((pos14_7f4c00*) (o + 0x52), 0, 1, 0);
	*(int*) (o + 0xbc) = 0;
	*(int*) (o + 0xc0) = 0;
	*(int*) (o + 0xc4) = 0;
}
