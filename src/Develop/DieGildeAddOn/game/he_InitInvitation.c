




// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(char*, int, int, int);

void __cdecl he_InitInvitation(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	gm_AddTime(e + 0x52, 2, 0, 0);
	*(int*) (e + 0x70) = 0;
}
