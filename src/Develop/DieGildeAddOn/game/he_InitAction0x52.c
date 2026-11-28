





// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(char*, int, int, int);

/* ADDRESS: GOLDDE 0x00536950 */
void __cdecl he_InitAction0x52(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	*(int*) (e + 0xb0) = *(int*) (e + 0xac) + 1;
	gm_AddTime(e + 0x52, 0x18, 0, 0);
}
