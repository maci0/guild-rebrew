


#include <string.h>




// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char* gm_CityEntity;

int __cdecl atoi(char*);
void __cdecl cm_SendCopyEntityData(void*);

int __cdecl hst_HandleFest(int sel, int id, char* arg)
{
	char m[0xf8];

	if (*arg != '-')
		return 0;
	if (atoi(arg + 1) > 0) {
		memset(m, 0, sizeof(m));
		m[4] = 0x53;
		*(int*) (m + 8) = *(int*) (gm_CityEntity + 4);
		*(int*) (m + 0xc) = -1;
		m[0x36] = 1;
		m[0x58] = 0;
		*(pos14_7f4c00*) (m + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
		*(short*) (m + 0x2c) = 0xc;
		*(int*) (m + 0x2e) = 0;
		cm_SendCopyEntityData(m);
	}
	return 1;
}
