void __cdecl gm_AddTime(char*, int, int, int);

#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;

/* ADDRESS: GOLDTL 0x005512f0 */
void __cdecl he_StartPeriodicApDrain(char* a1)
{
	*(pos14_7f4c00*) (a1 + 0x52) = gm_GameTime;
	gm_AddTime(a1 + 0x52, 0, 5, 0);
}
