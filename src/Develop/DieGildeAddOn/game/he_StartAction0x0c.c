#include "Develop/client_types.h"
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

extern pos14_7f4c00 gm_GameTime;


/* ADDRESS: GOLDTL 0x00573a10 */
/* ADDRESS: GOLDDE 0x00559990 */
void __cdecl he_StartAction0x0c(char* action)
{
	*(pos14_7f4c00*) (action + 0x52) = *(pos14_7f4c00*) (action + 0x44);
	*(pos14_7f4c00*) (action + 0x60) = *(pos14_7f4c00*) (action + 0x44);
	gm_AddTime((pos14_7f4c00*) (action + 0x52), 0, 1, 0);
	*(int*) (action + 0xbc) = 0;
	*(int*) (action + 0xc0) = 0;
	*(int*) (action + 0xc4) = 0;
}
