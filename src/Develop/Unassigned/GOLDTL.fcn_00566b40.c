


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl he_InitAction0x38(char* action)
{
	*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (action + 0x52), 4, 0, 0);
}
