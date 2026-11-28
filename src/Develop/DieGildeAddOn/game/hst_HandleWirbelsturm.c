


#include <string.h>




// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char* gm_CityEntity;

void __cdecl cm_SendCopyEntityData(void*);

/* ADDRESS: GOLDDE 0x0049e4b0 */
int __cdecl hst_HandleWirbelsturm(void)
{
	char m[0xf8];

	memset(m, 0, sizeof(m));
	m[4] = 0x50;
	*(int*) (m + 8) = *(int*) (gm_CityEntity + 4);
	*(int*) (m + 0xc) = -1;
	*(int*) (m + 0x58) = -1;
	m[0x36] = 2;
	*(int*) (m + 0x9c) = 1000;
	*(pos14_7f4c00*) (m + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
	*(short*) (m + 0x2c) = 0x10;
	cm_SendCopyEntityData(m);
	return 1;
}
