


#include <string.h>




// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char* gm_CityEntity;

void __cdecl cm_SendCopyEntityData(void*);

int __cdecl hst_CmdBrand(void)
{
	char m[0xf8];

	memset(m, 0, sizeof(m));
	m[4] = 0x4e;
	*(int*) (m + 8) = *(int*) (gm_CityEntity + 4);
	*(int*) (m + 0xc) = -1;
	*(int*) (m + 0x58) = -1;
	m[0x36] = 1;
	*(int*) (m + 0x9c) = 1000;
	*(pos14_7f4c00*) (m + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
	*(short*) (m + 0x2c) = 7;
	cm_SendCopyEntityData(m);
	return 1;
}
