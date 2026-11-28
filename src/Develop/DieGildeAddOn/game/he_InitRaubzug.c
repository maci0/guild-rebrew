

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl he_InitRaubzug(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 0, 1);
}
