





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

int __cdecl cm_SendSetHE(int, char*);

void __cdecl fcn_00556110(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
		*(int*) (e + 0xac) = 0;
		*(int*) (e + 0xb0) = 0;
		*(int*) (e + 0x84) = cm_SendSetHE(0, e);
	}
}
