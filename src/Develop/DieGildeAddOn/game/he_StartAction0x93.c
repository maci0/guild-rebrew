





// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl sim_SetSyncParams(char*, int, int, int);

/* ADDRESS: GOLDDE 0x00561190 */
void __cdecl he_StartAction0x93(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	sim_SetSyncParams(e + 0x52, 6, 0, 0);
	*(pos14_7f4c00*) (e + 0x60) = *(pos14_7f4c00*) (e + 0x52);
}
