#include "client_types.h"
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

extern pos14_7f4c00 gm_GameTime;


/* ADDRESS: GOLDTL 0x00551160 */
void __cdecl fcn_00551160(char* o)
{
	*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (o + 0x52), 0x60, 0, 0);
}
