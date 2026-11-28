


#include <string.h>




// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char gm_EntityIdField[];

void __cdecl cm_SendCopyEntityData(void*);

/* ADDRESS: GOLDDE 0x0049e2e0 */
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
	for (p = gm_EntityIdField; (int) p < (int) (gm_EntityIdField + 0x65400); p += 0x21c) {
		if (p[-2] == 6 || p[-2] == 7) {
			*(int*) (m + 8) = *(int*) p;
			*(int*) (m + 0x58) = *(int*) p;
			cm_SendCopyEntityData(m);
		}
	}
	return 1;
}
