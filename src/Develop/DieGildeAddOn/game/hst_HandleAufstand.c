


#include <string.h>




// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char* gm_CityEntity;

void __cdecl cm_SendCopyEntityData(void*);

int __cdecl hst_HandleAufstand(void)
{
	char msg[0xf8];

	memset(msg, 0, sizeof(msg));
	msg[4] = 0x7d;
	*(int*) (msg + 8) = *(int*) (gm_CityEntity + 4);
	*(int*) (msg + 0xc) = -1;
	msg[0x36] = 1;
	*(int*) (msg + 0x58) = 1;
	*(pos14_7f4c00*) (msg + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
	*(short*) (msg + 0x2c) = 8;
	*(int*) (msg + 0x2e) = 0;
	cm_SendCopyEntityData(msg);
	return 1;
}
