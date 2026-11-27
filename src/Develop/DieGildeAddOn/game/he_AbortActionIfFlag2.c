





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl cm_SendSetHE(int, char*);

void __cdecl he_AbortActionIfFlag2(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	if (e[0x78] & 2) {
		cm_SendSetHE(-1, e);
	}
}
