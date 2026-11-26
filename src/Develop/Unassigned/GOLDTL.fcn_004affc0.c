


#include <string.h>




// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char g_7f4ca4[];

void __cdecl cm_SendCopyEntityData(void*);

int __cdecl hst_HandleBelagerungStart(void)
{
	char m[0xf8];
	char* p;

	memset(m, 0, sizeof(m));
	m[4] = 0x7f;
	*(pos14_7f4c00*) (m + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
	*(int*) (m + 0xc) = -1;
	*(short*) (m + 0x2c) = 8;
	*(int*) (m + 0x2e) = 0;
	m[0x36] = 1;
	for (p = g_7f4ca4; (int) p < (int) (g_7f4ca4 + 0x65400); p += 0x21c) {
		if (p[-2] == 6 || p[-2] == 7) {
			*(int*) (m + 8) = *(int*) p;
			*(int*) (m + 0x58) = *(int*) p;
			cm_SendCopyEntityData(m);
		}
	}
	return 1;
}
