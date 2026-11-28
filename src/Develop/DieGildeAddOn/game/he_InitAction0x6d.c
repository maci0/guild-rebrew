





// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

int __cdecl cm_SendSetHE(int, char*);

/* ADDRESS: GOLDDE 0x0053c4c0 */
void __cdecl he_InitAction0x6d(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
		*(int*) (e + 0xac) = 0;
		*(int*) (e + 0xb0) = 0;
		*(int*) (e + 0x84) = cm_SendSetHE(0, e);
	}
}
