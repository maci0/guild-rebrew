





// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(char*, int, int, int);

/* ADDRESS: GOLDDE 0x0055ff90 */
void __cdecl he_StartAction0x8e(char* action)
{
	*(pos14_7f4c00*) (action + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	*(int*) (action + 0x70) = 0;
	gm_AddTime(action + 0x52, 0x48, 0, 0);
}
