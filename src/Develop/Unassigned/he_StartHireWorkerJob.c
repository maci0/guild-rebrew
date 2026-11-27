#include "client_types.h"

void __cdecl gm_AddTime(void* clock, int arg2, int arg3, int arg4);

/* ADDRESS: GOLDTL 0x0055c700 */
void __cdecl he_StartHireWorkerJob(char* object)
{
	*(pos14_7f4c00*) (object + 0x52) = *(pos14_7f4c00*) (object + 0x44);
	gm_AddTime(object + 0x52, 0, 0xf, 0);
}
